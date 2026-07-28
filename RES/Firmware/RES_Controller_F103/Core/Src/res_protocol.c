#include "res_protocol.h"

#define RES_MAGIC_0 0x52U
#define RES_MAGIC_1 0x45U
#define RES_PROTOCOL_VERSION 0x01U
#define RES_FRAME_TYPE_COMMAND 0x01U
#define RES_FRAME_TYPE_ACK 0x02U

static void put_u16_le(uint8_t *dst, uint16_t value)
{
    dst[0] = (uint8_t)value;
    dst[1] = (uint8_t)(value >> 8);
}

static void put_u32_le(uint8_t *dst, uint32_t value)
{
    dst[0] = (uint8_t)value;
    dst[1] = (uint8_t)(value >> 8);
    dst[2] = (uint8_t)(value >> 16);
    dst[3] = (uint8_t)(value >> 24);
}

static uint16_t get_u16_le(const uint8_t *src)
{
    return (uint16_t)((uint16_t)src[0] | ((uint16_t)src[1] << 8));
}

static uint32_t get_u32_le(const uint8_t *src)
{
    return (uint32_t)src[0]
        | ((uint32_t)src[1] << 8)
        | ((uint32_t)src[2] << 16)
        | ((uint32_t)src[3] << 24);
}

uint16_t res_crc16_ccitt(const uint8_t *data, size_t length)
{
    uint16_t crc = UINT16_C(0xFFFF);
    size_t i;
    uint8_t bit;

    for (i = 0U; i < length; ++i) {
        crc ^= (uint16_t)data[i] << 8;
        for (bit = 0U; bit < 8U; ++bit) {
            if ((crc & UINT16_C(0x8000)) != 0U) {
                crc = (uint16_t)((crc << 1) ^ UINT16_C(0x1021));
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

void res_protocol_encode_command(
    const ResCommandFrame *frame,
    uint8_t output[RES_COMMAND_FRAME_SIZE])
{
    uint16_t crc;

    output[0] = RES_MAGIC_0;
    output[1] = RES_MAGIC_1;
    output[2] = RES_PROTOCOL_VERSION;
    output[3] = RES_FRAME_TYPE_COMMAND;
    put_u32_le(&output[4], frame->pair_id);
    put_u32_le(&output[8], frame->session_id);
    put_u16_le(&output[12], frame->sequence);
    output[14] = (uint8_t)frame->command;
    output[15] = frame->flags;
    put_u16_le(&output[16], frame->battery_mv);
    put_u32_le(&output[18], frame->uptime_ms);
    crc = res_crc16_ccitt(output, RES_COMMAND_FRAME_SIZE - 2U);
    put_u16_le(&output[22], crc);
}

bool res_protocol_decode_command(
    const uint8_t input[RES_COMMAND_FRAME_SIZE],
    ResCommandFrame *frame)
{
    uint16_t expected_crc;

    if ((input[0] != RES_MAGIC_0) || (input[1] != RES_MAGIC_1)
        || (input[2] != RES_PROTOCOL_VERSION)
        || (input[3] != RES_FRAME_TYPE_COMMAND)) {
        return false;
    }
    expected_crc = res_crc16_ccitt(input, RES_COMMAND_FRAME_SIZE - 2U);
    if (expected_crc != get_u16_le(&input[22])) {
        return false;
    }

    frame->pair_id = get_u32_le(&input[4]);
    frame->session_id = get_u32_le(&input[8]);
    frame->sequence = get_u16_le(&input[12]);
    frame->command = (ResCommand)input[14];
    frame->flags = input[15];
    frame->battery_mv = get_u16_le(&input[16]);
    frame->uptime_ms = get_u32_le(&input[18]);
    return true;
}

void res_protocol_encode_ack(
    const ResAckFrame *frame,
    uint8_t output[RES_ACK_FRAME_SIZE])
{
    uint16_t crc;

    output[0] = RES_MAGIC_0;
    output[1] = RES_MAGIC_1;
    output[2] = RES_PROTOCOL_VERSION;
    output[3] = RES_FRAME_TYPE_ACK;
    put_u32_le(&output[4], frame->pair_id);
    put_u32_le(&output[8], frame->session_id);
    put_u16_le(&output[12], frame->acknowledged_sequence);
    output[14] = frame->receiver_state;
    output[15] = frame->receiver_faults;
    crc = res_crc16_ccitt(output, RES_ACK_FRAME_SIZE - 2U);
    put_u16_le(&output[16], crc);
}

bool res_protocol_decode_ack(
    const uint8_t *input,
    size_t length,
    ResAckFrame *frame)
{
    uint16_t expected_crc;

    if ((length != RES_ACK_FRAME_SIZE)
        || (input[0] != RES_MAGIC_0)
        || (input[1] != RES_MAGIC_1)
        || (input[2] != RES_PROTOCOL_VERSION)
        || (input[3] != RES_FRAME_TYPE_ACK)) {
        return false;
    }
    expected_crc = res_crc16_ccitt(input, RES_ACK_FRAME_SIZE - 2U);
    if (expected_crc != get_u16_le(&input[16])) {
        return false;
    }

    frame->pair_id = get_u32_le(&input[4]);
    frame->session_id = get_u32_le(&input[8]);
    frame->acknowledged_sequence = get_u16_le(&input[12]);
    frame->receiver_state = input[14];
    frame->receiver_faults = input[15];
    return true;
}

