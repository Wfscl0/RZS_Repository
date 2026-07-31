/*
 * VCU10.h
 *
 * Code generation for model "VCU10".
 *
 * Model version              : 1.44
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Fri Jul 31 01:34:11 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_VCU10_h_
#define RTW_HEADER_VCU10_h_
#include <math.h>
#ifndef VCU10_COMMON_INCLUDES_
#define VCU10_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* VCU10_COMMON_INCLUDES_ */

#include "VCU10_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Exported data define */

/* Definition for custom storage class: Define */
#define F                              false                     /* Referenced by:
                                                                  * '<S3>/Chart'
                                                                  * '<S4>/Chart'
                                                                  * '<S13>/TSLED_Inspection'
                                                                  * '<S18>/Chart'
                                                                  * '<S18>/Chart1'
                                                                  * '<S18>/Chart2'
                                                                  * '<S218>/Shutdown_Button'
                                                                  * '<S218>/display'
                                                                  * '<S65>/brkmotor_check_system'
                                                                  */
#define T                              true                      /* Referenced by:
                                                                  * '<S3>/Chart'
                                                                  * '<S4>/Chart'
                                                                  * '<S13>/TSLED_Inspection'
                                                                  * '<S18>/Chart'
                                                                  * '<S18>/Chart1'
                                                                  * '<S18>/Chart2'
                                                                  * '<S218>/Shutdown_Button'
                                                                  * '<S218>/display'
                                                                  * '<S65>/brkmotor_check_system'
                                                                  */

/* Block signals (default storage) */
typedef struct {
  real_T tarPrsReqFL;                  /* '<S143>/ESP_Chart1' */
  real_T tarPrsReqFR;                  /* '<S143>/ESP_Chart1' */
  real_T tarPrsReqRL;                  /* '<S143>/ESP_Chart1' */
  real_T tarPrsReqRR;                  /* '<S143>/ESP_Chart1' */
  real_T mode;                         /* '<S143>/ESP_Chart1' */
  real_T as_ebs_trig;                  /* '<S3>/Chart' */
  real_T as_led_blue;                  /* '<S3>/Chart' */
  real_T as_led_yellow;                /* '<S3>/Chart' */
  real_T steering_flag_o;              /* '<S3>/Chart' */
  real_T safety_lock;                  /* '<S3>/Chart' */
  real_T brake_flag_p;                 /* '<S3>/Chart' */
  real_T manual_driving_flag_j;        /* '<S3>/Chart' */
  real_T as_emergency_flag_m;          /* '<S3>/Chart' */
  real_T as_off_flag_g;                /* '<S3>/Chart' */
  real_T as_ready_flag_a;              /* '<S3>/Chart' */
  real_T as_driving_flag_a;            /* '<S3>/Chart' */
  real_T as_finished_flag_a;           /* '<S3>/Chart' */
  real_T r2d_flag_a;                   /* '<S3>/Chart' */
  real_T pedal_error;                  /* '<S237>/Pedal_Fault_Check' */
  real_T xorcheck;                     /* '<S271>/xor_Check' */
  real_T res_hbcheck;                  /* '<S271>/heaartbeat_chart' */
  real_T ts;                           /* '<S18>/Chart2' */
  uint32_T eps_cmdangle;               /* '<S48>/EPS_Stateflow1' */
  uint8_T eps_cmdworkmode;             /* '<S48>/EPS_Stateflow1' */
  uint8_T eps_cmdmiddle;               /* '<S48>/EPS_Stateflow1' */
  uint8_T eps_cmdvelocity;             /* '<S48>/EPS_Stateflow1' */
  uint8_T ami_process;                 /* '<S20>/Chart' */
  boolean_T brkmotor_check;            /* '<S65>/brkmotor_check_system' */
  boolean_T r2d_warning;               /* '<S3>/Chart' */
  boolean_T steer_return;              /* '<S3>/Chart' */
  boolean_T shutdown_flag;             /* '<S218>/Shutdown_Button' */
  boolean_T In1;                       /* '<S229>/In1' */
  boolean_T ts_warning;                /* '<S18>/Chart2' */
} B_VCU10_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T oilprs_frsensordata;          /* '<Root>/Data Store Memory24' */
  real_T ipc_astask;                   /* '<Root>/Data Store Memory22' */
  real_T safety_lock;                  /* '<Root>/FSEC_Safety_Lock_Memory' */
  real_T lscnt;                        /* '<S65>/brkmotor_check_system' */
  real_T fault_count;                  /* '<S237>/Pedal_Fault_Check' */
  real_T shutdown_count;               /* '<S218>/Shutdown_Button' */
  real_T err_cnt;                      /* '<S271>/xor_Check' */
  real_T hbcnt;                        /* '<S271>/heaartbeat_chart' */
  real_T run_check_flag;               /* '<S18>/Chart1' */
  real_T run_offcheck_flag;            /* '<S18>/Chart1' */
  real_T run_flag;                     /* '<S18>/Chart1' */
  real_T di8_offcheck_flag;            /* '<S18>/Chart' */
  real_T di8_check_flag;               /* '<S18>/Chart' */
  int32_T clockTickCounter;            /* '<S219>/Pulse Generator' */
  int32_T clockTickCounter_a;          /* '<S220>/Pulse Generator' */
  int32_T clockTickCounter_a2;         /* '<S4>/Pulse Generator' */
  uint32_T previousTicks;              /* '<S48>/EPS_Stateflow1' */
  uint32_T previousTicks_g;            /* '<S3>/Chart' */
  uint32_T previousTicks_o;            /* '<S13>/TSLED_Inspection' */
  uint32_T previousTicks_a;            /* '<S220>/yellow' */
  uint32_T previousTicks_av;           /* '<S219>/blue' */
  uint32_T previousTicks_ag;           /* '<S218>/display' */
  uint32_T previousTicks_f;            /* '<S218>/Shutdown_Button' */
  uint32_T previousTicks_c;            /* '<S4>/Chart' */
  uint32_T previousTicks_gm;           /* '<S18>/Chart2' */
  uint16_T seen_count;                 /* '<Root>/EPS_SCS_Monitor' */
  uint16_T stale_count;                /* '<Root>/EPS_SCS_Monitor' */
  uint16_T bad_count;                  /* '<Root>/EPS_SCS_Monitor' */
  uint16_T good_count;                 /* '<Root>/EPS_SCS_Monitor' */
  uint16_T wait_count;                 /* '<S7>/EBS_Response_Monitor' */
  uint16_T relation_count;             /* '<S7>/EBS_Response_Monitor' */
  uint16_T clear_count;                /* '<S7>/EBS_Response_Monitor' */
  uint16_T temporalCounter_i1;         /* '<S3>/Chart' */
  uint16_T bad_count_b;                /* '<S237>/APPS_Electrical_Monitor' */
  uint16_T good_count_d;               /* '<S237>/APPS_Electrical_Monitor' */
  uint16_T brake_bad;                  /* '<S2>/FSEC_Sensor_Monitor' */
  uint16_T brake_good;                 /* '<S2>/FSEC_Sensor_Monitor' */
  uint16_T air_bad;                    /* '<S2>/FSEC_Sensor_Monitor' */
  uint16_T air_good;                   /* '<S2>/FSEC_Sensor_Monitor' */
  uint16_T comm_bad;                   /* '<S2>/FSEC_Sensor_Monitor' */
  uint16_T comm_good;                  /* '<S2>/FSEC_Sensor_Monitor' */
  uint16_T ebs_bad;                    /* '<S2>/FSEC_Sensor_Monitor' */
  uint16_T ebs_good;                   /* '<S2>/FSEC_Sensor_Monitor' */
  uint16_T temporalCounter_i1_m;       /* '<S4>/Chart' */
  boolean_T FSEC_Safety_Fault_Delay_DSTATE;/* '<Root>/FSEC_Safety_Fault_Delay' */
  boolean_T EBS_Sensor_Fault_Delay_DSTATE;/* '<S7>/EBS_Sensor_Fault_Delay' */
  uint8_T last_counter;                /* '<Root>/EPS_SCS_Monitor' */
  uint8_T last_count[4];               /* '<Root>/DBC_Debug_Select' */
  uint8_T ages[4];                     /* '<Root>/DBC_Debug_Select' */
  uint8_T is_active_c15_VCU10;         /* '<S48>/EPS_Stateflow1' */
  uint8_T is_c15_VCU10;                /* '<S48>/EPS_Stateflow1' */
  uint8_T temporalCounter_i1_g;        /* '<S48>/EPS_Stateflow1' */
  uint8_T is_active_c16_VCU10;         /* '<S143>/ESP_Chart1' */
  uint8_T is_c16_VCU10;                /* '<S143>/ESP_Chart1' */
  uint8_T is_active_c18_VCU10;         /* '<S65>/brkmotor_check_system' */
  uint8_T is_c18_VCU10;                /* '<S65>/brkmotor_check_system' */
  uint8_T lifesig_start;               /* '<S65>/brkmotor_check_system' */
  uint8_T is_active_c1_VCU10;          /* '<S3>/Chart' */
  uint8_T is_c1_VCU10;                 /* '<S3>/Chart' */
  uint8_T is_AS_Driving;               /* '<S3>/Chart' */
  uint8_T is_active_c4_VCU10;          /* '<S14>/Motor_Torque_Stateflow' */
  uint8_T is_c4_VCU10;                 /* '<S14>/Motor_Torque_Stateflow' */
  uint8_T is_active_c2_VCU10;          /* '<S13>/TSLED_Inspection' */
  uint8_T is_c2_VCU10;                 /* '<S13>/TSLED_Inspection' */
  uint8_T temporalCounter_i1_o;        /* '<S13>/TSLED_Inspection' */
  uint8_T is_active_c14_VCU10;         /* '<S220>/yellow' */
  uint8_T is_c14_VCU10;                /* '<S220>/yellow' */
  uint8_T temporalCounter_i1_j;        /* '<S220>/yellow' */
  uint8_T is_active_c13_VCU10;         /* '<S219>/blue' */
  uint8_T is_c13_VCU10;                /* '<S219>/blue' */
  uint8_T temporalCounter_i1_c;        /* '<S219>/blue' */
  uint8_T is_active_c6_VCU10;          /* '<S218>/display' */
  uint8_T is_c6_VCU10;                 /* '<S218>/display' */
  uint8_T temporalCounter_i1_gw;       /* '<S218>/display' */
  uint8_T is_active_c17_VCU10;         /* '<S218>/Shutdown_Button' */
  uint8_T is_c17_VCU10;                /* '<S218>/Shutdown_Button' */
  uint8_T temporalCounter_i1_ct;       /* '<S218>/Shutdown_Button' */
  uint8_T is_active_c20_VCU10;         /* '<S20>/Chart' */
  uint8_T is_c20_VCU10;                /* '<S20>/Chart' */
  uint8_T is_active_c11_VCU10;         /* '<S4>/Chart' */
  uint8_T is_c11_VCU10;                /* '<S4>/Chart' */
  uint8_T is_active_c19_VCU10;         /* '<S271>/xor_Check' */
  uint8_T is_c19_VCU10;                /* '<S271>/xor_Check' */
  uint8_T is_active_c10_VCU10;         /* '<S271>/heaartbeat_chart' */
  uint8_T is_c10_VCU10;                /* '<S271>/heaartbeat_chart' */
  uint8_T res_heartbeat_start;         /* '<S271>/heaartbeat_chart' */
  uint8_T is_active_c9_VCU10;          /* '<S18>/Chart2' */
  uint8_T is_c9_VCU10;                 /* '<S18>/Chart2' */
  uint8_T temporalCounter_i1_p;        /* '<S18>/Chart2' */
  uint8_T is_active_c8_VCU10;          /* '<S18>/Chart1' */
  uint8_T is_c8_VCU10;                 /* '<S18>/Chart1' */
  uint8_T is_Ignition_Check;           /* '<S18>/Chart1' */
  uint8_T is_Flameout_Check;           /* '<S18>/Chart1' */
  uint8_T is_active_c3_VCU10;          /* '<S18>/Chart' */
  uint8_T is_c3_VCU10;                 /* '<S18>/Chart' */
  uint8_T is_Ignition_Check_f;         /* '<S18>/Chart' */
  uint8_T is_Flameout_Check_i;         /* '<S18>/Chart' */
  boolean_T brkmotor_check;            /* '<Root>/Data Store Memory' */
  boolean_T asb_check;                 /* '<Root>/Data Store Memory1' */
  boolean_T ts;                        /* '<Root>/Data Store Memory11' */
  boolean_T r2d_warning;               /* '<Root>/Data Store Memory12' */
  boolean_T steer_return;              /* '<Root>/Data Store Memory14' */
  boolean_T ebs_working;               /* '<Root>/Data Store Memory2' */
  boolean_T ebs_warning;               /* '<Root>/Data Store Memory20' */
  boolean_T task_finish;               /* '<Root>/Data Store Memory21' */
  boolean_T inspection_flag;           /* '<Root>/Data Store Memory25' */
  boolean_T astask_flag;               /* '<Root>/Data Store Memory26' */
  boolean_T brake_on;                  /* '<Root>/Data Store Memory3' */
  boolean_T ebs_check;                 /* '<Root>/Data Store Memory4' */
  boolean_T steer_zero;                /* '<Root>/Data Store Memory9' */
  boolean_T last_counter_not_empty;    /* '<Root>/EPS_SCS_Monitor' */
  boolean_T fault;                     /* '<Root>/EPS_SCS_Monitor' */
  boolean_T last_trigger;              /* '<S7>/EBS_Response_Monitor' */
  boolean_T waiting;                   /* '<S7>/EBS_Response_Monitor' */
  boolean_T fault_latched;             /* '<S7>/EBS_Response_Monitor' */
  boolean_T fault_n;                   /* '<S237>/APPS_Electrical_Monitor' */
  boolean_T brake_fault;               /* '<S2>/FSEC_Sensor_Monitor' */
  boolean_T air_fault;                 /* '<S2>/FSEC_Sensor_Monitor' */
  boolean_T comm_fault;                /* '<S2>/FSEC_Sensor_Monitor' */
  boolean_T ebs_comm_fault;            /* '<S2>/FSEC_Sensor_Monitor' */
  boolean_T di8_flag;                  /* '<S18>/Chart' */
} DW_VCU10_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Gain;                   /* '<S235>/Gain' */
  const real_T Gain1;                  /* '<S235>/Gain1' */
  const real_T Product;                /* '<S277>/Product' */
  const uint16_T DataTypeConversion8;  /* '<S235>/Data Type Conversion8' */
  const uint16_T Add2;                 /* '<S235>/Add2' */
  const uint16_T DataTypeConversion9;  /* '<S235>/Data Type Conversion9' */
  const uint16_T BitwiseAND7;          /* '<S235>/Bitwise AND7' */
  const uint16_T DataTypeConversion10; /* '<S235>/Data Type Conversion10' */
  const uint16_T BitwiseAND8;          /* '<S235>/Bitwise AND8' */
  const uint16_T BitwiseAND9;          /* '<S235>/Bitwise AND9' */
  const uint16_T BitwiseAND13;         /* '<S235>/Bitwise AND13' */
  const uint16_T BitwiseAND12;         /* '<S235>/Bitwise AND12' */
  const uint16_T BitwiseAND6;          /* '<S235>/Bitwise AND6' */
  const uint16_T DataTypeConversion5;  /* '<S236>/Data Type Conversion5' */
  const uint16_T BitwiseAND1;          /* '<S236>/Bitwise AND1' */
  const uint16_T DataTypeConversion1;  /* '<S236>/Data Type Conversion1' */
  const uint16_T BitwiseAND3;          /* '<S236>/Bitwise AND3' */
  const uint16_T BitwiseAND;           /* '<S236>/Bitwise AND' */
  const uint16_T BitwiseAND2;          /* '<S236>/Bitwise AND2' */
  const uint8_T BitwiseAND8_o;         /* '<S143>/Bitwise AND8' */
  const uint8_T DataTypeConversion1_c; /* '<S235>/Data Type Conversion1' */
  const uint8_T BitwiseAND1_a;         /* '<S235>/Bitwise AND1' */
  const uint8_T DataTypeConversion3;   /* '<S235>/Data Type Conversion3' */
  const uint8_T BitwiseAND2_o;         /* '<S235>/Bitwise AND2' */
  const uint8_T DataTypeConversion4;   /* '<S235>/Data Type Conversion4' */
  const uint8_T BitwiseAND3_o;         /* '<S235>/Bitwise AND3' */
  const uint8_T DataTypeConversion5_d; /* '<S235>/Data Type Conversion5' */
  const uint8_T BitwiseAND4;           /* '<S235>/Bitwise AND4' */
  const uint8_T DataTypeConversion6;   /* '<S235>/Data Type Conversion6' */
  const uint8_T BitwiseAND5;           /* '<S235>/Bitwise AND5' */
  const uint8_T MCU1_Rx_Commandbyte1;  /* '<S235>/Data Type Conversion11' */
  const uint8_T MCU1_Rx_Commandbyte6;  /* '<S235>/Data Type Conversion16' */
  const uint8_T MCU1_Rx_Command3byte0; /* '<S236>/Data Type Conversion2' */
  const uint8_T MCU1_Rx_Command3byte2; /* '<S236>/Data Type Conversion4' */
  const uint8_T bc2;                   /* '<S266>/bc2' */
} ConstB_VCU10_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: [0.0 1.0])
   * Referenced by:
   *   '<S17>/1-D Lookup Table'
   *   '<S17>/1-D Lookup Table9'
   */
  real_T pooled2[2];

  /* Pooled Parameter (Expression: [252 2000])
   * Referenced by:
   *   '<S17>/1-D Lookup Table'
   *   '<S17>/1-D Lookup Table9'
   */
  uint16_T pooled37[2];
} ConstP_VCU10_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint8_T model_lox;                   /* '<Root>/model_lox' */
  uint8_T model_hox;                   /* '<Root>/model_hox' */
  uint8_T ESP_R_00[8];                 /* '<Root>/ESP_R_00' */
  uint8_T vcu_dbg_status[8];           /* '<Root>/vcu_dbg_status' */
  uint8_T vcu_dbg_pedal_echo[8];       /* '<Root>/vcu_dbg_pedal_echo' */
  uint8_T vcu_dbg_air_wheel_echo[8];   /* '<Root>/vcu_dbg_air_wheel_echo' */
} ExtY_VCU10_T;

/* Real-time Model Data Structure */
struct tag_RTM_VCU10_T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
  } Timing;
};

/* Block signals (default storage) */
extern B_VCU10_T VCU10_B;

/* Block states (default storage) */
extern DW_VCU10_T VCU10_DW;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_VCU10_T VCU10_Y;
extern const ConstB_VCU10_T VCU10_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_VCU10_T VCU10_ConstP;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern uint16_T model_hin;             /* '<Root>/model_hin' */
extern uint16_T model_ain[5];          /* '<Root>/model_ain' */
extern real32_T wlspd_fsensor;         /* '<Root>/wlspd_fsensor' */
extern real32_T wlspd_hsensor;         /* '<Root>/wlspd_hsensor' */
extern uint8_T AMI_Tx[8];              /* '<Root>/AMI_Tx' */
extern uint8_T ESP_T_01[8];            /* '<Root>/ESP_T_01' */
extern uint8_T ESP_T_03[8];            /* '<Root>/ESP_T_03' */
extern uint8_T ESP_T_06[8];            /* '<Root>/ESP_T_06' */
extern uint8_T ESP_T_07[8];            /* '<Root>/ESP_T_07' */
extern uint8_T canb_epssendmsg1[8];    /* '<Root>/canb_epssendmsg1' */
extern uint8_T canb_epssendmsg2[8];    /* '<Root>/canb_epssendmsg2' */
extern uint8_T res_msg[8];             /* '<Root>/res_msg' */
extern uint8_T canb_ipctsmsg1[8];      /* '<Root>/canb_ipctsmsg1' */
extern uint8_T canb_ipctsmsg2[8];      /* '<Root>/canb_ipctsmsg2' */
extern uint8_T vcu_dbg_control[8];     /* '<Root>/vcu_dbg_control' */
extern uint8_T vcu_dbg_pedal_adc[8];   /* '<Root>/vcu_dbg_pedal_adc' */
extern uint8_T vcu_dbg_air_wheel[8];   /* '<Root>/vcu_dbg_air_wheel' */
extern uint8_T vcu_dbg_digital[8];     /* '<Root>/vcu_dbg_digital' */
extern uint8_T vcu_dbg_rx_count[4];    /* '<Root>/vcu_dbg_rx_count' */
extern uint16_T airprs2;               /* '<S12>/Data Type Conversion' */
extern uint16_T airprs1;               /* '<S12>/Data Type Conversion1' */
extern uint16_T brkps;                 /* '<S12>/Data Type Conversion2' */
extern uint16_T apps2;                 /* '<S12>/Data Type Conversion3' */
extern uint16_T apps1;                 /* '<S12>/Data Type Conversion4' */
extern uint8_T canb_epsmsg[8];         /* '<S8>/EPS_TransmitMsg' */
extern uint8_T cana_motor_cmd[8];      /* '<S235>/Signal Conversion' */
extern uint8_T cana_motor_cmd3[8];     /* '<S14>/MCU1_Rx_Command3' */
extern uint8_T AMI_Rx[8];              /* '<S20>/Signal Conversion' */
extern uint8_T canb_ipcrxmsg[8];       /* '<S11>/IPC_ReceiveMsg' */
extern boolean_T ebs_driver_check;     /* '<S196>/Data Type Conversion' */
extern boolean_T shutdown_s;           /* '<S196>/Data Type Conversion1' */
extern boolean_T shutdown_e;           /* '<S196>/Data Type Conversion2' */
extern boolean_T di8_cockpit;          /* '<S196>/Data Type Conversion3' */
extern boolean_T di8_side;             /* '<S196>/Data Type Conversion4' */
extern boolean_T run_button;           /* '<S196>/Data Type Conversion5' */
extern boolean_T tsms;                 /* '<S196>/Data Type Conversion6' */
extern boolean_T asms;                 /* '<S196>/Data Type Conversion7' */
extern boolean_T ebs_watchdog;
     /* '<S7>/BufferToMakeInportVirtual_InsertedFor_ebs_watchdog_at_inport_0' */
extern boolean_T ebs_trig;             /* '<S7>/EBS_Trigger_ASMS_Gate' */
extern boolean_T led_brake;            /* '<S13>/brake_on' */
extern boolean_T led_ebs_error;        /* '<S218>/Logical Operator' */
extern boolean_T led_assi_blue;        /* '<S219>/Data Type Conversion' */
extern boolean_T led_assi_yellow;      /* '<S220>/Data Type Conversion' */
extern boolean_T led_imd_error;        /* '<S13>/TSLED_Inspection' */
extern boolean_T led_bms_error;        /* '<S13>/TSLED_Inspection' */
extern boolean_T r2d_buzzer;           /* '<S4>/Switch1' */
extern boolean_T ebs_buzzer;           /* '<S4>/Switch' */
extern boolean_T res_error;            /*  */
extern boolean_T run;                  /* '<S18>/Chart1' */
extern boolean_T di8;                  /* '<S18>/Chart' */

/* Model entry point functions */
extern void VCU10_initialize(void);
extern void VCU10_step(void);
extern void VCU10_terminate(void);

/* Real-time Model object */
extern RT_MODEL_VCU10_T *const VCU10_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S49>/Add1' : Unused code path elimination
 * Block '<S49>/Constant' : Unused code path elimination
 * Block '<S49>/Data Type Conversion9' : Unused code path elimination
 * Block '<S49>/TorqueScale' : Unused code path elimination
 * Block '<S50>/Add1' : Unused code path elimination
 * Block '<S50>/Add2' : Unused code path elimination
 * Block '<S50>/Add5' : Unused code path elimination
 * Block '<S50>/Constant1' : Unused code path elimination
 * Block '<S50>/Constant2' : Unused code path elimination
 * Block '<S50>/Data Type Conversion1' : Unused code path elimination
 * Block '<S50>/Data Type Conversion10' : Unused code path elimination
 * Block '<S50>/Data Type Conversion2' : Unused code path elimination
 * Block '<S50>/Data Type Conversion4' : Unused code path elimination
 * Block '<S50>/Data Type Conversion5' : Unused code path elimination
 * Block '<S50>/Data Type Conversion6' : Unused code path elimination
 * Block '<S50>/Data Type Conversion8' : Unused code path elimination
 * Block '<S50>/Gain1' : Unused code path elimination
 * Block '<S50>/Gain2' : Unused code path elimination
 * Block '<S61>/Add' : Unused code path elimination
 * Block '<S61>/Add1' : Unused code path elimination
 * Block '<S61>/Add2' : Unused code path elimination
 * Block '<S61>/Add3' : Unused code path elimination
 * Block '<S61>/Bitwise AND' : Unused code path elimination
 * Block '<S61>/Bitwise AND19' : Unused code path elimination
 * Block '<S61>/Bitwise AND8' : Unused code path elimination
 * Block '<S61>/Data Type Conversion1' : Unused code path elimination
 * Block '<S61>/Data Type Conversion10' : Unused code path elimination
 * Block '<S61>/Data Type Conversion2' : Unused code path elimination
 * Block '<S61>/Data Type Conversion3' : Unused code path elimination
 * Block '<S61>/Data Type Conversion4' : Unused code path elimination
 * Block '<S61>/Data Type Conversion5' : Unused code path elimination
 * Block '<S61>/Data Type Conversion6' : Unused code path elimination
 * Block '<S61>/Data Type Conversion7' : Unused code path elimination
 * Block '<S61>/Data Type Conversion8' : Unused code path elimination
 * Block '<S61>/Data Type Conversion9' : Unused code path elimination
 * Block '<S61>/Gain' : Unused code path elimination
 * Block '<S63>/Add' : Unused code path elimination
 * Block '<S63>/Add1' : Unused code path elimination
 * Block '<S63>/Add2' : Unused code path elimination
 * Block '<S63>/Add3' : Unused code path elimination
 * Block '<S63>/Bitwise AND9' : Unused code path elimination
 * Block '<S64>/Add' : Unused code path elimination
 * Block '<S64>/Add1' : Unused code path elimination
 * Block '<S64>/Add2' : Unused code path elimination
 * Block '<S64>/Add3' : Unused code path elimination
 * Block '<S64>/Bitwise AND3' : Unused code path elimination
 * Block '<S64>/Bitwise AND7' : Unused code path elimination
 * Block '<S64>/Bitwise AND8' : Unused code path elimination
 * Block '<S64>/Data Type Conversion10' : Unused code path elimination
 * Block '<S64>/Data Type Conversion11' : Unused code path elimination
 * Block '<S64>/Data Type Conversion12' : Unused code path elimination
 * Block '<S64>/Data Type Conversion4' : Unused code path elimination
 * Block '<S64>/Data Type Conversion8' : Unused code path elimination
 * Block '<S64>/Data Type Conversion9' : Unused code path elimination
 * Block '<S64>/Gain' : Unused code path elimination
 * Block '<S64>/Gain1' : Unused code path elimination
 * Block '<S64>/Gain2' : Unused code path elimination
 * Block '<S64>/Gain3' : Unused code path elimination
 * Block '<S167>/Add1' : Unused code path elimination
 * Block '<S167>/Add2' : Unused code path elimination
 * Block '<S167>/Data Type Conversion5' : Unused code path elimination
 * Block '<S167>/Data Type Conversion7' : Unused code path elimination
 * Block '<S167>/Data Type Conversion9' : Unused code path elimination
 * Block '<S223>/Compare' : Unused code path elimination
 * Block '<S223>/Constant' : Unused code path elimination
 * Block '<S267>/Data Type Conversion1' : Unused code path elimination
 * Block '<S17>/1-D Lookup Table1' : Unused code path elimination
 * Block '<S17>/Data Type Conversion4' : Unused code path elimination
 * Block '<S17>/Saturation2' : Unused code path elimination
 * Block '<S49>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S48>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S48>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S48>/Data Type Conversion6' : Eliminate redundant data type conversion
 * Block '<S48>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S57>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S143>/Data Type Conversion12' : Eliminate redundant data type conversion
 * Block '<S234>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S17>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S17>/Data Type Conversion2' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'VCU10'
 * '<S1>'   : 'VCU10/AMI_CAN'
 * '<S2>'   : 'VCU10/ASB_Selfcheck'
 * '<S3>'   : 'VCU10/AS_Stateflow'
 * '<S4>'   : 'VCU10/Buzzer'
 * '<S5>'   : 'VCU10/DBC_Debug_Select'
 * '<S6>'   : 'VCU10/DBC_Debug_StatusPack'
 * '<S7>'   : 'VCU10/EBS'
 * '<S8>'   : 'VCU10/EPS'
 * '<S9>'   : 'VCU10/EPS_SCS_Monitor'
 * '<S10>'  : 'VCU10/ESP'
 * '<S11>'  : 'VCU10/IPC'
 * '<S12>'  : 'VCU10/Input_Convert'
 * '<S13>'  : 'VCU10/LED_Control'
 * '<S14>'  : 'VCU10/Motor_Control'
 * '<S15>'  : 'VCU10/Output_Convert'
 * '<S16>'  : 'VCU10/Res'
 * '<S17>'  : 'VCU10/Sensor_Signal'
 * '<S18>'  : 'VCU10/TS_Activation'
 * '<S19>'  : 'VCU10/AMI_CAN/AMI_Receivemsg'
 * '<S20>'  : 'VCU10/AMI_CAN/AMI_Transmitmsg'
 * '<S21>'  : 'VCU10/AMI_CAN/Compare To Constant'
 * '<S22>'  : 'VCU10/AMI_CAN/Compare To Constant1'
 * '<S23>'  : 'VCU10/AMI_CAN/AMI_Receivemsg/Bit Shift'
 * '<S24>'  : 'VCU10/AMI_CAN/AMI_Receivemsg/Bit Shift/bit_shift'
 * '<S25>'  : 'VCU10/AMI_CAN/AMI_Transmitmsg/Bit Shift'
 * '<S26>'  : 'VCU10/AMI_CAN/AMI_Transmitmsg/Chart'
 * '<S27>'  : 'VCU10/AMI_CAN/AMI_Transmitmsg/Bit Shift/bit_shift'
 * '<S28>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check'
 * '<S29>'  : 'VCU10/ASB_Selfcheck/FSEC_Sensor_Monitor'
 * '<S30>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant'
 * '<S31>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant1'
 * '<S32>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant2'
 * '<S33>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant3'
 * '<S34>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant4'
 * '<S35>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant5'
 * '<S36>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant6'
 * '<S37>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant7'
 * '<S38>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant8'
 * '<S39>'  : 'VCU10/AS_Stateflow/Car_Spdzero_Check'
 * '<S40>'  : 'VCU10/AS_Stateflow/Chart'
 * '<S41>'  : 'VCU10/AS_Stateflow/Car_Spdzero_Check/Compare To Constant'
 * '<S42>'  : 'VCU10/AS_Stateflow/Car_Spdzero_Check/Compare To Constant1'
 * '<S43>'  : 'VCU10/Buzzer/Chart'
 * '<S44>'  : 'VCU10/EBS/Compare To Constant'
 * '<S45>'  : 'VCU10/EBS/Compare To Constant1'
 * '<S46>'  : 'VCU10/EBS/EBS_Response_Monitor'
 * '<S47>'  : 'VCU10/EPS/EPS_ReceiveMsg'
 * '<S48>'  : 'VCU10/EPS/EPS_TransmitMsg'
 * '<S49>'  : 'VCU10/EPS/EPS_ReceiveMsg/EPS_Send_Msg1'
 * '<S50>'  : 'VCU10/EPS/EPS_ReceiveMsg/EPS_Send_Msg2'
 * '<S51>'  : 'VCU10/EPS/EPS_ReceiveMsg/EPS_Send_Msg2/Bit Shift1'
 * '<S52>'  : 'VCU10/EPS/EPS_ReceiveMsg/EPS_Send_Msg2/Bit Shift1/bit_shift'
 * '<S53>'  : 'VCU10/EPS/EPS_TransmitMsg/Bit Shift'
 * '<S54>'  : 'VCU10/EPS/EPS_TransmitMsg/Compare To Constant2'
 * '<S55>'  : 'VCU10/EPS/EPS_TransmitMsg/Compare To Constant3'
 * '<S56>'  : 'VCU10/EPS/EPS_TransmitMsg/EPS_Stateflow1'
 * '<S57>'  : 'VCU10/EPS/EPS_TransmitMsg/Subsystem2'
 * '<S58>'  : 'VCU10/EPS/EPS_TransmitMsg/Bit Shift/bit_shift'
 * '<S59>'  : 'VCU10/ESP/ESP_ReceiveMsg'
 * '<S60>'  : 'VCU10/ESP/ESP_TransmitMsg'
 * '<S61>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01'
 * '<S62>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03'
 * '<S63>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06'
 * '<S64>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07'
 * '<S65>'  : 'VCU10/ESP/ESP_ReceiveMsg/Subsystem'
 * '<S66>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift'
 * '<S67>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift1'
 * '<S68>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift10'
 * '<S69>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift11'
 * '<S70>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift12'
 * '<S71>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift13'
 * '<S72>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift14'
 * '<S73>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift15'
 * '<S74>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift16'
 * '<S75>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift2'
 * '<S76>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift3'
 * '<S77>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift4'
 * '<S78>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift5'
 * '<S79>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift6'
 * '<S80>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift7'
 * '<S81>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift8'
 * '<S82>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift9'
 * '<S83>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift/bit_shift'
 * '<S84>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift1/bit_shift'
 * '<S85>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift10/bit_shift'
 * '<S86>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift11/bit_shift'
 * '<S87>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift12/bit_shift'
 * '<S88>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift13/bit_shift'
 * '<S89>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift14/bit_shift'
 * '<S90>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift15/bit_shift'
 * '<S91>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift16/bit_shift'
 * '<S92>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift2/bit_shift'
 * '<S93>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift3/bit_shift'
 * '<S94>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift4/bit_shift'
 * '<S95>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift5/bit_shift'
 * '<S96>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift6/bit_shift'
 * '<S97>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift7/bit_shift'
 * '<S98>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift8/bit_shift'
 * '<S99>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift9/bit_shift'
 * '<S100>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift'
 * '<S101>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift1'
 * '<S102>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift2'
 * '<S103>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift3'
 * '<S104>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift4'
 * '<S105>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift5'
 * '<S106>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift/bit_shift'
 * '<S107>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift1/bit_shift'
 * '<S108>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift2/bit_shift'
 * '<S109>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift3/bit_shift'
 * '<S110>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift4/bit_shift'
 * '<S111>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift5/bit_shift'
 * '<S112>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift'
 * '<S113>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift1'
 * '<S114>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift2'
 * '<S115>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift3'
 * '<S116>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift4'
 * '<S117>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift5'
 * '<S118>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift6'
 * '<S119>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift7'
 * '<S120>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift8'
 * '<S121>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift/bit_shift'
 * '<S122>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift1/bit_shift'
 * '<S123>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift2/bit_shift'
 * '<S124>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift3/bit_shift'
 * '<S125>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift4/bit_shift'
 * '<S126>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift5/bit_shift'
 * '<S127>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift6/bit_shift'
 * '<S128>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift7/bit_shift'
 * '<S129>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift8/bit_shift'
 * '<S130>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift'
 * '<S131>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift1'
 * '<S132>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift2'
 * '<S133>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift3'
 * '<S134>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift4'
 * '<S135>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift5'
 * '<S136>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift/bit_shift'
 * '<S137>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift1/bit_shift'
 * '<S138>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift2/bit_shift'
 * '<S139>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift3/bit_shift'
 * '<S140>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift4/bit_shift'
 * '<S141>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift5/bit_shift'
 * '<S142>' : 'VCU10/ESP/ESP_ReceiveMsg/Subsystem/brkmotor_check_system'
 * '<S143>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00'
 * '<S144>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift'
 * '<S145>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift1'
 * '<S146>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift2'
 * '<S147>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift3'
 * '<S148>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift4'
 * '<S149>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift5'
 * '<S150>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift6'
 * '<S151>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/ESP_Chart1'
 * '<S152>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift/bit_shift'
 * '<S153>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift1/bit_shift'
 * '<S154>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift2/bit_shift'
 * '<S155>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift3/bit_shift'
 * '<S156>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift4/bit_shift'
 * '<S157>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift5/bit_shift'
 * '<S158>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift6/bit_shift'
 * '<S159>' : 'VCU10/IPC/IPC_ReceiveMsg'
 * '<S160>' : 'VCU10/IPC/IPC_TransmitMsg'
 * '<S161>' : 'VCU10/IPC/IPC_ReceiveMsg/IPC_Rx_Msg'
 * '<S162>' : 'VCU10/IPC/IPC_ReceiveMsg/IPC_Rx_Msg/Bit Shift'
 * '<S163>' : 'VCU10/IPC/IPC_ReceiveMsg/IPC_Rx_Msg/Bit Shift1'
 * '<S164>' : 'VCU10/IPC/IPC_ReceiveMsg/IPC_Rx_Msg/Bit Shift/bit_shift'
 * '<S165>' : 'VCU10/IPC/IPC_ReceiveMsg/IPC_Rx_Msg/Bit Shift1/bit_shift'
 * '<S166>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1'
 * '<S167>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2'
 * '<S168>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift'
 * '<S169>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift1'
 * '<S170>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift2'
 * '<S171>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift3'
 * '<S172>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift4'
 * '<S173>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift5'
 * '<S174>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift6'
 * '<S175>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift8'
 * '<S176>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift/bit_shift'
 * '<S177>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift1/bit_shift'
 * '<S178>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift2/bit_shift'
 * '<S179>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift3/bit_shift'
 * '<S180>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift4/bit_shift'
 * '<S181>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift5/bit_shift'
 * '<S182>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift6/bit_shift'
 * '<S183>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift8/bit_shift'
 * '<S184>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift'
 * '<S185>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift1'
 * '<S186>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift2'
 * '<S187>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift3'
 * '<S188>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift4'
 * '<S189>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift5'
 * '<S190>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift/bit_shift'
 * '<S191>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift1/bit_shift'
 * '<S192>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift2/bit_shift'
 * '<S193>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift3/bit_shift'
 * '<S194>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift4/bit_shift'
 * '<S195>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift5/bit_shift'
 * '<S196>' : 'VCU10/Input_Convert/Data_Analysis'
 * '<S197>' : 'VCU10/Input_Convert/Pedal_AinConvert_APP1'
 * '<S198>' : 'VCU10/Input_Convert/Pedal_AinConvert_APP2'
 * '<S199>' : 'VCU10/Input_Convert/Pedal_AinConvert_Brake'
 * '<S200>' : 'VCU10/Input_Convert/Pressure_AinConvert1'
 * '<S201>' : 'VCU10/Input_Convert/Pressure_AinConvert2'
 * '<S202>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift'
 * '<S203>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift1'
 * '<S204>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift2'
 * '<S205>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift3'
 * '<S206>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift4'
 * '<S207>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift5'
 * '<S208>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift6'
 * '<S209>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift7'
 * '<S210>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift/bit_shift'
 * '<S211>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift1/bit_shift'
 * '<S212>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift2/bit_shift'
 * '<S213>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift3/bit_shift'
 * '<S214>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift4/bit_shift'
 * '<S215>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift5/bit_shift'
 * '<S216>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift6/bit_shift'
 * '<S217>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift7/bit_shift'
 * '<S218>' : 'VCU10/LED_Control/EBS_LED'
 * '<S219>' : 'VCU10/LED_Control/Subsystem'
 * '<S220>' : 'VCU10/LED_Control/Subsystem1'
 * '<S221>' : 'VCU10/LED_Control/TSLED_Inspection'
 * '<S222>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant'
 * '<S223>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant1'
 * '<S224>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant2'
 * '<S225>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant3'
 * '<S226>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant4'
 * '<S227>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant5'
 * '<S228>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant6'
 * '<S229>' : 'VCU10/LED_Control/EBS_LED/Enabled Subsystem'
 * '<S230>' : 'VCU10/LED_Control/EBS_LED/Shutdown_Button'
 * '<S231>' : 'VCU10/LED_Control/EBS_LED/display'
 * '<S232>' : 'VCU10/LED_Control/Subsystem/blue'
 * '<S233>' : 'VCU10/LED_Control/Subsystem1/yellow'
 * '<S234>' : 'VCU10/Motor_Control/ASTorque_Calculation'
 * '<S235>' : 'VCU10/Motor_Control/MCU1_Rx_Command'
 * '<S236>' : 'VCU10/Motor_Control/MCU1_Rx_Command3'
 * '<S237>' : 'VCU10/Motor_Control/ManualTorque_Calculation'
 * '<S238>' : 'VCU10/Motor_Control/Motor_Torque_Stateflow'
 * '<S239>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift'
 * '<S240>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift1'
 * '<S241>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift2'
 * '<S242>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift3'
 * '<S243>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift4'
 * '<S244>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift5'
 * '<S245>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift6'
 * '<S246>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift7'
 * '<S247>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift8'
 * '<S248>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift9'
 * '<S249>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift/bit_shift'
 * '<S250>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift1/bit_shift'
 * '<S251>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift2/bit_shift'
 * '<S252>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift3/bit_shift'
 * '<S253>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift4/bit_shift'
 * '<S254>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift5/bit_shift'
 * '<S255>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift6/bit_shift'
 * '<S256>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift7/bit_shift'
 * '<S257>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift8/bit_shift'
 * '<S258>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift9/bit_shift'
 * '<S259>' : 'VCU10/Motor_Control/MCU1_Rx_Command3/Bit Shift'
 * '<S260>' : 'VCU10/Motor_Control/MCU1_Rx_Command3/Bit Shift1'
 * '<S261>' : 'VCU10/Motor_Control/MCU1_Rx_Command3/Bit Shift/bit_shift'
 * '<S262>' : 'VCU10/Motor_Control/MCU1_Rx_Command3/Bit Shift1/bit_shift'
 * '<S263>' : 'VCU10/Motor_Control/ManualTorque_Calculation/APPS_Electrical_Monitor'
 * '<S264>' : 'VCU10/Motor_Control/ManualTorque_Calculation/Pedal_Fault_Check'
 * '<S265>' : 'VCU10/Output_Convert/Physical_HO1_8_Pack'
 * '<S266>' : 'VCU10/Output_Convert/Physical_OUT1_7_Pack'
 * '<S267>' : 'VCU10/Res/Res_Msg'
 * '<S268>' : 'VCU10/Res/Res_Msg/Bit Shift'
 * '<S269>' : 'VCU10/Res/Res_Msg/Bit Shift1'
 * '<S270>' : 'VCU10/Res/Res_Msg/Bit Shift2'
 * '<S271>' : 'VCU10/Res/Res_Msg/Subsystem'
 * '<S272>' : 'VCU10/Res/Res_Msg/Bit Shift/bit_shift'
 * '<S273>' : 'VCU10/Res/Res_Msg/Bit Shift1/bit_shift'
 * '<S274>' : 'VCU10/Res/Res_Msg/Bit Shift2/bit_shift'
 * '<S275>' : 'VCU10/Res/Res_Msg/Subsystem/heaartbeat_chart'
 * '<S276>' : 'VCU10/Res/Res_Msg/Subsystem/xor_Check'
 * '<S277>' : 'VCU10/Sensor_Signal/Subsystem'
 * '<S278>' : 'VCU10/TS_Activation/Chart'
 * '<S279>' : 'VCU10/TS_Activation/Chart1'
 * '<S280>' : 'VCU10/TS_Activation/Chart2'
 */
#endif                                 /* RTW_HEADER_VCU10_h_ */
