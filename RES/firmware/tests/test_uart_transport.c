#include "res_uart_transport.h"
#include <assert.h>
#include <stdio.h>

UART_HandleTypeDef huart1;
static uint32_t now, primask, ipsr;
static uint8_t *rx_target;
static unsigned inject_during_tx;
uint32_t HAL_GetTick(void) { return now; }
uint32_t __get_PRIMASK(void) { return primask; }
uint32_t __get_IPSR(void) { return ipsr; }
void __disable_irq(void) { primask=1u; }
void __set_PRIMASK(uint32_t value) { primask=value; }
uint32_t HAL_UART_GetError(UART_HandleTypeDef *h) { return h->ErrorCode; }
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *h,uint8_t *p,uint16_t n)
{
    assert(n==1u);
    if(h->RxState!=HAL_UART_STATE_READY) return HAL_BUSY;
    rx_target=p;h->RxState=HAL_UART_STATE_BUSY_RX;return HAL_OK;
}
static void receive(uint8_t byte)
{
    assert(huart1.RxState==HAL_UART_STATE_BUSY_RX);
    *rx_target=byte;huart1.RxState=HAL_UART_STATE_READY;
    ipsr=1u;res_uart_received();ipsr=0u;
}
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *h,uint8_t *p,uint16_t n,uint32_t timeout)
{
    unsigned i;(void)h;(void)p;(void)n;(void)timeout;
    assert(ipsr==0u);
    for(i=0u;i<inject_during_tx;++i){++now;receive((uint8_t)i);}
    return HAL_OK;
}
int main(void)
{
    unsigned i;uint8_t b=0u;
    res_stream_parser_t parser={0};
    res_uart_start(2u);
    /* Bytes arriving while a foreground ACK transmits must remain available. */
    inject_during_tx=41u;
    assert(res_uart_send(&b,1u));
    for(i=0u;i<41u;++i){assert(res_uart_next(&parser,&b));assert(b==(uint8_t)i);}
    assert(!res_uart_next(&parser,&b));
    assert(res_uart_diag.rx_bytes==41u && res_uart_diag.tx_frames==1u);
    /* Buffer wrap with interleaved producer and consumer preserves order. */
    for(i=0u;i<1024u;++i){receive((uint8_t)i);assert(res_uart_next(&parser,&b));assert(b==(uint8_t)i);}
    /* Overflow discards the damaged stream and allows the next frame. */
    parser.length=3u;
    for(i=0u;i<256u;++i) receive((uint8_t)i);
    assert(res_uart_diag.rx_overflows==1u);
    assert(!res_uart_next(&parser,&b) && parser.length==0u);
    receive(0x52u);assert(res_uart_next(&parser,&b) && b==0x52u);
    /* HAL ORE ends RX: error callback must arm it again. */
    huart1.RxState=HAL_UART_STATE_READY;huart1.ErrorCode=8u;
    res_uart_error();
    assert(huart1.RxState==HAL_UART_STATE_BUSY_RX);
    assert(!res_uart_next(&parser,&b));
    receive(0x53u);assert(res_uart_next(&parser,&b) && b==0x53u);
    assert(res_uart_diag.uart_errors==1u && res_uart_diag.last_uart_error==8u);
    /* Stale queued bytes cannot refresh link liveness. */
    receive(0x52u);now+=101u;
    assert(!res_uart_next(&parser,&b) && res_uart_diag.stale_bytes==1u);
    /* Future regressions cannot perform blocking TX in an ISR. */
    ipsr=1u;assert(!res_uart_send(&b,1u));ipsr=0u;
    assert(res_uart_diag.tx_failures==1u);
    puts("UART foreground ACK, RX recovery, overflow and stale-data tests passed");
    return 0;
}
