#ifndef RES_PROTOCOL_H
#define RES_PROTOCOL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define RES_COMMAND_FRAME_SIZE 24U
#define RES_ACK_FRAME_SIZE     18U

typedef enum {
    RES_COMMAND_READY = 0x11,
    RES_COMMAND_GO = 0x13,
    RES_COMMAND_ESTOP = 0x10
} ResCommand;

enum {
    RES_FLAG_RADIO_OK = 1U << 0,
    RES_FLAG_ADC_OK = 1U << 1,
    RES_FLAG_LOW_BATTERY = 1U << 2,
    RES_FLAG_RUN_AUTHORIZED = 1U << 3,
    RES_FLAG_ESTOP_LATCHED = 1U << 4,
    RES_FLAG_GO_PRESSED = 1U << 5,
    RES_FLAG_SHUT_OPEN = 1U << 6
};

typedef struct {
    uint32_t pair_id;
    uint32_t session_id;
    uint16_t sequence;
    ResCommand command;
    uint8_t flags;
    uint16_t battery_mv;
    uint32_t uptime_ms;
} ResCommandFrame;

typedef struct {
    uint32_t pair_id;
    uint32_t session_id;
    uint16_t acknowledged_sequence;
    uint8_t receiver_state;
    uint8_t receiver_faults;
} ResAckFrame;

uint16_t res_crc16_ccitt(const uint8_t *data, size_t length);
void res_protocol_encode_command(
    const ResCommandFrame *frame,
    uint8_t output[RES_COMMAND_FRAME_SIZE]);
bool res_protocol_decode_command(
    const uint8_t input[RES_COMMAND_FRAME_SIZE],
    ResCommandFrame *frame);
void res_protocol_encode_ack(
    const ResAckFrame *frame,
    uint8_t output[RES_ACK_FRAME_SIZE]);
bool res_protocol_decode_ack(
    const uint8_t *input,
    size_t length,
    ResAckFrame *frame);

#endif

