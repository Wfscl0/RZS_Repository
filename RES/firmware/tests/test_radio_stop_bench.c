#include "res_remote_app.h"
#include <assert.h>
#include <string.h>
static uint32_t now, sent, previous;
static const uint8_t key[16] = {0};
static uint32_t clock_ms(void *p) { (void)p; return now; }
static bool send_frame(void *p, const uint8_t *bytes, size_t size)
{
    res_frame_t f;
    (void)p;
    assert(res_frame_decode(&f, bytes, size, key) == RES_DECODE_OK);
    assert(f.type == RES_MSG_COMMAND && f.payload[0] == RES_COMMAND_STOP);
    if (sent) assert(now - previous >= 2000u);
    previous = now; ++sent;
    return true;
}
static void led(void *p, res_led_t id, bool on) { (void)p; (void)id; (void)on; }
static void watchdog(void *p) { (void)p; }
int main(void)
{
    res_remote_app_t a;
    res_remote_io_t io = {0, clock_ms, send_frame, led, watchdog};
    res_remote_app_init(&a, &io, key, 123u);
    for (now = 0; now <= 10000u; now += 10u) {
        res_remote_app_set_power(&a, 12000u, 0, true);
        res_remote_app_set_raw_inputs(&a, (now / 100u) & 1u, false);
        res_remote_app_tick(&a);
        assert(a.safety_state == RES_REMOTE_STOP_LATCHED);
    }
    assert(sent == 6u);
    return 0;
}
