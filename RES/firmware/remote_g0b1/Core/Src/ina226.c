#include "ina226.h"

#define INA226_REG_CONFIG       0x00u
#define INA226_REG_BUS_VOLTAGE  0x02u
#define INA226_REG_POWER        0x03u
#define INA226_REG_CURRENT      0x04u
#define INA226_REG_CALIBRATION  0x05u
#define INA226_REG_MASK_ENABLE  0x06u
#define INA226_REG_MANUFACTURER 0xFEu
#define INA226_REG_DIE_ID       0xFFu

/* 10 mOhm shunt, 500 uA current LSB: CAL = 0.00512/(0.01*0.0005)=1024. */
#define INA226_CALIBRATION_10MOHM_500UA 1024u
/* AVG=16, VBUSCT=1.1 ms, VSHCT=1.1 ms, continuous shunt+bus. */
#define INA226_CONFIG_AVG16_CONTINUOUS  0x4527u

static bool fail(ina226_t *device, ina226_error_t error)
{
    device->last_error = error;
    if (error != INA226_NOT_READY) {
        device->initialized = false;
    }
    return false;
}

bool ina226_init(ina226_t *device)
{
    uint16_t manufacturer, die, config, calibration;
    if (device != 0) {
        device->initialized = false;
        device->last_error = INA226_NOT_INITIALIZED;
    }
    if ((device == 0) || (device->write_register == 0) ||
        (device->read_register == 0)) {
        return false;
    }
    device->current_lsb_ua = 500u;
    if (!device->read_register(device->context, INA226_REG_MANUFACTURER, &manufacturer) ||
        !device->read_register(device->context, INA226_REG_DIE_ID, &die)) {
        return fail(device, INA226_IO_ERROR);
    }
    /* TI data sheet allows die revision 0x2260 or 0x2261. */
    if ((manufacturer != 0x5449u) || ((die != 0x2260u) && (die != 0x2261u))) {
        return fail(device, INA226_ID_MISMATCH);
    }
    if (!(device->write_register(device->context,
                                  INA226_REG_CALIBRATION,
                                  INA226_CALIBRATION_10MOHM_500UA) &&
           device->write_register(device->context,
                                  INA226_REG_CONFIG,
                                  INA226_CONFIG_AVG16_CONTINUOUS)) ||
        !device->read_register(device->context, INA226_REG_CONFIG, &config) ||
        !device->read_register(device->context, INA226_REG_CALIBRATION, &calibration)) {
        return fail(device, INA226_IO_ERROR);
    }
    if (((config & 0x8FFFu) != (INA226_CONFIG_AVG16_CONTINUOUS & 0x8FFFu)) ||
        (calibration != INA226_CALIBRATION_10MOHM_500UA)) {
        return fail(device, INA226_CONFIG_MISMATCH);
    }
    device->initialized = true;
    device->last_error = INA226_OK;
    return true;
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
    int32_t scaled_current;
    uint16_t config, calibration, status;

    if ((device == 0) || (bus_voltage_mv == 0) ||
        (current_ma == 0) || (power_mw == 0)) {
        return false;
    }
    /* Never leave stale stack values available after a failed read. */
    *bus_voltage_mv = 0u;
    *current_ma = 0;
    *power_mw = 0u;
    if (!device->initialized) {
        return false;
    }
    if (!device->read_register(device->context, INA226_REG_CONFIG, &config) ||
        !device->read_register(device->context, INA226_REG_CALIBRATION, &calibration) ||
        !device->read_register(device->context, INA226_REG_MASK_ENABLE, &status)) {
        return fail(device, INA226_IO_ERROR);
    }
    if (((config & 0x8FFFu) != (INA226_CONFIG_AVG16_CONTINUOUS & 0x8FFFu)) ||
        (calibration != INA226_CALIBRATION_10MOHM_500UA)) {
        return fail(device, INA226_CONFIG_MISMATCH);
    }
    if ((status & 0x0004u) != 0u) {
        return fail(device, INA226_MATH_OVERFLOW);
    }
    /* Reading Mask/Enable clears CVRF. Require a new conversion every poll. */
    if ((status & 0x0008u) == 0u) {
        return fail(device, INA226_NOT_READY);
    }
    if (!device->read_register(device->context, INA226_REG_BUS_VOLTAGE, &bus_raw) ||
        !device->read_register(device->context, INA226_REG_CURRENT, &current_raw) ||
        !device->read_register(device->context, INA226_REG_POWER, &power_raw)) {
        return fail(device, INA226_IO_ERROR);
    }

    current_ua = (int32_t)(int16_t)current_raw * device->current_lsb_ua;
    scaled_current = current_ua / 1000;
    if ((bus_raw > 28800u) || (scaled_current < -32768) || (scaled_current > 32767)) {
        return fail(device, INA226_RANGE_ERROR);
    }
    /* Zero V is retained as a critical low reading, never replaced by a fake voltage. */
    *bus_voltage_mv = (uint16_t)(((uint32_t)bus_raw * 5u) / 4u);
    *current_ma = (int16_t)scaled_current;
    /* Power LSB = 25 * current LSB = 12.5 mW for 500 uA. */
    *power_mw = ((uint32_t)power_raw * 25u) / 2u;
    device->last_error = INA226_OK;
    return true;
}
