#include "res_remote_app.h"
#include "res_vehicle_app.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    uint32_t now;
    uint8_t packet[RES_MAX_FRAME_SIZE];
    size_t length;
    bool leds[RES_LED_COUNT];
    bool relays[2];
    bool can_fail;
} endpoint_t;
static uint32_t millis(void *p) { return ((endpoint_t *)p)->now; }
static bool tx(void *p,const uint8_t *data,size_t n)
{
    endpoint_t *e=p;
    assert(e->length==0u && n<=sizeof(e->packet));
    memcpy(e->packet,data,n); e->length=n; return true;
}
static void led(void *p,res_led_t id,bool on) { ((endpoint_t *)p)->leds[id]=on; }
static void wd(void *p) { (void)p; }
static void relay(void *p,res_vehicle_relay_t id,bool on)
{
    ((endpoint_t *)p)->relays[id] = on;
}
static void output(void *p,res_vehicle_output_t id,bool on) { (void)p;(void)id;(void)on; }
static bool can(void *p,uint16_t id,const uint8_t *data,uint8_t n)
{ (void)id;(void)data;(void)n;return !((endpoint_t *)p)->can_fail; }
static void step(endpoint_t *r,endpoint_t *v,res_remote_app_t *ra,res_vehicle_app_t *va,
                 uint32_t now,bool go,bool stop,bool deliver)
{
    size_t i;
    r->now=now;v->now=now;
    res_remote_app_set_power(ra,12000u,0,true);
    res_remote_app_set_raw_inputs(ra,go,stop);
    res_vehicle_app_tick(va);
    res_remote_app_tick(ra);
    if(deliver) {
        for(i=0u;i<r->length;++i) res_vehicle_app_receive_byte(va,r->packet[i]);
        for(i=0u;i<v->length;++i) res_remote_app_receive_byte(ra,v->packet[i]);
    }
    r->length=0u;v->length=0u;
}
int main(void)
{
    endpoint_t r={0},v={0};
    res_remote_app_t ra;res_vehicle_app_t va;
    const uint8_t key[16]={0};
    const res_remote_io_t rio={&r,millis,tx,led,wd};
    const res_vehicle_io_t vio={&v,millis,tx,can,relay,output,wd};
    uint32_t t;
    res_remote_app_init(&ra,&rio,key,123u);
    res_vehicle_app_init(&va,&vio,key,456u);
    for(t=10u;t<=1800u;t+=10u) {
        step(&r,&v,&ra,&va,t,false,false,true);
        if (t == 10u) {
            /* Vehicle-only standby contract: R1 closed, R2 released. */
            assert(v.relays[0] && !v.relays[1]);
        }
        if (t < 1010u) {
            assert(r.leds[0] && r.leds[1] && r.leds[2] && r.leds[3]);
            assert(va.state != RES_CAN_STATE_READY);
        }
    }
    assert(va.state==RES_CAN_STATE_READY && ra.vehicle_state==RES_VEHICLE_READY);
    assert(v.relays[0] && v.relays[1]);
    assert(r.leds[RES_LED_STATE_BLUE] && !r.leds[RES_LED_STATE_YELLOW]);
    for(;t<=1950u;t+=10u) {
        step(&r,&v,&ra,&va,t,true,false,true);
        assert(r.leds[RES_LED_STATE_BLUE] && r.leds[RES_LED_SOC_GREEN]);
        assert(!r.leds[RES_LED_STATE_YELLOW] && !r.leds[RES_LED_SOC_RED]);
    }
    assert(va.go_event_counter==1u); /* retry de-duplication */
    v.can_fail=true;
    for(;t<=2450u;t+=10u) step(&r,&v,&ra,&va,t,false,false,true);
    assert(ra.vehicle_fault_flags & RES_CAN_FLAG_CAN_LOCAL_FAULT);
    assert(r.leds[RES_LED_STATE_YELLOW]);
    for(;t<=2550u;t+=10u) step(&r,&v,&ra,&va,t,true,false,true);
    assert(va.go_event_counter==1u); /* fault blocks another GO */
    for(;t<=2750u;t+=10u) step(&r,&v,&ra,&va,t,false,true,true);
    assert(ra.safety_state==RES_REMOTE_STOP_LATCHED && va.fault_latched);
    assert(!r.leds[RES_LED_STATE_BLUE] && r.leds[RES_LED_STATE_YELLOW]);
    assert(!va.relay_1_closed && !va.relay_2_closed);
    for(;t<=3500u;t+=10u) step(&r,&v,&ra,&va,t,false,false,false);
    assert(!r.leds[RES_LED_STATE_BLUE]);
    assert(ra.safety_state==RES_REMOTE_STOP_LATCHED && va.fault_latched);
    /* Restore the actual local CAN condition, release STOP, and reboot only
     * the remote. Vehicle app/session and GO count survive this operation. */
    v.can_fail=false;
    res_vehicle_app_set_local_fault(&va,RES_VEHICLE_FAULT_CAN,false);
    res_remote_app_init(&ra,&rio,key,124u);
    for(;t<=6000u;t+=10u) step(&r,&v,&ra,&va,t,false,false,true);
    assert(va.local_session==456u && va.remote_session==124u);
    assert(!va.fault_latched && va.state==RES_CAN_STATE_READY);
    assert(v.relays[0] && v.relays[1] && !va.start_output_active);
    assert(va.go_event_counter==1u); /* recovery never produces GO */
    assert(r.leds[RES_LED_STATE_BLUE] && !r.leds[RES_LED_STATE_YELLOW]);
    for(;t<=6300u;t+=10u) step(&r,&v,&ra,&va,t,true,false,true);
    assert(va.go_event_counter==2u); /* new operator press is required */
    puts("test_res_lamp_link: PASS");return 0;
}
