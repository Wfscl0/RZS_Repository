#ifndef RES_VEHICLE_APP_H
#define RES_VEHICLE_APP_H

#include "res_can_contract.h"
#include "res_protocol.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    RES_VEHICLE_RELAY_1 = 0,
    RES_VEHICLE_RELAY_2 = 1
} res_vehicle_relay_t;

typedef enum {
    RES_VEHICLE_OUTPUT_START = 0,
    RES_VEHICLE_OUTPUT_FAULT = 1
} res_vehicle_output_t;

enum {
    RES_VEHICLE_FAULT_REMOTE_STOP = RES_CAN_FLAG_REMOTE_STOP,
    RES_VEHICLE_FAULT_RADIO_TIMEOUT = RES_CAN_FLAG_RADIO_TIMEOUT,
    RES_VEHICLE_FAULT_AUTH = RES_CAN_FLAG_AUTH_FAILURE,
    RES_VEHICLE_FAULT_RELAY = RES_CAN_FLAG_RELAY_MISMATCH,
    RES_VEHICLE_FAULT_CAN = RES_CAN_FLAG_CAN_LOCAL_FAULT,
    RES_VEHICLE_FAULT_LATCHED = RES_CAN_FLAG_SOFTWARE_LATCHED
};

typedef struct {
    void *context;
    uint32_t (*millis)(void *context);
    bool (*radio_write)(void *context, const uint8_t *data, size_t length);
    bool (*can_write)(void *context,
                      uint16_t standard_id,
                      const uint8_t *data,
                      uint8_t length);
    void (*set_relay)(void *context, res_vehicle_relay_t relay, bool closed);
    void (*set_output)(void *context, res_vehicle_output_t output, bool active);
    void (*refresh_watchdog)(void *context);
} res_vehicle_io_t;

typedef struct {
    res_vehicle_io_t io;
    uint8_t auth_key[RES_AUTH_KEY_SIZE];
    uint32_t local_session;
    uint32_t next_sequence;
    uint32_t remote_session;
    uint32_t latched_session;
    uint32_t last_valid_rx_ms;
    uint32_t last_status_tx_ms;
    uint32_t start_output_until_ms;
    uint32_t last_go_counter;
    uint16_t go_event_counter;
    uint16_t fault_flags;
    uint16_t local_fault_flags;
    uint8_t ready_confirmations;
    uint8_t active_channel;
    res_can_state_t state;
    bool relay_1_closed;
    bool relay_2_closed;
    bool start_output_active;
    bool fault_latched;
    bool started;
    res_stream_parser_t parser;
    res_replay_window_t replay;
} res_vehicle_app_t;

void res_vehicle_app_init(res_vehicle_app_t *app,
                          const res_vehicle_io_t *io,
                          const uint8_t auth_key[RES_AUTH_KEY_SIZE],
                          uint32_t local_session);

void res_vehicle_app_receive_byte(res_vehicle_app_t *app, uint8_t byte);
void res_vehicle_app_tick(res_vehicle_app_t *app);

/* HAL may report driver/feedback failures without bypassing the latch. */
void res_vehicle_app_set_local_fault(res_vehicle_app_t *app,
                                     uint16_t fault_mask,
                                     bool active);

#ifdef __cplusplus
}
#endif

#endif
