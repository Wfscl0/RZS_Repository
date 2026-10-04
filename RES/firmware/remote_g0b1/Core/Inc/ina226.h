#ifndef INA226_H
#define INA226_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    INA226_OK = 0,
    INA226_NOT_INITIALIZED,
    INA226_IO_ERROR,
    INA226_ID_MISMATCH,
    INA226_CONFIG_MISMATCH,
    INA226_NOT_READY,
    INA226_MATH_OVERFLOW,
    INA226_RANGE_ERROR
} ina226_error_t;

typedef struct {
    void *context;
    bool (*write_register)(void *context, uint8_t reg, uint16_t value);
    bool (*read_register)(void *context, uint8_t reg, uint16_t *value);
    uint16_t current_lsb_ua;
    bool initialized;
    ina226_error_t last_error;
} ina226_t;

bool ina226_init(ina226_t *device);
bool ina226_read(ina226_t *device,
                 uint16_t *bus_voltage_mv,
                 int16_t *current_ma,
                 uint32_t *power_mw);

#endif
