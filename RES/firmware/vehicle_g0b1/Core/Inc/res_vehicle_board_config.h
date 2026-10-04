#ifndef RES_VEHICLE_BOARD_CONFIG_H
#define RES_VEHICLE_BOARD_CONFIG_H

/* GPIO labels must match RES_Vehicle_G0B1.ioc. */
#define RES_RELAY_1_GPIO_Port       GPIOB
#define RES_RELAY_1_Pin             GPIO_PIN_10
#define RES_RELAY_2_GPIO_Port       GPIOB
#define RES_RELAY_2_Pin             GPIO_PIN_11
#define RES_START_OUT_GPIO_Port     GPIOB
#define RES_START_OUT_Pin           GPIO_PIN_12
#define RES_FAULT_OUT_GPIO_Port     GPIOB
#define RES_FAULT_OUT_Pin           GPIO_PIN_13
#define RES_CAN_STB_GPIO_Port       GPIOA
#define RES_CAN_STB_Pin             GPIO_PIN_0

/* Purchased relay modules are low-level driven. Verify every batch on bench. */
#define RES_RELAY_ACTIVE_LOW        1
/* START_OUT and FAULT_OUT are 3.3 V logic to the VCU/interface circuit. */
#define RES_LOGIC_OUTPUT_ACTIVE_HIGH 1
/* Typical CAN transceiver module STB is high=standby, low=normal. */
#define RES_CAN_STB_ACTIVE_HIGH     1

/* Public demonstration key: replace with an untracked per-team key. */
#define RES_DEMO_AUTH_KEY_BYTES \
    {0x63u,0x68u,0x61u,0x6Eu,0x67u,0x65u,0x2Du,0x74u, \
     0x68u,0x69u,0x73u,0x2Du,0x6Bu,0x65u,0x79u,0x21u}

#endif
