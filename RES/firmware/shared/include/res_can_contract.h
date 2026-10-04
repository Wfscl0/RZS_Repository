#ifndef RES_CAN_CONTRACT_H
#define RES_CAN_CONTRACT_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RES_CAN_STATUS_ID          0x510u
#define RES_CAN_GO_EVENT_ID        0x511u
#define RES_CAN_DIAGNOSTIC_ID      0x512u
#define RES_CAN_FRAME_LENGTH       8u
#define RES_CAN_PROTOCOL_VERSION   1u

typedef enum {
    RES_CAN_STATE_BOOT = 0,
    RES_CAN_STATE_WAIT_LINK = 1,
    RES_CAN_STATE_READY = 2,
    RES_CAN_STATE_GO_EVENT = 3,
    RES_CAN_STATE_STOPPED_FAULT = 4
} res_can_state_t;

enum {
    RES_CAN_FLAG_LINK_OK = 1u << 0,
    RES_CAN_FLAG_REMOTE_STOP = 1u << 1,
    RES_CAN_FLAG_RADIO_TIMEOUT = 1u << 2,
    RES_CAN_FLAG_AUTH_FAILURE = 1u << 3,
    RES_CAN_FLAG_RELAY_MISMATCH = 1u << 4,
    RES_CAN_FLAG_SESSION_RECOVERY = 1u << 5,
    RES_CAN_FLAG_CAN_LOCAL_FAULT = 1u << 6,
    RES_CAN_FLAG_SOFTWARE_LATCHED = 1u << 7
};

typedef struct {
    res_can_state_t state;
    uint16_t flags;
    uint8_t channel;
    bool relay_1_closed;
    bool relay_2_closed;
    uint16_t go_event_counter;
} res_can_status_t;

void res_can_pack_status(uint8_t output[RES_CAN_FRAME_LENGTH],
                         const res_can_status_t *status);

bool res_can_unpack_status(res_can_status_t *status,
                           const uint8_t input[RES_CAN_FRAME_LENGTH]);

void res_can_pack_go_event(uint8_t output[RES_CAN_FRAME_LENGTH],
                           uint32_t remote_session,
                           uint32_t command_counter);

#ifdef __cplusplus
}
#endif

#endif
