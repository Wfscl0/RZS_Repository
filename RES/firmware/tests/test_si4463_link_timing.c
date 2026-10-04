#include "res_remote_app.h"
#include "res_vehicle_app.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

/* Model the 48-byte vendor 2400 bit/s profile as 200 ms per packet,
 * with a single half-duplex radio and actual per-packet channel changes. */
typedef struct {
    uint32_t now, due, sends;
    bool busy, relays[2], leds[RES_LED_COUNT];
    uint8_t tuned, data[RES_MAX_FRAME_SIZE];
    size_t length;
} endpoint_t;
static uint32_t ms(void *p) { return ((endpoint_t *)p)->now; }
static bool tx(void *p, const uint8_t *data, size_t length)
{
    endpoint_t *e = p;
    bool stop = data[3] == RES_MSG_COMMAND && data[19] == RES_COMMAND_STOP;
    assert(!e->busy || stop);
    memcpy(e->data, data, length); e->length = length;
    e->busy = true; e->due = e->now + 200u; ++e->sends;
    e->tuned = data[9]; return true;
}
static bool can(void *p,uint16_t id,const uint8_t *b,uint8_t n)
{ (void)p;(void)id;(void)b;(void)n;return true; }
static void relay(void *p,res_vehicle_relay_t id,bool on)
{ ((endpoint_t *)p)->relays[id]=on; }
static void output(void *p,res_vehicle_output_t id,bool on)
{ (void)p;(void)id;(void)on; }
static void led(void *p,res_led_t id,bool on) { ((endpoint_t *)p)->leds[id]=on; }
static void wd(void *p) { (void)p; }

int main(void)
{
    endpoint_t r={0},v={0};
    res_remote_app_t ra; res_vehicle_app_t va;
    uint8_t key[16]={0}; uint32_t t;
    const res_remote_io_t rio={&r,ms,tx,led,wd};
    const res_vehicle_io_t vio={&v,ms,tx,can,relay,output,wd};
    res_remote_app_init(&ra,&rio,key,101u);
    res_vehicle_app_init(&va,&vio,key,202u);
    for(t=0;t<=8600u;t+=5u) {
        size_t i;
        r.now=v.now=t;
        if(r.busy && t>=r.due) {
            r.busy=false;
            r.tuned=res_hop_next_channel(r.data[9],res_get_u32_le(r.data+14),res_get_u32_le(r.data+10));
            if(t<8000u && !v.busy && v.tuned==r.data[9]) {
                for(i=0;i<r.length;++i) res_vehicle_app_receive_byte(&va,r.data[i]);
                if(!v.busy) v.tuned=va.active_channel;
            }
        }
        if(v.busy && t>=v.due) {
            v.busy=false;
            v.tuned=res_hop_next_channel(v.data[9],res_get_u32_le(v.data+14),res_get_u32_le(v.data+10));
            if(t<8000u && !r.busy && r.tuned==v.data[9]) {
                for(i=0;i<v.length;++i) res_remote_app_receive_byte(&ra,v.data[i]);
                r.tuned=ra.active_channel;
            }
        }
        res_remote_app_set_power(&ra,12000u,0,true);
        res_remote_app_set_raw_inputs(&ra,t>=4000u && t<4600u,false);
        res_vehicle_app_tick(&va);
        res_remote_app_tick(&ra);
        if(t>=2500u && t<7900u) {
            assert(!va.fault_latched && v.relays[0] && v.relays[1]);
            assert(ra.safety_state==RES_REMOTE_READY);
            assert(r.leds[RES_LED_STATE_BLUE] && !r.leds[RES_LED_STATE_YELLOW]);
        }
    }
    assert(va.go_event_counter==1u);
    assert(va.fault_latched && !v.relays[0] && !v.relays[1]);
    assert(ra.safety_state==RES_REMOTE_STOP_LATCHED);
    puts("Si4463 delayed half-duplex link: PASS");
    return 0;
}
