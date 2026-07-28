#include "sx127x.h"

#define REG_FIFO                 0x00U
#define REG_OP_MODE              0x01U
#define REG_FRF_MSB              0x06U
#define REG_FRF_MID              0x07U
#define REG_FRF_LSB              0x08U
#define REG_PA_CONFIG            0x09U
#define REG_LNA                  0x0CU
#define REG_FIFO_ADDR_PTR        0x0DU
#define REG_FIFO_TX_BASE_ADDR    0x0EU
#define REG_FIFO_RX_BASE_ADDR    0x0FU
#define REG_FIFO_RX_CURRENT_ADDR 0x10U
#define REG_IRQ_FLAGS            0x12U
#define REG_RX_NB_BYTES          0x13U
#define REG_MODEM_CONFIG_1       0x1DU
#define REG_MODEM_CONFIG_2       0x1EU
#define REG_PREAMBLE_MSB         0x20U
#define REG_PREAMBLE_LSB         0x21U
#define REG_PAYLOAD_LENGTH       0x22U
#define REG_MODEM_CONFIG_3       0x26U
#define REG_SYNC_WORD            0x39U
#define REG_VERSION              0x42U
#define REG_PA_DAC               0x4DU

#define MODE_LONG_RANGE          0x80U
#define MODE_SLEEP               0x00U
#define MODE_STANDBY             0x01U
#define MODE_TX                  0x03U
#define MODE_RX_CONTINUOUS       0x05U

#define IRQ_RX_DONE              0x40U
#define IRQ_PAYLOAD_CRC_ERROR    0x20U
#define IRQ_TX_DONE              0x08U

#define SX127X_SPI_TIMEOUT_MS     10U
#define SX127X_VERSION_EXPECTED   0x12U

static void select_radio(Sx127x *radio)
{
    HAL_GPIO_WritePin(radio->nss_port, radio->nss_pin, GPIO_PIN_RESET);
}

static void deselect_radio(Sx127x *radio)
{
    HAL_GPIO_WritePin(radio->nss_port, radio->nss_pin, GPIO_PIN_SET);
}

static bool transfer(
    Sx127x *radio,
    uint8_t address,
    const uint8_t *tx_data,
    uint8_t *rx_data,
    uint8_t length,
    bool write)
{
    uint8_t command = write ? (uint8_t)(address | 0x80U)
                            : (uint8_t)(address & 0x7FU);
    HAL_StatusTypeDef status;

    select_radio(radio);
    status = HAL_SPI_Transmit(
        radio->spi, &command, 1U, SX127X_SPI_TIMEOUT_MS);
    if ((status == HAL_OK) && (length > 0U)) {
        if (write) {
            status = HAL_SPI_Transmit(
                radio->spi,
                (uint8_t *)tx_data,
                length,
                SX127X_SPI_TIMEOUT_MS);
        } else {
            status = HAL_SPI_Receive(
                radio->spi,
                rx_data,
                length,
                SX127X_SPI_TIMEOUT_MS);
        }
    }
    deselect_radio(radio);
    if (status != HAL_OK) {
        radio->io_error = true;
        return false;
    }
    return true;
}

static bool write_reg(Sx127x *radio, uint8_t address, uint8_t value)
{
    return transfer(radio, address, &value, NULL, 1U, true);
}

static bool read_reg(Sx127x *radio, uint8_t address, uint8_t *value)
{
    return transfer(radio, address, NULL, value, 1U, false);
}

static bool write_fifo(
    Sx127x *radio,
    const uint8_t *payload,
    uint8_t length)
{
    return transfer(radio, REG_FIFO, payload, NULL, length, true);
}

static bool read_fifo(Sx127x *radio, uint8_t *payload, uint8_t length)
{
    return transfer(radio, REG_FIFO, NULL, payload, length, false);
}

static bool set_mode(Sx127x *radio, uint8_t mode)
{
    return write_reg(radio, REG_OP_MODE, (uint8_t)(MODE_LONG_RANGE | mode));
}

bool sx127x_set_frequency(Sx127x *radio, uint32_t frequency_hz)
{
    /* FRF = frequency * 2^19 / 32 MHz，使用 64 位避免中间值溢出。 */
    uint64_t frf = ((uint64_t)frequency_hz << 19) / UINT64_C(32000000);

    return set_mode(radio, MODE_STANDBY)
        && write_reg(radio, REG_FRF_MSB, (uint8_t)(frf >> 16))
        && write_reg(radio, REG_FRF_MID, (uint8_t)(frf >> 8))
        && write_reg(radio, REG_FRF_LSB, (uint8_t)frf);
}

static bool set_tx_power(Sx127x *radio, int8_t dbm)
{
    uint8_t output_power;

    if (dbm < 2) {
        dbm = 2;
    } else if (dbm > 17) {
        dbm = 17;
    }
    output_power = (uint8_t)(dbm - 2);
    return write_reg(radio, REG_PA_DAC, 0x84U)
        && write_reg(
            radio,
            REG_PA_CONFIG,
            (uint8_t)(0x80U | output_power));
}

bool sx127x_init(
    Sx127x *radio,
    SPI_HandleTypeDef *spi,
    GPIO_TypeDef *nss_port,
    uint16_t nss_pin,
    GPIO_TypeDef *reset_port,
    uint16_t reset_pin,
    uint32_t frequency_hz,
    int8_t tx_power_dbm)
{
    uint8_t version = 0U;

    radio->spi = spi;
    radio->nss_port = nss_port;
    radio->nss_pin = nss_pin;
    radio->reset_port = reset_port;
    radio->reset_pin = reset_pin;
    radio->transmitting = false;
    radio->io_error = false;

    deselect_radio(radio);
    HAL_GPIO_WritePin(reset_port, reset_pin, GPIO_PIN_RESET);
    HAL_Delay(2U);
    HAL_GPIO_WritePin(reset_port, reset_pin, GPIO_PIN_SET);
    HAL_Delay(10U);

    if (!read_reg(radio, REG_VERSION, &version)
        || (version != SX127X_VERSION_EXPECTED)) {
        return false;
    }

    return set_mode(radio, MODE_SLEEP)
        && sx127x_set_frequency(radio, frequency_hz)
        && write_reg(radio, REG_FIFO_TX_BASE_ADDR, 0x00U)
        && write_reg(radio, REG_FIFO_RX_BASE_ADDR, 0x00U)
        && write_reg(radio, REG_LNA, 0x23U)
        /* BW=125 kHz, CR=4/5, explicit header. */
        && write_reg(radio, REG_MODEM_CONFIG_1, 0x72U)
        /* SF7, payload CRC enabled, symbol-timeout MSBs=0. */
        && write_reg(radio, REG_MODEM_CONFIG_2, 0x74U)
        /* Low-data-rate optimization off, AGC on. */
        && write_reg(radio, REG_MODEM_CONFIG_3, 0x04U)
        && write_reg(radio, REG_PREAMBLE_MSB, 0x00U)
        && write_reg(radio, REG_PREAMBLE_LSB, 0x0CU)
        && write_reg(radio, REG_SYNC_WORD, 0x12U)
        && set_tx_power(radio, tx_power_dbm)
        && write_reg(radio, REG_IRQ_FLAGS, 0xFFU)
        && set_mode(radio, MODE_STANDBY);
}

bool sx127x_begin_tx(
    Sx127x *radio,
    const uint8_t *payload,
    uint8_t length,
    uint32_t now_ms)
{
    if (radio->transmitting || (length == 0U)) {
        return false;
    }
    radio->io_error = false;
    if (!set_mode(radio, MODE_STANDBY)
        || !write_reg(radio, REG_IRQ_FLAGS, 0xFFU)
        || !write_reg(radio, REG_FIFO_ADDR_PTR, 0x00U)
        || !write_fifo(radio, payload, length)
        || !write_reg(radio, REG_PAYLOAD_LENGTH, length)
        || !set_mode(radio, MODE_TX)) {
        return false;
    }
    radio->tx_started_ms = now_ms;
    radio->transmitting = true;
    return true;
}

Sx127xTxStatus sx127x_poll_tx(
    Sx127x *radio,
    uint32_t now_ms,
    uint32_t timeout_ms)
{
    uint8_t flags = 0U;

    if (!radio->transmitting) {
        return SX127X_TX_DONE;
    }
    if (!read_reg(radio, REG_IRQ_FLAGS, &flags)) {
        radio->transmitting = false;
        return SX127X_TX_IO_ERROR;
    }
    if ((flags & IRQ_TX_DONE) != 0U) {
        (void)write_reg(radio, REG_IRQ_FLAGS, IRQ_TX_DONE);
        radio->transmitting = false;
        return SX127X_TX_DONE;
    }
    if ((now_ms - radio->tx_started_ms) > timeout_ms) {
        (void)set_mode(radio, MODE_STANDBY);
        radio->transmitting = false;
        return SX127X_TX_TIMEOUT;
    }
    return SX127X_TX_BUSY;
}

bool sx127x_start_rx(Sx127x *radio)
{
    return write_reg(radio, REG_IRQ_FLAGS, 0xFFU)
        && set_mode(radio, MODE_RX_CONTINUOUS);
}

bool sx127x_poll_rx(
    Sx127x *radio,
    uint8_t *payload,
    size_t capacity,
    uint8_t *length)
{
    uint8_t flags = 0U;
    uint8_t packet_length = 0U;
    uint8_t current_address = 0U;

    *length = 0U;
    if (!read_reg(radio, REG_IRQ_FLAGS, &flags)) {
        return false;
    }
    if ((flags & IRQ_RX_DONE) == 0U) {
        return true;
    }
    (void)write_reg(
        radio,
        REG_IRQ_FLAGS,
        (uint8_t)(IRQ_RX_DONE | IRQ_PAYLOAD_CRC_ERROR));
    /* 硬件包 CRC 错误直接丢弃；上层还会再次验证协议 CRC16。 */
    if ((flags & IRQ_PAYLOAD_CRC_ERROR) != 0U) {
        return true;
    }
    if (!read_reg(radio, REG_RX_NB_BYTES, &packet_length)
        || !read_reg(radio, REG_FIFO_RX_CURRENT_ADDR, &current_address)
        || !write_reg(radio, REG_FIFO_ADDR_PTR, current_address)) {
        return false;
    }
    if ((size_t)packet_length > capacity) {
        uint8_t discarded;
        while (packet_length-- > 0U) {
            if (!read_fifo(radio, &discarded, 1U)) {
                return false;
            }
        }
        return true;
    }
    if (!read_fifo(radio, payload, packet_length)) {
        return false;
    }
    *length = packet_length;
    return true;
}

void sx127x_sleep(Sx127x *radio)
{
    (void)set_mode(radio, MODE_SLEEP);
    radio->transmitting = false;
}
