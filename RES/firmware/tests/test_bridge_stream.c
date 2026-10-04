#include <assert.h>
#include <string.h>
#include "res_protocol.h"
#define main bridge_embedded_main
#include "../radio_bridge_stm8/res_bridge_main.c"
#undef main
#include "../radio_bridge_stm8/res_bridge_callback.c"

static unsigned sent, forwarded, listening;
static uint8_t last_frame[61], last_size;
static void init_stub(void) {}
static void send_stub(uint8e_t *b, uint8e_t n, uint32e_t timeout)
{
    (void)timeout;
    memcpy(last_frame, b, n);
    last_size = n;
    ++sent;
}
static void receive_stub(uint32e_t ticks) { (void)ticks; ++listening; }
static void sleep_stub(uint8e_t mode) { (void)mode; }
const Ebyte_RF_t Ebyte_RF = {
    init_stub, send_stub, sleep_stub, receive_stub, init_stub
};
void Ebyte_BSP_Init(void) {}
void Ebyte_BSP_GlobalIntEnable(void) {}
void Ebyte_FIFO_Init(Ebyte_FIFO_t *f, uint16e_t n) { (void)f; (void)n; }
void Ebyte_E220x_SetRfFrequency(uint32e_t f) { (void)f; }
void Ebyte_BSP_UartTransmit(uint8e_t *b, uint8e_t n)
{
    (void)b; (void)n;
    assert(listening != 0); /* RX must be armed before the endpoint can reply. */
    ++forwarded;
}
static size_t make_frame(uint8_t *b, uint32_t seq, uint8_t payload_size)
{
    const uint8_t key[16] = {0};
    res_frame_t f;
    memset(&f, 0, sizeof(f));
    f.type = RES_MSG_COMMAND;
    f.source = RES_NODE_REMOTE;
    f.destination = RES_NODE_VEHICLE;
    f.session = 42;
    f.sequence = seq;
    f.payload_length = payload_size;
    return res_frame_encode(b, 61, &f, key);
}
static void feed(const uint8_t *b, size_t n)
{
    size_t i;
    for (i = 0; i < n; ++i) RES_Bridge_OnUartByte(b[i]);
}
int main(void)
{
    uint8_t a[61], b[61];
    size_t n = make_frame(a, 1, 8);
    size_t m = make_frame(b, 2, 8);
    size_t i;
    assert(n == 37 && m == 37);
    /* Complete frames must pass with both legacy idle flags zero. */
    feed(a, n - 1); task_transmit(); assert(sent == 0);
    feed(a + n - 1, 1); task_transmit();
    assert(sent == 1 && last_size == n && memcmp(a, last_frame, n) == 0);
    /* Two frames exceed the old 64-byte FIFO but must remain separate. */
    feed(a, n); feed(b, m);
    task_transmit(); task_transmit();
    assert(sent == 3 && memcmp(b, last_frame, m) == 0);
    /* CRC-corrupted data followed by a valid frame must resynchronize. */
    a[20] ^= 1;
    feed(a, n); feed(b, m);
    task_transmit(); task_transmit();
    assert(sent == 4 && res_bridge_bad_frames != 0);
    /* Maximum-size frames, including split UART arrivals. */
    n = make_frame(a, 3, 32);
    for (i = 0; i < n; ++i) { feed(a + i, 1); task_transmit(); }
    assert(sent == 5 && last_size == 61);
    /* Overflow must discard partial data, never emit a spliced frame. */
    for (i = 0; i < 200; ++i) RES_Bridge_OnUartByte(0x52);
    task_transmit(); assert(sent == 5 && res_bridge_overflows != 0);
    feed(b, m); task_transmit(); assert(sent == 6);
    /* No debug output or malformed RF payload forwarded to STM32. */
    listening = 0;
    Ebyte_Port_ReceiveCallback(IRQ_RX_DONE, b, (uint8_t)m);
    assert(forwarded == 1 && listening != 0);
    b[20] ^= 1;
    Ebyte_Port_ReceiveCallback(IRQ_RX_DONE, b, (uint8_t)m);
    assert(forwarded == 1);
    listening = 0;
    apply_pending_radio_event();
    assert(listening == 1); /* Bad RF frame must not leave receiver stopped. */
    listening = 0;
    Ebyte_Port_ReceiveCallback(IRQ_RX_TX_TIMEOUT, b, 0);
    apply_pending_radio_event();
    assert(listening == 1);
    return 0;
}
