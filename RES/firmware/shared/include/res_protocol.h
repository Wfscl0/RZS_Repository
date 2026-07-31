#ifndef RES_PROTOCOL_H
#define RES_PROTOCOL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RES_PROTOCOL_VERSION       2u
#define RES_FRAME_HEADER_SIZE      19u
#define RES_FRAME_TRAILER_SIZE     10u
#define RES_MAX_PAYLOAD_SIZE       32u
#define RES_MAX_FRAME_SIZE         (RES_FRAME_HEADER_SIZE + RES_MAX_PAYLOAD_SIZE + RES_FRAME_TRAILER_SIZE)
#define RES_AUTH_KEY_SIZE          16u

/*
 * The legal operating frequencies are configured in the E220 STM8 bridge.
 * Endpoints only exchange a channel index.  Three channels are the minimum
 * used by this project for deterministic automatic hopping and resync scan.
 */
#define RES_HOP_CHANNEL_COUNT      3u

#define RES_NODE_REMOTE            0x0001u
#define RES_NODE_VEHICLE           0x0002u
#define RES_NODE_BROADCAST         0xFFFFu

typedef enum {
    RES_MSG_HELLO = 1,
    RES_MSG_HEARTBEAT = 2,
    RES_MSG_COMMAND = 3,
    RES_MSG_ACK = 4,
    RES_MSG_STATUS = 5
} res_message_type_t;

typedef enum {
    RES_COMMAND_STOP = 0,
    RES_COMMAND_READY = 1,
    RES_COMMAND_GO = 2
} res_command_t;

enum {
    RES_FLAG_ACK_REQUIRED = 1u << 0,
    RES_FLAG_CRITICAL = 1u << 1,
    RES_FLAG_RETRANSMISSION = 1u << 2
};

typedef struct {
    uint8_t type;
    uint16_t source;
    uint16_t destination;
    uint8_t flags;
    uint8_t channel;
    uint32_t sequence;
    uint32_t session;
    uint8_t payload_length;
    uint8_t payload[RES_MAX_PAYLOAD_SIZE];
} res_frame_t;

typedef enum {
    RES_DECODE_OK = 0,
    RES_DECODE_NEED_MORE,
    RES_DECODE_BAD_LENGTH,
    RES_DECODE_BAD_MAGIC,
    RES_DECODE_BAD_VERSION,
    RES_DECODE_BAD_CRC,
    RES_DECODE_BAD_AUTH
} res_decode_result_t;

typedef struct {
    uint8_t buffer[RES_MAX_FRAME_SIZE];
    uint8_t length;
    uint8_t expected_length;
} res_stream_parser_t;

typedef struct {
    bool initialized;
    uint32_t session;
    uint32_t highest_sequence;
    uint32_t seen_bitmap;
} res_replay_window_t;

uint16_t res_crc16_ccitt(const uint8_t *data, size_t length);
uint64_t res_siphash24(const uint8_t key[RES_AUTH_KEY_SIZE],
                       const uint8_t *data,
                       size_t length);

size_t res_frame_encode(uint8_t *output,
                        size_t output_capacity,
                        const res_frame_t *frame,
                        const uint8_t key[RES_AUTH_KEY_SIZE]);

res_decode_result_t res_frame_decode(res_frame_t *frame,
                                     const uint8_t *input,
                                     size_t input_length,
                                     const uint8_t key[RES_AUTH_KEY_SIZE]);

void res_stream_parser_init(res_stream_parser_t *parser);

bool res_stream_parser_push(res_stream_parser_t *parser,
                            uint8_t byte,
                            res_frame_t *frame,
                            const uint8_t key[RES_AUTH_KEY_SIZE]);

bool res_replay_window_accept(res_replay_window_t *window,
                              uint32_t session,
                              uint32_t sequence);

/* Use only after an authenticated physical re-pairing or deliberate local reset. */
void res_replay_window_reset(res_replay_window_t *window);

void res_put_u16_le(uint8_t *destination, uint16_t value);
void res_put_u32_le(uint8_t *destination, uint32_t value);
uint16_t res_get_u16_le(const uint8_t *source);
uint32_t res_get_u32_le(const uint8_t *source);

/*
 * Returns the channel used after a successfully transmitted/received frame.
 * Both STM32 endpoints and both STM8 radio bridges use this exact function.
 * A lost frame is recovered by the receiver bridge scanning every channel.
 */
uint8_t res_hop_next_channel(uint8_t current_channel,
                             uint32_t session,
                             uint32_t sequence);

#ifdef __cplusplus
}
#endif

#endif
