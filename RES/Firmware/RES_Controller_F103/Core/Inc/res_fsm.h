#ifndef RES_FSM_H
#define RES_FSM_H

#include <stdbool.h>
#include <stdint.h>

#include "res_protocol.h"

typedef enum {
    RES_STATE_LAMP_TEST = 0,
    RES_STATE_STANDBY,
    RES_STATE_GO_REPEAT,
    RES_STATE_ESTOP_LATCHED
} ResState;

typedef enum {
    RES_ESTOP_NONE = 0,
    RES_ESTOP_BUTTON_OR_WIRE_OPEN,
    RES_ESTOP_LINK_LOSS,
    RES_ESTOP_RECEIVER_FAULT
} ResEstopReason;

typedef struct {
    ResState state;
    ResEstopReason estop_reason;
    uint32_t state_since_ms;
    uint32_t go_edge_since_ms;
    uint32_t go_release_since_ms;
    uint32_t last_ack_ms;
    uint16_t go_event;
    bool go_edge_timing;
    bool go_release_timing;
    bool go_armed;
    bool run_authorized;
    bool ever_acknowledged;
    bool go_rejected_no_link;
} ResFsm;

void res_fsm_init(ResFsm *fsm, uint32_t now_ms, bool shut_circuit_open);
void res_fsm_update(
    ResFsm *fsm,
    uint32_t now_ms,
    bool go_pressed,
    bool shut_circuit_open);
void res_fsm_on_ack(ResFsm *fsm, uint32_t now_ms);
void res_fsm_force_estop(
    ResFsm *fsm,
    uint32_t now_ms,
    ResEstopReason reason);
bool res_fsm_link_ok(const ResFsm *fsm, uint32_t now_ms);
ResCommand res_fsm_command(const ResFsm *fsm);

#endif

