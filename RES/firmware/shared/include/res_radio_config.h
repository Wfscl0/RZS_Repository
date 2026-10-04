#ifndef RES_RADIO_CONFIG_H
#define RES_RADIO_CONFIG_H
/* S017 is the current board. Set to 0 only for a legacy E220 build. */
#ifndef RES_RADIO_SI4463
#define RES_RADIO_SI4463 1
#endif
#if RES_RADIO_SI4463 && ((defined(RES_E220_STOCK_BRIDGE_TEST) && RES_E220_STOCK_BRIDGE_TEST) || (defined(RES_STOCK_BRIDGE_GAP_MS) && RES_STOCK_BRIDGE_GAP_MS))
#error S017 cannot use the E220 UART compatibility timing profile
#endif
/* 48 RF bytes: one length byte, up to 47 RES bytes, zero padding.
 * Current HELLO/heartbeat=41, command/ACK=37. At 2400 bit/s with vendor
 * preamble/sync/CRC this is about 193 ms one way, subject to HIL measurement.
 * Never silently truncate larger future RES messages. */
#define RES_RADIO_PACKET_SIZE 48u
#define RES_RADIO_TX_TIMEOUT_MS 240u
#define RES_RADIO_ACK_TIMEOUT_MS 450u
#define RES_RADIO_SCAN_MS 600u
/* PA code, NOT dBm. Requires conducted/EIRP measurement before deployment. */
#define RES_RADIO_PA_CODE 0x10u
#endif
