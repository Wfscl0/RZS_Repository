#include "res_si4463_transport.h"
#include <assert.h>
#include <stdio.h>

static uint32_t now;
static bool cts=true, fail_spi, selected, shutdown;
static unsigned phase, power_ups;
static uint8_t last_cmd, ph_pending, chip_pending, physical_channel;
static uint8_t rx_packet[RES_RADIO_PACKET_SIZE], tx_packet[RES_RADIO_PACKET_SIZE];
static uint16_t chip_part=0x4463;
static uint8_t rx_count=RES_RADIO_PACKET_SIZE;
static uint32_t calibration_until;
static unsigned calibrations;
static bool bad_properties;
static uint8_t bad_property_group;
static uint8_t properties[0x41][256], get_group, get_start;
static bool irq_stuck_high;
static unsigned guard_nops;
void res_test_nop(void) { ++guard_nops; }
uint32_t HAL_GetTick(void) { return now; }
uint32_t __get_IPSR(void) { return 0; }
void HAL_Delay(uint32_t ms) { now+=ms; }
void HAL_GPIO_Init(GPIO_TypeDef *p,GPIO_InitTypeDef *g) { (void)p;if(g->Mode==GPIO_MODE_AF_PP) assert(g->Speed==GPIO_SPEED_FREQ_LOW); }
void HAL_GPIO_WritePin(GPIO_TypeDef *p,uint32_t pin,GPIO_PinState s)
{
    if(p==GPIOA && pin==GPIO_PIN_4) { selected=s==GPIO_PIN_RESET;phase=0; }
    if(p==GPIOB && pin==GPIO_PIN_3) shutdown=s==GPIO_PIN_SET;
}
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *p,uint32_t pin)
{ (void)p;(void)pin;return (!irq_stuck_high && (ph_pending || chip_pending))?GPIO_PIN_RESET:GPIO_PIN_SET; }
HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *h) { assert(h->Init.BaudRatePrescaler==256u);return HAL_OK; }
HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *h,uint8_t *tx,uint8_t *rx,uint16_t n,uint32_t timeout)
{
    (void)h; assert(selected && timeout==3u && guard_nops!=0u);
    if(fail_spi) return HAL_ERROR;
    memset(rx,0,n);
    if(phase) {
        if(last_cmd==0x01) { assert(n==8);rx[1]=(uint8_t)(chip_part>>8);rx[2]=(uint8_t)chip_part; }
        if(last_cmd==0x20) { assert(n==8);rx[2]=ph_pending;rx[6]=chip_pending;ph_pending=chip_pending=0; }
        if(last_cmd==0x23) { assert(n==4);rx[2]=0x12;rx[3]=0x32; }
        if(last_cmd==0x15) { assert(n==2);rx[0]=rx_count;rx[1]=64; }
        if(last_cmd==0x12) { memcpy(rx,&properties[get_group][get_start],n);if(bad_properties && get_group==bad_property_group) rx[0]^=1; }
        return HAL_OK;
    }
    if(tx[0]==0x44) { bool ready=cts && now>=calibration_until;assert(n==2);rx[1]=ready?0xff:0;phase=1;if(!ready) ++now;return HAL_OK; }
    last_cmd=tx[0];
    if(tx[0]==0x11) { assert(tx[1]<0x41 && n==tx[2]+4);memcpy(&properties[tx[1]][tx[3]],tx+4,tx[2]); }
    if(tx[0]==0x12) { get_group=tx[1];get_start=tx[3]; }
    if(tx[0]==0x17) { calibration_until=now+(calibrations++==0?150u:100u); }
    if(tx[0]==0x02) { assert(n==7); ++power_ups; }
    if(tx[0]==0x66) { assert(n==RES_RADIO_PACKET_SIZE+1);memcpy(tx_packet,tx+1,RES_RADIO_PACKET_SIZE); }
    if(tx[0]==0x77) { assert(n==RES_RADIO_PACKET_SIZE+1);memcpy(rx+1,rx_packet,RES_RADIO_PACKET_SIZE); }
    if(tx[0]==0x31 || tx[0]==0x32) physical_channel=tx[1];
    return HAL_OK;
}

static void reset(void)
{
    memset((void *)&res_si4463_diag,0,sizeof(res_si4463_diag));
    memset((void *)&res_uart_diag,0,sizeof(res_uart_diag));
    res_rf_length=res_rf_pos=0;now=0;cts=true;fail_spi=false;
    ph_pending=chip_pending=0;power_ups=0;chip_part=0x4463;rx_count=RES_RADIO_PACKET_SIZE;
    calibration_until=0;calibrations=0;bad_properties=false;
    bad_property_group=1;
    irq_stuck_high=false;guard_nops=0;res_rf_last_irq_check=0;memset(properties,0,sizeof(properties));
}
int main(void)
{
    res_frame_t frame={0}; uint8_t key[16]={0}, encoded[RES_MAX_FRAME_SIZE],b;
    size_t len,i;res_stream_parser_t parser;
    reset();res_uart_start(1);
    assert(res_si4463_diag.ready && power_ups==1 && !shutdown);
    assert(calibrations==2 && now>=265u);
    assert(res_si4463_diag.configured_xo_hz==30000000u);
    assert(res_si4463_diag.property_checks==10u);
    frame.type=RES_MSG_HELLO;frame.source=1;frame.destination=2;frame.session=42;frame.sequence=1;frame.payload_length=12;
    len=res_frame_encode(encoded,sizeof(encoded),&frame,key);
    assert(res_uart_send(encoded,len) && res_si4463_diag.tx_busy);
    assert(tx_packet[0]==len && memcmp(tx_packet+1,encoded,len)==0);
    assert(!res_uart_send(encoded,len)); /* no second normal TX while busy */
    irq_stuck_high=true;ph_pending=0x20;now+=200;res_rf_poll();
    assert(res_si4463_diag.irq_fallbacks==1u);
    irq_stuck_high=false;
    assert(!res_si4463_diag.tx_busy && res_si4463_diag.tx_done==1);
    assert(physical_channel==res_hop_next_channel(0,42,1));
    rx_packet[0]=(uint8_t)len;memcpy(rx_packet+1,encoded,len);ph_pending=0x10;
    res_stream_parser_init(&parser);
    for(i=0;i<len;i++) { assert(res_uart_next(&parser,&b));assert(b==encoded[i]); }
    assert(!res_uart_next(&parser,&b));
    res_radio_follow(2);assert(physical_channel==2);
    now+=RES_RADIO_SCAN_MS;res_rf_poll();assert(physical_channel==0);
    ph_pending=8;res_rf_poll();assert(res_si4463_diag.crc_errors==1 && !res_uart_next(&parser,&b));
    assert(res_uart_send(encoded,len));
    frame.type=RES_MSG_COMMAND;frame.payload_length=8;frame.payload[0]=RES_COMMAND_STOP;
    len=res_frame_encode(encoded,sizeof(encoded),&frame,key);
    assert(res_uart_send(encoded,len)); /* STOP preempts current normal frame */
    now+=RES_RADIO_TX_TIMEOUT_MS;res_rf_poll();
    assert(!res_si4463_diag.ready && shutdown && res_si4463_diag.error==7);
    reset();cts=false;res_uart_start(1);assert(shutdown && !res_si4463_diag.ready && res_si4463_diag.error==2);
    reset();fail_spi=true;res_uart_start(1);assert(shutdown && res_si4463_diag.error==1);
    reset();chip_part=0x4460;res_uart_start(1);assert(shutdown && res_si4463_diag.error==4);
    reset();res_uart_start(2);rx_count=64;ph_pending=0x10;res_rf_poll();assert(shutdown && res_si4463_diag.error==6);
    reset();res_uart_start(2);chip_pending=8;res_rf_poll();assert(shutdown && res_si4463_diag.error==5);
    assert(res_si4463_diag.chip_detail_valid==1 && res_si4463_diag.cmd_error_status==0x12 && res_si4463_diag.cmd_error_id==0x32);
    reset();bad_properties=true;res_uart_start(1);assert(shutdown && !res_si4463_diag.ready && res_si4463_diag.error==8);
    assert(res_si4463_diag.property_expected==0x28003805u);
    assert(res_si4463_diag.property_actual==0x28003804u);
    reset();bad_properties=true;bad_property_group=0x20;res_uart_start(1);
    assert(shutdown && !res_si4463_diag.ready && res_si4463_diag.property_failure==0x2000);
    reset();bad_properties=true;bad_property_group=0x40;res_uart_start(2);
    assert(shutdown && !res_si4463_diag.ready && res_si4463_diag.property_failure==0x4000);
    res_uart_received();res_uart_error();
    puts("Si4463 SPI/FIFO/timeout transport: PASS");return 0;
}
