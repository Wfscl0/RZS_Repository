#ifndef RES_BRIDGE_CONFIG_H
#define RES_BRIDGE_CONFIG_H

/*
 * Bench frequency plan for E220-400MBL-01 / LLCC68.
 * These centre frequencies keep a 500 kHz LoRa occupied bandwidth inside
 * 433.05--434.79 MHz.  Before competition, the team must confirm local radio
 * approval, event allocation, permitted EIRP and duty cycle.  Do not change
 * one bridge only: both ends require the identical table and order.
 */
#define RES_BRIDGE_CHANNEL_COUNT       3u
#define RES_BRIDGE_FREQUENCY_0_HZ      433300000UL
#define RES_BRIDGE_FREQUENCY_1_HZ      433900000UL
#define RES_BRIDGE_FREQUENCY_2_HZ      434500000UL

/* LLCC68 timeout unit is 15.625 us: 15360 ticks = 240 ms scan dwell. */
#define RES_BRIDGE_RX_DWELL_TICKS      15360UL

/* Protocol constants mirrored from shared/include/res_protocol.h. */
#define RES_BRIDGE_PROTOCOL_VERSION    2u
#define RES_BRIDGE_HEADER_SIZE         19u
#define RES_BRIDGE_TRAILER_SIZE        10u
#define RES_BRIDGE_MAX_PAYLOAD         32u
#define RES_BRIDGE_MAX_FRAME           61u

#endif
