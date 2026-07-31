#ifndef RES_REMOTE_APP_H
#define RES_REMOTE_APP_H

#include "res_protocol.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RES_REMOTE_PENDING_COUNT 6u

typedef enum {
    RES_LED_STATE_BLUE = 0,
    RES_LED_STATE_YELLOW,
    RES_LED_SOC_GREEN,
    RES_LED_SOC_RED,
    RES_LED_COUNT
} res_led_t;

typedef enum {
    RES_VEHICLE_UNKNOWN = 0,
    RES_VEHICLE_WAIT_LINK = 1,
    RES_VEHICLE_READY = 2,
    RES_VEHICLE_GO_EVENT = 3,
    RES_VEHICLE_STOPPED_FAULT = 4
} res_vehicle_state_t;

typedef enum {
    RES_REMOTE_STARTUP_STOP = 0,
    RES_REMOTE_READY = 1,
    RES_REMOTE_STOP_LATCHED = 2
} res_remote_safety_state_t;

enum {
    RES_REMOTE_FAULT_BATTERY_LOW = 1u << 0,
    RES_REMOTE_FAULT_BATTERY_CRITICAL = 1u << 1,
    RES_REMOTE_FAULT_RADIO_TX = 1u << 2
};

typedef struct {
    void *context;
    uint32_t (*millis)(void *context);
    bool (*radio_write)(void *context, const uint8_t *data, size_t length);
    void (*set_led)(void *context, res_led_t led, bool on);
    void (*refresh_watchdog)(void *context);
} res_remote_io_t;

typedef struct {
    bool used;
    uint32_t sequence;
    uint32_t sent_ms;
    uint8_t channel;
} res_pending_ack_t;

typedef struct {
    res_remote_io_t io;
    uint8_t auth_key[RES_AUTH_KEY_SIZE];
    uint32_t session;
    uint32_t next_sequence;
    uint32_t command_counter;
    uint32_t startup_ms;
    uint32_t last_heartbeat_ms;
    uint32_t last_valid_rx_ms;
    uint32_t next_burst_tx_ms;
    uint32_t go_change_ms;
    uint16_t battery_mv;
    int16_t current_ma;
    uint16_t fault_flags;
    uint8_t channel_health[RES_HOP_CHANNEL_COUNT];
    uint8_t stop_burst_remaining;
    uint8_t go_burst_remaining;
    uint8_t active_channel;
    res_vehicle_state_t vehicle_state;
    res_remote_safety_state_t safety_state;
    bool raw_go_pressed;
    bool raw_stop_fault;
    bool debounced_go_pressed;
    bool previous_go_pressed;
    bool battery_measurement_valid;
    bool startup_input_checked;
    bool started;
    res_pending_ack_t pending[RES_REMOTE_PENDING_COUNT];
    res_stream_parser_t parser;
    res_replay_window_t replay;
} res_remote_app_t;

void res_remote_app_init(res_remote_app_t *app,
                         const res_remote_io_t *io,
                         const uint8_t auth_key[RES_AUTH_KEY_SIZE],
                         uint32_t session);

/* stop_fault=true means pressed E-stop, broken NC wire, or detector power loss. */
void res_remote_app_set_raw_inputs(res_remote_app_t *app,
                                   bool go_pressed,
                                   bool stop_fault);

void res_remote_app_set_power(res_remote_app_t *app,
                              uint16_t battery_mv,
                              int16_t current_ma,
                              bool valid);

void res_remote_app_set_fault(res_remote_app_t *app,
                              uint16_t fault_mask,
                              bool active);

void res_remote_app_receive_byte(res_remote_app_t *app, uint8_t byte);
void res_remote_app_tick(res_remote_app_t *app);
bool res_remote_app_link_ok(const res_remote_app_t *app, uint32_t now_ms);

#ifdef __cplusplus
}
#endif

#endif
