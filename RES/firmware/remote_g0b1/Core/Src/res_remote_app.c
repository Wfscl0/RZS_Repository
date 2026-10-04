#include "res_remote_app.h"
#include "res_can_contract.h"
#include "res_radio_config.h"

#include <string.h>

#ifndef RES_RADIO_STOP_BENCH
#define RES_RADIO_STOP_BENCH 0
#endif
#ifndef RES_E220_STOCK_BRIDGE_TEST
#define RES_E220_STOCK_BRIDGE_TEST      0
#endif
#if RES_RADIO_STOP_BENCH
#define RES_HEARTBEAT_PERIOD_MS       2000u
#elif RES_E220_STOCK_BRIDGE_TEST
#define RES_HEARTBEAT_PERIOD_MS       1500u
#else
#define RES_HEARTBEAT_PERIOD_MS       200u
#endif

/*
 * The vendor example detects UART idle after about 10 timer ticks, with a
 * 500-tick fallback. Blocking RF transmission can delay servicing its FIFO.
 * Keep this bench-only compatibility profile out of the production build;
 * the custom radio bridge has bounded, much shorter turnaround time.
 */
#if RES_RADIO_STOP_BENCH
#define RES_ACK_TIMEOUT_MS           1800u
#define RES_LINK_TIMEOUT_MS           500u
#elif RES_E220_STOCK_BRIDGE_TEST
#define RES_ACK_TIMEOUT_MS           1800u
#define RES_LINK_TIMEOUT_MS          3000u
#else
#define RES_ACK_TIMEOUT_MS            (RES_RADIO_SI4463 ? RES_RADIO_ACK_TIMEOUT_MS : 260u)
#define RES_LINK_TIMEOUT_MS           500u
#endif
#define RES_BUTTON_DEBOUNCE_MS        25u
#define RES_CRITICAL_REPEAT_MS        (RES_RADIO_SI4463 ? 240u : 30u)
#define RES_GO_REPEAT_MS              (RES_RADIO_SI4463 ? 450u : 60u)
#define RES_POWER_STARTUP_GRACE_MS   500u
#define RES_LAMP_SELFTEST_MS         1000u
#define RES_BATTERY_WARN_MV           11100u
#define RES_BATTERY_CRITICAL_MV       10500u
#define RES_POWER_STALE_MS            300u
/* Hysteresis affects recovery only, never delays entering critical STOP. */
#define RES_BATTERY_RECOVERY_MV        200u
#define RES_VEHICLE_INFORMATION_FLAGS (RES_CAN_FLAG_LINK_OK | RES_CAN_FLAG_SESSION_RECOVERY)

static bool elapsed(uint32_t now, uint32_t since, uint32_t interval)
{
    return (uint32_t)(now - since) >= interval;
}

static bool time_reached(uint32_t now, uint32_t deadline)
{
    return (int32_t)(now - deadline) >= 0;
}

static bool has_pending_ack(const res_remote_app_t *app)
{
    uint8_t index;

    for (index = 0u; index < RES_REMOTE_PENDING_COUNT; ++index) {
        if (app->pending[index].used) {
            return true;
        }
    }
    return false;
}

static void add_pending(res_remote_app_t *app,
                        uint32_t sequence,
                        uint32_t now,
                        uint8_t channel,
                        uint8_t type)
{
    uint8_t index;
    uint8_t oldest = 0u;

    for (index = 0u; index < RES_REMOTE_PENDING_COUNT; ++index) {
        if (!app->pending[index].used) {
            oldest = index;
            break;
        }
        if (app->pending[index].sent_ms < app->pending[oldest].sent_ms) {
            oldest = index;
        }
    }
    app->pending[oldest].used = true;
    app->pending[oldest].sequence = sequence;
    app->pending[oldest].sent_ms = now;
    app->pending[oldest].channel = channel;
    app->pending[oldest].type = type;
}

static void update_pending_timeouts(res_remote_app_t *app, uint32_t now)
{
    uint8_t index;
    for (index = 0u; index < RES_REMOTE_PENDING_COUNT; ++index) {
        res_pending_ack_t *pending = &app->pending[index];
        if (pending->used && elapsed(now, pending->sent_ms, RES_ACK_TIMEOUT_MS)) {
            uint8_t *health = &app->channel_health[pending->channel];
            *health = (*health > 12u) ? (uint8_t)(*health - 12u) : 0u;
            pending->used = false;
        }
    }
}

static res_pending_ack_t *find_ack(res_remote_app_t *app, uint32_t sequence,
                                    uint8_t type, uint32_t now)
{
    uint8_t index;
    for (index = 0u; index < RES_REMOTE_PENDING_COUNT; ++index) {
        res_pending_ack_t *pending = &app->pending[index];
        if (pending->used && (pending->sequence == sequence) &&
            (pending->type == type) &&
            !elapsed(now, pending->sent_ms, RES_ACK_TIMEOUT_MS)) {
            return pending;
        }
    }
    return NULL;
}

static bool transmit_on_channel(res_remote_app_t *app,
                                uint8_t type,
                                uint8_t flags,
                                const uint8_t *payload,
                                uint8_t payload_length,
                                uint8_t channel,
                                uint32_t now)
{
    res_frame_t frame;
    uint8_t encoded[RES_MAX_FRAME_SIZE];
    size_t encoded_length;

    memset(&frame, 0, sizeof(frame));
    frame.type = type;
    frame.source = RES_NODE_REMOTE;
    frame.destination = RES_NODE_VEHICLE;
    frame.flags = flags;
    frame.channel = (uint8_t)(channel % RES_HOP_CHANNEL_COUNT);
    frame.sequence = app->next_sequence++;
    frame.session = app->session;
    frame.payload_length = payload_length;
    if ((payload_length != 0u) && (payload != NULL)) {
        memcpy(frame.payload, payload, payload_length);
    }

    encoded_length = res_frame_encode(encoded, sizeof(encoded), &frame, app->auth_key);
    if ((encoded_length == 0u) ||
        !app->io.radio_write(app->io.context, encoded, encoded_length)) {
        app->fault_flags |= RES_REMOTE_FAULT_RADIO_TX;
        return false;
    }

    app->fault_flags &= (uint16_t)~RES_REMOTE_FAULT_RADIO_TX;
    app->active_channel = res_hop_next_channel(frame.channel,
                                               frame.session,
                                               frame.sequence);
    if ((flags & RES_FLAG_ACK_REQUIRED) != 0u) {
        add_pending(app, frame.sequence, now, frame.channel, frame.type);
    }
    return true;
}

static bool transmit(res_remote_app_t *app,
                     uint8_t type,
                     uint8_t flags,
                     const uint8_t *payload,
                     uint8_t payload_length,
                     uint32_t now)
{
    return transmit_on_channel(app,
                               type,
                               flags,
                               payload,
                               payload_length,
                               app->active_channel,
                               now);
}

static void build_state_payload(const res_remote_app_t *app, uint8_t payload[12])
{
    payload[0] = (app->safety_state == RES_REMOTE_READY)
        ? (uint8_t)RES_COMMAND_READY
        : (uint8_t)RES_COMMAND_STOP;
    payload[1] = (uint8_t)((app->debounced_go_pressed ? 1u : 0u) |
                           (app->raw_stop_fault ? 2u : 0u));
    res_put_u16_le(payload + 2u, app->battery_mv);
    res_put_u16_le(payload + 4u, (uint16_t)app->current_ma);
    res_put_u16_le(payload + 6u, app->fault_flags);
    res_put_u32_le(payload + 8u, app->command_counter);
}

static void send_periodic(res_remote_app_t *app, uint32_t now)
{
    uint8_t payload[12];
    const uint8_t type = (app->safety_state == RES_REMOTE_READY) && res_remote_app_link_ok(app, now)
        ? (uint8_t)RES_MSG_HEARTBEAT
        : (uint8_t)RES_MSG_HELLO;

    build_state_payload(app, payload);
    (void)transmit(app,
                   type,
                   RES_FLAG_ACK_REQUIRED,
                   payload,
                   sizeof(payload),
                   now);
}

static void send_command(res_remote_app_t *app,
                         res_command_t command,
                         bool retransmission,
                         uint8_t channel,
                         uint32_t now)
{
    uint8_t payload[8];
    uint8_t flags = RES_FLAG_ACK_REQUIRED;

    payload[0] = (uint8_t)command;
    payload[1] = (app->safety_state == RES_REMOTE_STOP_LATCHED) ? 1u : 0u;
    res_put_u16_le(payload + 2u, app->battery_mv);
    res_put_u32_le(payload + 4u, app->command_counter);
    if (command == RES_COMMAND_STOP) {
        flags |= RES_FLAG_CRITICAL;
    }
    if (retransmission) {
        flags |= RES_FLAG_RETRANSMISSION;
    }
    (void)transmit_on_channel(app,
                              RES_MSG_COMMAND,
                              flags,
                              payload,
                              sizeof(payload),
                              channel,
                              now);
}

static void update_go_debounce(res_remote_app_t *app, uint32_t now)
{
    if (app->raw_go_pressed == app->debounced_go_pressed) {
        app->go_change_ms = now;
    } else if (elapsed(now, app->go_change_ms, RES_BUTTON_DEBOUNCE_MS)) {
        app->debounced_go_pressed = app->raw_go_pressed;
        app->go_change_ms = now;
    }
}

static void latch_stop(res_remote_app_t *app, uint32_t now)
{
    if (app->safety_state != RES_REMOTE_STOP_LATCHED) {
        ++app->command_counter;
        app->stop_burst_remaining = RES_HOP_CHANNEL_COUNT;
        app->next_burst_tx_ms = now;
    }
    app->safety_state = RES_REMOTE_STOP_LATCHED;
    app->go_burst_remaining = 0u;
}

static bool vehicle_consistent(const res_remote_app_t *app)
{
    if (!app->vehicle_feedback_valid) {
        return false;
    }
    if (app->safety_state == RES_REMOTE_READY) {
        return ((app->vehicle_state == RES_VEHICLE_READY) ||
                (app->vehicle_state == RES_VEHICLE_GO_EVENT)) &&
               (app->vehicle_relay_commands == 3u);
    }
    return (app->vehicle_state == RES_VEHICLE_STOPPED_FAULT) &&
           (app->vehicle_relay_commands == 0u);
}

static bool vehicle_fault(const res_remote_app_t *app)
{
    return (app->vehicle_fault_flags & (uint8_t)~RES_VEHICLE_INFORMATION_FLAGS) != 0u;
}

static bool go_permitted(const res_remote_app_t *app, uint32_t now)
{
    return (app->safety_state == RES_REMOTE_READY) &&
           app->battery_measurement_valid && (app->fault_flags == 0u) &&
           res_remote_app_link_ok(app, now) && vehicle_consistent(app) &&
           !vehicle_fault(app);
}

static void update_leds(res_remote_app_t *app, uint32_t now)
{
    const bool link_ok = res_remote_app_link_ok(app, now);
    const bool consistent = vehicle_consistent(app);
    const bool warning = (app->fault_flags != 0u) || !link_ok || !consistent ||
                         vehicle_fault(app) ||
                         (app->safety_state == RES_REMOTE_STOP_LATCHED);
    const bool battery_ok = app->battery_measurement_valid &&
                            ((app->fault_flags & RES_REMOTE_FAULT_BATTERY_LOW) == 0u);
    if (!elapsed(now, app->startup_ms, RES_LAMP_SELFTEST_MS)) {
        unsigned i;
        for (i = 0u; i < RES_LED_COUNT; ++i) {
            app->io.set_led(app->io.context, (res_led_t)i, true);
        }
        return; /* Nonblocking self-test; STOP processing remains active. */
    }
    app->io.set_led(app->io.context,
                    RES_LED_STATE_BLUE,
                    !warning);
    app->io.set_led(app->io.context,
                    RES_LED_STATE_YELLOW,
                    warning);
    app->io.set_led(app->io.context, RES_LED_SOC_GREEN, battery_ok);
    app->io.set_led(app->io.context,
                    RES_LED_SOC_RED,
                    !battery_ok);
}

void res_remote_app_init(res_remote_app_t *app,
                         const res_remote_io_t *io,
                         const uint8_t auth_key[RES_AUTH_KEY_SIZE],
                         uint32_t session)
{
    uint8_t index;
    memset(app, 0, sizeof(*app));
    app->io = *io;
    memcpy(app->auth_key, auth_key, RES_AUTH_KEY_SIZE);
    app->session = session;
    app->next_sequence = 1u;
    app->vehicle_state = RES_VEHICLE_UNKNOWN;
    app->safety_state = RES_REMOTE_STARTUP_STOP;
    app->fault_flags = RES_REMOTE_FAULT_BATTERY_LOW |
                       RES_REMOTE_FAULT_BATTERY_CRITICAL |
                       RES_REMOTE_FAULT_POWER_INVALID;
    for (index = 0u; index < RES_HOP_CHANNEL_COUNT; ++index) {
        app->channel_health[index] = 128u;
    }
    res_stream_parser_init(&app->parser);
}

void res_remote_app_set_raw_inputs(res_remote_app_t *app,
                                   bool go_pressed,
                                   bool stop_fault)
{
    app->raw_go_pressed = go_pressed;
    app->raw_stop_fault = stop_fault;
}

void res_remote_app_set_power(res_remote_app_t *app,
                              uint16_t battery_mv,
                              int16_t current_ma,
                              bool valid)
{
    const bool was_valid = app->battery_measurement_valid;
    app->battery_mv = battery_mv;
    app->current_ma = current_ma;
    app->last_power_sample_ms = app->io.millis(app->io.context);
    app->battery_measurement_valid = valid;
    if (!valid) {
        app->fault_flags |= RES_REMOTE_FAULT_POWER_INVALID;
    } else {
        app->fault_flags &= (uint16_t)~RES_REMOTE_FAULT_POWER_INVALID;
    }
    if (!valid || (battery_mv < RES_BATTERY_WARN_MV)) {
        app->fault_flags |= RES_REMOTE_FAULT_BATTERY_LOW;
    } else if (!was_valid || battery_mv >= RES_BATTERY_WARN_MV + RES_BATTERY_RECOVERY_MV) {
        app->fault_flags &= (uint16_t)~RES_REMOTE_FAULT_BATTERY_LOW;
    }
    if (!valid || (battery_mv < RES_BATTERY_CRITICAL_MV)) {
        app->fault_flags |= RES_REMOTE_FAULT_BATTERY_CRITICAL;
    } else if (!was_valid || battery_mv >= RES_BATTERY_CRITICAL_MV + RES_BATTERY_RECOVERY_MV) {
        app->fault_flags &= (uint16_t)~RES_REMOTE_FAULT_BATTERY_CRITICAL;
    }
}

void res_remote_app_set_fault(res_remote_app_t *app,
                              uint16_t fault_mask,
                              bool active)
{
    if (active) {
        app->fault_flags |= fault_mask;
    } else {
        app->fault_flags &= (uint16_t)~fault_mask;
    }
}

void res_remote_app_receive_byte(res_remote_app_t *app, uint8_t byte)
{
    res_frame_t frame;
    uint32_t now;
    uint32_t acknowledged_sequence;
    res_pending_ack_t *pending;
    uint8_t *health;

    if (!res_stream_parser_push(&app->parser, byte, &frame, app->auth_key)) {
        return;
    }
    if ((frame.source != RES_NODE_VEHICLE) ||
        ((frame.destination != RES_NODE_REMOTE) &&
         (frame.destination != RES_NODE_BROADCAST))) {
        return;
    }

    ++app->decoded_frames;

    now = app->io.millis(app->io.context);
    if (app->vehicle_feedback_valid && !res_remote_app_link_ok(app, now)) {
        app->fault_flags |= RES_REMOTE_FAULT_LINK_TIMEOUT;
        latch_stop(app, now);
    }
    /* Only a well-formed, timely reply to our own transmission proves a
     * bidirectional link. Unsolicited STATUS/HELLO cannot refresh it. */
    if ((frame.type != RES_MSG_ACK) || (frame.payload_length != 8u) ||
        (frame.payload[1] < RES_VEHICLE_WAIT_LINK) ||
        (frame.payload[1] > RES_VEHICLE_STOPPED_FAULT) ||
        ((frame.payload[2] & 0xFCu) != 0u)) {
        return;
    }
    acknowledged_sequence = res_get_u32_le(frame.payload + 4u);
    pending = find_ack(app, acknowledged_sequence, frame.payload[0], now);
    if (pending == NULL) {
        ++app->unmatched_acks;
        return;
    }
    /* The vehicle may reboot and answer the next remote HELLO with an ACK. */
    if (!res_remote_app_link_ok(app, now) &&
        app->replay.initialized &&
        (app->replay.session != frame.session)) {
        res_replay_window_reset(&app->replay);
    }
    if (!res_replay_window_accept(&app->replay, frame.session, frame.sequence)) {
        return;
    }

    app->active_channel = res_hop_next_channel(frame.channel,
                                               frame.session,
                                               frame.sequence);
    app->last_valid_rx_ms = now;
    ++app->accepted_acks;
    app->vehicle_feedback_valid = true;
    app->vehicle_state = (res_vehicle_state_t)frame.payload[1];
    app->vehicle_relay_commands = frame.payload[2];
    app->vehicle_fault_flags = frame.payload[3];
    health = &app->channel_health[pending->channel];
    *health = (*health < 247u) ? (uint8_t)(*health + 8u) : 255u;
    pending->used = false;
}

bool res_remote_app_link_ok(const res_remote_app_t *app, uint32_t now_ms)
{
    return app->vehicle_feedback_valid &&
           !elapsed(now_ms, app->last_valid_rx_ms, RES_LINK_TIMEOUT_MS);
}

void res_remote_app_tick(res_remote_app_t *app)
{
    const uint32_t now = app->io.millis(app->io.context);
    bool go_rising_edge;
    bool burst_sent = false;

    if (!app->started) {
        app->started = true;
        app->startup_ms = now;
        app->go_change_ms = now;
        /* Startup STOP is a local self-test state, not a latched E-stop event. */
        app->last_heartbeat_ms = now - RES_HEARTBEAT_PERIOD_MS;
    }

    update_go_debounce(app, now);
    update_pending_timeouts(app, now);
#if RES_RADIO_STOP_BENCH
    /* Isolated RF diagnosis: never emit READY/GO, even with healthy inputs. */
    latch_stop(app, now);
    app->stop_burst_remaining = 0u;
#endif
    if (app->battery_measurement_valid &&
        elapsed(now, app->last_power_sample_ms, RES_POWER_STALE_MS)) {
        res_remote_app_set_power(app, app->battery_mv, app->current_ma, false);
    }
    go_rising_edge = app->debounced_go_pressed && !app->previous_go_pressed;
    app->previous_go_pressed = app->debounced_go_pressed;

    /* STOP activation is deliberately not debounced: a single high sample wins. */
    if (app->vehicle_feedback_valid && !res_remote_app_link_ok(app, now)) {
        app->fault_flags |= RES_REMOTE_FAULT_LINK_TIMEOUT;
    }
    if (app->raw_stop_fault ||
        ((app->fault_flags & (RES_REMOTE_FAULT_RADIO_TX |
                             RES_REMOTE_FAULT_LINK_TIMEOUT)) != 0u) ||
        (((app->fault_flags & RES_REMOTE_FAULT_BATTERY_CRITICAL) != 0u) &&
         ((app->safety_state != RES_REMOTE_STARTUP_STOP) ||
          elapsed(now, app->startup_ms, RES_POWER_STARTUP_GRACE_MS)))) {
        latch_stop(app, now);
    } else if (!app->startup_input_checked &&
               elapsed(now, app->startup_ms, RES_BUTTON_DEBOUNCE_MS)) {
        app->startup_input_checked = true;
    }
    if (app->startup_input_checked &&
        (app->safety_state == RES_REMOTE_STARTUP_STOP) &&
        elapsed(now, app->startup_ms, RES_LAMP_SELFTEST_MS) &&
        app->battery_measurement_valid &&
        ((app->fault_flags & RES_REMOTE_FAULT_BATTERY_CRITICAL) == 0u)) {
        app->safety_state = RES_REMOTE_READY;
    }

    if (!go_permitted(app, now)) {
        app->go_burst_remaining = 0u;
    }
    if (go_rising_edge && go_permitted(app, now)) {
        ++app->command_counter;
        app->go_burst_remaining = 2u;
        app->next_burst_tx_ms = now;
    }

    if ((app->stop_burst_remaining != 0u) &&
        time_reached(now, app->next_burst_tx_ms)) {
        const uint8_t channel = (uint8_t)(RES_HOP_CHANNEL_COUNT -
                                          app->stop_burst_remaining);
        send_command(app,
                     RES_COMMAND_STOP,
                     app->stop_burst_remaining != RES_HOP_CHANNEL_COUNT,
                     channel,
                     now);
        --app->stop_burst_remaining;
        burst_sent = true;
        app->next_burst_tx_ms = now + RES_CRITICAL_REPEAT_MS;
    } else if ((app->go_burst_remaining != 0u) &&
               !has_pending_ack(app) &&
               time_reached(now, app->next_burst_tx_ms)) {
        send_command(app,
                     RES_COMMAND_GO,
                     app->go_burst_remaining != 2u,
                     app->active_channel,
                     now);
        --app->go_burst_remaining;
        burst_sent = true;
        app->next_burst_tx_ms = now + RES_GO_REPEAT_MS;
    }

    /*
     * Periodic traffic uses stop-and-wait ARQ.  This leaves a deterministic
     * receive window after every half-duplex transmission instead of filling
     * a slow bridge FIFO faster than it can reach the air interface.
     * Critical STOP repeats above deliberately retain priority.
     */
    if (!burst_sent && app->go_burst_remaining == 0u && !has_pending_ack(app) &&
        elapsed(now, app->last_heartbeat_ms, RES_HEARTBEAT_PERIOD_MS)) {
        app->last_heartbeat_ms = now;
        if (app->safety_state == RES_REMOTE_STOP_LATCHED) {
            /* ASF: safety STOP reporting is NOT a normal heartbeat. */
            send_command(app, RES_COMMAND_STOP, true, app->active_channel, now);
        } else {
            send_periodic(app, now);
        }
    }

    update_leds(app, now);
    app->io.refresh_watchdog(app->io.context);
}
