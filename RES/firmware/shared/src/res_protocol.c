#include "res_protocol.h"

#include <string.h>

#define RES_MAGIC_0 0x52u
#define RES_MAGIC_1 0x53u

static uint64_t rotate_left64(uint64_t value, unsigned int count)
{
    return (value << count) | (value >> (64u - count));
}

static uint64_t get_u64_le(const uint8_t *source)
{
    uint64_t value = 0u;
    unsigned int index;
    for (index = 0u; index < 8u; ++index) {
        value |= ((uint64_t)source[index]) << (8u * index);
    }
    return value;
}

static void put_u64_le(uint8_t *destination, uint64_t value)
{
    unsigned int index;
    for (index = 0u; index < 8u; ++index) {
        destination[index] = (uint8_t)(value >> (8u * index));
    }
}

void res_put_u16_le(uint8_t *destination, uint16_t value)
{
    destination[0] = (uint8_t)value;
    destination[1] = (uint8_t)(value >> 8u);
}

void res_put_u32_le(uint8_t *destination, uint32_t value)
{
    destination[0] = (uint8_t)value;
    destination[1] = (uint8_t)(value >> 8u);
    destination[2] = (uint8_t)(value >> 16u);
    destination[3] = (uint8_t)(value >> 24u);
}

uint16_t res_get_u16_le(const uint8_t *source)
{
    return (uint16_t)((uint16_t)source[0] | ((uint16_t)source[1] << 8u));
}

uint32_t res_get_u32_le(const uint8_t *source)
{
    return (uint32_t)source[0] |
           ((uint32_t)source[1] << 8u) |
           ((uint32_t)source[2] << 16u) |
           ((uint32_t)source[3] << 24u);
}

uint8_t res_hop_next_channel(uint8_t current_channel,
                             uint32_t session,
                             uint32_t sequence)
{
    uint32_t mixed;
    uint8_t step;

    if (current_channel >= RES_HOP_CHANNEL_COUNT) {
        current_channel = 0u;
    }
    mixed = session ^ (sequence * 0x9E3779B9u);
    mixed ^= mixed >> 16u;
    mixed *= 0x7FEB352Du;
    mixed ^= mixed >> 15u;
    step = (uint8_t)(1u + (mixed % (RES_HOP_CHANNEL_COUNT - 1u)));
    return (uint8_t)((current_channel + step) % RES_HOP_CHANNEL_COUNT);
}

uint16_t res_crc16_ccitt(const uint8_t *data, size_t length)
{
    uint16_t crc = 0xFFFFu;
    size_t index;
    unsigned int bit;

    for (index = 0u; index < length; ++index) {
        crc ^= (uint16_t)data[index] << 8u;
        for (bit = 0u; bit < 8u; ++bit) {
            crc = (crc & 0x8000u) ? (uint16_t)((crc << 1u) ^ 0x1021u)
                                  : (uint16_t)(crc << 1u);
        }
    }
    return crc;
}

#define SIPROUND() do {                 \
    v0 += v1; v1 = rotate_left64(v1, 13); v1 ^= v0; v0 = rotate_left64(v0, 32); \
    v2 += v3; v3 = rotate_left64(v3, 16); v3 ^= v2;                              \
    v0 += v3; v3 = rotate_left64(v3, 21); v3 ^= v0;                              \
    v2 += v1; v1 = rotate_left64(v1, 17); v1 ^= v2; v2 = rotate_left64(v2, 32); \
} while (0)

uint64_t res_siphash24(const uint8_t key[RES_AUTH_KEY_SIZE],
                       const uint8_t *data,
                       size_t length)
{
    const uint64_t k0 = get_u64_le(key);
    const uint64_t k1 = get_u64_le(key + 8u);
    uint64_t v0 = UINT64_C(0x736f6d6570736575) ^ k0;
    uint64_t v1 = UINT64_C(0x646f72616e646f6d) ^ k1;
    uint64_t v2 = UINT64_C(0x6c7967656e657261) ^ k0;
    uint64_t v3 = UINT64_C(0x7465646279746573) ^ k1;
    uint64_t final_block = ((uint64_t)length) << 56u;
    size_t offset = 0u;
    unsigned int round;

    while ((length - offset) >= 8u) {
        const uint64_t message = get_u64_le(data + offset);
        v3 ^= message;
        SIPROUND();
        SIPROUND();
        v0 ^= message;
        offset += 8u;
    }

    for (round = 0u; offset + round < length; ++round) {
        final_block |= ((uint64_t)data[offset + round]) << (8u * round);
    }

    v3 ^= final_block;
    SIPROUND();
    SIPROUND();
    v0 ^= final_block;
    v2 ^= 0xFFu;
    SIPROUND();
    SIPROUND();
    SIPROUND();
    SIPROUND();
    return v0 ^ v1 ^ v2 ^ v3;
}

#undef SIPROUND

static bool constant_time_equal_8(const uint8_t *left, const uint8_t *right)
{
    uint8_t difference = 0u;
    unsigned int index;
    for (index = 0u; index < 8u; ++index) {
        difference |= (uint8_t)(left[index] ^ right[index]);
    }
    return difference == 0u;
}

size_t res_frame_encode(uint8_t *output,
                        size_t output_capacity,
                        const res_frame_t *frame,
                        const uint8_t key[RES_AUTH_KEY_SIZE])
{
    size_t message_length;
    size_t total_length;
    uint16_t crc;
    uint64_t tag;

    if ((output == NULL) || (frame == NULL) || (key == NULL) ||
        (frame->payload_length > RES_MAX_PAYLOAD_SIZE)) {
        return 0u;
    }

    message_length = RES_FRAME_HEADER_SIZE + frame->payload_length;
    total_length = message_length + RES_FRAME_TRAILER_SIZE;
    if (output_capacity < total_length) {
        return 0u;
    }

    output[0] = RES_MAGIC_0;
    output[1] = RES_MAGIC_1;
    output[2] = RES_PROTOCOL_VERSION;
    output[3] = frame->type;
    res_put_u16_le(output + 4u, frame->source);
    res_put_u16_le(output + 6u, frame->destination);
    output[8] = frame->flags;
    output[9] = frame->channel;
    res_put_u32_le(output + 10u, frame->sequence);
    res_put_u32_le(output + 14u, frame->session);
    output[18] = frame->payload_length;
    if (frame->payload_length != 0u) {
        memcpy(output + RES_FRAME_HEADER_SIZE, frame->payload, frame->payload_length);
    }

    crc = res_crc16_ccitt(output, message_length);
    res_put_u16_le(output + message_length, crc);
    tag = res_siphash24(key, output, message_length + 2u);
    put_u64_le(output + message_length + 2u, tag);
    return total_length;
}

res_decode_result_t res_frame_decode(res_frame_t *frame,
                                     const uint8_t *input,
                                     size_t input_length,
                                     const uint8_t key[RES_AUTH_KEY_SIZE])
{
    size_t message_length;
    size_t expected_length;
    uint16_t expected_crc;
    uint64_t expected_tag;
    uint8_t tag_bytes[8];
    uint8_t payload_length;

    if ((frame == NULL) || (input == NULL) || (key == NULL)) {
        return RES_DECODE_BAD_LENGTH;
    }
    if (input_length < RES_FRAME_HEADER_SIZE + RES_FRAME_TRAILER_SIZE) {
        return RES_DECODE_NEED_MORE;
    }
    if ((input[0] != RES_MAGIC_0) || (input[1] != RES_MAGIC_1)) {
        return RES_DECODE_BAD_MAGIC;
    }
    if (input[2] != RES_PROTOCOL_VERSION) {
        return RES_DECODE_BAD_VERSION;
    }

    payload_length = input[18];
    if (payload_length > RES_MAX_PAYLOAD_SIZE) {
        return RES_DECODE_BAD_LENGTH;
    }
    message_length = RES_FRAME_HEADER_SIZE + payload_length;
    expected_length = message_length + RES_FRAME_TRAILER_SIZE;
    if (input_length != expected_length) {
        return (input_length < expected_length) ? RES_DECODE_NEED_MORE : RES_DECODE_BAD_LENGTH;
    }

    expected_crc = res_crc16_ccitt(input, message_length);
    if (res_get_u16_le(input + message_length) != expected_crc) {
        return RES_DECODE_BAD_CRC;
    }

    expected_tag = res_siphash24(key, input, message_length + 2u);
    put_u64_le(tag_bytes, expected_tag);
    if (!constant_time_equal_8(tag_bytes, input + message_length + 2u)) {
        return RES_DECODE_BAD_AUTH;
    }

    frame->type = input[3];
    frame->source = res_get_u16_le(input + 4u);
    frame->destination = res_get_u16_le(input + 6u);
    frame->flags = input[8];
    frame->channel = input[9];
    frame->sequence = res_get_u32_le(input + 10u);
    frame->session = res_get_u32_le(input + 14u);
    frame->payload_length = payload_length;
    if (payload_length != 0u) {
        memcpy(frame->payload, input + RES_FRAME_HEADER_SIZE, payload_length);
    }
    return RES_DECODE_OK;
}

void res_stream_parser_init(res_stream_parser_t *parser)
{
    if (parser != NULL) {
        parser->length = 0u;
        parser->expected_length = 0u;
    }
}

bool res_stream_parser_push(res_stream_parser_t *parser,
                            uint8_t byte,
                            res_frame_t *frame,
                            const uint8_t key[RES_AUTH_KEY_SIZE])
{
    if ((parser == NULL) || (frame == NULL) || (key == NULL)) {
        return false;
    }

    if (parser->length == 0u) {
        if (byte != RES_MAGIC_0) {
            return false;
        }
        parser->buffer[parser->length++] = byte;
        return false;
    }

    if ((parser->length == 1u) && (byte != RES_MAGIC_1)) {
        parser->length = (byte == RES_MAGIC_0) ? 1u : 0u;
        parser->buffer[0] = RES_MAGIC_0;
        return false;
    }

    if (parser->length >= RES_MAX_FRAME_SIZE) {
        res_stream_parser_init(parser);
        return false;
    }

    parser->buffer[parser->length++] = byte;
    if (parser->length == RES_FRAME_HEADER_SIZE) {
        if (parser->buffer[18] > RES_MAX_PAYLOAD_SIZE) {
            res_stream_parser_init(parser);
            return false;
        }
        parser->expected_length = (uint8_t)(RES_FRAME_HEADER_SIZE +
                                             parser->buffer[18] +
                                             RES_FRAME_TRAILER_SIZE);
    }

    if ((parser->expected_length != 0u) &&
        (parser->length == parser->expected_length)) {
        const bool valid = res_frame_decode(frame,
                                            parser->buffer,
                                            parser->length,
                                            key) == RES_DECODE_OK;
        res_stream_parser_init(parser);
        return valid;
    }
    return false;
}

bool res_replay_window_accept(res_replay_window_t *window,
                              uint32_t session,
                              uint32_t sequence)
{
    uint32_t distance;
    uint32_t mask;

    if (window == NULL) {
        return false;
    }
    if (!window->initialized) {
        window->initialized = true;
        window->session = session;
        window->highest_sequence = sequence;
        window->seen_bitmap = 1u;
        return true;
    }
    if (window->session != session) {
        return false;
    }

    if (sequence > window->highest_sequence) {
        distance = sequence - window->highest_sequence;
        window->seen_bitmap = (distance >= 32u) ? 1u
                                                : (window->seen_bitmap << distance) | 1u;
        window->highest_sequence = sequence;
        return true;
    }

    distance = window->highest_sequence - sequence;
    if (distance >= 32u) {
        return false;
    }
    mask = UINT32_C(1) << distance;
    if ((window->seen_bitmap & mask) != 0u) {
        return false;
    }
    window->seen_bitmap |= mask;
    return true;
}

void res_replay_window_reset(res_replay_window_t *window)
{
    if (window != NULL) {
        window->initialized = false;
        window->session = 0u;
        window->highest_sequence = 0u;
        window->seen_bitmap = 0u;
    }
}
