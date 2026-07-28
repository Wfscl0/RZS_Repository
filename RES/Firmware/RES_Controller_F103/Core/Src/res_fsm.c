#include "res_fsm.h"

#include <string.h>

#include "res_config.h"

static uint32_t elapsed_ms(uint32_t now_ms, uint32_t since_ms)
{
    return now_ms - since_ms;
}

void res_fsm_force_estop(
    ResFsm *fsm,
    uint32_t now_ms,
    ResEstopReason reason)
{
    /* 急停是单向状态迁移：只能重新上电，任何通信恢复都不能清除。 */
    if (fsm->state != RES_STATE_ESTOP_LATCHED) {
        fsm->state = RES_STATE_ESTOP_LATCHED;
        fsm->state_since_ms = now_ms;
        fsm->estop_reason = reason;
        fsm->run_authorized = false;
    }
}

void res_fsm_init(ResFsm *fsm, uint32_t now_ms, bool shut_circuit_open)
{
    memset(fsm, 0, sizeof(*fsm));
    fsm->state = RES_STATE_LAMP_TEST;
    fsm->state_since_ms = now_ms;
    if (shut_circuit_open) {
        res_fsm_force_estop(
            fsm, now_ms, RES_ESTOP_BUTTON_OR_WIRE_OPEN);
    }
}

void res_fsm_on_ack(ResFsm *fsm, uint32_t now_ms)
{
    fsm->last_ack_ms = now_ms;
    fsm->ever_acknowledged = true;
}

bool res_fsm_link_ok(const ResFsm *fsm, uint32_t now_ms)
{
    return fsm->ever_acknowledged
        && (elapsed_ms(now_ms, fsm->last_ack_ms)
            <= RES_LINK_GO_MAX_AGE_MS);
}

void res_fsm_update(
    ResFsm *fsm,
    uint32_t now_ms,
    bool go_pressed,
    bool shut_circuit_open)
{
    /*
     * SHUT 使用常闭触点。这里不对“开路”做消抖，按钮动作、断线或
     * 接插件脱落都应在第一次采样时进入安全状态。
     */
    if (shut_circuit_open) {
        res_fsm_force_estop(
            fsm, now_ms, RES_ESTOP_BUTTON_OR_WIRE_OPEN);
    }
    if (fsm->state == RES_STATE_ESTOP_LATCHED) {
        return;
    }

    if (fsm->run_authorized && fsm->ever_acknowledged
        && (elapsed_ms(now_ms, fsm->last_ack_ms)
            > RES_LINK_LOSS_LATCH_MS)) {
        res_fsm_force_estop(fsm, now_ms, RES_ESTOP_LINK_LOSS);
        return;
    }

    /* 1~3 s 灯检取中间值 2 s，同时禁止上电时因 GO 卡住而误发车。 */
    if (fsm->state == RES_STATE_LAMP_TEST) {
        if (elapsed_ms(now_ms, fsm->state_since_ms) >= RES_LAMP_TEST_MS) {
            fsm->state = RES_STATE_STANDBY;
            fsm->state_since_ms = now_ms;
        } else {
            return;
        }
    }

    if (!go_pressed) {
        fsm->go_edge_timing = false;
        if (!fsm->go_release_timing) {
            fsm->go_release_timing = true;
            fsm->go_release_since_ms = now_ms;
        } else if (elapsed_ms(now_ms, fsm->go_release_since_ms)
                   >= RES_GO_RELEASE_MS) {
            fsm->go_armed = true;
            fsm->go_rejected_no_link = false;
        }
    } else {
        fsm->go_release_timing = false;
        if (fsm->go_armed) {
            if (!fsm->go_edge_timing) {
                fsm->go_edge_timing = true;
                fsm->go_edge_since_ms = now_ms;
            } else if (elapsed_ms(now_ms, fsm->go_edge_since_ms)
                       >= RES_GO_DEBOUNCE_MS) {
                fsm->go_armed = false;
                fsm->go_edge_timing = false;
                /*
                 * GO 不是“盲发”命令：只有接收端 ACK 足够新鲜时才生成
                 * 新的发车事件，防止接收端掉线时积累待执行命令。
                 */
                if (res_fsm_link_ok(fsm, now_ms)) {
                    fsm->state = RES_STATE_GO_REPEAT;
                    fsm->state_since_ms = now_ms;
                    fsm->run_authorized = true;
                    ++fsm->go_event;
                } else {
                    fsm->go_rejected_no_link = true;
                }
            }
        }
    }

    if ((fsm->state == RES_STATE_GO_REPEAT)
        && (elapsed_ms(now_ms, fsm->state_since_ms)
            >= RES_GO_REPEAT_MS)) {
        fsm->state = RES_STATE_STANDBY;
        fsm->state_since_ms = now_ms;
    }
}

ResCommand res_fsm_command(const ResFsm *fsm)
{
    if (fsm->state == RES_STATE_ESTOP_LATCHED) {
        return RES_COMMAND_ESTOP;
    }
    if (fsm->state == RES_STATE_GO_REPEAT) {
        return RES_COMMAND_GO;
    }
    return RES_COMMAND_READY;
}
