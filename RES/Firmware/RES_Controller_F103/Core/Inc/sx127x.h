#ifndef SX127X_H
#define SX127X_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "stm32f1xx_hal.h"

typedef enum {
    SX127X_TX_BUSY = 0,
    SX127X_TX_DONE,
    SX127X_TX_TIMEOUT,
    SX127X_TX_IO_ERROR
} Sx127xTxStatus;

typedef struct {
    SPI_HandleTypeDef *spi;
    GPIO_TypeDef *nss_port;
    uint16_t nss_pin;
    GPIO_TypeDef *reset_port;
    uint16_t reset_pin;
    uint32_t tx_started_ms;
    bool transmitting;
    bool io_error;
} Sx127x;

bool sx127x_init(
    Sx127x *radio,
    SPI_HandleTypeDef *spi,
    GPIO_TypeDef *nss_port,
    uint16_t nss_pin,
    GPIO_TypeDef *reset_port,
    uint16_t reset_pin,
    uint32_t frequency_hz,
    int8_t tx_power_dbm);
bool sx127x_set_frequency(Sx127x *radio, uint32_t frequency_hz);
bool sx127x_begin_tx(
    Sx127x *radio,
    const uint8_t *payload,
    uint8_t length,
    uint32_t now_ms);
Sx127xTxStatus sx127x_poll_tx(
    Sx127x *radio,
    uint32_t now_ms,
    uint32_t timeout_ms);
bool sx127x_start_rx(Sx127x *radio);
bool sx127x_poll_rx(
    Sx127x *radio,
    uint8_t *payload,
    size_t capacity,
    uint8_t *length);
void sx127x_sleep(Sx127x *radio);

#endif

