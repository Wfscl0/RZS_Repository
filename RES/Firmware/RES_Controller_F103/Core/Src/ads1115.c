#include "ads1115.h"

#define ADS1115_REG_CONVERSION 0x00U
#define ADS1115_REG_CONFIG     0x01U
#define ADS1115_REG_LO_THRESH  0x02U
#define ADS1115_REG_HI_THRESH  0x03U

#define ADS1115_TIMEOUT_MS 20U

static bool write_register(Ads1115 *device, uint8_t reg, uint16_t value)
{
    uint8_t bytes[3];

    bytes[0] = reg;
    bytes[1] = (uint8_t)(value >> 8);
    bytes[2] = (uint8_t)value;
    return HAL_I2C_Master_Transmit(
        device->i2c,
        device->address,
        bytes,
        sizeof(bytes),
        ADS1115_TIMEOUT_MS) == HAL_OK;
}

bool ads1115_init(
    Ads1115 *device,
    I2C_HandleTypeDef *i2c,
    uint8_t address_7bit)
{
    device->i2c = i2c;
    device->address = (uint16_t)address_7bit << 1;

    if (HAL_I2C_IsDeviceReady(
            device->i2c,
            device->address,
            2U,
            ADS1115_TIMEOUT_MS) != HAL_OK) {
        return false;
    }

    /*
     * Conversion-ready mode:
     * Hi_thresh MSB = 1 and Lo_thresh MSB = 0. ALERT/RDY then goes low
     * when the single conversion completes.
     */
    return write_register(device, ADS1115_REG_HI_THRESH, UINT16_C(0x8000))
        && write_register(device, ADS1115_REG_LO_THRESH, UINT16_C(0x0000));
}

bool ads1115_start_ain0_single(Ads1115 *device)
{
    /*
     * 单次采样可降低功耗；AIN0 对地、+/-4.096 V、128 SPS。
     * 比较器设为低有效并在一次转换后拉低 ALERT/RDY。
     */
    return write_register(device, ADS1115_REG_CONFIG, UINT16_C(0xC380));
}

bool ads1115_read_conversion(Ads1115 *device, int16_t *raw)
{
    uint8_t reg = ADS1115_REG_CONVERSION;
    uint8_t bytes[2];

    if (HAL_I2C_Master_Transmit(
            device->i2c,
            device->address,
            &reg,
            1U,
            ADS1115_TIMEOUT_MS) != HAL_OK) {
        return false;
    }
    if (HAL_I2C_Master_Receive(
            device->i2c,
            device->address,
            bytes,
            sizeof(bytes),
            ADS1115_TIMEOUT_MS) != HAL_OK) {
        return false;
    }

    *raw = (int16_t)(((uint16_t)bytes[0] << 8) | bytes[1]);
    return true;
}
