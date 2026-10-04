#include "res_remote_app.h"
#include "res_can_contract.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    uint32_t now;
    bool leds[RES_LED_COUNT];
    unsigned go_count;
    uint32_t sequence;
    uint8_t type;
} fixture_t;
static const uint8_t key[16] = {0};
static uint32_t millis(void *ctx) { return ((fixture_t *)ctx)->now; }
static bool write_radio(void *ctx, const uint8_t *data, size_t length)
{
    fixture_t *f = ctx;
    res_frame_t frame;
    assert(res_frame_decode(&frame, data, length, key) == RES_DECODE_OK);
    f->sequence = frame.sequence;
    f->type = frame.type;
    if (frame.type == RES_MSG_COMMAND && frame.payload[0] == RES_COMMAND_GO) {
        ++f->go_count;
    }
    return true;
}
static void led(void *ctx, res_led_t index, bool on) { ((fixture_t *)ctx)->leds[index] = on; }
static void watchdog(void *ctx) { (void)ctx; }
static void init(fixture_t *f, res_remote_app_t *a)
{
    const res_remote_io_t io = {f, millis, write_radio, led, watchdog};
    memset(f, 0, sizeof(*f));
    res_remote_app_init(a, &io, key, 123u);
    res_remote_app_set_power(a, 12000u, 0, true);
    res_remote_app_tick(a);
    /* Isolate post-self-test indicator logic. */
    a->startup_ms -= 1000u;
    f->now = 30u;
    res_remote_app_tick(a);
    assert(a->safety_state == RES_REMOTE_READY);
}
static void inject(fixture_t *f, res_remote_app_t *a, uint8_t packet_type,
                   uint8_t state, uint8_t relays, uint8_t faults,
                   uint32_t acknowledged_sequence, uint8_t acknowledged_type,
                   uint8_t length, uint32_t sequence)
{
    res_frame_t packet;
    uint8_t encoded[RES_MAX_FRAME_SIZE];
    size_t i, n;
    memset(&packet, 0, sizeof(packet));
    packet.source = RES_NODE_VEHICLE;
    packet.destination = RES_NODE_REMOTE;
    packet.type = packet_type;
    packet.session = 900u;
    packet.sequence = sequence;
    packet.payload_length = length;
    packet.payload[0] = acknowledged_type;
    packet.payload[1] = state;
    packet.payload[2] = relays;
    packet.payload[3] = faults;
    res_put_u32_le(packet.payload + 4u, acknowledged_sequence);
    n = res_frame_encode(encoded, sizeof(encoded), &packet, key);
    assert(n != 0u);
    for (i = 0u; i < n; ++i) { res_remote_app_receive_byte(a, encoded[i]); }
    (void)f;
}
static void ack(fixture_t *f, res_remote_app_t *a, uint8_t state, uint8_t relays, uint8_t faults)
{
    f->now = 40u;
    inject(f,a,RES_MSG_ACK,state,relays,faults,f->sequence,f->type,8u,1u);
}
static void press_go(fixture_t *f, res_remote_app_t *a)
{
    res_remote_app_set_raw_inputs(a, true, false);
    f->now = 80u;
    res_remote_app_tick(a);
}
int main(void)
{
    fixture_t f;
    res_remote_app_t a;
    unsigned i;

    /* First valid conversion uses nominal thresholds, not recovery thresholds. */
    init(&f,&a); res_remote_app_set_power(&a,0u,0,false);
    res_remote_app_set_power(&a,11100u,0,true); f.now=250u; res_remote_app_tick(&a);
    assert(f.leds[RES_LED_SOC_GREEN] && !f.leds[RES_LED_SOC_RED]);

    init(&f,&a); ack(&f,&a,RES_VEHICLE_READY,3u,0u);
    f.now=250u; res_remote_app_tick(&a);
    assert(f.leds[RES_LED_STATE_BLUE] && !f.leds[RES_LED_STATE_YELLOW]);
    assert(f.leds[RES_LED_SOC_GREEN] && !f.leds[RES_LED_SOC_RED]);

    init(&f,&a); ack(&f,&a,RES_VEHICLE_READY,3u,0u); press_go(&f,&a);
    assert(f.go_count == 1u);
    /* A newly reported vehicle fault cancels a pending GO repetition. */
    a.vehicle_fault_flags = RES_CAN_FLAG_CAN_LOCAL_FAULT;
    f.now=141u; res_remote_app_tick(&a); assert(f.go_count == 1u);

    init(&f,&a); ack(&f,&a,RES_VEHICLE_READY,3u,RES_CAN_FLAG_CAN_LOCAL_FAULT);
    press_go(&f,&a); assert(f.go_count == 0u);
    f.now=250u; res_remote_app_tick(&a);
    assert(f.leds[RES_LED_STATE_YELLOW]);
    assert(!f.leds[RES_LED_STATE_BLUE]); /* ASF: blue/yellow mutually exclusive */

    init(&f,&a); ack(&f,&a,RES_VEHICLE_WAIT_LINK,1u,0u); press_go(&f,&a);
    assert(f.go_count == 0u);
    f.now=250u; res_remote_app_tick(&a);
    assert(!f.leds[RES_LED_STATE_BLUE] && f.leds[RES_LED_STATE_YELLOW]);

    init(&f,&a); ack(&f,&a,RES_VEHICLE_READY,1u,0u); press_go(&f,&a);
    assert(f.go_count == 0u); /* relay COMMAND disagreement */

    /* Invalid replies neither refresh freshness nor consume pending ACK. */
    for(i=0u;i<7u;++i) {
        init(&f,&a); f.now = (i==6u) ? 500u : 40u;
        inject(&f,&a,i==0u?RES_MSG_STATUS:RES_MSG_ACK,
               i==1u?99u:RES_VEHICLE_READY,i==2u?0x83u:3u,0u,
               f.sequence+(i==3u?99u:0u),i==4u?RES_MSG_COMMAND:f.type,
               i==5u?7u:8u,1u);
        assert(!a.vehicle_feedback_valid && !res_remote_app_link_ok(&a,f.now));
    }
    init(&f,&a); ack(&f,&a,RES_VEHICLE_READY,3u,0u);
    f.now=100u;
    inject(&f,&a,RES_MSG_ACK,RES_VEHICLE_READY,3u,0u,f.sequence,f.type,8u,1u);
    assert(a.last_valid_rx_ms==40u); /* replay or consumed ACK */
    f.now=540u; res_remote_app_set_power(&a,12000u,0,true); res_remote_app_tick(&a);
    assert(!res_remote_app_link_ok(&a,f.now) && !f.leds[RES_LED_STATE_BLUE]);

    /* Matched STOP remains latched even after release and healthy power. */
    init(&f,&a); res_remote_app_set_raw_inputs(&a,false,true);
    f.now=35u; res_remote_app_tick(&a);
    ack(&f,&a,RES_VEHICLE_STOPPED_FAULT,0u,
        RES_CAN_FLAG_REMOTE_STOP|RES_CAN_FLAG_SOFTWARE_LATCHED);
    res_remote_app_set_raw_inputs(&a,false,false);
    f.now=250u; res_remote_app_tick(&a);
    assert(a.safety_state==RES_REMOTE_STOP_LATCHED);
    assert(!f.leds[RES_LED_STATE_BLUE] && f.leds[RES_LED_STATE_YELLOW]);

    init(&f,&a); f.now=250u; res_remote_app_set_power(&a,11000u,0,true);
    res_remote_app_tick(&a);
    assert(!f.leds[RES_LED_SOC_GREEN] && f.leds[RES_LED_SOC_RED]);
    res_remote_app_set_power(&a,11200u,0,true); res_remote_app_tick(&a);
    assert(!f.leds[RES_LED_SOC_GREEN]); /* recovery hysteresis */
    res_remote_app_set_power(&a,11300u,0,true); res_remote_app_tick(&a);
    assert(f.leds[RES_LED_SOC_GREEN] && !f.leds[RES_LED_SOC_RED]);
    f.now=375u; res_remote_app_set_power(&a,10499u,0,true); res_remote_app_tick(&a);
    assert(a.safety_state==RES_REMOTE_STOP_LATCHED && f.leds[RES_LED_SOC_RED]);
    assert(!(a.fault_flags & RES_REMOTE_FAULT_POWER_INVALID));

    init(&f,&a); f.now=375u; res_remote_app_set_power(&a,12000u,0,false);
    res_remote_app_tick(&a);
    assert(a.fault_flags & RES_REMOTE_FAULT_POWER_INVALID);
    assert(!f.leds[RES_LED_SOC_GREEN] && f.leds[RES_LED_SOC_RED]);
    init(&f,&a); f.now=300u; res_remote_app_tick(&a);
    assert(!a.battery_measurement_valid && a.safety_state==RES_REMOTE_STOP_LATCHED);

    /* Freshness arithmetic survives the millisecond counter wrapping. */
    init(&f,&a); a.vehicle_feedback_valid=true; a.last_valid_rx_ms=UINT32_MAX-100u;
    assert(res_remote_app_link_ok(&a,50u));
    assert(!res_remote_app_link_ok(&a,500u));
    puts("test_res_indicators: PASS");
    return 0;
}
