#ifndef RES_CONFIG_H
#define RES_CONFIG_H

#include <stdint.h>

/*
 * Project-specific constants.
 *
 * The three RF frequencies are conservative 433 MHz examples only. Before a
 * competition or road test, the team must confirm the permitted frequencies,
 * occupied bandwidth, antenna gain and EIRP for the site and radio module.
 */
#define RES_PAIR_ID                         UINT32_C(0x525A5301)
#define RES_RF_CHANNEL_COUNT                3U
#define RES_RF_CHANNEL_0_HZ                 UINT32_C(433175000)
#define RES_RF_CHANNEL_1_HZ                 UINT32_C(433525000)
#define RES_RF_CHANNEL_2_HZ                 UINT32_C(433875000)
#define RES_RF_TX_POWER_DBM                 10

#define RES_RADIO_TX_PERIOD_MS              UINT32_C(100)
#define RES_RADIO_ESTOP_TX_PERIOD_MS        UINT32_C(60)
#define RES_RADIO_TX_TIMEOUT_MS             UINT32_C(150)
#define RES_RADIO_RETRY_MS                  UINT32_C(1000)
#define RES_LINK_GO_MAX_AGE_MS              UINT32_C(300)
#define RES_LINK_LOSS_LATCH_MS              UINT32_C(500)

#define RES_LAMP_TEST_MS                     UINT32_C(2000)
#define RES_GO_DEBOUNCE_MS                   UINT32_C(30)
#define RES_GO_RELEASE_MS                    UINT32_C(200)
#define RES_GO_REPEAT_MS                     UINT32_C(600)

#define RES_ADS1115_I2C_ADDRESS              0x48U
#define RES_ADC_SAMPLE_PERIOD_MS             UINT32_C(500)
#define RES_ADC_CONVERSION_MS                UINT32_C(10)
#define RES_ADC_FAILURE_LIMIT                3U

/* Default divider: battery -> 100 kOhm -> AIN0 -> 27 kOhm -> GND. */
#define RES_BAT_DIVIDER_TOP_OHM              UINT32_C(100000)
#define RES_BAT_DIVIDER_BOTTOM_OHM           UINT32_C(27000)
#define RES_BATTERY_LOW_MV                   UINT16_C(10800)
#define RES_BATTERY_MID_MV                   UINT16_C(11600)
#define RES_BATTERY_MAX_VALID_MV             UINT16_C(15000)

#endif

