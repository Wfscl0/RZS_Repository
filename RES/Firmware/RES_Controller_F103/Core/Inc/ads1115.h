#ifndef ADS1115_H
#define ADS1115_H

#include <stdbool.h>
#include <stdint.h>

#include "stm32f1xx_hal.h"

typedef struct {
    I2C_HandleTypeDef *i2c;
    uint16_t address;
} Ads1115;

bool ads1115_init(
    Ads1115 *device,
    I2C_HandleTypeDef *i2c,
    uint8_t address_7bit);
bool ads1115_start_ain0_single(Ads1115 *device);
bool ads1115_read_conversion(Ads1115 *device, int16_t *raw);

#endif

