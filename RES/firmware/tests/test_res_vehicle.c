#include "res_vehicle_app.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    uint32_t now;
    bool relays[2];
    bool outputs[2];
    uint16_t can_ids[32];
    uint8_t can_data[32][8];
    size_t can_count;
    uint8_t radio[32][RES_MAX_FRAME_SIZE];
    size_t radio_lengths[32];
    size_t radio_count;
} fixture_t;

static const uint8_t key[16] = {
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
    0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
};

static uint32_t now_ms(void *context) { return ((fixture_t *)context)->now; }

static bool radio_write(void *context, const uint8_t *data, size_t length)
{
    fixture_t *f = (fixture_t *)context;
    assert(f->radio_count < 32u);
    memcpy(f->radio[f->radio_count], data, length);
    f->radio_lengths[f->radio_count++] = length;
    return true;
}

static bool can_write(void *context, uint16_t id, const uint8_t *data, uint8_t length)
{
    fixture_t *f = (fixture_t *)context;
    assert(length == 8u && f->can_count < 32u);
    f->can_ids[f->can_count] = id;
    memcpy(f->can_data[f->can_count++], data, length);
    return true;
}

static void set_relay(void *context, res_vehicle_relay_t relay, bool closed)
{
    ((fixture_t *)context)->relays[relay] = closed;
}

static void set_output(void *context, res_vehicle_output_t output, bool active)
{
    ((fixture_t *)context)->outputs[output] = active;
}

static void watchdog(void *context) { (void)context; }

static void inject_remote(res_vehicle_app_t *app,
                          uint8_t type,
                          uint8_t command,
                          uint32_t session,
                          uint32_t sequence,
                          uint32_t counter)
{
    res_frame_t frame;
    uint8_t encoded[RES_MAX_FRAME_SIZE];
    size_t length;
    size_t index;

    memset(&frame, 0, sizeof(frame));
    frame.type = type;
    frame.source = RES_NODE_REMOTE;
    frame.destination = RES_NODE_VEHICLE;
    frame.flags = RES_FLAG_ACK_REQUIRED;
    frame.channel = (uint8_t)(sequence % RES_HOP_CHANNEL_COUNT);
    frame.sequence = sequence;
    frame.session = session;
    frame.payload_length = (type == RES_MSG_COMMAND) ? 8u : 12u;
    frame.payload[0] = command;
    res_put_u32_le(frame.payload + ((type == RES_MSG_COMMAND) ? 4u : 8u), counter);
    length = res_frame_encode(encoded, sizeof(encoded), &frame, key);
    assert(length != 0u);
    for (index = 0u; index < length; ++index) {
        res_vehicle_app_receive_byte(app, encoded[index]);
    }
}

static bool can_seen(const fixture_t *fixture, uint16_t id)
{
    size_t index;
    for (index = 0u; index < fixture->can_count; ++index) {
        if (fixture->can_ids[index] == id) return true;
    }
    return false;
}

int main(void)
{
    fixture_t fixture = {0};
    res_vehicle_app_t app;
    const res_vehicle_io_t io = {
        &fixture, now_ms, radio_write, can_write,
        set_relay, set_output, watchdog
    };

    res_vehicle_app_init(&app, &io, key, 0x5001u);
    res_vehicle_app_tick(&app);
    assert(fixture.relays[0] && !fixture.relays[1]);
    assert(fixture.outputs[RES_VEHICLE_OUTPUT_FAULT]);

    fixture.now = 10u;
    inject_remote(&app, RES_MSG_HELLO, RES_COMMAND_READY, 0x1001u, 1u, 0u);
    fixture.now = 30u;
    inject_remote(&app, RES_MSG_HEARTBEAT, RES_COMMAND_READY, 0x1001u, 2u, 0u);
    fixture.now = 50u;
    inject_remote(&app, RES_MSG_HEARTBEAT, RES_COMMAND_READY, 0x1001u, 3u, 0u);
    assert(fixture.relays[0] && fixture.relays[1]);
    assert(!fixture.outputs[RES_VEHICLE_OUTPUT_FAULT]);
    assert(app.state == RES_CAN_STATE_READY);

    fixture.now = 80u;
    inject_remote(&app, RES_MSG_COMMAND, RES_COMMAND_GO, 0x1001u, 4u, 9u);
    assert(fixture.outputs[RES_VEHICLE_OUTPUT_START]);
    assert(can_seen(&fixture, RES_CAN_GO_EVENT_ID));
    fixture.now = 181u;
    res_vehicle_app_tick(&app);
    assert(!fixture.outputs[RES_VEHICLE_OUTPUT_START]);

    fixture.now = 200u;
    inject_remote(&app, RES_MSG_COMMAND, RES_COMMAND_STOP, 0x1001u, 5u, 10u);
    assert(!fixture.relays[0] && !fixture.relays[1]);
    assert(app.fault_latched);

    /* Same-session READY may never recover a latched stop. */
    fixture.now = 220u;
    inject_remote(&app, RES_MSG_HEARTBEAT, RES_COMMAND_READY, 0x1001u, 6u, 10u);
    assert(!fixture.relays[0] && !fixture.relays[1]);

    /* A new authenticated HELLO session plus three confirmations recovers. */
    fixture.now = 240u;
    inject_remote(&app, RES_MSG_HELLO, RES_COMMAND_READY, 0x1002u, 1u, 0u);
    fixture.now = 260u;
    inject_remote(&app, RES_MSG_HEARTBEAT, RES_COMMAND_READY, 0x1002u, 2u, 0u);
    fixture.now = 280u;
    inject_remote(&app, RES_MSG_HEARTBEAT, RES_COMMAND_READY, 0x1002u, 3u, 0u);
    assert(fixture.relays[0] && fixture.relays[1]);

    fixture.now = 800u;
    res_vehicle_app_tick(&app);
    assert(app.fault_latched);
    assert(!fixture.relays[0] && !fixture.relays[1]);
    assert((app.fault_flags & RES_CAN_FLAG_RADIO_TIMEOUT) != 0u);

    /* A local hardware fault cannot be cleared by a new radio session. */
    res_vehicle_app_set_local_fault(&app, RES_VEHICLE_FAULT_RELAY, true);
    fixture.now = 820u;
    inject_remote(&app, RES_MSG_HELLO, RES_COMMAND_READY, 0x1003u, 1u, 0u);
    fixture.now = 840u;
    inject_remote(&app, RES_MSG_HEARTBEAT, RES_COMMAND_READY, 0x1003u, 2u, 0u);
    fixture.now = 860u;
    inject_remote(&app, RES_MSG_HEARTBEAT, RES_COMMAND_READY, 0x1003u, 3u, 0u);
    assert(app.fault_latched);
    assert(!fixture.relays[0] && !fixture.relays[1]);

    puts("test_res_vehicle: PASS");
    return 0;
}
