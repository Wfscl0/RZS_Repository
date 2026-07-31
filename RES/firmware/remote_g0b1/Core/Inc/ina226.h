#ifndef INA226_H
#define INA226_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    void *context;
    bool (*write_register)(void *context, uint8_t reg, uint16_t value);
    bool (*read_register)(void *context, uint8_t reg, uint16_t *value);
    uint16_t current_lsb_ua;
} ina226_t;

bool ina226_init(ina226_t *device);
bool ina226_read(ina226_t *device,
                 uint16_t *bus_voltage_mv,
                 int16_t *current_ma,
                 uint32_t *power_mw);

#endif
