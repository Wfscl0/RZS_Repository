#ifndef RES_BRIDGE_CONTROL_H
#define RES_BRIDGE_CONTROL_H

#include "ebyte_conf.h"

/* RF callbacks run in the vendor polling task, never a hardware ISR.
 * Valid RX retunes immediately; UART byte ingestion alone is ISR-safe. */
uint8e_t RES_Bridge_OnReceivedFrame(const uint8e_t *buffer, uint8e_t length);
void RES_Bridge_OnUartByte(uint8e_t byte);
void RES_Bridge_OnReceiveTimeout(void);

#endif
