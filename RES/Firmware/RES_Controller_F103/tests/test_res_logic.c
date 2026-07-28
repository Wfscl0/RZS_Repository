#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "res_config.h"
#include "res_fsm.h"
#include "res_protocol.h"

static void test_protocol_round_trip(void)
{
    ResCommandFrame input = {
        .pair_id = RES_PAIR_ID,
        .session_id = UINT32_C(0x12345678),
        .sequence = UINT16_C(0x3456),
        .command = RES_COMMAND_GO,
        .flags = RES_FLAG_RADIO_OK | RES_FLAG_ADC_OK,
        .battery_mv = UINT16_C(11980),
        .uptime_ms = UINT32_C(0x89ABCDEF)
    };
    ResCommandFrame output;
    uint8_t bytes[RES_COMMAND_FRAME_SIZE];

    res_protocol_encode_command(&input, bytes);
    assert(res_protocol_decode_command(bytes, &output));
    assert(output.pair_id == input.pair_id);
    assert(output.session_id == input.session_id);
    assert(output.sequence == input.sequence);
    assert(output.command == input.command);
    assert(output.flags == input.flags);
    assert(output.battery_mv == input.battery_mv);
    assert(output.uptime_ms == input.uptime_ms);

    bytes[9] ^= 0x01U;
    assert(!res_protocol_decode_command(bytes, &output));
}

static void test_ack_round_trip(void)
{
    ResAckFrame input = {
        .pair_id = RES_PAIR_ID,
        .session_id = UINT32_C(0x87654321),
        .acknowledged_sequence = 42U,
        .receiver_state = 3U,
        .receiver_faults = 0U
    };
    ResAckFrame output;
    uint8_t bytes[RES_ACK_FRAME_SIZE];

    res_protocol_encode_ack(&input, bytes);
    assert(res_protocol_decode_ack(bytes, sizeof(bytes), &output));
    assert(memcmp(&input, &output, sizeof(input)) == 0);
    assert(!res_protocol_decode_ack(bytes, sizeof(bytes) - 1U, &output));
}

static void finish_lamp_test_and_arm(ResFsm *fsm)
{
    res_fsm_update(fsm, RES_LAMP_TEST_MS, false, false);
    res_fsm_update(
        fsm,
        RES_LAMP_TEST_MS + RES_GO_RELEASE_MS,
        false,
        false);
    assert(fsm->state == RES_STATE_STANDBY);
    assert(fsm->go_armed);
}

static void test_go_requires_fresh_ack(void)
{
    ResFsm fsm;
    uint32_t t = RES_LAMP_TEST_MS + RES_GO_RELEASE_MS;

    res_fsm_init(&fsm, 0U, false);
    finish_lamp_test_and_arm(&fsm);

    res_fsm_update(&fsm, t + 1U, true, false);
    res_fsm_update(&fsm, t + 1U + RES_GO_DEBOUNCE_MS, true, false);
    assert(fsm.state == RES_STATE_STANDBY);
    assert(fsm.go_rejected_no_link);
    assert(!fsm.run_authorized);
}

static void test_go_and_link_loss_latch(void)
{
    ResFsm fsm;
    uint32_t t = RES_LAMP_TEST_MS + RES_GO_RELEASE_MS;

    res_fsm_init(&fsm, 0U, false);
    finish_lamp_test_and_arm(&fsm);
    res_fsm_on_ack(&fsm, t);

    res_fsm_update(&fsm, t + 1U, true, false);
    res_fsm_update(&fsm, t + 1U + RES_GO_DEBOUNCE_MS, true, false);
    assert(fsm.state == RES_STATE_GO_REPEAT);
    assert(fsm.run_authorized);
    assert(res_fsm_command(&fsm) == RES_COMMAND_GO);

    res_fsm_update(
        &fsm,
        t + RES_LINK_LOSS_LATCH_MS + 1U,
        true,
        false);
    assert(fsm.state == RES_STATE_ESTOP_LATCHED);
    assert(fsm.estop_reason == RES_ESTOP_LINK_LOSS);
    assert(res_fsm_command(&fsm) == RES_COMMAND_ESTOP);

    res_fsm_on_ack(&fsm, t + RES_LINK_LOSS_LATCH_MS + 2U);
    res_fsm_update(
        &fsm,
        t + RES_LINK_LOSS_LATCH_MS + 3U,
        false,
        false);
    assert(fsm.state == RES_STATE_ESTOP_LATCHED);
}

static void test_nc_shutdown_is_immediate_and_latched(void)
{
    ResFsm fsm;

    res_fsm_init(&fsm, 0U, false);
    res_fsm_update(&fsm, 10U, false, true);
    assert(fsm.state == RES_STATE_ESTOP_LATCHED);
    assert(fsm.estop_reason == RES_ESTOP_BUTTON_OR_WIRE_OPEN);

    res_fsm_update(&fsm, 20U, false, false);
    assert(fsm.state == RES_STATE_ESTOP_LATCHED);
}

int main(void)
{
    test_protocol_round_trip();
    test_ack_round_trip();
    test_go_requires_fresh_ack();
    test_go_and_link_loss_latch();
    test_nc_shutdown_is_immediate_and_latched();
    puts("RES logic tests passed");
    return 0;
}

