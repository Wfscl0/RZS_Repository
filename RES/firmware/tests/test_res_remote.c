#include "res_remote_app.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    uint32_t now;
    uint8_t packets[32][RES_MAX_FRAME_SIZE];
    size_t lengths[32];
    size_t packet_count;
    bool leds[RES_LED_COUNT];
} fixture_t;

static const uint8_t key[16] = {
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
    0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
};

static uint32_t now_ms(void *context)
{
    return ((fixture_t *)context)->now;
}

static bool radio_write(void *context, const uint8_t *data, size_t length)
{
    fixture_t *fixture = (fixture_t *)context;
    assert(fixture->packet_count < 32u);
    memcpy(fixture->packets[fixture->packet_count], data, length);
    fixture->lengths[fixture->packet_count] = length;
    ++fixture->packet_count;
    return true;
}

static void set_led(void *context, res_led_t led, bool on)
{
    ((fixture_t *)context)->leds[led] = on;
}

static void watchdog(void *context)
{
    (void)context;
}

static bool has_command(const fixture_t *fixture, res_command_t command)
{
    size_t index;
    for (index = 0u; index < fixture->packet_count; ++index) {
        res_frame_t frame;
        if ((res_frame_decode(&frame,
                              fixture->packets[index],
                              fixture->lengths[index],
                              key) == RES_DECODE_OK) &&
            (frame.type == RES_MSG_COMMAND) &&
            (frame.payload_length >= 1u) &&
            (frame.payload[0] == (uint8_t)command)) {
            return true;
        }
    }
    return false;
}

static void inject_vehicle_ack(res_remote_app_t *app,
                               uint32_t acknowledged_sequence,
                               uint32_t now)
{
    res_frame_t frame;
    uint8_t encoded[RES_MAX_FRAME_SIZE];
    size_t length;
    size_t index;

    memset(&frame, 0, sizeof(frame));
    frame.type = RES_MSG_ACK;
    frame.source = RES_NODE_VEHICLE;
    frame.destination = RES_NODE_REMOTE;
    frame.channel = app->active_channel;
    frame.sequence = 1u;
    frame.session = 0x9001u;
    frame.payload_length = 8u;
    frame.payload[0] = RES_MSG_HELLO;
    frame.payload[1] = RES_VEHICLE_READY;
    frame.payload[2] = 3u;
    res_put_u32_le(frame.payload + 4u, acknowledged_sequence);
    length = res_frame_encode(encoded, sizeof(encoded), &frame, key);
    assert(length != 0u);
    ((fixture_t *)app->io.context)->now = now;
    for (index = 0u; index < length; ++index) {
        res_remote_app_receive_byte(app, encoded[index]);
    }
}

int main(void)
{
    fixture_t fixture = {0};
    fixture_t startup_fixture = {0};
    res_remote_app_t app;
    res_remote_app_t startup_app;
    const res_remote_io_t io = {
        &fixture, now_ms, radio_write, set_led, watchdog
    };

    res_remote_app_init(&app, &io, key, 0x1234u);
    res_remote_app_set_power(&app, 12000u, 100, true);
    res_remote_app_set_raw_inputs(&app, false, false);
    res_remote_app_tick(&app);
    assert(app.safety_state == RES_REMOTE_STARTUP_STOP);
    assert(!has_command(&fixture, RES_COMMAND_STOP));

    fixture.now = 30u;
    res_remote_app_set_raw_inputs(&app, false, false);
    res_remote_app_tick(&app);
    assert(app.safety_state == RES_REMOTE_READY);

    /* A GO event is prohibited until an authenticated vehicle reply exists. */
    inject_vehicle_ack(&app, app.next_sequence - 1u, 40u);
    res_remote_app_set_raw_inputs(&app, true, false);
    fixture.now = 60u;
    res_remote_app_tick(&app);
    fixture.now = 90u;
    res_remote_app_tick(&app);
    assert(app.safety_state == RES_REMOTE_READY);
    assert(has_command(&fixture, RES_COMMAND_GO));

    fixture.now = 100u;
    res_remote_app_set_raw_inputs(&app, true, true);
    res_remote_app_tick(&app);
    fixture.now = 120u;
    res_remote_app_tick(&app);
    assert(app.safety_state == RES_REMOTE_STOP_LATCHED);

    /* Missing INA226 data keeps startup non-running, then fails safe. */
    {
        const res_remote_io_t startup_io = {
            &startup_fixture, now_ms, radio_write, set_led, watchdog
        };
        res_remote_app_init(&startup_app, &startup_io, key, 0x2222u);
        res_remote_app_set_power(&startup_app, 0u, 0, false);
        res_remote_app_set_raw_inputs(&startup_app, false, false);
        res_remote_app_tick(&startup_app);
        startup_fixture.now = 100u;
        res_remote_app_tick(&startup_app);
        assert(startup_app.safety_state == RES_REMOTE_STARTUP_STOP);
        startup_fixture.now = 501u;
        res_remote_app_tick(&startup_app);
        assert(startup_app.safety_state == RES_REMOTE_STOP_LATCHED);
    }
    assert(has_command(&fixture, RES_COMMAND_STOP));

    /* Releasing E-stop cannot clear the latch without a power cycle. */
    res_remote_app_set_raw_inputs(&app, false, false);
    fixture.now = 500u;
    res_remote_app_tick(&app);
    assert(app.safety_state == RES_REMOTE_STOP_LATCHED);

    puts("test_res_remote: PASS");
    return 0;
}
