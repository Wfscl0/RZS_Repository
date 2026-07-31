/* Replacement ebyte/E220xMx/ebyte_callback.c for the official IAR project. */
#include "ebyte_callback.h"
#include "board.h"
#include "res_bridge_control.h"

#define IRQ_TX_DONE        0x0001u
#define IRQ_RX_DONE        0x0002u
#define IRQ_RX_TX_TIMEOUT  0x0200u

void Ebyte_Port_TransmitCallback(uint16e_t state)
{
    if ((state & IRQ_TX_DONE) != 0u) {
        return;
    }
    if ((state & IRQ_RX_TX_TIMEOUT) != 0u) {
        return;
    }
    /* Unknown IRQ bits are ignored here; endpoint heartbeat timeout is fail-safe. */
}

void Ebyte_Port_ReceiveCallback(uint16e_t state,
                                uint8e_t *buffer,
                                uint8e_t length)
{
    if ((state & IRQ_RX_DONE) != 0u) {
        /* Preserve the exact authenticated frame; do not print debug text on UART. */
        Ebyte_BSP_UartTransmit(buffer, length);
        RES_Bridge_OnReceivedFrame(buffer, length);
    } else if ((state & IRQ_RX_TX_TIMEOUT) != 0u) {
        RES_Bridge_OnReceiveTimeout();
    }
    /* CRC and timeout errors are intentionally not forwarded. */
}
