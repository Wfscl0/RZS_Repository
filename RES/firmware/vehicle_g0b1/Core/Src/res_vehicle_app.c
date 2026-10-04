#include "res_vehicle_app.h"

#include <string.h>

#ifndef RES_E220_STOCK_BRIDGE_TEST
#define RES_E220_STOCK_BRIDGE_TEST      0
#endif
#if RES_E220_STOCK_BRIDGE_TEST
#define RES_LINK_TIMEOUT_MS          3000u
#else
#define RES_LINK_TIMEOUT_MS           500u
#endif
#define RES_CAN_STATUS_PERIOD_MS      50u
#define RES_START_OUTPUT_PULSE_MS    100u
#define RES_READY_CONFIRMATIONS        3u

static bool elapsed(uint32_t now, uint32_t since, uint32_t interval)
{
    return (uint32_t)(now - since) >= interval;
}

static bool time_reached(uint32_t now, uint32_t deadline)
{
    return (int32_t)(now - deadline) >= 0;
}

static void apply_outputs(res_vehicle_app_t *app,
                          bool relay_1_closed,
                          bool relay_2_closed,
                          bool fault_active)
{
    app->relay_1_closed = relay_1_closed;
    app->relay_2_closed = relay_2_closed;
    app->io.set_relay(app->io.context,
                      RES_VEHICLE_RELAY_1,
                      relay_1_closed);
    app->io.set_relay(app->io.context,
                      RES_VEHICLE_RELAY_2,
                      relay_2_closed);
    app->io.set_output(app->io.context,
                       RES_VEHICLE_OUTPUT_FAULT,
                       fault_active);
}

static void latch_fault(res_vehicle_app_t *app, uint16_t reason)
{
    app->fault_flags |= (uint16_t)(reason | RES_VEHICLE_FAULT_LATCHED);
    app->fault_latched = true;
    app->recovery_pending = false;
    app->latched_session = app->remote_session;
    app->ready_confirmations = 0u;
    app->state = RES_CAN_STATE_STOPPED_FAULT;
    app->start_output_active = false;
    app->io.set_output(app->io.context, RES_VEHICLE_OUTPUT_START, false);
    apply_outputs(app, false, false, true);
}

/* Check before dispatching RX as well as in tick: a late frame must not
 * erase an already expired deadline before the main loop notices it. */
static void check_link_deadline(res_vehicle_app_t *app, uint32_t now)
{
    if ((!app->fault_latched || app->recovery_pending) && app->valid_frame_seen &&
        elapsed(now, app->last_valid_frame_ms, RES_LINK_TIMEOUT_MS)) {
        latch_fault(app, RES_VEHICLE_FAULT_RADIO_TIMEOUT);
    }
}

static bool transmit(res_vehicle_app_t *app,
                     uint8_t type,
                     const uint8_t *payload,
                     uint8_t payload_length)
{
    res_frame_t frame;
    uint8_t encoded[RES_MAX_FRAME_SIZE];
    size_t encoded_length;

    memset(&frame, 0, sizeof(frame));
    frame.type = type;
    frame.source = RES_NODE_VEHICLE;
    frame.destination = RES_NODE_REMOTE;
    frame.channel = app->active_channel;
    frame.sequence = app->next_sequence++;
    frame.session = app->local_session;
    frame.payload_length = payload_length;
    if ((payload_length != 0u) && (payload != NULL)) {
        memcpy(frame.payload, payload, payload_length);
    }

    encoded_length = res_frame_encode(encoded, sizeof(encoded), &frame, app->auth_key);
    if ((encoded_length == 0u) ||
        !app->io.radio_write(app->io.context, encoded, encoded_length)) {
        return false;
    }
    app->active_channel = res_hop_next_channel(frame.channel,
                                               frame.session,
                                               frame.sequence);
    return true;
}

static void send_ack(res_vehicle_app_t *app,
                     uint8_t acknowledged_type,
                     uint32_t acknowledged_sequence)
{
    uint8_t payload[8];
    payload[0] = acknowledged_type;
    payload[1] = (uint8_t)app->state;
    payload[2] = (uint8_t)((app->relay_1_closed ? 1u : 0u) |
                           (app->relay_2_closed ? 2u : 0u));
    payload[3] = (uint8_t)app->fault_flags;
    res_put_u32_le(payload + 4u, acknowledged_sequence);
    (void)transmit(app, RES_MSG_ACK, payload, sizeof(payload));
}

static void publish_can_status(res_vehicle_app_t *app)
{
    res_can_status_t status;
    uint8_t data[RES_CAN_FRAME_LENGTH];

    status.state = app->state;
    status.flags = app->fault_flags;
    if (app->valid_frame_seen && !app->fault_latched &&
        (app->state == RES_CAN_STATE_READY || app->state == RES_CAN_STATE_GO_EVENT)) {
        status.flags |= RES_CAN_FLAG_LINK_OK;
    }
    status.channel = app->active_channel;
    status.relay_1_closed = app->relay_1_closed;
    status.relay_2_closed = app->relay_2_closed;
    status.go_event_counter = app->go_event_counter;
    res_can_pack_status(data, &status);
    if (!app->io.can_write(app->io.context,
                           RES_CAN_STATUS_ID,
                           data,
                           RES_CAN_FRAME_LENGTH)) {
        res_vehicle_app_set_local_fault(app, RES_VEHICLE_FAULT_CAN, true);
    }
}

static void publish_go_event(res_vehicle_app_t *app, uint32_t command_counter)
{
    uint8_t data[RES_CAN_FRAME_LENGTH];
    res_can_pack_go_event(data, app->remote_session, command_counter);
    if (!app->io.can_write(app->io.context,
                           RES_CAN_GO_EVENT_ID,
                           data,
                           RES_CAN_FRAME_LENGTH)) {
        res_vehicle_app_set_local_fault(app, RES_VEHICLE_FAULT_CAN, true);
    }
}

static bool frame_state_is_ready(const res_frame_t *frame)
{
    return ((frame->type == RES_MSG_HELLO) ||
            (frame->type == RES_MSG_HEARTBEAT)) &&
           (frame->payload_length >= 1u) &&
           (frame->payload[0] == (uint8_t)RES_COMMAND_READY);
}

static bool frame_state_is_stop(const res_frame_t *frame)
{
    /* HELLO+STOP is the remote's non-latching startup input self-test. */
    if ((frame->type == RES_MSG_HEARTBEAT) &&
        (frame->payload_length >= 1u)) {
        return frame->payload[0] == (uint8_t)RES_COMMAND_STOP;
    }
    return (frame->type == RES_MSG_COMMAND) &&
           (frame->payload_length >= 1u) &&
           (frame->payload[0] == (uint8_t)RES_COMMAND_STOP);
}

static void begin_new_remote_session(res_vehicle_app_t *app, uint32_t session)
{
    const bool recovering = app->fault_latched;
    app->seen_sessions[app->seen_session_count++] = session;
    app->remote_session = session;
    app->ready_confirmations = 0u;
    app->last_go_counter = 0u;
    res_replay_window_reset(&app->replay);

    /* A new authenticated remote boot can re-arm RES after three READYs.
     * It cannot reset the independent, non-programmable vehicle latch. */
    app->recovery_pending = recovering && app->local_fault_flags == 0u;
}

static bool session_was_seen(const res_vehicle_app_t *app, uint32_t session)
{
    uint8_t i;
    for (i = 0u; i < app->seen_session_count; ++i) {
        if (app->seen_sessions[i] == session) return true;
    }
    return false;
}

static void handle_ready_frame(res_vehicle_app_t *app)
{
    if ((app->fault_latched && !app->recovery_pending) || app->local_fault_flags != 0u) {
        return;
    }
    if (app->ready_confirmations < RES_READY_CONFIRMATIONS) {
        ++app->ready_confirmations;
    }
    if (app->ready_confirmations >= RES_READY_CONFIRMATIONS) {
        if (app->recovery_pending) {
            app->fault_latched = false;
            app->recovery_pending = false;
            app->fault_flags = 0u;
            app->latched_session = 0u;
        }
        app->fault_flags &= (uint16_t)~RES_CAN_FLAG_SESSION_RECOVERY;
        if (!app->start_output_active) {
            app->state = RES_CAN_STATE_READY;
        }
        apply_outputs(app, true, true, false);
    }
}

static void handle_go_frame(res_vehicle_app_t *app,
                            const res_frame_t *frame,
                            uint32_t now)
{
    uint32_t command_counter;
    uint8_t data[RES_CAN_FRAME_LENGTH];

    if ((frame->payload_length < 8u) ||
        app->fault_latched || app->local_fault_flags != 0u ||
        (app->state != RES_CAN_STATE_READY)) {
        return;
    }
    command_counter = res_get_u32_le(frame->payload + 4u);
    if (command_counter <= app->last_go_counter) {
        return; /* Retransmission of the same operator action. */
    }
    app->last_go_counter = command_counter;
    ++app->go_event_counter;
    app->state = RES_CAN_STATE_GO_EVENT;
    app->start_output_active = true;
    app->start_output_until_ms = now + RES_START_OUTPUT_PULSE_MS;
    app->io.set_output(app->io.context, RES_VEHICLE_OUTPUT_START, true);
    publish_go_event(app, command_counter);
    if (app->fault_latched) {
        return;
    }

    /* Diagnostic copy carries the command counter for offline logs. */
    res_put_u32_le(data, command_counter);
    res_put_u16_le(data + 4u, app->go_event_counter);
    data[6] = app->active_channel;
    data[7] = RES_CAN_PROTOCOL_VERSION;
    if (!app->io.can_write(app->io.context,
                            RES_CAN_DIAGNOSTIC_ID,
                            data,
                            RES_CAN_FRAME_LENGTH)) {
        res_vehicle_app_set_local_fault(app, RES_VEHICLE_FAULT_CAN, true);
    }
}

void res_vehicle_app_init(res_vehicle_app_t *app,
                          const res_vehicle_io_t *io,
                          const uint8_t auth_key[RES_AUTH_KEY_SIZE],
                          uint32_t local_session)
{
    memset(app, 0, sizeof(*app));
    app->io = *io;
    memcpy(app->auth_key, auth_key, RES_AUTH_KEY_SIZE);
    app->local_session = local_session;
    app->next_sequence = 1u;
    app->state = RES_CAN_STATE_BOOT;
    res_stream_parser_init(&app->parser);
    app->io.set_output(app->io.context, RES_VEHICLE_OUTPUT_START, false);
    apply_outputs(app, false, false, true);
}

void res_vehicle_app_receive_byte(res_vehicle_app_t *app, uint8_t byte)
{
    res_frame_t frame;
    uint32_t now;

    if (!res_stream_parser_push(&app->parser, byte, &frame, app->auth_key)) {
        return;
    }
    if ((frame.source != RES_NODE_REMOTE) ||
        ((frame.destination != RES_NODE_VEHICLE) &&
         (frame.destination != RES_NODE_BROADCAST))) {
        return;
    }

    now = app->io.millis(app->io.context);
    check_link_deadline(app, now);
    /* Reject unsupported messages before they can affect liveness/session state. */
    if (!((((frame.type == RES_MSG_HELLO) || (frame.type == RES_MSG_HEARTBEAT)) &&
           (frame.payload_length == 12u) &&
           ((frame.payload[0] == RES_COMMAND_READY) || (frame.payload[0] == RES_COMMAND_STOP))) ||
          ((frame.type == RES_MSG_COMMAND) && (frame.payload_length == 8u) &&
           ((frame.payload[0] == RES_COMMAND_GO) || (frame.payload[0] == RES_COMMAND_STOP))))) {
        return;
    }
    if (!app->replay.initialized || (frame.session != app->remote_session)) {
        if (frame_state_is_stop(&frame)) {
            /* Authenticated STOP must work even before the first HELLO.
             * Do not run session recovery/unlatch for this safety-only path. */
            latch_fault(app, RES_VEHICLE_FAULT_REMOTE_STOP);
            app->active_channel = res_hop_next_channel(frame.channel, frame.session, frame.sequence);
            if ((frame.flags & RES_FLAG_ACK_REQUIRED) != 0u) {
                send_ack(app, frame.type, frame.sequence);
            }
            return;
        }
        /* Only HELLO can introduce a new session; random frames cannot unlatch. */
        if (frame.type != RES_MSG_HELLO) {
            return;
        }
        if (session_was_seen(app, frame.session) ||
            app->seen_session_count >= RES_REMOTE_SESSION_HISTORY) {
            return; /* Fail closed, never evict replay history to grant recovery. */
        }
        if (app->replay.initialized) {
            /* A restart first withdraws permission. READY confirmation below
             * restores RES only, never START or the external hardware latch. */
            latch_fault(app, RES_VEHICLE_FAULT_REMOTE_STOP);
        }
        begin_new_remote_session(app, frame.session);
    }
    /* The generic replay window accepts unseen out-of-order packets. Such
     * packets must not renew permission or count as consecutive READYs.
     * Authenticated STOP retains priority, including when delayed. */
    if (app->replay.initialized &&
        frame.sequence <= app->replay.highest_sequence &&
        !frame_state_is_stop(&frame)) {
        return;
    }
    if (!res_replay_window_accept(&app->replay, frame.session, frame.sequence)) {
        return;
    }

    /* Any authenticated, replay-accepted frame proves that the remote was
     * alive.  This timer is intentionally separate from last_valid_rx_ms:
     * startup HELLO+STOP must not grant running permission, but a subsequent
     * remote power loss must still release the standby relay within 500 ms. */
    app->last_valid_frame_ms = now;
    app->valid_frame_seen = true;

    /* STOP and startup safety reports never renew running permission. */
    if (frame_state_is_ready(&frame) ||
        ((frame.type == RES_MSG_COMMAND) && (frame.payload[0] == RES_COMMAND_GO))) {
        app->last_valid_rx_ms = now;
    }
    app->active_channel = res_hop_next_channel(frame.channel,
                                               frame.session,
                                               frame.sequence);

    if (frame_state_is_stop(&frame)) {
        latch_fault(app, RES_VEHICLE_FAULT_REMOTE_STOP);
    } else if ((frame.type == RES_MSG_HELLO) &&
               (frame.payload_length >= 1u) &&
               (frame.payload[0] == (uint8_t)RES_COMMAND_STOP)) {
        if (app->relay_2_closed || app->start_output_active) {
            latch_fault(app, RES_VEHICLE_FAULT_REMOTE_STOP);
        }
        app->ready_confirmations = 0u;
        if (!app->fault_latched) {
            app->state = RES_CAN_STATE_WAIT_LINK;
            apply_outputs(app, true, false, true);
        }
    } else if (frame_state_is_ready(&frame)) {
        handle_ready_frame(app);
    } else if ((frame.type == RES_MSG_COMMAND) &&
               (frame.payload_length >= 1u) &&
               (frame.payload[0] == (uint8_t)RES_COMMAND_GO)) {
        handle_go_frame(app, &frame, now);
    }

    if ((frame.flags & RES_FLAG_ACK_REQUIRED) != 0u) {
        send_ack(app, frame.type, frame.sequence);
    }
}

void res_vehicle_app_set_local_fault(res_vehicle_app_t *app,
                                     uint16_t fault_mask,
                                     bool active)
{
    if (active) {
        app->local_fault_flags |= fault_mask;
        latch_fault(app, fault_mask);
    } else {
        /* Clearing a diagnostic bit never clears the safety latch. */
        app->local_fault_flags &= (uint16_t)~fault_mask;
        app->fault_flags &= (uint16_t)~fault_mask;
    }
}

void res_vehicle_app_tick(res_vehicle_app_t *app)
{
    const uint32_t now = app->io.millis(app->io.context);

    if (!app->started) {
        app->started = true;
        if (app->fault_latched) {
            app->state = RES_CAN_STATE_STOPPED_FAULT;
            apply_outputs(app, false, false, true);
        } else {
            app->state = RES_CAN_STATE_WAIT_LINK;
            /* ASF/HIL standby state: relay 1 closed, relay 2 released.
             * This is not running permission; both relays still open on STOP,
             * timeout, reset and any latched fault. */
            apply_outputs(app, true, false, true);
        }
    }

    check_link_deadline(app, now);

    if (app->start_output_active &&
        time_reached(now, app->start_output_until_ms)) {
        app->start_output_active = false;
        app->io.set_output(app->io.context, RES_VEHICLE_OUTPUT_START, false);
        if (!app->fault_latched) {
            app->state = RES_CAN_STATE_READY;
        }
    }

    if (elapsed(now, app->last_status_tx_ms, RES_CAN_STATUS_PERIOD_MS)) {
        app->last_status_tx_ms = now;
        publish_can_status(app);
    }
    app->io.refresh_watchdog(app->io.context);
}
