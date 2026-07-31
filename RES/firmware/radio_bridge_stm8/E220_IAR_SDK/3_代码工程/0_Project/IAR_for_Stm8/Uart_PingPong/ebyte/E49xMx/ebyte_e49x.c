#include "ebyte_e49x.h"
#define ENABLE_AUTO_SWITCH_CHIP_STATUS   /* Enable the auto switch chip status */
/* ---------- CMT bank defines ---------- */
#define CMT2300A_CMT_BANK_ADDR           0x00
#define CMT2300A_CMT_BANK_SIZE           12
#define CMT2300A_CUS_CMT1                0x00
#define CMT2300A_CUS_CMT2                0x01
#define CMT2300A_CUS_CMT3                0x02
#define CMT2300A_CUS_CMT4                0x03
#define CMT2300A_CUS_CMT5                0x04
#define CMT2300A_CUS_CMT6                0x05
#define CMT2300A_CUS_CMT7                0x06
#define CMT2300A_CUS_CMT8                0x07
#define CMT2300A_CUS_CMT9                0x08
#define CMT2300A_CUS_CMT10               0x09
#define CMT2300A_CUS_CMT11               0x0A
#define CMT2300A_CUS_RSSI                0x0B

/* ---------- System bank defines ---------- */
#define CMT2300A_SYSTEM_BANK_ADDR        0x0C
#define CMT2300A_SYSTEM_BANK_SIZE        12
#define CMT2300A_CUS_SYS1                0x0C
#define CMT2300A_CUS_SYS2                0x0D
#define CMT2300A_CUS_SYS3                0x0E
#define CMT2300A_CUS_SYS4                0x0F
#define CMT2300A_CUS_SYS5                0x10
#define CMT2300A_CUS_SYS6                0x11
#define CMT2300A_CUS_SYS7                0x12
#define CMT2300A_CUS_SYS8                0x13
#define CMT2300A_CUS_SYS9                0x14
#define CMT2300A_CUS_SYS10               0x15
#define CMT2300A_CUS_SYS11               0x16
#define CMT2300A_CUS_SYS12               0x17

/* ---------- Frequency bank defines ---------- */
#define CMT2300A_FREQUENCY_BANK_ADDR     0x18
#define CMT2300A_FREQUENCY_BANK_SIZE     8
#define CMT2300A_CUS_RF1                 0x18
#define CMT2300A_CUS_RF2                 0x19
#define CMT2300A_CUS_RF3                 0x1A
#define CMT2300A_CUS_RF4                 0x1B
#define CMT2300A_CUS_RF5                 0x1C
#define CMT2300A_CUS_RF6                 0x1D
#define CMT2300A_CUS_RF7                 0x1E
#define CMT2300A_CUS_RF8                 0x1F

/* ---------- Data rate bank defines ---------- */
#define CMT2300A_DATA_RATE_BANK_ADDR     0x20
#define CMT2300A_DATA_RATE_BANK_SIZE     24
#define CMT2300A_CUS_RF9                 0x20
#define CMT2300A_CUS_RF10                0x21
#define CMT2300A_CUS_RF11                0x22
#define CMT2300A_CUS_RF12                0x23
#define CMT2300A_CUS_FSK1                0x24
#define CMT2300A_CUS_FSK2                0x25
#define CMT2300A_CUS_FSK3                0x26
#define CMT2300A_CUS_FSK4                0x27
#define CMT2300A_CUS_FSK5                0x28
#define CMT2300A_CUS_FSK6                0x29
#define CMT2300A_CUS_FSK7                0x2A
#define CMT2300A_CUS_CDR1                0x2B
#define CMT2300A_CUS_CDR2                0x2C
#define CMT2300A_CUS_CDR3                0x2D
#define CMT2300A_CUS_CDR4                0x2E
#define CMT2300A_CUS_AGC1                0x2F
#define CMT2300A_CUS_AGC2                0x30
#define CMT2300A_CUS_AGC3                0x31
#define CMT2300A_CUS_AGC4                0x32
#define CMT2300A_CUS_OOK1                0x33
#define CMT2300A_CUS_OOK2                0x34
#define CMT2300A_CUS_OOK3                0x35
#define CMT2300A_CUS_OOK4                0x36
#define CMT2300A_CUS_OOK5                0x37

/* ---------- Baseband bank defines ---------- */
#define CMT2300A_BASEBAND_BANK_ADDR      0x38
#define CMT2300A_BASEBAND_BANK_SIZE      29
#define CMT2300A_CUS_PKT1                0x38
#define CMT2300A_CUS_PKT2                0x39
#define CMT2300A_CUS_PKT3                0x3A
#define CMT2300A_CUS_PKT4                0x3B
#define CMT2300A_CUS_PKT5                0x3C
#define CMT2300A_CUS_PKT6                0x3D
#define CMT2300A_CUS_PKT7                0x3E
#define CMT2300A_CUS_PKT8                0x3F
#define CMT2300A_CUS_PKT9                0x40
#define CMT2300A_CUS_PKT10               0x41
#define CMT2300A_CUS_PKT11               0x42
#define CMT2300A_CUS_PKT12               0x43
#define CMT2300A_CUS_PKT13               0x44
#define CMT2300A_CUS_PKT14               0x45
#define CMT2300A_CUS_PKT15               0x46
#define CMT2300A_CUS_PKT16               0x47
#define CMT2300A_CUS_PKT17               0x48
#define CMT2300A_CUS_PKT18               0x49
#define CMT2300A_CUS_PKT19               0x4A
#define CMT2300A_CUS_PKT20               0x4B
#define CMT2300A_CUS_PKT21               0x4C
#define CMT2300A_CUS_PKT22               0x4D
#define CMT2300A_CUS_PKT23               0x4E
#define CMT2300A_CUS_PKT24               0x4F
#define CMT2300A_CUS_PKT25               0x50
#define CMT2300A_CUS_PKT26               0x51
#define CMT2300A_CUS_PKT27               0x52
#define CMT2300A_CUS_PKT28               0x53
#define CMT2300A_CUS_PKT29               0x54

/* ---------- Tx bank defines ---------- */
#define CMT2300A_TX_BANK_ADDR            0x55
#define CMT2300A_TX_BANK_SIZE            11
#define CMT2300A_CUS_TX1                 0x55
#define CMT2300A_CUS_TX2                 0x56
#define CMT2300A_CUS_TX3                 0x57
#define CMT2300A_CUS_TX4                 0x58
#define CMT2300A_CUS_TX5                 0x59
#define CMT2300A_CUS_TX6                 0x5A
#define CMT2300A_CUS_TX7                 0x5B
#define CMT2300A_CUS_TX8                 0x5C
#define CMT2300A_CUS_TX9                 0x5D
#define CMT2300A_CUS_TX10                0x5E
#define CMT2300A_CUS_LBD                 0x5F

/* ---------- Control1 bank defines ---------- */
#define CMT2300A_CONTROL1_BANK_ADDR      0x60
#define CMT2300A_CONTROL1_BANK_SIZE      11
#define CMT2300A_CUS_MODE_CTL            0x60
#define CMT2300A_CUS_MODE_STA            0x61
#define CMT2300A_CUS_EN_CTL              0x62
#define CMT2300A_CUS_FREQ_CHNL           0x63
#define CMT2300A_CUS_FREQ_OFS            0x64
#define CMT2300A_CUS_IO_SEL              0x65
#define CMT2300A_CUS_INT1_CTL            0x66
#define CMT2300A_CUS_INT2_CTL            0x67
#define CMT2300A_CUS_INT_EN              0x68
#define CMT2300A_CUS_FIFO_CTL            0x69
#define CMT2300A_CUS_INT_CLR1            0x6A

/* ---------- Control2 bank defines ---------- */
#define CMT2300A_CONTROL2_BANK_ADDR      0x6B
#define CMT2300A_CONTROL2_BANK_SIZE      7
#define CMT2300A_CUS_INT_CLR2            0x6B
#define CMT2300A_CUS_FIFO_CLR            0x6C
#define CMT2300A_CUS_INT_FLAG            0x6D
#define CMT2300A_CUS_FIFO_FLAG           0x6E
#define CMT2300A_CUS_RSSI_CODE           0x6F
#define CMT2300A_CUS_RSSI_DBM            0x70
#define CMT2300A_CUS_LBD_RESULT          0x71


/* ********** CMT2300A_CUS_CMT2 registers ********** */
#define CMT2300A_MASK_PRODUCT_ID         0xFF

/* ********** CMT2300A_CUS_CMT5 registers ********** */
#define CMT2300A_MASK_LMT_CODE           0xC0

/* ********** CMT2300A_CUS_CMT9 registers ********** */
#define CMT2300A_MASK_RSSI_OFFSET_SIGN   0x80
#define CMT2300A_MASK_DIG_CLKDIV         0x1F

/* ********** CMT2300A_CUS_RSSI registers ********** */
#define CMT2300A_MASK_RSSI_OFFSET        0xF8
#define CMT2300A_MASK_RSSI_SLOPE         0x07

/* ********** CMT2300A_CUS_SYS1 registers ********** */
#define CMT2300A_MASK_LMT_VTR            0xC0
#define CMT2300A_MASK_MIXER_BIAS         0x30
#define CMT2300A_MASK_LNA_MODE           0x0C
#define CMT2300A_MASK_LNA_BIAS           0x03

/* ********** CMT2300A_CUS_SYS2 registers ********** */
#define CMT2300A_MASK_LFOSC_RECAL_EN     0x80
#define CMT2300A_MASK_LFOSC_CAL1_EN      0x40
#define CMT2300A_MASK_LFOSC_CAL2_EN      0x20
#define CMT2300A_MASK_RX_TIMER_EN        0x10
#define CMT2300A_MASK_SLEEP_TIMER_EN     0x08
#define CMT2300A_MASK_TX_DC_EN           0x04
#define CMT2300A_MASK_RX_DC_EN           0x02
#define CMT2300A_MASK_DC_PAUSE           0x01

/* ********** CMT2300A_CUS_SYS3 registers ********** */
#define CMT2300A_MASK_SLEEP_BYPASS_EN    0x80
#define CMT2300A_MASK_XTAL_STB_TIME      0x70
#define CMT2300A_MASK_TX_EXIT_STATE      0x0C
#define CMT2300A_MASK_RX_EXIT_STATE      0x03

/* ********** CMT2300A_CUS_SYS4 registers ********** */
#define CMT2300A_MASK_SLEEP_TIMER_M_7_0  0xFF

/* ********** CMT2300A_CUS_SYS5 registers ********** */
#define CMT2300A_MASK_SLEEP_TIMER_M_10_8 0x70
#define CMT2300A_MASK_SLEEP_TIMER_R      0x0F

/* ********** CMT2300A_CUS_SYS6 registers ********** */
#define CMT2300A_MASK_RX_TIMER_T1_M_7_0  0xFF

/* ********** CMT2300A_CUS_SYS7 registers ********** */
#define CMT2300A_MASK_RX_TIMER_T1_M_10_8 0x70
#define CMT2300A_MASK_RX_TIMER_T1_R      0x0F

/* ********** CMT2300A_CUS_SYS8 registers ********** */
#define CMT2300A_MASK_RX_TIMER_T2_M_7_0  0xFF

/* ********** CMT2300A_CUS_SYS9 registers ********** */
#define CMT2300A_MASK_RX_TIMER_T2_M_10_8 0x70
#define CMT2300A_MASK_RX_TIMER_T2_R      0x0F

/* ********** CMT2300A_CUS_SYS10 registers ********** */
#define CMT2300A_MASK_COL_DET_EN         0x80
#define CMT2300A_MASK_COL_OFS_SEL        0x40
#define CMT2300A_MASK_RX_AUTO_EXIT_DIS   0x20
#define CMT2300A_MASK_DOUT_MUTE          0x10
#define CMT2300A_MASK_RX_EXTEND_MODE     0x0F

/* ********** CMT2300A_CUS_SYS11 registers ********** */
#define CMT2300A_MASK_PJD_TH_SEL         0x80
#define CMT2300A_MASK_CCA_INT_SEL        0x60
#define CMT2300A_MASK_RSSI_DET_SEL       0x18
#define CMT2300A_MASK_RSSI_AVG_MODE      0x07

/* ********** CMT2300A_CUS_SYS12 registers ********** */
#define CMT2300A_MASK_PJD_WIN_SEL        0xC0
#define CMT2300A_MASK_CLKOUT_EN          0x20
#define CMT2300A_MASK_CLKOUT_DIV         0x1F

/* ********** CMT2300A_CUS_RF1 registers ********** */
#define CMT2300A_MASK_FREQ_RX_N          0xFF

/* ********** CMT2300A_CUS_RF2 registers ********** */
#define CMT2300A_MASK_FREQ_RX_K_7_0      0xFF

/* ********** CMT2300A_CUS_RF3 registers ********** */
#define CMT2300A_MASK_FREQ_RX_K_15_8     0xFF

/* ********** CMT2300A_CUS_RF4 registers ********** */
#define CMT2300A_MASK_FREQ_PALDO_SEL     0x80
#define CMT2300A_MASK_FREQ_DIVX_CODE     0x70
#define CMT2300A_MASK_FREQ_RX_K_19_16    0x0F

/* ********** CMT2300A_CUS_RF5 registers ********** */
#define CMT2300A_MASK_FREQ_TX_N          0xFF

/* ********** CMT2300A_CUS_RF6 registers ********** */
#define CMT2300A_MASK_FREQ_TX_K_7_0      0xFF

/* ********** CMT2300A_CUS_RF7 registers ********** */
#define CMT2300A_MASK_FREQ_TX_K_15_8     0xFF

/* ********** CMT2300A_CUS_RF8 registers ********** */
#define CMT2300A_MASK_FSK_SWT            0x80
#define CMT2300A_MASK_FREQ_VCO_BANK      0x70
#define CMT2300A_MASK_FREQ_TX_K_19_16    0x0F

/* ********** CMT2300A_CUS_PKT1 registers ********** */
#define CMT2300A_MASK_RX_PREAM_SIZE      0xF8
#define CMT2300A_MASK_PREAM_LENG_UNIT    0x04
#define CMT2300A_MASK_DATA_MODE          0x03
/* CMT2300A_MASK_PREAM_LENG_UNIT options */
#define CMT2300A_PREAM_LENG_UNIT_8_BITS  0x00
#define CMT2300A_PREAM_LENG_UNIT_4_BITS  0x04
/* CMT2300A_MASK_DATA_MODE options */
#define CMT2300A_DATA_MODE_DIRECT        0x00
#define CMT2300A_DATA_MODE_PACKET        0x02

/* ********** CMT2300A_CUS_PKT2 registers ********** */
#define CMT2300A_MASK_TX_PREAM_SIZE_7_0  0xFF

/* ********** CMT2300A_CUS_PKT3 registers ********** */
#define CMT2300A_MASK_TX_PREAM_SIZE_15_8 0xFF

/* ********** CMT2300A_CUS_PKT4 registers ********** */
#define CMT2300A_MASK_PREAM_VALUE        0xFF

/* ********** CMT2300A_CUS_PKT5 registers ********** */
#define CMT2300A_MASK_SYNC_TOL           0x70
#define CMT2300A_MASK_SYNC_SIZE          0x0E
#define CMT2300A_MASK_SYNC_MAN_EN        0x01

/* ********** CMT2300A_CUS_PKT6 registers ********** */
#define CMT2300A_MASK_SYNC_VALUE_7_0     0xFF

/* ********** CMT2300A_CUS_PKT7 registers ********** */
#define CMT2300A_MASK_SYNC_VALUE_15_8    0xFF

/* ********** CMT2300A_CUS_PKT8 registers ********** */
#define CMT2300A_MASK_SYNC_VALUE_23_16   0xFF

/* ********** CMT2300A_CUS_PKT9 registers ********** */
#define CMT2300A_MASK_SYNC_VALUE_31_24   0xFF

/* ********** CMT2300A_CUS_PKT10 registers ********** */
#define CMT2300A_MASK_SYNC_VALUE_39_32   0xFF

/* ********** CMT2300A_CUS_PKT11 registers ********** */
#define CMT2300A_MASK_SYNC_VALUE_47_40   0xFF

/* ********** CMT2300A_CUS_PKT12 registers ********** */
#define CMT2300A_MASK_SYNC_VALUE_55_48   0xFF

/* ********** CMT2300A_CUS_PKT13 registers ********** */
#define CMT2300A_MASK_SYNC_VALUE_63_56   0xFF

/* ********** CMT2300A_CUS_PKT14 registers ********** */
#define CMT2300A_MASK_PAYLOAD_LENG_10_8  0x70
#define CMT2300A_MASK_AUTO_ACK_EN        0x08
#define CMT2300A_MASK_NODE_LENG_POS_SEL  0x04
#define CMT2300A_MASK_PAYLOAD_BIT_ORDER  0x02
#define CMT2300A_MASK_PKT_TYPE           0x01
/* CMT2300A_MASK_NODE_LENG_POS_SEL options */
#define CMT2300A_NODE_LENG_FIRST_NODE    0x00
#define CMT2300A_NODE_LENG_FIRST_LENGTH  0x04
/* CMT2300A_MASK_PAYLOAD_BIT_ORDER options */
#define CMT2300A_PAYLOAD_BIT_ORDER_MSB   0x00
#define CMT2300A_PAYLOAD_BIT_ORDER_LSB   0x02
/* CMT2300A_MASK_PKT_TYPE options */
#define CMT2300A_PKT_TYPE_FIXED          0x00
#define CMT2300A_PKT_TYPE_VARIABLE       0x01

/* ********** CMT2300A_CUS_PKT15 registers ********** */
#define CMT2300A_MASK_PAYLOAD_LENG_7_0   0xFF

/* ********** CMT2300A_CUS_PKT16 registers ********** */
#define CMT2300A_MASK_NODE_FREE_EN       0x20
#define CMT2300A_MASK_NODE_ERR_MASK      0x10
#define CMT2300A_MASK_NODE_SIZE          0x0C
#define CMT2300A_MASK_NODE_DET_MODE      0x03
/* CMT2300A_MASK_NODE_DET_MODE options */
#define CMT2300A_NODE_DET_NODE           0x00
#define CMT2300A_NODE_DET_VALUE          0x01
#define CMT2300A_NODE_DET_VALUE_0        0x02
#define CMT2300A_NODE_DET_VALUE_0_1      0x03

/* ********** CMT2300A_CUS_PKT17 registers ********** */
#define CMT2300A_MASK_NODE_VALUE_7_0     0xFF

/* ********** CMT2300A_CUS_PKT18 registers ********** */
#define CMT2300A_MASK_NODE_VALUE_15_8    0xFF

/* ********** CMT2300A_CUS_PKT19 registers ********** */
#define CMT2300A_MASK_NODE_VALUE_23_16   0xFF

/* ********** CMT2300A_CUS_PKT20 registers ********** */
#define CMT2300A_MASK_NODE_VALUE_31_24   0xFF

/* ********** CMT2300A_CUS_PKT21 registers ********** */
#define CMT2300A_MASK_FEC_TYPE           0x80
#define CMT2300A_MASK_FEC_EN             0x40
#define CMT2300A_MASK_CRC_BYTE_SWAP      0x20
#define CMT2300A_MASK_CRC_BIT_INV        0x10
#define CMT2300A_MASK_CRC_RANGE          0x08
#define CMT2300A_MASK_CRC_TYPE           0x06
#define CMT2300A_MASK_CRC_EN             0x01
/* CMT2300A_MASK_CRC_BYTE_SWAP options */
#define CMT2300A_CRC_ORDER_HBYTE         0x00
#define CMT2300A_CRC_ORDER_LBYTE         0x20
/* CMT2300A_MASK_CRC_RANGE options */
#define CMT2300A_CRC_RANGE_PAYLOAD       0x00
#define CMT2300A_CRC_RANGE_DATA          0x08
/* CMT2300A_MASK_CRC_TYPE options */
#define CMT2300A_CRC_TYPE_CCITT16        0x00
#define CMT2300A_CRC_TYPE_IBM16          0x02
#define CMT2300A_CRC_TYPE_ITU16          0x04

/* ********** CMT2300A_CUS_PKT22 registers ********** */
#define CMT2300A_MASK_CRC_SEED_7_0       0xFF

/* ********** CMT2300A_CUS_PKT23 registers ********** */
#define CMT2300A_MASK_CRC_SEED_15_8      0xFF

/* ********** CMT2300A_CUS_PKT24 registers ********** */
#define CMT2300A_MASK_CRC_BIT_ORDER      0x80
#define CMT2300A_MASK_WHITEN_SEED_8_8    0x40
#define CMT2300A_MASK_WHITEN_SEED_TYPE   0x20
#define CMT2300A_MASK_WHITEN_TYPE        0x18
#define CMT2300A_MASK_WHITEN_EN          0x04
#define CMT2300A_MASK_MANCH_TYPE         0x02
#define CMT2300A_MASK_MANCH_EN           0x01
/* CMT2300A_MASK_CRC_BIT_ORDER options */
#define CMT2300A_CRC_BIT_ORDER_MSB       0x00
#define CMT2300A_CRC_BIT_ORDER_LSB       0x80
/* CMT2300A_MASK_WHITEN_SEED_TYPE options */
#define CMT2300A_WHITEN_SEED_TYPE_1      0x00
#define CMT2300A_WHITEN_SEED_TYPE_2      0x20
/* CMT2300A_MASK_WHITEN_TYPE options */
#define CMT2300A_WHITEN_TYPE_PN9_CCITT   0x00
#define CMT2300A_WHITEN_TYPE_PN9_IBM     0x08
#define CMT2300A_WHITEN_TYPE_PN7         0x10
/* CMT2300A_MASK_MANCH_TYPE options */
#define CMT2300A_MANCH_TYPE_ONE_01       0x00
#define CMT2300A_MANCH_TYPE_ONE_10       0x02

/* ********** CMT2300A_CUS_PKT25 registers ********** */
#define CMT2300A_MASK_WHITEN_SEED_7_0    0xFF

/* ********** CMT2300A_CUS_PKT26 registers ********** */
#define CMT2300A_MASK_TX_PREFIX_TYPE     0x03

/* ********** CMT2300A_CUS_PKT27 registers ********** */
#define CMT2300A_MASK_TX_PKT_NUM         0xFF

/* ********** CMT2300A_CUS_PKT28 registers ********** */
#define CMT2300A_MASK_TX_PKT_GAP         0xFF

/* ********** CMT2300A_CUS_PKT29 registers ********** */
#define CMT2300A_MASK_FIFO_AUTO_RES_EN   0x80
#define CMT2300A_MASK_FIFO_TH            0x7F

/* ********** CMT2300A_CUS_MODE_CTL registers ********** */
#define CMT2300A_MASK_CHIP_MODE_SWT      0xFF
/* CMT2300A_MASK_CHIP_MODE_SWT options */
#define CMT2300A_GO_EEPROM               0x01
#define CMT2300A_GO_STBY                 0x02
#define CMT2300A_GO_RFS                  0x04
#define CMT2300A_GO_RX                   0x08
#define CMT2300A_GO_SLEEP                0x10
#define CMT2300A_GO_TFS                  0x20
#define CMT2300A_GO_TX                   0x40
#define CMT2300A_GO_SWITCH               0x80

/* ********** CMT2300A_CUS_MODE_STA registers ********** */
#define CMT2300A_MASK_RSTN_IN_EN         0x20
#define CMT2300A_MASK_CFG_RETAIN         0x10
#define CMT2300A_MASK_CHIP_MODE_STA      0x0F
/* CMT2300A_MASK_CHIP_MODE_STA options */
#define CMT2300A_STA_IDLE                0x00
#define CMT2300A_STA_SLEEP               0x01
#define CMT2300A_STA_STBY                0x02
#define CMT2300A_STA_RFS                 0x03
#define CMT2300A_STA_TFS                 0x04
#define CMT2300A_STA_RX                  0x05
#define CMT2300A_STA_TX                  0x06
#define CMT2300A_STA_EEPROM              0x07
#define CMT2300A_STA_ERROR               0x08
#define CMT2300A_STA_CAL                 0x09

/* ********** CMT2300A_CUS_EN_CTL registers ********** */
#define CMT2300A_MASK_LOCKING_EN         0x20

/* ********** CMT2300A_CUS_FREQ_CHNL registers ********** */
#define CMT2300A_MASK_FH_CHANNEL         0xFF

/* ********** CMT2300A_CUS_FREQ_OFS registers ********** */
#define CMT2300A_MASK_FH_OFFSET          0xFF

/* ********** CMT2300A_CUS_IO_SEL registers ********** */
#define CMT2300A_MASK_GPIO4_SEL          0xC0
#define CMT2300A_MASK_GPIO3_SEL          0x30
#define CMT2300A_MASK_GPIO2_SEL          0x0C
#define CMT2300A_MASK_GPIO1_SEL          0x03
/* CMT2300A_MASK_GPIO4_SEL options */
#define CMT2300A_GPIO4_SEL_RSTIN         0x00
#define CMT2300A_GPIO4_SEL_INT1          0x40
#define CMT2300A_GPIO4_SEL_DOUT          0x80
#define CMT2300A_GPIO4_SEL_DCLK          0xC0
/* CMT2300A_MASK_GPIO3_SEL options */
#define CMT2300A_GPIO3_SEL_CLKO          0x00
#define CMT2300A_GPIO3_SEL_DOUT          0x10
#define CMT2300A_GPIO3_SEL_DIN           0x10
#define CMT2300A_GPIO3_SEL_INT2          0x20
#define CMT2300A_GPIO3_SEL_DCLK          0x30
/* CMT2300A_MASK_GPIO2_SEL options */
#define CMT2300A_GPIO2_SEL_INT1          0x00
#define CMT2300A_GPIO2_SEL_INT2          0x04
#define CMT2300A_GPIO2_SEL_DOUT          0x08
#define CMT2300A_GPIO2_SEL_DIN           0x08
#define CMT2300A_GPIO2_SEL_DCLK          0x0C
/* CMT2300A_MASK_GPIO1_SEL options */
#define CMT2300A_GPIO1_SEL_DOUT          0x00
#define CMT2300A_GPIO1_SEL_DIN           0x00
#define CMT2300A_GPIO1_SEL_INT1          0x01
#define CMT2300A_GPIO1_SEL_INT2          0x02
#define CMT2300A_GPIO1_SEL_DCLK          0x03

/* ********** CMT2300A_CUS_INT1_CTL registers ********** */
#define CMT2300A_MASK_RF_SWT1_EN         0x80
#define CMT2300A_MASK_RF_SWT2_EN         0x40
#define CMT2300A_MASK_INT_POLAR          0x20
#define CMT2300A_MASK_INT1_SEL           0x1F
/* CMT2300A_MASK_INT_POLAR options */
#define CMT2300A_INT_POLAR_SEL_0         0x00
#define CMT2300A_INT_POLAR_SEL_1         0x20
/* CMT2300A_MASK_INT1_SEL options */
#define CMT2300A_INT_SEL_RX_ACTIVE       0x00
#define CMT2300A_INT_SEL_TX_ACTIVE       0x01
#define CMT2300A_INT_SEL_RSSI_VLD        0x02
#define CMT2300A_INT_SEL_PREAM_OK        0x03
#define CMT2300A_INT_SEL_SYNC_OK         0x04
#define CMT2300A_INT_SEL_NODE_OK         0x05
#define CMT2300A_INT_SEL_CRC_OK          0x06
#define CMT2300A_INT_SEL_PKT_OK          0x07
#define CMT2300A_INT_SEL_SL_TMO          0x08
#define CMT2300A_INT_SEL_RX_TMO          0x09
#define CMT2300A_INT_SEL_TX_DONE         0x0A
#define CMT2300A_INT_SEL_RX_FIFO_NMTY    0x0B
#define CMT2300A_INT_SEL_RX_FIFO_TH      0x0C
#define CMT2300A_INT_SEL_RX_FIFO_FULL    0x0D
#define CMT2300A_INT_SEL_RX_FIFO_WBYTE   0x0E
#define CMT2300A_INT_SEL_RX_FIFO_OVF     0x0F
#define CMT2300A_INT_SEL_TX_FIFO_NMTY    0x10
#define CMT2300A_INT_SEL_TX_FIFO_TH      0x11
#define CMT2300A_INT_SEL_TX_FIFO_FULL    0x12
#define CMT2300A_INT_SEL_STATE_IS_STBY   0x13
#define CMT2300A_INT_SEL_STATE_IS_FS     0x14
#define CMT2300A_INT_SEL_STATE_IS_RX     0x15
#define CMT2300A_INT_SEL_STATE_IS_TX     0x16
#define CMT2300A_INT_SEL_LED             0x17
#define CMT2300A_INT_SEL_TRX_ACTIVE      0x18
#define CMT2300A_INT_SEL_PKT_DONE        0x19

/* ********** CMT2300A_CUS_INT2_CTL registers ********** */
#define CMT2300A_MASK_LFOSC_OUT_EN       0x40
#define CMT2300A_MASK_TX_DIN_INV         0x20
#define CMT2300A_MASK_INT2_SEL           0x1F

/* ********** CMT2300A_CUS_INT_EN registers ********** */
#define CMT2300A_MASK_SL_TMO_EN          0x80
#define CMT2300A_MASK_RX_TMO_EN          0x40
#define CMT2300A_MASK_TX_DONE_EN         0x20
#define CMT2300A_MASK_PREAM_OK_EN        0x10
#define CMT2300A_MASK_SYNC_OK_EN         0x08
#define CMT2300A_MASK_NODE_OK_EN         0x04
#define CMT2300A_MASK_CRC_OK_EN          0x02
#define CMT2300A_MASK_PKT_DONE_EN        0x01

/* ********** CMT2300A_CUS_FIFO_CTL registers ********** */
#define CMT2300A_MASK_TX_DIN_EN          0x80
#define CMT2300A_MASK_TX_DIN_SEL         0x60
#define CMT2300A_MASK_FIFO_AUTO_CLR_DIS  0x10
#define CMT2300A_MASK_FIFO_TX_RD_EN      0x08
#define CMT2300A_MASK_FIFO_RX_TX_SEL     0x04
#define CMT2300A_MASK_FIFO_MERGE_EN      0x02
#define CMT2300A_MASK_SPI_FIFO_RD_WR_SEL 0x01
/* CMT2300A_MASK_TX_DIN_SEL options */
#define CMT2300A_TX_DIN_SEL_GPIO1        0x00
#define CMT2300A_TX_DIN_SEL_GPIO2        0x20
#define CMT2300A_TX_DIN_SEL_GPIO3        0x40

/* ********** CMT2300A_CUS_INT_CLR1 registers ********** */
#define CMT2300A_MASK_SL_TMO_FLG         0x20
#define CMT2300A_MASK_RX_TMO_FLG         0x10
#define CMT2300A_MASK_TX_DONE_FLG        0x08
#define CMT2300A_MASK_TX_DONE_CLR        0x04
#define CMT2300A_MASK_SL_TMO_CLR         0x02
#define CMT2300A_MASK_RX_TMO_CLR         0x01

/* ********** CMT2300A_CUS_INT_CLR2 registers ********** */
#define CMT2300A_MASK_LBD_CLR            0x20
#define CMT2300A_MASK_PREAM_OK_CLR       0x10
#define CMT2300A_MASK_SYNC_OK_CLR        0x08
#define CMT2300A_MASK_NODE_OK_CLR        0x04
#define CMT2300A_MASK_CRC_OK_CLR         0x02
#define CMT2300A_MASK_PKT_DONE_CLR       0x01

/* ********** CMT2300A_CUS_FIFO_CLR registers ********** */
#define CMT2300A_MASK_FIFO_RESTORE       0x04
#define CMT2300A_MASK_FIFO_CLR_RX        0x02
#define CMT2300A_MASK_FIFO_CLR_TX        0x01

/* ********** CMT2300A_CUS_INT_FLAG registers ********** */
#define CMT2300A_MASK_LBD_FLG            0x80
#define CMT2300A_MASK_COL_ERR_FLG        0x40
#define CMT2300A_MASK_PKT_ERR_FLG        0x20
#define CMT2300A_MASK_PREAM_OK_FLG       0x10
#define CMT2300A_MASK_SYNC_OK_FLG        0x08
#define CMT2300A_MASK_NODE_OK_FLG        0x04
#define CMT2300A_MASK_CRC_OK_FLG         0x02
#define CMT2300A_MASK_PKT_OK_FLG         0x01

/* ********** CMT2300A_CUS_FIFO_FLAG registers ********** */
#define CMT2300A_MASK_RX_FIFO_FULL_FLG   0x40
#define CMT2300A_MASK_RX_FIFO_NMTY_FLG   0x20
#define CMT2300A_MASK_RX_FIFO_TH_FLG     0x10
#define CMT2300A_MASK_RX_FIFO_OVF_FLG    0x08
#define CMT2300A_MASK_TX_FIFO_FULL_FLG   0x04
#define CMT2300A_MASK_TX_FIFO_NMTY_FLG   0x02
#define CMT2300A_MASK_TX_FIFO_TH_FLG     0x01

/* ********** CMT2300A_CUS_RSSI_CODE registers ********** */
#define CMT2300A_MASK_RSSI_CODE          0xFF

/* ********** CMT2300A_CUS_RSSI_DBM registers ********** */
#define CMT2300A_MASK_RSSI_DBM           0xFF

/* ********** CMT2300A_CUS_LBD_RESULT registers ********** */
#define CMT2300A_MASK_LBD_RESULT         0xFF
#define CMT2300A_DelayUs                 Ebyte_Port_DelayUs

//////////////////////////////////////     463_PACKET_V   /////////////////////////////////////////////	
	
//410  2.4  9.6  50BW

	
/* [CMT Bank] */	
 uint8e_t g_cmt2300aCmtBank[CMT2300A_CMT_BANK_SIZE] = {	
0x00,	
0x66,	
0xEC,	
0x1D,	
0xF0,	
0x80,	
0x14,	
0x08,	
0x91,	
0x02,	
0x02,	
0xD0,		
};	
	
/* [System Bank] */	
 uint8e_t g_cmt2300aSystemBank[CMT2300A_SYSTEM_BANK_SIZE] = {	
0xAE,	
0xE0,	
0x30,	
0x00,	
0x00,	
0xF4,	
0x10,	
0xE2,	
0x42,	
0x20,	
0x00,	
0x81,	
	
};	
	
/* [Frequency Bank] */	
 uint8e_t g_cmt2300aFrequencyBank[CMT2300A_FREQUENCY_BANK_SIZE] = {	
0x3F,	
0x29,	
0xED,	
0x11,	
0x3F,	
0x13,	
0x3B,	
0x61,	
	
};	
	
/* [Data Rate Bank] */	
 uint8e_t g_cmt2300aDataRateBank[CMT2300A_DATA_RATE_BANK_SIZE] = {	
0x32,	
0x18,	
0x00,	
0x99,	
0xD1,	
0x9B,	
0x0C,	
0x0A,	
0x9F,	
0x39,	
0x29,	
0x29,	
0xC0,	
0x51,	
0x2A,	
0x53,	
0x00,	
0x00,	
0xB4,	
0x00,	
0x00,	
0x01,	
0x00,	
0x00,	
	
};	
	
/* [Baseband Bank] */	
 uint8e_t g_cmt2300aBasebandBank[CMT2300A_BASEBAND_BANK_SIZE] = {	
0x32,	
0x08,	
0x00,	
0x55,	
0x0A,	
0x00,	
0x00,	
0x1A,	
0x9C,	
0x17,	
0x3B,	
0xD4,	
0x2D,	
0x01,	
0x1F,	
0x00,	
0x00,	
0x00,	
0x00,	
0x00,	
0x41,	
0x4C,	
0x7C,	
0x64,	
0x78,	
0x00,	
0x00,	
0x1F,	
0x10,	
	
};	
	
/* [Tx Bank] */	
 uint8e_t g_cmt2300aTxBank[CMT2300A_TX_BANK_SIZE] = {	
0x70,	
0x0C,	
0x06,	
0x00,	
0x42,	
0xB0,	
0x00,	
0x8A,	
0x18,	
0x3F,	
0x7F,	
	
};	
	
/* [Frequency Bank] */	
 uint8e_t g_cmt2300aFrequencyBank915M[CMT2300A_FREQUENCY_BANK_SIZE] = {	
0x46,	
0x6D,	
0x80,	
0x86,	
0x46,	
0x62,	
0x27,	
0x16,	
	
};	
	


/* !
 * @brief IO模拟半双工SPI时钟周期  辅助延时
 * 
 * @param time 节拍
 */
void Ebyte_E49x_SpiDelay(uint8e_t time)
{
    uint8e_t n = time;
    while(n--);
}

/* !
 * @brief 1Byte=8Bit 逐位输出 
 * 
 * @param data 输出数据
 *
 * @note 时序请参考CMOSTEK文档 AN142第2节 SPI写寄存器时序
 */
void Ebyte_E49x_ByteBitOutput( uint8e_t data )
{
    uint8e_t i;
  
    /* 数据 1Byte=8bit逐位输出 */
    for( i=0 ; i<8 ; i++)
    {
        /* SLCK = 0 */
        Ebyte_Port_SlckIoControl(0);
        
        /* 数据位比较 通过SDIO输出 */
        if( data & 0x80 )
        {
            Ebyte_Port_SdioIoControl(1);
        }
        else
        {
            Ebyte_Port_SdioIoControl(0);
        }
        
        Ebyte_E49x_SpiDelay(7);
        
        /* 数据位调整 */
        data <<=1;
        
        /* SLCK = 1 */
        Ebyte_Port_SlckIoControl(1);
        
        Ebyte_E49x_SpiDelay(7);
    }  
}


/* !
 * @brief 通过地址向内部寄存器写入数据
 * 
 * @param address 寄存器地址 
 * @param data 数据 
 *
 * @note  奇怪的是用的2线半双工SPI+2线CS片选通信接口，不是标准4线全双工SPI接口
 *        时序请参考CMOSTEK文档 AN142第2节
 */
void Ebyte_E49x_WriteDataByAddress( uint8e_t address, uint8e_t data )
{

    /* SDIO 切换为输出  */
    Ebyte_Port_SdioIoControl(3);//设置SDIO为输出模式
    Ebyte_Port_SdioIoControl(1);//设置SDIO输出高电平  
    
    /* SLCK 输出低电平 */
    Ebyte_Port_SlckIoControl(0);
    
    /* CS二选一 CSB输出低电平表示选择寄存器 */
    Ebyte_Port_FcsbIoControl(1);
    Ebyte_Port_CsbIoControl(0);
    
    /* 至少等待半个 SLCK周期 */
    Ebyte_E49x_SpiDelay(20);
    
    /* 写地址 */
    Ebyte_E49x_ByteBitOutput( address & 0x7F );//地址特殊处理 与0x7F 让r/w位=0
    
    /* 写数据 */
    Ebyte_E49x_ByteBitOutput( data ); 
    
    Ebyte_Port_SlckIoControl(0);
    Ebyte_E49x_SpiDelay(20);
    
    Ebyte_Port_CsbIoControl(1);
    
    /* SDIO 切换为输入  */
    Ebyte_Port_SdioIoControl(2); 
}


/* !
 * @brief 逐位读取 8Bit数据位 
 * 
 * @return 读取的数据 1Byte
 *
 * @note 时序请参考CMOSTEK文档 AN142第2节 SPI读寄存器时序
 */
uint8e_t Ebyte_E49x_ByteBitInput( void )
{
    uint8e_t i;  
    uint8e_t data = 0xFF;
    
    for( i=0 ; i<8; i++ )
    {
        Ebyte_Port_SlckIoControl(0);
        
        Ebyte_E49x_SpiDelay(7);
        
        data <<= 1;
        
        Ebyte_Port_SlckIoControl(1);
        
        if( Ebyte_Port_SdioIoControl(4))
        {
            data |= 0x01;
        }
        else
        {
            data &= ~0x01;
        }
        
        Ebyte_E49x_SpiDelay(7);
    }
    
    return data;
}

/* !
 * @brief 通过地址向内部寄存器读取数据
 * 
 * @param address 寄存器地址 
 * @return data 数据 1Byte 
 *
 * @note  奇怪的是用的2线半双工SPI+2线CS片选通信接口，不是标准4线全双工SPI接口
 *        时序请参考CMOSTEK文档 AN142第2节
 */
uint8e_t Ebyte_E49x_ReadDataByAddress( uint8e_t address )
{
    uint8e_t result = 0xFF;

    /* SDIO 切换为输出  */
    Ebyte_Port_SdioIoControl(3);//设置SDIO为输出模式
    Ebyte_Port_SdioIoControl(1);//设置SDIO输出高电平  

    /* SLCK  */
    Ebyte_Port_SlckIoControl(0);
    
    /* CS二选一 CSB输出低电平表示选择寄存器 */
    Ebyte_Port_FcsbIoControl(1);
    Ebyte_Port_CsbIoControl(0);
    
    /* 至少等待半个 SLCK周期 */
    Ebyte_E49x_SpiDelay(20);
    
    /* 写地址 */
    Ebyte_E49x_ByteBitOutput( address|0x80 ); //地址特殊处理 或0x80 让r/w位=1
    
    /* SDIO 切换为输入  */
    Ebyte_Port_SdioIoControl(2);
    
    /* 读数据 */
    result = Ebyte_E49x_ByteBitInput();
    
    Ebyte_Port_SlckIoControl(0);
    
    Ebyte_E49x_SpiDelay(20);
    
    Ebyte_Port_CsbIoControl(1);
    
    return result;
}

/* !
 * @brief 写内部FIFO
 * 
 * @param data 指向待写入数据首地址的指针
 * @param size 写入数据长度
 */
void Ebyte_E49x_WriteFifo( uint8e_t *data , uint16e_t size )
{
    uint8e_t i;
  
    /* CS二选一 FCSB输出低电平表示选择内部FIFO */
    Ebyte_Port_FcsbIoControl(1);
    Ebyte_Port_CsbIoControl(1);
    
    Ebyte_Port_SlckIoControl(0);
    
    /* SDIO 切换为输出  */
    Ebyte_Port_SdioIoControl(3);
    
    /* 循环写入  */
    for( i=0 ; i<size ; i++)
    {
        Ebyte_Port_FcsbIoControl(0);
        
        Ebyte_E49x_SpiDelay(20);
        
        Ebyte_E49x_ByteBitOutput( data[i] );
        
        Ebyte_Port_SlckIoControl(0);
        
        Ebyte_E49x_SpiDelay(30);
        
        Ebyte_Port_FcsbIoControl(1);
        
        Ebyte_E49x_SpiDelay(60);
    }
    
    Ebyte_Port_SlckIoControl(2);
    
}

/* !
 * @brief 读内部FIFO
 * 
 * @param data 指向存放数据首地址的指针
 * @param size 需要读取的数据长度
 */
void Ebyte_E49x_ReadFifo( uint8e_t *data , uint16e_t size )
{
    uint8e_t i;
    
    /* CS二选一 FCSB输出低电平表示选择内部FIFO */
    Ebyte_Port_FcsbIoControl(1);
    Ebyte_Port_CsbIoControl(1);
    
    Ebyte_Port_SlckIoControl(0);
  
    /* SDIO 切换为输入  */
    Ebyte_Port_SdioIoControl(2);
    
    /* 循环读取  */
    for( i=0 ; i<size ; i++)
    {
        Ebyte_Port_FcsbIoControl(0);
        
        Ebyte_E49x_SpiDelay(20);
        
        data[i] = Ebyte_E49x_ByteBitInput();
        
        Ebyte_Port_SlckIoControl(0);
        
        Ebyte_E49x_SpiDelay(30);
        
        Ebyte_Port_FcsbIoControl(1);
        
        Ebyte_E49x_SpiDelay(60);
    } 
}



/*! ********************************************************
* @name    CMT2300A_ReadReg
* @desc    Read the CMT2300A register at the specified address.
* @param   addr: register address
* @return  Register value
* *********************************************************/
uint8e_t CMT2300A_ReadReg(uint8e_t addr)
{
    uint8e_t dat = 0xFF;
//    cmt_spi3_read(addr, &dat);
	
    dat = Ebyte_E49x_ReadDataByAddress( addr );
    return dat;
}

/*! ********************************************************
* @name    CMT2300A_WriteReg
* @desc    Write the CMT2300A register at the specified address.
* @param   addr: register address
*          dat: register value
* *********************************************************/
void CMT2300A_WriteReg(uint8e_t addr, uint8e_t dat)
{
    Ebyte_E49x_WriteDataByAddress(addr, dat);
}

/*! ********************************************************
* @name    CMT2300A_ReadFifo
* @desc    Reads the contents of the CMT2300A FIFO.
* @param   buf: buffer where to copy the FIFO read data
*          len: number of bytes to be read from the FIFO
* *********************************************************/
void CMT2300A_ReadFifo(uint8e_t buf[], uint16e_t len)
{
    Ebyte_E49x_ReadFifo(buf, len);
}

/*! ********************************************************
* @name    CMT2300A_WriteFifo
* @desc    Writes the buffer contents to the CMT2300A FIFO.
* @param   buf: buffer containing data to be put on the FIFO
*          len: number of bytes to be written to the FIFO
* *********************************************************/
void CMT2300A_WriteFifo(uint8e_t buf[], uint16e_t len)
{
    Ebyte_E49x_WriteFifo(buf, len);
}

/*! ********************************************************
* @name    CMT2300A_SoftReset
* @desc    Soft reset.
* *********************************************************/
void CMT2300A_SoftReset(void)
{
    CMT2300A_WriteReg(0x7F, 0xFF);
}

/*! ********************************************************
* @name    CMT2300A_GetChipStatus
* @desc    Get the chip status.
* @return
*          CMT2300A_STA_PUP
*          CMT2300A_STA_SLEEP
*          CMT2300A_STA_STBY
*          CMT2300A_STA_RFS
*          CMT2300A_STA_TFS
*          CMT2300A_STA_RX
*          CMT2300A_STA_TX
*          CMT2300A_STA_EEPROM
*          CMT2300A_STA_ERROR
*          CMT2300A_STA_CAL
* *********************************************************/
uint8e_t CMT2300A_GetChipStatus(void)
{
    return  CMT2300A_ReadReg(CMT2300A_CUS_MODE_STA) & CMT2300A_MASK_CHIP_MODE_STA;
}

/*! ********************************************************
* @name    CMT2300A_AutoSwitchStatus
* @desc    Auto switch the chip status, and 10 ms as timeout.
* @param   nGoCmd: the chip next status
* @return  0 or 1
* *********************************************************/
uint8e_t CMT2300A_AutoSwitchStatus(uint8e_t nGoCmd)
{
#ifdef ENABLE_AUTO_SWITCH_CHIP_STATUS
//    uint32e_t nBegTick = CMT2300A_GetTickCount();
  
    
    uint8e_t  nWaitStatus;
    uint8e_t  nBegTick=0;
    
    switch(nGoCmd)
    {
    case CMT2300A_GO_SLEEP: nWaitStatus = CMT2300A_STA_SLEEP; break;
    case CMT2300A_GO_STBY : nWaitStatus = CMT2300A_STA_STBY ; break;
    case CMT2300A_GO_TFS  : nWaitStatus = CMT2300A_STA_TFS  ; break;
    case CMT2300A_GO_TX   : nWaitStatus = CMT2300A_STA_TX   ; break;
    case CMT2300A_GO_RFS  : nWaitStatus = CMT2300A_STA_RFS  ; break;
    case CMT2300A_GO_RX   : nWaitStatus = CMT2300A_STA_RX   ; break;
    }
    
    CMT2300A_WriteReg(CMT2300A_CUS_MODE_CTL, nGoCmd);
    
//    while(CMT2300A_GetTickCount()-nBegTick < 10)
    while( nBegTick < 10 )
    {
        CMT2300A_DelayUs(100);
        
        if(nWaitStatus==CMT2300A_GetChipStatus())
            return 0;
        
        if(CMT2300A_GO_TX==nGoCmd) {
            CMT2300A_DelayUs(100);
            
            if(CMT2300A_MASK_TX_DONE_FLG & CMT2300A_ReadReg(CMT2300A_CUS_INT_CLR1))
                return 0;
        }
        
        if(CMT2300A_GO_RX==nGoCmd) {
            CMT2300A_DelayUs(100);
            
            if(CMT2300A_MASK_PKT_OK_FLG & CMT2300A_ReadReg(CMT2300A_CUS_INT_FLAG))
                return 0;
        }
        
        CMT2300A_DelayUs(1000);
        nBegTick++;
    }
    
    return 1;
    
#else
    CMT2300A_WriteReg(CMT2300A_CUS_MODE_CTL, nGoCmd);
    return 0;
#endif
}

/*! ********************************************************
* @name    CMT2300A_GoSleep
* @desc    Entry SLEEP mode.
* @return  0 or 1
* *********************************************************/
uint8e_t CMT2300A_GoSleep(void)
{
    return CMT2300A_AutoSwitchStatus(CMT2300A_GO_SLEEP);
}

/*! ********************************************************
* @name    CMT2300A_GoStby
* @desc    Entry Sleep mode.
* @return  0 or 1
* *********************************************************/
uint8e_t CMT2300A_GoStby(void)
{
    return CMT2300A_AutoSwitchStatus(CMT2300A_GO_STBY);
}

/*! ********************************************************
* @name    CMT2300A_GoTFS
* @desc    Entry TFS mode.
* @return  0 or 1
* *********************************************************/
uint8e_t CMT2300A_GoTFS(void)
{
    return CMT2300A_AutoSwitchStatus(CMT2300A_GO_TFS);
}

/*! ********************************************************
* @name    CMT2300A_GoRFS
* @desc    Entry RFS mode.
* @return  0 or 1
* *********************************************************/
uint8e_t CMT2300A_GoRFS(void)
{
    return CMT2300A_AutoSwitchStatus(CMT2300A_GO_RFS);
}

/*! ********************************************************
* @name    CMT2300A_GoTx
* @desc    Entry Tx mode.
* @return  0 or 1
* *********************************************************/
uint8e_t CMT2300A_GoTx(void)
{
    return CMT2300A_AutoSwitchStatus(CMT2300A_GO_TX);
}

/*! ********************************************************
* @name    CMT2300A_GoRx
* @desc    Entry Rx mode.
* @return  0 or 1
* *********************************************************/
uint8e_t CMT2300A_GoRx(void)
{
    return CMT2300A_AutoSwitchStatus(CMT2300A_GO_RX);
}

/*! ********************************************************
* @name    CMT2300A_ConfigGpio
* @desc    Config GPIO pins mode.
* @param   nGpioSel: GPIO1_SEL | GPIO2_SEL | GPIO3_SEL | GPIO4_SEL
*          GPIO1_SEL:
*            CMT2300A_GPIO1_SEL_DOUT/DIN 
*            CMT2300A_GPIO1_SEL_INT1
*            CMT2300A_GPIO1_SEL_INT2 
*            CMT2300A_GPIO1_SEL_DCLK
*
*          GPIO2_SEL:
*            CMT2300A_GPIO2_SEL_INT1 
*            CMT2300A_GPIO2_SEL_INT2
*            CMT2300A_GPIO2_SEL_DOUT/DIN 
*            CMT2300A_GPIO2_SEL_DCLK
*
*          GPIO3_SEL:
*            CMT2300A_GPIO3_SEL_CLKO 
*            CMT2300A_GPIO3_SEL_DOUT/DIN
*            CMT2300A_GPIO3_SEL_INT2 
*            CMT2300A_GPIO3_SEL_DCLK
*
*          GPIO4_SEL:
*            CMT2300A_GPIO4_SEL_RSTIN 
*            CMT2300A_GPIO4_SEL_INT1
*            CMT2300A_GPIO4_SEL_DOUT 
*            CMT2300A_GPIO4_SEL_DCLK
* *********************************************************/
void CMT2300A_ConfigGpio(uint8e_t nGpioSel)
{
    CMT2300A_WriteReg(CMT2300A_CUS_IO_SEL, nGpioSel);
}

/*! ********************************************************
* @name    CMT2300A_ConfigInterrupt
* @desc    Config interrupt on INT1 and INT2.
* @param   nInt1Sel, nInt2Sel
*            CMT2300A_INT_SEL_RX_ACTIVE
*            CMT2300A_INT_SEL_TX_ACTIVE
*            CMT2300A_INT_SEL_RSSI_VLD
*            CMT2300A_INT_SEL_PREAM_OK
*            CMT2300A_INT_SEL_SYNC_OK
*            CMT2300A_INT_SEL_NODE_OK
*            CMT2300A_INT_SEL_CRC_OK
*            CMT2300A_INT_SEL_PKT_OK
*            CMT2300A_INT_SEL_SL_TMO
*            CMT2300A_INT_SEL_RX_TMO
*            CMT2300A_INT_SEL_TX_DONE
*            CMT2300A_INT_SEL_RX_FIFO_NMTY
*            CMT2300A_INT_SEL_RX_FIFO_TH
*            CMT2300A_INT_SEL_RX_FIFO_FULL
*            CMT2300A_INT_SEL_RX_FIFO_WBYTE
*            CMT2300A_INT_SEL_RX_FIFO_OVF
*            CMT2300A_INT_SEL_TX_FIFO_NMTY
*            CMT2300A_INT_SEL_TX_FIFO_TH
*            CMT2300A_INT_SEL_TX_FIFO_FULL
*            CMT2300A_INT_SEL_STATE_IS_STBY
*            CMT2300A_INT_SEL_STATE_IS_FS
*            CMT2300A_INT_SEL_STATE_IS_RX
*            CMT2300A_INT_SEL_STATE_IS_TX
*            CMT2300A_INT_SEL_LED
*            CMT2300A_INT_SEL_TRX_ACTIVE
*            CMT2300A_INT_SEL_PKT_DONE
* *********************************************************/
void CMT2300A_ConfigInterrupt(uint8e_t nInt1Sel, uint8e_t nInt2Sel)
{
    nInt1Sel &= CMT2300A_MASK_INT1_SEL;
    nInt1Sel |= (~CMT2300A_MASK_INT1_SEL) & CMT2300A_ReadReg(CMT2300A_CUS_INT1_CTL);
    CMT2300A_WriteReg(CMT2300A_CUS_INT1_CTL, nInt1Sel);

    nInt2Sel &= CMT2300A_MASK_INT2_SEL;
    nInt2Sel |= (~CMT2300A_MASK_INT2_SEL) & CMT2300A_ReadReg(CMT2300A_CUS_INT2_CTL);
    CMT2300A_WriteReg(CMT2300A_CUS_INT2_CTL, nInt2Sel);
}

/*! ********************************************************
* @name    CMT2300A_SetInterruptPolar
* @desc    Set the polarity of the interrupt.
* @param   bEnable(0): active-high (default)
*          bEnable(1): active-low
* *********************************************************/
void CMT2300A_SetInterruptPolar(uint8e_t bActiveHigh)
{
    uint8e_t tmp = CMT2300A_ReadReg(CMT2300A_CUS_INT1_CTL);

    if(bActiveHigh)
        tmp &= ~CMT2300A_MASK_INT_POLAR;
    else
        tmp |= CMT2300A_MASK_INT_POLAR;

    CMT2300A_WriteReg(CMT2300A_CUS_INT1_CTL, tmp);
}

/*! ********************************************************
* @name    CMT2300A_SetFifoThreshold
* @desc    Set FIFO threshold.
* @param   nFifoThreshold
* *********************************************************/
void CMT2300A_SetFifoThreshold(uint8e_t nFifoThreshold)
{ 
    uint8e_t tmp = CMT2300A_ReadReg(CMT2300A_CUS_PKT29);
    
    tmp &= ~CMT2300A_MASK_FIFO_TH;
    tmp |= nFifoThreshold & CMT2300A_MASK_FIFO_TH;
    
    CMT2300A_WriteReg(CMT2300A_CUS_PKT29, tmp);
}

/*! ********************************************************
* @name    CMT2300A_EnableAntennaSwitch
* @desc    Enable antenna switch, output TX_ACTIVE/RX_ACTIVE
*          via GPIO1/GPIO2.
* @param   nMode 
*            0: RF_SWT1_EN=1, RF_SWT2_EN=0
*               GPIO1: RX_ACTIVE, GPIO2: TX_ACTIVE
*            1: RF_SWT1_EN=0, RF_SWT2_EN=1
*               GPIO1: RX_ACTIVE, GPIO2: ~RX_ACTIVE
* *********************************************************/
void CMT2300A_EnableAntennaSwitch(uint8e_t nMode)
{
    uint8e_t tmp = CMT2300A_ReadReg(CMT2300A_CUS_INT1_CTL);

    if(0 == nMode) {
        tmp |= CMT2300A_MASK_RF_SWT1_EN;
        tmp &= ~CMT2300A_MASK_RF_SWT2_EN;
    }
    else if(1 == nMode) {
        tmp &= ~CMT2300A_MASK_RF_SWT1_EN;
        tmp |= CMT2300A_MASK_RF_SWT2_EN;
    }

    CMT2300A_WriteReg(CMT2300A_CUS_INT1_CTL, tmp);
}

/*! ********************************************************
* @name    CMT2300A_EnableInterrupt
* @desc    Enable interrupt.
* @param   nEnable 
*            CMT2300A_MASK_SL_TMO_EN   |
*            CMT2300A_MASK_RX_TMO_EN   |
*            CMT2300A_MASK_TX_DONE_EN  |
*            CMT2300A_MASK_PREAM_OK_EN |
*            CMT2300A_MASK_SYNC_OK_EN  |
*            CMT2300A_MASK_NODE_OK_EN  |
*            CMT2300A_MASK_CRC_OK_EN   |
*            CMT2300A_MASK_PKT_DONE_EN
* *********************************************************/
void CMT2300A_EnableInterrupt(uint8e_t nEnable)
{
    CMT2300A_WriteReg(CMT2300A_CUS_INT_EN, nEnable);
}

/*! ********************************************************
* @name    CMT2300A_EnableRxFifoAutoClear
* @desc    Auto clear Rx FIFO before entry Rx mode.
* @param   bEnable(0): Enable it(default)
*          bEnable(1): Disable it
* *********************************************************/
void CMT2300A_EnableRxFifoAutoClear(uint8e_t bEnable)
{
    uint8e_t tmp = CMT2300A_ReadReg(CMT2300A_CUS_FIFO_CTL);

    if(bEnable)
        tmp &= ~CMT2300A_MASK_FIFO_AUTO_CLR_DIS;
    else
        tmp |= CMT2300A_MASK_FIFO_AUTO_CLR_DIS;

    CMT2300A_WriteReg(CMT2300A_CUS_FIFO_CTL, tmp);
}

/*! ********************************************************
* @name    CMT2300A_EnableFifoMerge
* @desc    Enable FIFO merge.
* @param   bEnable(0): use a single 64-byte FIFO for either Tx or Rx
*          bEnable(1): use a 32-byte FIFO for Tx and another 32-byte FIFO for Rx(default)
* *********************************************************/
void CMT2300A_EnableFifoMerge(uint8e_t bEnable)
{
    uint8e_t tmp = CMT2300A_ReadReg(CMT2300A_CUS_FIFO_CTL);

    if  (bEnable)
        tmp |= CMT2300A_MASK_FIFO_MERGE_EN;
    else
        tmp &= ~CMT2300A_MASK_FIFO_MERGE_EN;

    CMT2300A_WriteReg(CMT2300A_CUS_FIFO_CTL, tmp);
}

/*! ********************************************************
* @name    CMT2300A_EnableReadFifo
* @desc    Enable SPI to read the FIFO.
* *********************************************************/
void CMT2300A_EnableReadFifo(void)
{
    uint8e_t tmp = CMT2300A_ReadReg(CMT2300A_CUS_FIFO_CTL);
    tmp &= ~CMT2300A_MASK_SPI_FIFO_RD_WR_SEL; 
    tmp &= ~CMT2300A_MASK_FIFO_RX_TX_SEL;
    CMT2300A_WriteReg(CMT2300A_CUS_FIFO_CTL, tmp);
}

/*! ********************************************************
* @name    CMT2300A_EnableWriteFifo
* @desc    Enable SPI to write the FIFO.
* *********************************************************/
void CMT2300A_EnableWriteFifo(void)
{
    uint8e_t tmp = CMT2300A_ReadReg(CMT2300A_CUS_FIFO_CTL);
    tmp |= CMT2300A_MASK_SPI_FIFO_RD_WR_SEL;
    tmp |= CMT2300A_MASK_FIFO_RX_TX_SEL;
    CMT2300A_WriteReg(CMT2300A_CUS_FIFO_CTL, tmp);
}

/*! ********************************************************
* @name    CMT2300A_RestoreFifo
* @desc    Restore the FIFO.
* *********************************************************/
void CMT2300A_RestoreFifo(void)
{
    CMT2300A_WriteReg(CMT2300A_CUS_FIFO_CLR, CMT2300A_MASK_FIFO_RESTORE);
}

/*! ********************************************************
* @name    CMT2300A_ClearFifo
* @desc    Clear the Tx FIFO.
* @return  FIFO flags
*            CMT2300A_MASK_RX_FIFO_FULL_FLG |
*            CMT2300A_MASK_RX_FIFO_NMTY_FLG |
*            CMT2300A_MASK_RX_FIFO_TH_FLG   |
*            CMT2300A_MASK_RX_FIFO_OVF_FLG  |
*            CMT2300A_MASK_TX_FIFO_FULL_FLG |
*            CMT2300A_MASK_TX_FIFO_NMTY_FLG |
*            CMT2300A_MASK_TX_FIFO_TH_FLG
* *********************************************************/
uint8e_t CMT2300A_ClearTxFifo(void)
{
    uint8e_t tmp = CMT2300A_ReadReg(CMT2300A_CUS_FIFO_FLAG);
    CMT2300A_WriteReg(CMT2300A_CUS_FIFO_CLR, CMT2300A_MASK_FIFO_CLR_TX);
    return tmp;
}

/*! ********************************************************
* @name    CMT2300A_ClearFifo
* @desc    Clear the Rx FIFO.
* @return  FIFO flags
*            CMT2300A_MASK_RX_FIFO_FULL_FLG |
*            CMT2300A_MASK_RX_FIFO_NMTY_FLG |
*            CMT2300A_MASK_RX_FIFO_TH_FLG   |
*            CMT2300A_MASK_RX_FIFO_OVF_FLG  |
*            CMT2300A_MASK_TX_FIFO_FULL_FLG |
*            CMT2300A_MASK_TX_FIFO_NMTY_FLG |
*            CMT2300A_MASK_TX_FIFO_TH_FLG
* *********************************************************/
uint8e_t CMT2300A_ClearRxFifo(void)
{
    uint8e_t tmp = CMT2300A_ReadReg(CMT2300A_CUS_FIFO_FLAG);
    CMT2300A_WriteReg(CMT2300A_CUS_FIFO_CLR, CMT2300A_MASK_FIFO_CLR_RX);
    return tmp;
}

/*! ********************************************************
* @name    CMT2300A_ClearInterruptFlags
* @desc    Clear all interrupt flags.
* @return  Some interrupt flags
*            CMT2300A_MASK_SL_TMO_EN    |
*            CMT2300A_MASK_RX_TMO_EN    |
*            CMT2300A_MASK_TX_DONE_EN   |
*            CMT2300A_MASK_PREAM_OK_FLG |
*            CMT2300A_MASK_SYNC_OK_FLG  |
*            CMT2300A_MASK_NODE_OK_FLG  |
*            CMT2300A_MASK_CRC_OK_FLG   |
*            CMT2300A_MASK_PKT_OK_FLG
* *********************************************************/
uint8e_t CMT2300A_ClearInterruptFlags(void)
{
    uint8e_t nFlag1, nFlag2;
    uint8e_t nClr1 = 0;
    uint8e_t nClr2 = 0;
    uint8e_t nRet  = 0;
    uint8e_t nIntPolar;
    
    nIntPolar = CMT2300A_ReadReg(CMT2300A_CUS_INT1_CTL);
    nIntPolar = (nIntPolar & CMT2300A_MASK_INT_POLAR) ?1 :0;

    nFlag1 = CMT2300A_ReadReg(CMT2300A_CUS_INT_FLAG);
    nFlag2 = CMT2300A_ReadReg(CMT2300A_CUS_INT_CLR1);
    
    if(nIntPolar) {
        /* Interrupt flag active-low */
        nFlag1 = ~nFlag1;
        nFlag2 = ~nFlag2;
    }

    if(CMT2300A_MASK_LBD_FLG & nFlag1) {
        nClr2 |= CMT2300A_MASK_LBD_CLR;         /* Clear LBD_FLG */
    }

    if(CMT2300A_MASK_COL_ERR_FLG & nFlag1) {
        nClr2 |= CMT2300A_MASK_PKT_DONE_CLR;    /* Clear COL_ERR_FLG by PKT_DONE_CLR */
    }

    if(CMT2300A_MASK_PKT_ERR_FLG & nFlag1) {
        nClr2 |= CMT2300A_MASK_PKT_DONE_CLR;    /* Clear PKT_ERR_FLG by PKT_DONE_CLR */
    }

    if(CMT2300A_MASK_PREAM_OK_FLG & nFlag1) {
        nClr2 |= CMT2300A_MASK_PREAM_OK_CLR;    /* Clear PREAM_OK_FLG */
        nRet  |= CMT2300A_MASK_PREAM_OK_FLG;    /* Return PREAM_OK_FLG */
    }

    if(CMT2300A_MASK_SYNC_OK_FLG & nFlag1) {
        nClr2 |= CMT2300A_MASK_SYNC_OK_CLR;    /* Clear SYNC_OK_FLG */
        nRet  |= CMT2300A_MASK_SYNC_OK_FLG;    /* Return SYNC_OK_FLG */
    }

    if(CMT2300A_MASK_NODE_OK_FLG & nFlag1) {
        nClr2 |= CMT2300A_MASK_NODE_OK_CLR;    /* Clear NODE_OK_FLG */
        nRet  |= CMT2300A_MASK_NODE_OK_FLG;    /* Return NODE_OK_FLG */
    }

    if(CMT2300A_MASK_CRC_OK_FLG & nFlag1) {
        nClr2 |= CMT2300A_MASK_CRC_OK_CLR;    /* Clear CRC_OK_FLG */
        nRet  |= CMT2300A_MASK_CRC_OK_FLG;    /* Return CRC_OK_FLG */
    }

    if(CMT2300A_MASK_PKT_OK_FLG & nFlag1) {
        nClr2 |= CMT2300A_MASK_PKT_DONE_CLR;  /* Clear PKT_OK_FLG */
        nRet  |= CMT2300A_MASK_PKT_OK_FLG;    /* Return PKT_OK_FLG */
    }    

    if(CMT2300A_MASK_SL_TMO_FLG & nFlag2) {
        nClr1 |= CMT2300A_MASK_SL_TMO_CLR;    /* Clear SL_TMO_FLG */
        nRet  |= CMT2300A_MASK_SL_TMO_EN;     /* Return SL_TMO_FLG by SL_TMO_EN */
    }

    if(CMT2300A_MASK_RX_TMO_FLG & nFlag2) {
        nClr1 |= CMT2300A_MASK_RX_TMO_CLR;    /* Clear RX_TMO_FLG */
        nRet  |= CMT2300A_MASK_RX_TMO_EN;     /* Return RX_TMO_FLG by RX_TMO_EN */
    }

    if(CMT2300A_MASK_TX_DONE_FLG & nFlag2) {
        nClr1 |= CMT2300A_MASK_TX_DONE_CLR;   /* Clear TX_DONE_FLG */
        nRet  |= CMT2300A_MASK_TX_DONE_EN;    /* Return TX_DONE_FLG by TX_DONE_EN */
    }
    
    CMT2300A_WriteReg(CMT2300A_CUS_INT_CLR1, nClr1);
    CMT2300A_WriteReg(CMT2300A_CUS_INT_CLR2, nClr2);

    if(nIntPolar) {
        /* Interrupt flag active-low */
        nRet = ~nRet;
    }

    return nRet;
}

/*! ********************************************************
* @name    CMT2300A_ConfigTxDin
* @desc    Used to select whether to use GPIO1 or GPIO2 or GPIO3
*          as DIN in the direct mode. It only takes effect when 
*          call CMT2300A_EnableTxDin(0) in the direct mode.
* @param   nDinSel
*            CMT2300A_TX_DIN_SEL_GPIO1
*            CMT2300A_TX_DIN_SEL_GPIO2
*            CMT2300A_TX_DIN_SEL_GPIO3
* *********************************************************/
void CMT2300A_ConfigTxDin(uint8e_t nDinSel)
{
    uint8e_t tmp = CMT2300A_ReadReg(CMT2300A_CUS_FIFO_CTL);
    tmp &= ~CMT2300A_MASK_TX_DIN_SEL;
    tmp |= nDinSel;
    CMT2300A_WriteReg(CMT2300A_CUS_FIFO_CTL, tmp);
}

/*! ********************************************************
* @name    CMT2300A_EnableTxDin
* @desc    Used to change GPIO1/GPIO2/GPIO3 between DOUT and DIN.
* @param   bEnable(0): used as DIN
*          bEnable(1): used as DOUT(default)
* *********************************************************/
void CMT2300A_EnableTxDin(uint8e_t bEnable)
{
    uint8e_t tmp = CMT2300A_ReadReg(CMT2300A_CUS_FIFO_CTL);

    if(bEnable)
        tmp |= CMT2300A_MASK_TX_DIN_EN;
    else
        tmp &= ~CMT2300A_MASK_TX_DIN_EN;

    CMT2300A_WriteReg(CMT2300A_CUS_FIFO_CTL, tmp);
}

/*! ********************************************************
* @name    CMT2300A_EnableTxDinInvert
* @desc    Used to invert DIN data in direct mode.
* @param   bEnable(0): invert DIN
*          bEnable(1): not invert DIN(default)
* *********************************************************/
void CMT2300A_EnableTxDinInvert(uint8e_t bEnable)
{
    uint8e_t tmp = CMT2300A_ReadReg(CMT2300A_CUS_INT2_CTL);

    if(bEnable)
        tmp |= CMT2300A_MASK_TX_DIN_INV;
    else
        tmp &= ~CMT2300A_MASK_TX_DIN_INV;

    CMT2300A_WriteReg(CMT2300A_CUS_INT2_CTL, tmp);
}

/*! ********************************************************
* @name    CMT2300A_IsExist
* @desc    Chip indentify.
* @return  0: chip is exist, 1: chip not found
* *********************************************************/
uint8e_t CMT2300A_IsExist(void)
{
    uint8e_t back, dat;

    back = CMT2300A_ReadReg(CMT2300A_CUS_PKT17);
    CMT2300A_WriteReg(CMT2300A_CUS_PKT17, 0xAA);

    dat = CMT2300A_ReadReg(CMT2300A_CUS_PKT17);
    CMT2300A_WriteReg(CMT2300A_CUS_PKT17, back);

    if(0xAA==dat)
        return 0;
    else
        return 1;
}

/*! ********************************************************
* @name    CMT2300A_GetRssiCode
* @desc    Get RSSI code.
* @return  RSSI code
* *********************************************************/
uint8e_t CMT2300A_GetRssiCode(void)
{
    return CMT2300A_ReadReg(CMT2300A_CUS_RSSI_CODE);
}

/*! ********************************************************
* @name    CMT2300A_GetRssiDBm
* @desc    Get RSSI dBm.
* @return  dBm
* *********************************************************/
int CMT2300A_GetRssiDBm(void)
{
    return (int)CMT2300A_ReadReg(CMT2300A_CUS_RSSI_DBM) - 128;
}

/*! ********************************************************
* @name    CMT2300A_SetFrequencyChannel
* @desc    This defines up to 255 frequency channel
*          for fast frequency hopping operation.
* @param   nChann: the frequency channel
* *********************************************************/
void CMT2300A_SetFrequencyChannel(uint8e_t nChann)
{
    CMT2300A_WriteReg(CMT2300A_CUS_FREQ_CHNL, nChann);
}

/*! ********************************************************
* @name    CMT2300A_SetFrequencyStep
* @desc    This defines the frequency channel step size 
*          for fast frequency hopping operation. 
*          One step size is 2.5 kHz.
* @param   nOffset: the frequency step
* *********************************************************/
void CMT2300A_SetFrequencyStep(uint8e_t nOffset)
{
    CMT2300A_WriteReg(CMT2300A_CUS_FREQ_OFS, nOffset);
}

/*! ********************************************************
* @name    CMT2300A_SetPayloadLength
* @desc    Set payload length.
* @param   nLength
* *********************************************************/
void CMT2300A_SetPayloadLength(uint16e_t nLength)
{ 
    uint8e_t tmp = CMT2300A_ReadReg(CMT2300A_CUS_PKT14);
    
    tmp &= ~CMT2300A_MASK_PAYLOAD_LENG_10_8;
    tmp |= (nLength >> 4) & CMT2300A_MASK_PAYLOAD_LENG_10_8;
    CMT2300A_WriteReg(CMT2300A_CUS_PKT14, tmp);
    
    tmp = nLength & CMT2300A_MASK_PAYLOAD_LENG_7_0;
    CMT2300A_WriteReg(CMT2300A_CUS_PKT15, tmp);
}

/*! ********************************************************
* @name    CMT2300A_EnableLfosc
* @desc    If you need use sleep timer, you should enable LFOSC.
* @param   bEnable(0): Enable it(default)
*          bEnable(1): Disable it
* *********************************************************/
void CMT2300A_EnableLfosc(uint8e_t bEnable)
{
    uint8e_t tmp = CMT2300A_ReadReg(CMT2300A_CUS_SYS2);
    
    if(bEnable) {
        tmp |= CMT2300A_MASK_LFOSC_RECAL_EN;
        tmp |= CMT2300A_MASK_LFOSC_CAL1_EN;
        tmp |= CMT2300A_MASK_LFOSC_CAL2_EN;
    }
    else {
        tmp &= ~CMT2300A_MASK_LFOSC_RECAL_EN;
        tmp &= ~CMT2300A_MASK_LFOSC_CAL1_EN;
        tmp &= ~CMT2300A_MASK_LFOSC_CAL2_EN;
    }
    
    CMT2300A_WriteReg(CMT2300A_CUS_SYS2, tmp);
}

/*! ********************************************************
* @name    CMT2300A_EnableLfoscOutput
* @desc    LFOSC clock is output via GPIO3.
* @param   bEnable(0): Enable it
*          bEnable(1): Disable it(default)
* *********************************************************/
void CMT2300A_EnableLfoscOutput(uint8e_t bEnable)
{
    uint8e_t tmp = CMT2300A_ReadReg(CMT2300A_CUS_INT2_CTL);
    
    if(bEnable)
        tmp |= CMT2300A_MASK_LFOSC_OUT_EN;
    else
        tmp &= ~CMT2300A_MASK_LFOSC_OUT_EN;
    
    CMT2300A_WriteReg(CMT2300A_CUS_INT2_CTL, tmp);
}

/*! ********************************************************
* @name    CMT2300A_EnableAfc
* @desc    AFC enable or disanble.
* @param   bEnable(0): Enable it
*          bEnable(1): Disable it(default)
* *********************************************************/
void CMT2300A_EnableAfc(uint8e_t bEnable)
{
    uint8e_t tmp = CMT2300A_ReadReg(CMT2300A_CUS_FSK5);
    
    if(bEnable)
        tmp |= 0x10;
    else
        tmp &= ~0x10;
    
    CMT2300A_WriteReg(CMT2300A_CUS_FSK5, tmp);
}

/*! ********************************************************
* @name    CMT2300A_SetAfcOvfTh
* @desc    This is optional, only needed when using Rx fast frequency hopping.
* @param   afcOvfTh: AFC_OVF_TH see AN142 and AN197 for details.
* *********************************************************/
void CMT2300A_SetAfcOvfTh(uint8e_t afcOvfTh)
{
    CMT2300A_WriteReg(CMT2300A_CUS_FSK4, afcOvfTh);
}

/*! ********************************************************
* @name    CMT2300A_ConfigRegBank
* @desc    Config one register bank.
* *********************************************************/
uint8e_t CMT2300A_ConfigRegBank(uint8e_t base_addr, const uint8e_t bank[], uint8e_t len)
{
    uint8e_t i;
    for(i=0; i<len; i++)
        CMT2300A_WriteReg(i+base_addr, bank[i]);

    return 0;
}


void RF_Config(uint8e_t mode)       //主要是设置GPIO及其中断类型            
{
    /* 进入配置模式 */
    CMT2300A_GoStby();        

    /* 设置GPIO工作模式  这里将GPIO1映射到INT1,GPIO2映射到INT2 */                  
    CMT2300A_ConfigGpio( CMT2300A_GPIO1_SEL_INT1 | CMT2300A_GPIO2_SEL_INT2 | CMT2300A_GPIO3_SEL_DOUT );
    
    /* 模式1 发送 */
    if( mode == 1 )
    {
        /* 中断类型映射  这里将接收完成中断映射到INT1即GPIO1 发送完成中断映射到INT2即GPIO2 */
        CMT2300A_ConfigInterrupt( CMT2300A_INT_SEL_PKT_OK,  CMT2300A_INT_SEL_TX_DONE );           
    }
    /* 模式0 接收 */  
    else
    {
        /* 中断类型映射  这里将发送完成中断映射到INT1即GPIO1 接收完成中断映射到INT2即GPIO2 */
        CMT2300A_ConfigInterrupt( CMT2300A_INT_SEL_TX_DONE,  CMT2300A_INT_SEL_PKT_OK );         
    }
    
    /* 使能无线芯片GPIO中断 */               
    CMT2300A_EnableInterrupt(CMT2300A_MASK_TX_DONE_EN  |CMT2300A_MASK_PREAM_OK_EN |CMT2300A_MASK_SYNC_OK_EN |
                             CMT2300A_MASK_NODE_OK_EN  |CMT2300A_MASK_CRC_OK_EN   |CMT2300A_MASK_PKT_DONE_EN);
    
    /* 关闭LFOSC模块 */
    CMT2300A_EnableLfosc(1);             
    
    /* 这里简单的将发送使用的32字节FIFO与接收使用的32字节FIFO合并为一个64字节的共用FIFO  
       注意：一些特殊应用例如发送内容重复或只接收等场合，可以特殊处理FIFO来降低功耗 */
    CMT2300A_EnableFifoMerge(0);
    
    /* 无线芯片进入睡眠模式，使配置生效 */
    CMT2300A_GoSleep();                    
}

/* !
 * @brief BBYTE 无线模块进入接收模式
 */
void Ebyte_E49x_SetRx( uint32e_t timeout )
{
    /* 无线参数设置，GPIO中断及使能，进入SLEEP模式使配置生效*/
    RF_Config(0); 
    
    /* 进入配置模式 */
    CMT2300A_GoStby();   
    
    /* 清除内部中断标志位 */
    CMT2300A_ClearInterruptFlags(); 
    
    /* 允许读FIFO */
    CMT2300A_EnableReadFifo();       
    
    /* 清空FIFO */
    CMT2300A_ClearRxFifo();         
    
    /* 进入接收模式 开始监听 */
    if(1==CMT2300A_GoRx())       
    {
        while(1); //异常 请检查硬件
    }      
}

/* !
 * @brief 通过模块发送数据
 *
 * @param payload 指向待传输数据
 * @param size 待传输数据长度
 * @param timeout 超时时间
 */
void Ebyte_E49x_SendPayload( uint8e_t *payload, uint8e_t size, uint32e_t timeout )
{
    /* 无线参数设置，GPIO中断及使能，进入SLEEP模式使配置生效*/
    RF_Config(1);
    
    /* 进入配置模式 */
    CMT2300A_GoStby();        
    
    /* 清除无线中断标志位 */
    CMT2300A_ClearInterruptFlags(); 
    
    /* 允许写入内部FIFO */
    CMT2300A_EnableWriteFifo();  

    /* 清空FIFO */  
    CMT2300A_ClearTxFifo();         
    
    /* 写入FIFO 注意长度限制 */
    CMT2300A_SetPayloadLength(size + 1);
    CMT2300A_WriteFifo(payload, size);     
    
    
    if( 0==(CMT2300A_MASK_TX_FIFO_NMTY_FLG & CMT2300A_ReadReg(CMT2300A_CUS_FIFO_FLAG)) )
    {
        //
    }
    
    /* 进入发送模式，FIFO内数据开始无线传输。完成后通过IO中断通知或者主循环查询 */
    if(1==CMT2300A_GoTx())                
    {
        while(1);
    }
    
}

/* !
 * @brief EBYTE 无线模块初始化
 */
void Ebyte_E49x_Init( void )
{   
    uint8e_t tmp,i;

    /* 软复位 */
    CMT2300A_SoftReset();     
    
    /* 至少等待20ms */
    for (i=0;i<20;i++)
    {
        CMT2300A_DelayUs(1000);
    }
    
    /* 进入配置模式 */
    CMT2300A_GoStby();        

    /* 开启配置保持功能  关闭复位引脚功能 */
    tmp  = CMT2300A_ReadReg(CMT2300A_CUS_MODE_STA);
    tmp |= CMT2300A_MASK_CFG_RETAIN;       
    tmp &= ~CMT2300A_MASK_RSTN_IN_EN;      
    CMT2300A_WriteReg(CMT2300A_CUS_MODE_STA, tmp);

    /* 开启锁相环频率锁定 (不开有一定概率频率不正确，导致无法接收数据)*/
    tmp  = CMT2300A_ReadReg(CMT2300A_CUS_EN_CTL);
    tmp |= CMT2300A_MASK_LOCKING_EN;        
    CMT2300A_WriteReg(CMT2300A_CUS_EN_CTL, tmp);
    
    /* 关闭LFOSC矫正模块 （LFOSC主要用于驱动 Sleep Timer，关闭后降低了休眠功耗以及节约5ms的矫正时间） */
    CMT2300A_EnableLfosc(1);             

    /* 清除中断标志位 */
    CMT2300A_ClearInterruptFlags(); 
    
    /* 状态检查 */
    if(1==CMT2300A_IsExist())  
    {
        while(1);  //异常 1、请检查硬件连接 2、ebyte_port.c中的用户填充函数是否正确
    }    
    
    /* 内部寄存器组初始化  包含频率、空速等 */
    CMT2300A_ConfigRegBank(CMT2300A_CMT_BANK_ADDR       , g_cmt2300aCmtBank      , CMT2300A_CMT_BANK_SIZE       );
    CMT2300A_ConfigRegBank(CMT2300A_SYSTEM_BANK_ADDR    , g_cmt2300aSystemBank    , CMT2300A_SYSTEM_BANK_SIZE    );
    CMT2300A_ConfigRegBank(CMT2300A_FREQUENCY_BANK_ADDR , g_cmt2300aFrequencyBank915M , CMT2300A_FREQUENCY_BANK_SIZE );
    CMT2300A_ConfigRegBank(CMT2300A_DATA_RATE_BANK_ADDR , g_cmt2300aDataRateBank , CMT2300A_DATA_RATE_BANK_SIZE );
    CMT2300A_ConfigRegBank(CMT2300A_BASEBAND_BANK_ADDR  , g_cmt2300aBasebandBank  , CMT2300A_BASEBAND_BANK_SIZE  );
    CMT2300A_ConfigRegBank(CMT2300A_TX_BANK_ADDR        , g_cmt2300aTxBank       , CMT2300A_TX_BANK_SIZE        );    
    
    /* 原厂BUG需要兼容 */
    tmp = (~0x07) & CMT2300A_ReadReg(CMT2300A_CUS_CMT10);
    CMT2300A_WriteReg(CMT2300A_CUS_CMT10, tmp|0x02);
    
    /* 默认初始化后进入接收模式 */
    Ebyte_E49x_SetRx(0);   
}

/* !
 * @brief 保留 待兼容DIO硬件中断
 */
uint8e_t testBuffer[32]={0};
void Ebyte_E49x_InterruptTrigger( void )
{
        CMT2300A_GoStby();     //无线芯片  GOTO  STANDBY 模式
        
        /* The length need be smaller than 32 */
        CMT2300A_ReadFifo(testBuffer, 
                          64);              
        
        
        CMT2300A_ClearInterruptFlags();   ////清除无线中断标志位
        CMT2300A_GoSleep();                                  //无线芯片进入睡眠

        
        Ebyte_E49x_SetRx(0);
    
}

/* !
 * @brief BBYTE 无线模块周期任务 
 *
 * @note 必须被周期性调用，否则无法接收到数据
 */

void Ebyte_E49x_IntOrPollTask( void )
{

}



/* !
 * @brief 获取模块类型
 * 
 * @return 32位的编码 
 * @note 高16位代表模块名 例如0x0220 代表E22模块
 *       低16位代表频段名 例如0x0400 代表400频段
 */
//uint32e_t Ebyte_E49x_GetName(void)
//{
//  return  (  (((uint32e_t)EBYTE_E22_NAME_TYPE<<16)) | EBYTE_E22_FREQUENCY_TYPE);
//}
//
///* !
// * @brief 获取模块程序版本
// * 
// * @return 8位的编码 
// * @note 例如0x10 代表V1.0
// */
//uint8e_t Ebyte_E49x_GetDriverVersion(void)
//{
//  return  EBYTE_E22_PROGRAM_TYPE;
//}
