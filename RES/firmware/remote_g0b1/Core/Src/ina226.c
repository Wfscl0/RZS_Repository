#include "ina226.h"

#define INA226_REG_CONFIG       0x00u
#define INA226_REG_BUS_VOLTAGE  0x02u
#define INA226_REG_POWER        0x03u
#define INA226_REG_CURRENT      0x04u
#define INA226_REG_CALIBRATION  0x05u

/* 10 mOhm shunt, 500 uA current LSB: CAL = 0.00512/(0.01*0.0005)=1024. */
#define INA226_CALIBRATION_10MOHM_500UA 1024u
/* AVG=16, VBUSCT=1.1 ms, VSHCT=1.1 ms, continuous shunt+bus. */
#define INA226_CONFIG_AVG16_CONTINUOUS  0x0527u

bool ina226_init(ina226_t *device)
{
    if ((device == 0) || (device->write_register == 0) ||
        (device->read_register == 0)) {
        return false;
    }
    device->current_lsb_ua = 500u;
    return device->write_register(device->context,
                                  INA226_REG_CALIBRATION,
                                  INA226_CALIBRATION_10MOHM_500UA) &&
           device->write_register(device->context,
                                  INA226_REG_CONFIG,
                                  INA226_CONFIG_AVG16_CONTINUOUS);
}

bool ina226_read(ina226_t *device,
                 uint16_t *bus_voltage_mv,
                 int16_t *current_ma,
                 uint32_t *power_mw)
{
    uint16_t bus_raw;
    uint16_t current_raw;
    uint16_t power_raw;
    int32_t current_ua;

    if ((device == 0) || (bus_voltage_mv == 0) ||
        (current_ma == 0) || (power_mw == 0)) {
        return false;
    }
    if (!device->read_register(device->context, INA226_REG_BUS_VOLTAGE, &bus_raw) ||
        !device->read_register(device->context, INA226_REG_CURRENT, &current_raw) ||
        !device->read_register(device->context, INA226_REG_POWER, &power_raw)) {
        return false;
    }

    *bus_voltage_mv = (uint16_t)(((uint32_t)bus_raw * 5u) / 4u);
    current_ua = (int32_t)(int16_t)current_raw * device->current_lsb_ua;
    *current_ma = (int16_t)(current_ua / 1000);
    /* Power LSB = 25 * current LSB = 12.5 mW for 500 uA. */
    *power_mw = ((uint32_t)power_raw * 25u) / 2u;
    return true;
}
