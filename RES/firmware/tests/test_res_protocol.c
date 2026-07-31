#include "res_protocol.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static const uint8_t key[16] = {
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
    0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
};

int main(void)
{
    static const uint8_t siphash_empty[8] =
        {0x31,0x0e,0x0e,0xdd,0x47,0xdb,0x6f,0x72};
    res_frame_t input;
    res_frame_t output;
    res_stream_parser_t parser;
    res_replay_window_t replay = {0};
    uint8_t encoded[RES_MAX_FRAME_SIZE];
    uint64_t empty_tag;
    size_t length;
    size_t index;

    empty_tag = res_siphash24(key, NULL, 0u);
    for (index = 0u; index < 8u; ++index) {
        assert((uint8_t)(empty_tag >> (8u * index)) == siphash_empty[index]);
    }

    memset(&input, 0, sizeof(input));
    input.type = RES_MSG_COMMAND;
    input.source = RES_NODE_REMOTE;
    input.destination = RES_NODE_VEHICLE;
    input.flags = RES_FLAG_CRITICAL | RES_FLAG_ACK_REQUIRED;
    input.channel = 0u;
    input.sequence = 12345u;
    input.session = 0x12345678u;
    input.payload_length = 3u;
    input.payload[0] = RES_COMMAND_STOP;
    input.payload[1] = 0xA5u;
    input.payload[2] = 0x5Au;

    length = res_frame_encode(encoded, sizeof(encoded), &input, key);
    assert(length == RES_FRAME_HEADER_SIZE + 3u + RES_FRAME_TRAILER_SIZE);
    assert(res_frame_decode(&output, encoded, length, key) == RES_DECODE_OK);
    assert(output.sequence == input.sequence);
    assert(output.session == input.session);
    assert(output.payload_length == input.payload_length);
    assert(memcmp(output.payload, input.payload, input.payload_length) == 0);

    encoded[20] ^= 0x01u;
    assert(res_frame_decode(&output, encoded, length, key) == RES_DECODE_BAD_CRC);
    encoded[20] ^= 0x01u;
    encoded[length - 1u] ^= 0x01u;
    assert(res_frame_decode(&output, encoded, length, key) == RES_DECODE_BAD_AUTH);
    encoded[length - 1u] ^= 0x01u;

    res_stream_parser_init(&parser);
    assert(!res_stream_parser_push(&parser, 0x00u, &output, key));
    for (index = 0u; index < length; ++index) {
        const bool complete = res_stream_parser_push(&parser, encoded[index], &output, key);
        assert(complete == (index == length - 1u));
    }
    assert(output.sequence == input.sequence);

    assert(res_replay_window_accept(&replay, 1u, 100u));
    assert(!res_replay_window_accept(&replay, 1u, 100u));
    assert(res_replay_window_accept(&replay, 1u, 102u));
    assert(res_replay_window_accept(&replay, 1u, 101u));
    assert(!res_replay_window_accept(&replay, 1u, 101u));
    assert(!res_replay_window_accept(&replay, 1u, 60u));
    assert(!res_replay_window_accept(&replay, 2u, 1u));
    res_replay_window_reset(&replay);
    assert(res_replay_window_accept(&replay, 2u, 1u));

    /* Both bridges/endpoints must calculate the same deterministic sequence. */
    assert(res_hop_next_channel(0u, 0x12345678u, 1u) < RES_HOP_CHANNEL_COUNT);
    assert(res_hop_next_channel(0u, 0x12345678u, 1u) != 0u);
    assert(res_hop_next_channel(1u, 0x12345678u, 2u) != 1u);

    puts("test_res_protocol: PASS");
    return 0;
}
