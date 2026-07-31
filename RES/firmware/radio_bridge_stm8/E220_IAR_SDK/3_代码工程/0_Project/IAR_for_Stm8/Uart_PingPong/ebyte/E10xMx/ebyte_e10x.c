#include "ebyte_e10x.h"
#include "radio_config.h"
#include <stdarg.h>

#define RADIO_CONFIGURATION_DATA_RADIO_XO_FREQ                     30000000L
#define RADIO_CONFIGURATION_DATA_CHANNEL_NUMBER                    0x00
#define RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH               0x08
#define RADIO_CONFIGURATION_DATA_RADIO_STATE_AFTER_POWER_UP        0x03
#define RADIO_CONFIGURATION_DATA_RADIO_DELAY_CNT_AFTER_RESET       0xF000
#define RADIO_CONFIGURATION_DATA_CUSTOM_PAYLOAD					   {0x07, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5}


#define SI446X_PATCH_ROMID  00
#define SI446X_PATCH_ID     00

#define SI446X_PATCH_CMDS                   \
0x08,0x04,0x21,0x71,0x4B,0x00,0x00,0xDC,0x95, \
0x08,0x05,0xA6,0x22,0x21,0xF0,0x41,0x5B,0x26, \
0x08,0xE2,0x2F,0x1C,0xBB,0x0A,0xA8,0x94,0x28, \
0x08,0x05,0x87,0x67,0xE2,0x58,0x1A,0x07,0x5B, \
0x08,0xE1,0xD0,0x72,0xD8,0x8A,0xB8,0x5B,0x7D, \
0x08,0x05,0x11,0xEC,0x9E,0x28,0x23,0x1B,0x6D, \
0x08,0xE2,0x4F,0x8A,0xB2,0xA9,0x29,0x14,0x13, \
0x08,0x05,0xD1,0x2E,0x71,0x6A,0x51,0x4C,0x2C, \
0x08,0xE5,0x80,0x27,0x42,0xA4,0x69,0xB0,0x7F, \
0x08,0x05,0xAA,0x81,0x2A,0xBD,0x45,0xE8,0xA8, \
0x08,0xEA,0xE4,0xF0,0x24,0xC9,0x9F,0xCC,0x3C, \
0x08,0x05,0x08,0xF5,0x05,0x04,0x27,0x62,0x98, \
0x08,0xEA,0x6B,0x62,0x84,0xA1,0xF9,0x4A,0xE2, \
0x08,0x05,0xE9,0x77,0x05,0x4F,0x84,0xEE,0x35, \
0x08,0xE2,0x43,0xC3,0x8D,0xFB,0xAD,0x54,0x25, \
0x08,0x05,0x14,0x06,0x5E,0x39,0x36,0x2F,0x45, \
0x08,0xEA,0x0C,0x1C,0x74,0xD0,0x11,0xFC,0x32, \
0x08,0x05,0xDA,0x38,0xBA,0x0E,0x3C,0xE7,0x8B, \
0x08,0xEA,0xB0,0x09,0xE6,0xFF,0x94,0xBB,0xA9, \
0x08,0x05,0xD7,0x11,0x29,0xFE,0xDC,0x71,0xD5, \
0x08,0xEA,0x7F,0x83,0xA7,0x60,0x90,0x62,0x18, \
0x08,0x05,0x84,0x7F,0x6A,0xD1,0x91,0xC6,0x52, \
0x08,0xEA,0x2A,0xD8,0x7B,0x8E,0x4A,0x9F,0x91, \
0x08,0x05,0xBD,0xAA,0x9D,0x16,0x18,0x06,0x15, \
0x08,0xE2,0x55,0xAD,0x2D,0x0A,0x14,0x1F,0x5D, \
0x08,0x05,0xD3,0xE0,0x7C,0x39,0xCF,0x01,0xF0, \
0x08,0xEF,0x3A,0x91,0x72,0x6A,0x03,0xBB,0x96, \
0x08,0xE7,0x83,0x6D,0xA4,0x92,0xFC,0x13,0xA7, \
0x08,0xEF,0xF8,0xFD,0xCF,0x62,0x07,0x6F,0x1E, \
0x08,0xE7,0x4C,0xEA,0x4A,0x75,0x4F,0xD6,0xCF, \
0x08,0xE2,0xF6,0x11,0xE4,0x26,0x0D,0x4D,0xC6, \
0x08,0x05,0xFB,0xBF,0xE8,0x07,0x89,0xC3,0x51, \
0x08,0xEF,0x82,0x27,0x04,0x3F,0x96,0xA8,0x58, \
0x08,0xE7,0x41,0x29,0x3C,0x75,0x2A,0x03,0x1C, \
0x08,0xEF,0xAF,0x59,0x98,0x36,0xAA,0x0F,0x06, \
0x08,0xE6,0xF6,0x93,0x41,0x2D,0xEC,0x0E,0x99, \
0x08,0x05,0x29,0x19,0x90,0xE5,0xAA,0x36,0x40, \
0x08,0xE7,0xFB,0x68,0x10,0x7D,0x77,0x5D,0xC0, \
0x08,0xE7,0xCB,0xB4,0xDD,0xCE,0x90,0x54,0xBE, \
0x08,0xE7,0x72,0x8A,0xD6,0x02,0xF4,0xDD,0xCC, \
0x08,0xE7,0x6A,0x21,0x0B,0x02,0x86,0xEC,0x15, \
0x08,0xE7,0x7B,0x7C,0x3D,0x6B,0x81,0x03,0xD0, \
0x08,0xEF,0x7D,0x61,0x36,0x94,0x7C,0xA0,0xDF, \
0x08,0xEF,0xCC,0x85,0x3B,0xDA,0xE0,0x5C,0x1C, \
0x08,0xE7,0xE3,0x75,0xBB,0x39,0x22,0x4B,0xA8, \
0x08,0xEF,0xF9,0xCE,0xE0,0x5E,0xEB,0x1D,0xCB, \
0x08,0xE7,0xBD,0xE2,0x70,0xD5,0xAB,0x4E,0x3F, \
0x08,0xE7,0xB7,0x8D,0x20,0x68,0x6B,0x09,0x52, \
0x08,0xEF,0xA1,0x1B,0x90,0xCD,0x98,0x00,0x63, \
0x08,0xEF,0x54,0x67,0x5D,0x9C,0x11,0xFC,0x45, \
0x08,0xE7,0xD4,0x9B,0xC8,0x97,0xBE,0x8A,0x07, \
0x08,0xEF,0x52,0x8D,0x90,0x63,0x73,0xD5,0x2A, \
0x08,0xEF,0x03,0xBC,0x6E,0x1C,0x76,0xBE,0x4A, \
0x08,0xE7,0xC2,0xED,0x67,0xBA,0x5E,0x66,0x21, \
0x08,0xEF,0xE7,0x3F,0x87,0xBE,0xE0,0x7A,0x6D, \
0x08,0xE7,0xC9,0x70,0x93,0x1D,0x64,0xF5,0x6C, \
0x08,0xEF,0xF5,0x28,0x08,0x34,0xB3,0xB6,0x2C, \
0x08,0xEF,0x3A,0x0A,0xEC,0x0F,0xDB,0x56,0xCA, \
0x08,0xEF,0x39,0xA0,0x6E,0xED,0x79,0xD0,0x24, \
0x08,0xE7,0x6C,0x0B,0xAF,0xA9,0x4E,0x40,0xB5, \
0x08,0xE9,0xB9,0xAF,0xBF,0x25,0x50,0xD1,0x37, \
0x08,0x05,0x9E,0xDB,0xDE,0x3F,0x94,0xE9,0x6B, \
0x08,0xEC,0xC5,0x05,0xAA,0x57,0xDC,0x8A,0x5E, \
0x08,0x05,0x70,0xDA,0x84,0x84,0xDD,0xCA,0x90



#define RF_POWER_UP 0x02, 0x81, 0x00, 0x01, 0xC9, 0xC3, 0x80
#define RF_GPIO_PIN_CFG 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#define RF_GLOBAL_XO_TUNE_2 0x11, 0x00, 0x02, 0x00, 0x52, 0x00
#define RF_GLOBAL_CONFIG_1 0x11, 0x00, 0x01, 0x03, 0x20
#define RF_INT_CTL_ENABLE_2 0x11, 0x01, 0x02, 0x00, 0x01, 0x20
#define RF_FRR_CTL_A_MODE_4 0x11, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00
#define RF_PREAMBLE_TX_LENGTH_9 0x11, 0x10, 0x09, 0x00, 0x08, 0x14, 0x00, 0x0F, 0x31, 0x00, 0x00, 0x00, 0x00
#define RF_SYNC_CONFIG_6 0x11, 0x11, 0x06, 0x00, 0x01, 0xB4, 0x2B, 0x00, 0x00, 0x00
#define RF_PKT_CRC_CONFIG_12 0x11, 0x12, 0x0C, 0x00, 0x05, 0x01, 0x08, 0xFF, 0xFF, 0x20, 0x02, 0x00, 0x00, 0x00, 0x00, 0x30
#define RF_PKT_FIELD_3_CRC_CONFIG_12 0x11, 0x12, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#define RF_PKT_RX_FIELD_1_CRC_CONFIG_12 0x11, 0x12, 0x0C, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#define RF_PKT_RX_FIELD_4_CRC_CONFIG_5 0x11, 0x12, 0x05, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00
#define RF_MODEM_MOD_TYPE_12 0x11, 0x20, 0x0C, 0x00, 0x02, 0x00, 0x07, 0x01, 0x86, 0xA0, 0x01, 0xC9, 0xC3, 0x80, 0x00, 0x05
#define RF_MODEM_FREQ_DEV_0_1 0x11, 0x20, 0x01, 0x0C, 0x76
#define RF_MODEM_TX_RAMP_DELAY_12 0x11, 0x20, 0x0C, 0x18, 0x01, 0x80, 0x08, 0x03, 0x80, 0x00, 0x20, 0x20, 0x00, 0xE8, 0x01, 0x77
#define RF_MODEM_BCR_NCO_OFFSET_2_12 0x11, 0x20, 0x0C, 0x24, 0x01, 0x5D, 0x86, 0x00, 0xAF, 0x02, 0xC2, 0x00, 0x04, 0x23, 0x80, 0x1D
#define RF_MODEM_AFC_LIMITER_1_3 0x11, 0x20, 0x03, 0x30, 0x10, 0x04, 0x80
#define RF_MODEM_AGC_CONTROL_1 0x11, 0x20, 0x01, 0x35, 0xE0
#define RF_MODEM_AGC_WINDOW_SIZE_3 0x11, 0x20, 0x03, 0x38, 0x11, 0x52, 0x52
#define RF_MODEM_OOK_PDTC_4 0x11, 0x20, 0x04, 0x40, 0x2A, 0x0C, 0xA4, 0x22
#define RF_MODEM_RAW_CONTROL_5 0x11, 0x20, 0x05, 0x45, 0x83, 0x01, 0x55, 0x01, 0x00
#define RF_MODEM_RSSI_JUMP_THRESH_1 0x11, 0x20, 0x01, 0x4B, 0x06
#define RF_MODEM_RSSI_CONTROL2_2 0x11, 0x20, 0x02, 0x4D, 0x18, 0x40
#define RF_MODEM_RAW_SEARCH2_2 0x11, 0x20, 0x02, 0x50, 0x84, 0x0A
#define RF_MODEM_SPIKE_DET_2 0x11, 0x20, 0x02, 0x54, 0x04, 0x07
#define RF_MODEM_RSSI_MUTE_1 0x11, 0x20, 0x01, 0x57, 0x00
#define RF_MODEM_DSA_CTRL1_5 0x11, 0x20, 0x05, 0x5B, 0x40, 0x04, 0x0B, 0x78, 0x20
#define RF_MODEM_CHFLT_RX1_CHFLT_COE13_7_0_12 0x11, 0x21, 0x0C, 0x00, 0xA2, 0x81, 0x26, 0xAF, 0x3F, 0xEE, 0xC8, 0xC7, 0xDB, 0xF2, 0x02, 0x08
#define RF_MODEM_CHFLT_RX1_CHFLT_COE1_7_0_12 0x11, 0x21, 0x0C, 0x0C, 0x07, 0x03, 0x15, 0xFC, 0x0F, 0x00, 0xA2, 0x81, 0x26, 0xAF, 0x3F, 0xEE
#define RF_MODEM_CHFLT_RX2_CHFLT_COE7_7_0_12 0x11, 0x21, 0x0C, 0x18, 0xC8, 0xC7, 0xDB, 0xF2, 0x02, 0x08, 0x07, 0x03, 0x15, 0xFC, 0x0F, 0x00
#define RF_PA_MODE_4 0x11, 0x22, 0x04, 0x00, 0x08, 0x7F, 0x00, 0x1D
#define RF_SYNTH_PFDCP_CPFF_7 0x11, 0x23, 0x07, 0x00, 0x2C, 0x0E, 0x0B, 0x04, 0x0C, 0x73, 0x03
#define RF_MATCH_VALUE_1_12 0x11, 0x30, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#define RF_FREQ_CONTROL_INTE_8 0x11, 0x40, 0x08, 0x00, 0x38, 0x0D, 0xDD, 0xDD, 0x44, 0x44, 0x20, 0xFE
#ifndef FIRMWARE_LOAD_COMPILE
#define RADIO_CONFIGURATION_DATA_ARRAY { \
        SI446X_PATCH_CMDS, \
        0x07, RF_POWER_UP, \
        0x08, RF_GPIO_PIN_CFG, \
        0x06, RF_GLOBAL_XO_TUNE_2, \
        0x05, RF_GLOBAL_CONFIG_1, \
        0x06, RF_INT_CTL_ENABLE_2, \
        0x08, RF_FRR_CTL_A_MODE_4, \
        0x0D, RF_PREAMBLE_TX_LENGTH_9, \
        0x0A, RF_SYNC_CONFIG_6, \
        0x10, RF_PKT_CRC_CONFIG_12, \
        0x10, RF_PKT_RX_THRESHOLD_12, \
        0x10, RF_PKT_FIELD_3_CRC_CONFIG_12, \
        0x10, RF_PKT_RX_FIELD_1_CRC_CONFIG_12, \
        0x09, RF_PKT_RX_FIELD_4_CRC_CONFIG_5, \
        0x10, RF_MODEM_MOD_TYPE_12, \
        0x05, RF_MODEM_FREQ_DEV_0_1, \
        0x10, RF_MODEM_TX_RAMP_DELAY_12, \
        0x10, RF_MODEM_BCR_NCO_OFFSET_2_12, \
        0x07, RF_MODEM_AFC_LIMITER_1_3, \
        0x05, RF_MODEM_AGC_CONTROL_1, \
        0x07, RF_MODEM_AGC_WINDOW_SIZE_3, \
        0x08, RF_MODEM_OOK_PDTC_4, \
        0x09, RF_MODEM_RAW_CONTROL_5, \
        0x05, RF_MODEM_RSSI_JUMP_THRESH_1, \
        0x06, RF_MODEM_RSSI_CONTROL2_2, \
        0x06, RF_MODEM_RAW_SEARCH2_2, \
        0x06, RF_MODEM_SPIKE_DET_2, \
        0x05, RF_MODEM_RSSI_MUTE_1, \
        0x09, RF_MODEM_DSA_CTRL1_5, \
        0x10, RF_MODEM_CHFLT_RX1_CHFLT_COE13_7_0_12, \
        0x10, RF_MODEM_CHFLT_RX1_CHFLT_COE1_7_0_12, \
        0x10, RF_MODEM_CHFLT_RX2_CHFLT_COE7_7_0_12, \
        0x08, RF_PA_MODE_4, \
        0x0B, RF_SYNTH_PFDCP_CPFF_7, \
        0x10, RF_MATCH_VALUE_1_12, \
        0x0C, RF_FREQ_CONTROL_INTE_8, \
        0x00 \
 }
#else
#define RADIO_CONFIGURATION_DATA_ARRAY { 0 }
#endif

// DEFAULT VALUES FOR CONFIGURATION PARAMETERS
#define RADIO_CONFIGURATION_DATA_RADIO_XO_FREQ_DEFAULT                     30000000L
#define RADIO_CONFIGURATION_DATA_CHANNEL_NUMBER_DEFAULT                    0x00
#define RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH_DEFAULT               0x10
#define RADIO_CONFIGURATION_DATA_RADIO_STATE_AFTER_POWER_UP_DEFAULT        0x01
#define RADIO_CONFIGURATION_DATA_RADIO_DELAY_CNT_AFTER_RESET_DEFAULT       0x1000
#define RADIO_CONFIGURATION_DATA_CUSTOM_PAYLOAD_DEFAULT					   {0x42, 0x55, 0x54, 0x54, 0x4F, 0x4E, 0x31} // BUTTON1 

#define RADIO_CONFIGURATION_DATA_RADIO_PATCH_INCLUDED                      0x00
#define RADIO_CONFIGURATION_DATA_RADIO_PATCH_SIZE                          0x00
#define RADIO_CONFIGURATION_DATA_RADIO_PATCH                               {  }

#ifndef RADIO_CONFIGURATION_DATA_ARRAY
#error "This property must be defined!"
#endif

#ifndef RADIO_CONFIGURATION_DATA_RADIO_XO_FREQ
#define RADIO_CONFIGURATION_DATA_RADIO_XO_FREQ          RADIO_CONFIGURATION_DATA_RADIO_XO_FREQ_DEFAULT 
#endif

#ifndef RADIO_CONFIGURATION_DATA_CHANNEL_NUMBER
#define RADIO_CONFIGURATION_DATA_CHANNEL_NUMBER         RADIO_CONFIGURATION_DATA_CHANNEL_NUMBER_DEFAULT 
#endif

#ifndef RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH
#define RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH    RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH_DEFAULT 
#endif

#ifndef RADIO_CONFIGURATION_DATA_RADIO_STATE_AFTER_POWER_UP
#define RADIO_CONFIGURATION_DATA_RADIO_STATE_AFTER_POWER_UP   RADIO_CONFIGURATION_DATA_RADIO_STATE_AFTER_POWER_UP_DEFAULT 
#endif

#ifndef RADIO_CONFIGURATION_DATA_RADIO_DELAY_CNT_AFTER_RESET
#define RADIO_CONFIGURATION_DATA_RADIO_DELAY_CNT_AFTER_RESET  RADIO_CONFIGURATION_DATA_RADIO_DELAY_CNT_AFTER_RESET_DEFAULT 
#endif

#ifndef RADIO_CONFIGURATION_DATA_CUSTOM_PAYLOAD
#define RADIO_CONFIGURATION_DATA_CUSTOM_PAYLOAD         RADIO_CONFIGURATION_DATA_CUSTOM_PAYLOAD_DEFAULT 
#endif

//#define RADIO_CONFIGURATION_DATA { \
//                            Radio_Configuration_Data_Array,                            \
//                            RADIO_CONFIGURATION_DATA_CHANNEL_NUMBER,                   \
//                            RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH,              \
//                            RADIO_CONFIGURATION_DATA_RADIO_STATE_AFTER_POWER_UP,       \
//                            RADIO_CONFIGURATION_DATA_RADIO_DELAY_CNT_AFTER_RESET,       \
//                            RADIO_CONFIGURATION_DATA_CUSTOM_PAYLOAD                   \
//                            }

#define RADIO_CTS_TIMEOUT 10000
#define SI446X_CMD_ID_POWER_UP 0x02
#define SI446X_CMD_ARG_COUNT_POWER_UP 7
#define SI446X_CMD_ID_GET_INT_STATUS 0x20
#define SI446X_CMD_ARG_COUNT_CHANGE_STATE 2
#define SI446X_CMD_ARG_COUNT_GET_INT_STATUS 4
#define SI446X_CMD_REPLY_COUNT_GET_INT_STATUS 8
#define SI446X_CMD_ID_PART_INFO 0x01
#define SI446X_CMD_ARG_COUNT_PART_INFO 1
#define SI446X_CMD_REPLY_COUNT_PART_INFO 8
#define SI446X_CMD_ID_START_TX 0x31
#define SI446X_CMD_ARG_COUNT_START_TX 7
#define SI446X_CMD_ID_START_RX 0x32
#define SI446X_CMD_ARG_COUNT_START_RX 8
#define SI446X_CMD_ID_GPIO_PIN_CFG 0x13
#define SI446X_CMD_ARG_COUNT_GPIO_PIN_CFG 8

#define SI446X_CMD_REPLY_COUNT_GPIO_PIN_CFG 7
#define SI446X_CMD_ID_SET_PROPERTY 0x11
#define SI446X_CMD_ID_CHANGE_STATE 0x34
#define RADIO_DRIVER_EXTENDED_SUPPORT
#define SI446X_CMD_ID_NOP 0x00
/* NOP ARGS */
#define SI446X_CMD_ARG_COUNT_NOP 1
#define SI446X_CMD_ID_FIFO_INFO 0x15
#define SI446X_CMD_ARG_COUNT_FIFO_INFO 2
#define SI446X_CMD_REPLY_COUNT_FIFO_INFO 2
#define SI446X_CMD_ID_WRITE_TX_FIFO 0x66
#define SI446X_CMD_ID_READ_RX_FIFO 0x77
#define SI446X_CMD_ID_GET_PROPERTY 0x12
#define SI446X_CMD_ARG_COUNT_GET_PROPERTY 4
enum
{
    SI446X_SUCCESS,
    SI446X_NO_PATCH,
    SI446X_CTS_TIMEOUT,
    SI446X_PATCH_FAIL,
    SI446X_COMMAND_ERROR
};

struct si446x_reply_GENERIC_map {
        uint8e_t  REPLY[16];
};

struct si446x_reply_PART_INFO_map {
        uint8e_t  CHIPREV;
        uint16e_t  PART;
        uint8e_t  PBUILD;
        uint16e_t  ID;
        uint8e_t  CUSTOMER;
        uint8e_t  ROMID;
};

struct si446x_reply_FUNC_INFO_map {
        uint8e_t  REVEXT;
        uint8e_t  REVBRANCH;
        uint8e_t  REVINT;
        uint8e_t  FUNC;
};

struct si446x_reply_GET_PROPERTY_map {
        uint8e_t  DATA[16];
};

struct si446x_reply_GPIO_PIN_CFG_map {
        uint8e_t  GPIO[4];
        uint8e_t  NIRQ;
        uint8e_t  SDO;
        uint8e_t  GEN_CONFIG;
};

struct si446x_reply_FIFO_INFO_map {
        uint8e_t  RX_FIFO_COUNT;
        uint8e_t  TX_FIFO_SPACE;
};

struct si446x_reply_GET_INT_STATUS_map {
        uint8e_t  INT_PEND;
        uint8e_t  INT_STATUS;
        uint8e_t  PH_PEND;
        uint8e_t  PH_STATUS;
        uint8e_t  MODEM_PEND;
        uint8e_t  MODEM_STATUS;
        uint8e_t  CHIP_PEND;
        uint8e_t  CHIP_STATUS;
};

struct si446x_reply_REQUEST_DEVICE_STATE_map {
        uint8e_t  CURR_STATE;
        uint8e_t  CURRENT_CHANNEL;
};

struct si446x_reply_READ_CMD_BUFF_map {
        uint8e_t  BYTE[16];
};

struct si446x_reply_FRR_A_READ_map {
        uint8e_t  FRR_A_VALUE;
        uint8e_t  FRR_B_VALUE;
        uint8e_t  FRR_C_VALUE;
        uint8e_t  FRR_D_VALUE;
};

struct si446x_reply_FRR_B_READ_map {
        uint8e_t  FRR_B_VALUE;
        uint8e_t  FRR_C_VALUE;
        uint8e_t  FRR_D_VALUE;
        uint8e_t  FRR_A_VALUE;
};

struct si446x_reply_FRR_C_READ_map {
        uint8e_t  FRR_C_VALUE;
        uint8e_t  FRR_D_VALUE;
        uint8e_t  FRR_A_VALUE;
        uint8e_t  FRR_B_VALUE;
};

struct si446x_reply_FRR_D_READ_map {
        uint8e_t  FRR_D_VALUE;
        uint8e_t  FRR_A_VALUE;
        uint8e_t  FRR_B_VALUE;
        uint8e_t  FRR_C_VALUE;
};

struct si446x_reply_IRCAL_MANUAL_map {
        uint8e_t  IRCAL_AMP_REPLY;
        uint8e_t  IRCAL_PH_REPLY;
};

struct si446x_reply_PACKET_INFO_map {
        uint16e_t  LENGTH;
};

struct si446x_reply_GET_MODEM_STATUS_map {
        uint8e_t  MODEM_PEND;
        uint8e_t  MODEM_STATUS;
        uint8e_t  CURR_RSSI;
        uint8e_t  LATCH_RSSI;
        uint8e_t  ANT1_RSSI;
        uint8e_t  ANT2_RSSI;
        uint16e_t  AFC_FREQ_OFFSET;
};

struct si446x_reply_READ_RX_FIFO_map {
        uint8e_t  DATA[2];
};

struct si446x_reply_GET_ADC_READING_map {
        uint16e_t  GPIO_ADC;
        uint16e_t  BATTERY_ADC;
        uint16e_t  TEMP_ADC;
};

struct si446x_reply_GET_PH_STATUS_map {
        uint8e_t  PH_PEND;
        uint8e_t  PH_STATUS;
};

struct si446x_reply_GET_CHIP_STATUS_map {
        uint8e_t  CHIP_PEND;
        uint8e_t  CHIP_STATUS;
        uint8e_t  CMD_ERR_STATUS;
        uint8e_t  CMD_ERR_CMD_ID;
};


/* The union that stores the reply written back to the host registers */
union si446x_cmd_reply_union {
        uint8e_t                                                               RAW[16];
        struct si446x_reply_GENERIC_map                                  GENERIC;
        struct si446x_reply_PART_INFO_map                                PART_INFO;
        struct si446x_reply_FUNC_INFO_map                                FUNC_INFO;
        struct si446x_reply_GET_PROPERTY_map                             GET_PROPERTY;
        struct si446x_reply_GPIO_PIN_CFG_map                             GPIO_PIN_CFG;
        struct si446x_reply_FIFO_INFO_map                                FIFO_INFO;
        struct si446x_reply_GET_INT_STATUS_map                           GET_INT_STATUS;
        struct si446x_reply_REQUEST_DEVICE_STATE_map                     REQUEST_DEVICE_STATE;
        struct si446x_reply_READ_CMD_BUFF_map                            READ_CMD_BUFF;
        struct si446x_reply_FRR_A_READ_map                               FRR_A_READ;
        struct si446x_reply_FRR_B_READ_map                               FRR_B_READ;
        struct si446x_reply_FRR_C_READ_map                               FRR_C_READ;
        struct si446x_reply_FRR_D_READ_map                               FRR_D_READ;
        struct si446x_reply_IRCAL_MANUAL_map                             IRCAL_MANUAL;
        struct si446x_reply_PACKET_INFO_map                              PACKET_INFO;
        struct si446x_reply_GET_MODEM_STATUS_map                         GET_MODEM_STATUS;
        struct si446x_reply_READ_RX_FIFO_map                             READ_RX_FIFO;
        struct si446x_reply_GET_ADC_READING_map                          GET_ADC_READING;
        struct si446x_reply_GET_PH_STATUS_map                            GET_PH_STATUS;
        struct si446x_reply_GET_CHIP_STATUS_map                          GET_CHIP_STATUS;
};

typedef struct
{
    uint8e_t   *Radio_ConfigurationArray;

    uint8e_t   Radio_ChannelNumber;
    uint8e_t   Radio_PacketLength;
    uint8e_t   Radio_State_After_Power_Up;

    uint16e_t  Radio_Delay_Cnt_After_Reset;

    uint8e_t   Radio_CustomPayload[64];
} tRadioConfiguration;

uint8e_t Pro2Cmd[16];
union si446x_cmd_reply_union Si446xCmd;

uint8e_t Radio_Configuration_Data_Array[] = RADIO_CONFIGURATION_DATA_ARRAY;
tRadioConfiguration  RadioConfiguration = RADIO_CONFIGURATION_DATA;
tRadioConfiguration  *pRadioConfiguration = &RadioConfiguration;

void radio_comm_SendCmd(uint8e_t byteCount, uint8e_t* pData)
{
    uint8e_t i;
//    while (!ctsWentHigh)
//    {
//        radio_comm_PollCTS();
//    }
    Ebyte_Port_SpiCsIoControl(0);
//    radio_hal_SpiWriteData(byteCount, pData);
    for( i=0 ; i<byteCount;i++)
    {
        Ebyte_Port_SpiTransmitAndReceivce( *pData++ );
    }

    Ebyte_Port_SpiCsIoControl(1);
//    ctsWentHigh = 0;
}

void si446x_reset(void)
{
//    uint8e_t loopCount;

    /* Put radio in shutdown, wait then release */
    Ebyte_Port_SdnIoControl(1);
    //! @todo this needs to be a better delay function.
//    for (loopCount = 255; loopCount != 0; loopCount--);
    Ebyte_Port_DelayMs(2);
    Ebyte_Port_SdnIoControl(0);
//    for (loopCount = 255; loopCount != 0; loopCount--);
    Ebyte_Port_DelayMs(5);
//    radio_comm_ClearCTS();
}

void si446x_power_up(uint8e_t BOOT_OPTIONS, uint8e_t XTAL_OPTIONS, uint32e_t XO_FREQ)
{
    Pro2Cmd[0] = SI446X_CMD_ID_POWER_UP;
    Pro2Cmd[1] = BOOT_OPTIONS;
    Pro2Cmd[2] = XTAL_OPTIONS;
    Pro2Cmd[3] = (uint8e_t)(XO_FREQ >> 24);
    Pro2Cmd[4] = (uint8e_t)(XO_FREQ >> 16);
    Pro2Cmd[5] = (uint8e_t)(XO_FREQ >> 8);
    Pro2Cmd[6] = (uint8e_t)(XO_FREQ);

    radio_comm_SendCmd( SI446X_CMD_ARG_COUNT_POWER_UP, Pro2Cmd );
}

uint8e_t radio_comm_GetResp(uint8e_t byteCount, uint8e_t* pData)
{
  uint8e_t  ctsVal = 0,i;
  uint16e_t errCnt = RADIO_CTS_TIMEOUT;
  while (errCnt != 0)      //wait until radio IC is ready with the data
  {
//    radio_hal_ClearNsel();
    Ebyte_Port_SpiCsIoControl(0);
//    radio_hal_SpiWriteByte(0x44);    //read CMD buffer
    Ebyte_Port_SpiTransmitAndReceivce(0x44);
//    ctsVal = radio_hal_SpiReadByte();
    ctsVal = Ebyte_Port_SpiTransmitAndReceivce(0xFF);
    if (ctsVal == 0xFF)
    {
      if (byteCount)
      {
//        radio_hal_SpiReadData(byteCount, pData);
        for( i=0 ; i<byteCount;i++)
        {
          Ebyte_Port_SpiTransmitAndReceivce( *pData++ );
        }
      }
//      radio_hal_SetNsel();
      Ebyte_Port_SpiCsIoControl(1);
      break;
    }
//    radio_hal_SetNsel();
    Ebyte_Port_SpiCsIoControl(1);
    errCnt--;
  }

  if (errCnt == 0)
  {
    while(1)
    {
      /* ERROR!!!!  CTS should never take this long. */
    }
  }

//  if (ctsVal == 0xFF)
//  {
//    ctsWentHigh = 1;
//  }

  return ctsVal;
}


uint8e_t radio_comm_SendCmdGetResp(uint8e_t cmdByteCount, uint8e_t* pCmdData, uint8e_t respByteCount, uint8e_t* pRespData)
{
    radio_comm_SendCmd(cmdByteCount, pCmdData);
    return radio_comm_GetResp(respByteCount, pRespData);
}

void si446x_get_int_status(uint8e_t PH_CLR_PEND, uint8e_t MODEM_CLR_PEND, uint8e_t CHIP_CLR_PEND)
{
    Pro2Cmd[0] = SI446X_CMD_ID_GET_INT_STATUS;
    Pro2Cmd[1] = PH_CLR_PEND;
    Pro2Cmd[2] = MODEM_CLR_PEND;
    Pro2Cmd[3] = CHIP_CLR_PEND;

    radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_GET_INT_STATUS,
                              Pro2Cmd,
                              SI446X_CMD_REPLY_COUNT_GET_INT_STATUS,
                              Pro2Cmd );

    Si446xCmd.GET_INT_STATUS.INT_PEND       = Pro2Cmd[0];
    Si446xCmd.GET_INT_STATUS.INT_STATUS     = Pro2Cmd[1];
    Si446xCmd.GET_INT_STATUS.PH_PEND        = Pro2Cmd[2];
    Si446xCmd.GET_INT_STATUS.PH_STATUS      = Pro2Cmd[3];
    Si446xCmd.GET_INT_STATUS.MODEM_PEND     = Pro2Cmd[4];
    Si446xCmd.GET_INT_STATUS.MODEM_STATUS   = Pro2Cmd[5];
    Si446xCmd.GET_INT_STATUS.CHIP_PEND      = Pro2Cmd[6];
    Si446xCmd.GET_INT_STATUS.CHIP_STATUS    = Pro2Cmd[7];
}

uint8e_t si446x_configuration_init(const uint8e_t* pSetPropCmd)
{
  uint8e_t col,numOfBytes;
  
  /* While cycle as far as the pointer points to a command */
  while (*pSetPropCmd != 0x00)
  {
    /* Commands structure in the array:
     * --------------------------------
     * LEN | <LEN length of data>
     */

    numOfBytes = *pSetPropCmd++;

    if (numOfBytes > 16u)
    {
      /* Number of command bytes exceeds maximal allowable length */
      return SI446X_COMMAND_ERROR;
    }

    for (col = 0u; col < numOfBytes; col++)
    {
      Pro2Cmd[col] = *pSetPropCmd;
      pSetPropCmd++;
    }

    if (radio_comm_SendCmdGetResp(numOfBytes, Pro2Cmd, 0, 0) != 0xFF)
    {
      /* Timeout occured */
      return SI446X_CTS_TIMEOUT;
    }

//    if (radio_hal_NirqLevel() == 0)
    
    if( Ebyte_Port_IrqIoRead()==0 )
    {
      /* Get and clear all interrupts.  An error has occured... */
      si446x_get_int_status(0, 0, 0);
//      if (Si446xCmd.GET_INT_STATUS.CHIP_PEND & SI446X_CMD_GET_CHIP_STATUS_REP_CHIP_PEND_CMD_ERROR_PEND_MASK)
      if (Si446xCmd.GET_INT_STATUS.CHIP_PEND & 0x08)
      {
        return SI446X_COMMAND_ERROR;
      }
    }
  }

  return SI446X_SUCCESS;
}

void si446x_part_info(void)
{
    Pro2Cmd[0] = SI446X_CMD_ID_PART_INFO;

    radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_PART_INFO,
                              Pro2Cmd,
                              SI446X_CMD_REPLY_COUNT_PART_INFO,
                              Pro2Cmd );

    Si446xCmd.PART_INFO.CHIPREV         = Pro2Cmd[0];
    Si446xCmd.PART_INFO.PART            = ((uint16e_t)Pro2Cmd[1] << 8) & 0xFF00;
    Si446xCmd.PART_INFO.PART           |= (uint16e_t)Pro2Cmd[2] & 0x00FF;
    Si446xCmd.PART_INFO.PBUILD          = Pro2Cmd[3];
    Si446xCmd.PART_INFO.ID              = ((uint16e_t)Pro2Cmd[4] << 8) & 0xFF00;
    Si446xCmd.PART_INFO.ID             |= (uint16e_t)Pro2Cmd[5] & 0x00FF;
    Si446xCmd.PART_INFO.CUSTOMER        = Pro2Cmd[6];
    Si446xCmd.PART_INFO.ROMID           = Pro2Cmd[7];
}

void si446x_start_tx(uint8e_t CHANNEL, uint8e_t CONDITION, uint16e_t TX_LEN)
{
    Pro2Cmd[0] = SI446X_CMD_ID_START_TX;
    Pro2Cmd[1] = CHANNEL;
    Pro2Cmd[2] = CONDITION;
    Pro2Cmd[3] = (uint8e_t)(TX_LEN >> 8);
    Pro2Cmd[4] = (uint8e_t)(TX_LEN);
    Pro2Cmd[5] = 0x00;

    // Don't repeat the packet, 
    // ie. transmit the packet only once
    Pro2Cmd[6] = 0x00;

    radio_comm_SendCmd( SI446X_CMD_ARG_COUNT_START_TX, Pro2Cmd );
}

void si446x_start_rx(uint8e_t CHANNEL, uint8e_t CONDITION, uint16e_t RX_LEN, uint8e_t NEXT_STATE1, uint8e_t NEXT_STATE2, uint8e_t NEXT_STATE3)
{
    Pro2Cmd[0] = SI446X_CMD_ID_START_RX;
    Pro2Cmd[1] = CHANNEL;
    Pro2Cmd[2] = CONDITION;
    Pro2Cmd[3] = (uint8e_t)(RX_LEN >> 8);
    Pro2Cmd[4] = (uint8e_t)(RX_LEN);
    Pro2Cmd[5] = NEXT_STATE1;
    Pro2Cmd[6] = NEXT_STATE2;
    Pro2Cmd[7] = NEXT_STATE3;

    radio_comm_SendCmd( SI446X_CMD_ARG_COUNT_START_RX, Pro2Cmd );
}



void si446x_gpio_pin_cfg(uint8e_t GPIO0, uint8e_t GPIO1, uint8e_t GPIO2, uint8e_t GPIO3, uint8e_t NIRQ, uint8e_t SDO, uint8e_t GEN_CONFIG)
{
    Pro2Cmd[0] = SI446X_CMD_ID_GPIO_PIN_CFG;
    Pro2Cmd[1] = GPIO0;
    Pro2Cmd[2] = GPIO1;
    Pro2Cmd[3] = GPIO2;
    Pro2Cmd[4] = GPIO3;
    Pro2Cmd[5] = NIRQ;
    Pro2Cmd[6] = SDO;
    Pro2Cmd[7] = GEN_CONFIG;

    radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_GPIO_PIN_CFG,
                              Pro2Cmd,
                              SI446X_CMD_REPLY_COUNT_GPIO_PIN_CFG,
                              Pro2Cmd );

    Si446xCmd.GPIO_PIN_CFG.GPIO[0]        = Pro2Cmd[0];
    Si446xCmd.GPIO_PIN_CFG.GPIO[1]        = Pro2Cmd[1];
    Si446xCmd.GPIO_PIN_CFG.GPIO[2]        = Pro2Cmd[2];
    Si446xCmd.GPIO_PIN_CFG.GPIO[3]        = Pro2Cmd[3];
    Si446xCmd.GPIO_PIN_CFG.NIRQ         = Pro2Cmd[4];
    Si446xCmd.GPIO_PIN_CFG.SDO          = Pro2Cmd[5];
    Si446xCmd.GPIO_PIN_CFG.GEN_CONFIG   = Pro2Cmd[6];
}


void si446x_set_property( uint8e_t GROUP, uint8e_t NUM_PROPS, uint8e_t START_PROP, ... )
{
    va_list argList;
    uint8e_t cmdIndex;

    Pro2Cmd[0] = SI446X_CMD_ID_SET_PROPERTY;
    Pro2Cmd[1] = GROUP;
    Pro2Cmd[2] = NUM_PROPS;
    Pro2Cmd[3] = START_PROP;

    va_start (argList, START_PROP);
    cmdIndex = 4;
    while(NUM_PROPS--)
    {
        Pro2Cmd[cmdIndex] = va_arg (argList, uint8e_t);
        cmdIndex++;
    }
    va_end(argList);

    radio_comm_SendCmd( cmdIndex, Pro2Cmd );
}

void si446x_change_state(uint8e_t NEXT_STATE1)
{
    Pro2Cmd[0] = SI446X_CMD_ID_CHANGE_STATE;
    Pro2Cmd[1] = NEXT_STATE1;

    radio_comm_SendCmd( SI446X_CMD_ARG_COUNT_CHANGE_STATE, Pro2Cmd );
}


#ifdef RADIO_DRIVER_EXTENDED_SUPPORT
void si446x_nop(void)
{
    Pro2Cmd[0] = SI446X_CMD_ID_NOP;

    radio_comm_SendCmd( SI446X_CMD_ARG_COUNT_NOP, Pro2Cmd );
}

void si446x_fifo_info(uint8e_t FIFO)
{
    Pro2Cmd[0] = SI446X_CMD_ID_FIFO_INFO;
    Pro2Cmd[1] = FIFO;

    radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_FIFO_INFO,
                              Pro2Cmd,
                              SI446X_CMD_REPLY_COUNT_FIFO_INFO,
                              Pro2Cmd );

    Si446xCmd.FIFO_INFO.RX_FIFO_COUNT   = Pro2Cmd[0];
    Si446xCmd.FIFO_INFO.TX_FIFO_SPACE   = Pro2Cmd[1];
}


void si446x_write_tx_fifo(uint8e_t numBytes, uint8e_t* pTxData)
{
//  radio_comm_WriteData( SI446X_CMD_ID_WRITE_TX_FIFO, 0, numBytes, pTxData );
    uint8e_t i;
    Ebyte_Port_SpiCsIoControl(0);
    Ebyte_Port_SpiTransmitAndReceivce(SI446X_CMD_ID_WRITE_TX_FIFO);
    for(i=0;i<numBytes;i++)
    {
       Ebyte_Port_SpiTransmitAndReceivce( *pTxData++ );
    }

    Ebyte_Port_SpiCsIoControl(1); 
}

void si446x_read_rx_fifo(uint8e_t numBytes, uint8e_t* pRxData)
{
//  radio_comm_ReadData( SI446X_CMD_ID_READ_RX_FIFO, 0, numBytes, pRxData );
    uint8e_t i;
    Ebyte_Port_SpiCsIoControl(0);
    Ebyte_Port_SpiTransmitAndReceivce(SI446X_CMD_ID_READ_RX_FIFO);
    for(i=0;i<numBytes;i++)
    {
       *pRxData++ = Ebyte_Port_SpiTransmitAndReceivce( 0xFF );
    }

    Ebyte_Port_SpiCsIoControl(1);
}

void si446x_get_property(uint8e_t GROUP, uint8e_t NUM_PROPS, uint8e_t START_PROP)
{
    Pro2Cmd[0] = SI446X_CMD_ID_GET_PROPERTY;
    Pro2Cmd[1] = GROUP;
    Pro2Cmd[2] = NUM_PROPS;
    Pro2Cmd[3] = START_PROP;

    radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_GET_PROPERTY,
                              Pro2Cmd,
                              Pro2Cmd[2],
                              Pro2Cmd );

    Si446xCmd.GET_PROPERTY.DATA[0 ]   = Pro2Cmd[0];
    Si446xCmd.GET_PROPERTY.DATA[1 ]   = Pro2Cmd[1];
    Si446xCmd.GET_PROPERTY.DATA[2 ]   = Pro2Cmd[2];
    Si446xCmd.GET_PROPERTY.DATA[3 ]   = Pro2Cmd[3];
    Si446xCmd.GET_PROPERTY.DATA[4 ]   = Pro2Cmd[4];
    Si446xCmd.GET_PROPERTY.DATA[5 ]   = Pro2Cmd[5];
    Si446xCmd.GET_PROPERTY.DATA[6 ]   = Pro2Cmd[6];
    Si446xCmd.GET_PROPERTY.DATA[7 ]   = Pro2Cmd[7];
    Si446xCmd.GET_PROPERTY.DATA[8 ]   = Pro2Cmd[8];
    Si446xCmd.GET_PROPERTY.DATA[9 ]   = Pro2Cmd[9];
    Si446xCmd.GET_PROPERTY.DATA[10]   = Pro2Cmd[10];
    Si446xCmd.GET_PROPERTY.DATA[11]   = Pro2Cmd[11];
    Si446xCmd.GET_PROPERTY.DATA[12]   = Pro2Cmd[12];
    Si446xCmd.GET_PROPERTY.DATA[13]   = Pro2Cmd[13];
    Si446xCmd.GET_PROPERTY.DATA[14]   = Pro2Cmd[14];
    Si446xCmd.GET_PROPERTY.DATA[15]   = Pro2Cmd[15];
}

#endif

void Ebyte_E10x_Init()
{
    si446x_reset();
    
  while (SI446X_SUCCESS != si446x_configuration_init(pRadioConfiguration->Radio_ConfigurationArray))
  {
      /* error */
  }    
  
  si446x_get_int_status(0u, 0u, 0u);
}

void Ebyte_E10x_SendPayload(uint8e_t *payload, uint8e_t size, uint32e_t timeout)
{
//  vRadio_StartTx(pRadioConfiguration->Radio_ChannelNumber, (U8 *) &pRadioConfiguration->Radio_CustomPayload[0u]);
  
  /* Reset TX FIFO */
//  si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_TX_BIT);
  si446x_fifo_info(0x01);
  // Read ITs, clear pending ones
  si446x_get_int_status(0u, 0u, 0u);

  /* Fill the TX fifo with datas */
  si446x_write_tx_fifo(size, payload);

  /* Start sending packet, channel 0, START immediately, Packet length according to PH, go READY when done */
  si446x_start_tx(pRadioConfiguration->Radio_ChannelNumber, 0x30,  0x00);
  
}

void Ebyte_E10x_SetRx( uint32e_t timeout )
{
   // Read ITs, clear pending ones
  si446x_get_int_status(0u, 0u, 0u);

  /* Start Receiving packet, channel 0, START immediately, Packet length according to PH */
//  si446x_start_rx(channel, 0u, 0x00,
//                  SI446X_CMD_START_RX_ARG_NEXT_STATE1_RXTIMEOUT_STATE_ENUM_NOCHANGE,
//                  SI446X_CMD_START_RX_ARG_NEXT_STATE2_RXVALID_STATE_ENUM_RX,
//                  SI446X_CMD_START_RX_ARG_NEXT_STATE3_RXINVALID_STATE_ENUM_RX ); 
    si446x_start_rx(pRadioConfiguration->Radio_ChannelNumber, 0u, 0x00,
                  0,
                  8,
                  8 ); 
}

/* !
 * @brief BBYTE 无线模块周期任务 
 *
 * @note 必须被客户周期性调用，否则无法接收到数据
 */
void Ebyte_E10x_IntOrPollTask( void )
{
    /* 读取内部状态 */

}