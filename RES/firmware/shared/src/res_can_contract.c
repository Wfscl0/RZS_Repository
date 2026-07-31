#include "res_can_contract.h"

#include <stddef.h>

#include "res_protocol.h"

void res_can_pack_status(uint8_t output[RES_CAN_FRAME_LENGTH],
                         const res_can_status_t *status)
{
    output[0] = RES_CAN_PROTOCOL_VERSION;
    output[1] = (uint8_t)status->state;
    res_put_u16_le(output + 2u, status->flags);
    output[4] = status->channel;
    output[5] = (uint8_t)((status->relay_1_closed ? 1u : 0u) |
                          (status->relay_2_closed ? 2u : 0u));
    res_put_u16_le(output + 6u, status->go_event_counter);
}

bool res_can_unpack_status(res_can_status_t *status,
                           const uint8_t input[RES_CAN_FRAME_LENGTH])
{
    if ((status == NULL) || (input == NULL) ||
        (input[0] != RES_CAN_PROTOCOL_VERSION) ||
        (input[1] > (uint8_t)RES_CAN_STATE_STOPPED_FAULT)) {
        return false;
    }
    status->state = (res_can_state_t)input[1];
    status->flags = res_get_u16_le(input + 2u);
    status->channel = input[4];
    status->relay_1_closed = (input[5] & 1u) != 0u;
    status->relay_2_closed = (input[5] & 2u) != 0u;
    status->go_event_counter = res_get_u16_le(input + 6u);
    return true;
}

void res_can_pack_go_event(uint8_t output[RES_CAN_FRAME_LENGTH],
                           uint32_t remote_session,
                           uint32_t command_counter)
{
    res_put_u32_le(output, remote_session);
    res_put_u32_le(output + 4u, command_counter);
}
