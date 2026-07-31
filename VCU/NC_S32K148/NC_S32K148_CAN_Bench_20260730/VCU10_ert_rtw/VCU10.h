/*
 * VCU10.h
 *
 * Code generation for model "VCU10".
 *
 * Model version              : 1.42
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Thu Jul 30 12:09:44 2026
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
                                                                  * '<S12>/TSLED_Inspection'
                                                                  * '<S17>/Chart'
                                                                  * '<S17>/Chart1'
                                                                  * '<S17>/Chart2'
                                                                  * '<S225>/Shutdown_Button'
                                                                  * '<S225>/display'
                                                                  * '<S72>/brkmotor_check_system'
                                                                  */
#define T                              true                      /* Referenced by:
                                                                  * '<S3>/Chart'
                                                                  * '<S4>/Chart'
                                                                  * '<S12>/TSLED_Inspection'
                                                                  * '<S17>/Chart'
                                                                  * '<S17>/Chart1'
                                                                  * '<S17>/Chart2'
                                                                  * '<S225>/Shutdown_Button'
                                                                  * '<S225>/display'
                                                                  * '<S72>/brkmotor_check_system'
                                                                  */

/* Block signals (default storage) */
typedef struct {
  real_T tarPrsReqFL;                  /* '<S150>/ESP_Chart1' */
  real_T tarPrsReqFR;                  /* '<S150>/ESP_Chart1' */
  real_T tarPrsReqRL;                  /* '<S150>/ESP_Chart1' */
  real_T tarPrsReqRR;                  /* '<S150>/ESP_Chart1' */
  real_T mode;                         /* '<S150>/ESP_Chart1' */
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
  real_T pedal_error;                  /* '<S244>/Pedal_Fault_Check' */
  real_T xorcheck;                     /* '<S277>/xor_Check' */
  real_T res_hbcheck;                  /* '<S277>/heaartbeat_chart' */
  real_T ts;                           /* '<S17>/Chart2' */
  uint32_T eps_cmdangle;               /* '<S55>/EPS_Stateflow1' */
  uint8_T eps_cmdworkmode;             /* '<S55>/EPS_Stateflow1' */
  uint8_T eps_cmdmiddle;               /* '<S55>/EPS_Stateflow1' */
  uint8_T eps_cmdvelocity;             /* '<S55>/EPS_Stateflow1' */
  uint8_T ami_process;                 /* '<S19>/Chart' */
  boolean_T brkmotor_check;            /* '<S72>/brkmotor_check_system' */
  boolean_T RelationalOperator1;       /* '<S53>/Relational Operator1' */
  boolean_T RelationalOperator1_n;     /* '<S52>/Relational Operator1' */
  boolean_T RelationalOperator1_no;    /* '<S50>/Relational Operator1' */
  boolean_T RelationalOperator1_k;     /* '<S49>/Relational Operator1' */
  boolean_T r2d_warning;               /* '<S3>/Chart' */
  boolean_T steer_return;              /* '<S3>/Chart' */
  boolean_T shutdown_flag;             /* '<S225>/Shutdown_Button' */
  boolean_T In1;                       /* '<S236>/In1' */
  boolean_T ts_warning;                /* '<S17>/Chart2' */
} B_VCU10_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T oilprs_frsensordata;          /* '<Root>/Data Store Memory24' */
  real_T ipc_astask;                   /* '<Root>/Data Store Memory22' */
  real_T safety_lock;                  /* '<Root>/FSEC_Safety_Lock_Memory' */
  real_T lscnt;                        /* '<S72>/brkmotor_check_system' */
  real_T fault_count;                  /* '<S244>/Pedal_Fault_Check' */
  real_T shutdown_count;               /* '<S225>/Shutdown_Button' */
  real_T err_cnt;                      /* '<S277>/xor_Check' */
  real_T hbcnt;                        /* '<S277>/heaartbeat_chart' */
  real_T run_check_flag;               /* '<S17>/Chart1' */
  real_T run_offcheck_flag;            /* '<S17>/Chart1' */
  real_T run_flag;                     /* '<S17>/Chart1' */
  real_T di8_offcheck_flag;            /* '<S17>/Chart' */
  real_T di8_check_flag;               /* '<S17>/Chart' */
  int32_T clockTickCounter;            /* '<S226>/Pulse Generator' */
  int32_T clockTickCounter_a;          /* '<S227>/Pulse Generator' */
  int32_T clockTickCounter_a2;         /* '<S4>/Pulse Generator' */
  uint32_T previousTicks;              /* '<S55>/EPS_Stateflow1' */
  uint32_T previousTicks_g;            /* '<S3>/Chart' */
  uint32_T previousTicks_o;            /* '<S12>/TSLED_Inspection' */
  uint32_T previousTicks_a;            /* '<S227>/yellow' */
  uint32_T previousTicks_av;           /* '<S226>/blue' */
  uint32_T previousTicks_ag;           /* '<S225>/display' */
  uint32_T previousTicks_f;            /* '<S225>/Shutdown_Button' */
  uint32_T previousTicks_c;            /* '<S4>/Chart' */
  uint32_T previousTicks_gm;           /* '<S17>/Chart2' */
  uint16_T wait_count;                 /* '<S7>/EBS_Response_Monitor' */
  uint16_T relation_count;             /* '<S7>/EBS_Response_Monitor' */
  uint16_T clear_count;                /* '<S7>/EBS_Response_Monitor' */
  uint16_T temporalCounter_i1;         /* '<S3>/Chart' */
  uint16_T brake_bad;                  /* '<S2>/FSEC_Sensor_Monitor' */
  uint16_T brake_good;                 /* '<S2>/FSEC_Sensor_Monitor' */
  uint16_T air_bad;                    /* '<S2>/FSEC_Sensor_Monitor' */
  uint16_T air_good;                   /* '<S2>/FSEC_Sensor_Monitor' */
  uint16_T comm_bad;                   /* '<S2>/FSEC_Sensor_Monitor' */
  uint16_T comm_good;                  /* '<S2>/FSEC_Sensor_Monitor' */
  uint16_T temporalCounter_i1_m;       /* '<S4>/Chart' */
  boolean_T FSEC_Safety_Fault_Delay_DSTATE;/* '<Root>/FSEC_Safety_Fault_Delay' */
  boolean_T UnitDelay_DSTATE;          /* '<S48>/Unit Delay' */
  boolean_T UnitDelay_DSTATE_e;        /* '<S51>/Unit Delay' */
  boolean_T EBS_Sensor_Fault_Delay_DSTATE;/* '<S7>/EBS_Sensor_Fault_Delay' */
  uint8_T last_count[4];               /* '<Root>/DBC_Debug_Select' */
  uint8_T ages[4];                     /* '<Root>/DBC_Debug_Select' */
  uint8_T is_active_c15_VCU10;         /* '<S55>/EPS_Stateflow1' */
  uint8_T is_c15_VCU10;                /* '<S55>/EPS_Stateflow1' */
  uint8_T temporalCounter_i1_g;        /* '<S55>/EPS_Stateflow1' */
  uint8_T is_active_c16_VCU10;         /* '<S150>/ESP_Chart1' */
  uint8_T is_c16_VCU10;                /* '<S150>/ESP_Chart1' */
  uint8_T is_active_c18_VCU10;         /* '<S72>/brkmotor_check_system' */
  uint8_T is_c18_VCU10;                /* '<S72>/brkmotor_check_system' */
  uint8_T lifesig_start;               /* '<S72>/brkmotor_check_system' */
  uint8_T is_active_c1_VCU10;          /* '<S3>/Chart' */
  uint8_T is_c1_VCU10;                 /* '<S3>/Chart' */
  uint8_T is_AS_Driving;               /* '<S3>/Chart' */
  uint8_T is_active_c4_VCU10;          /* '<S13>/Motor_Torque_Stateflow' */
  uint8_T is_c4_VCU10;                 /* '<S13>/Motor_Torque_Stateflow' */
  uint8_T is_active_c2_VCU10;          /* '<S12>/TSLED_Inspection' */
  uint8_T is_c2_VCU10;                 /* '<S12>/TSLED_Inspection' */
  uint8_T temporalCounter_i1_o;        /* '<S12>/TSLED_Inspection' */
  uint8_T is_active_c14_VCU10;         /* '<S227>/yellow' */
  uint8_T is_c14_VCU10;                /* '<S227>/yellow' */
  uint8_T temporalCounter_i1_j;        /* '<S227>/yellow' */
  uint8_T is_active_c13_VCU10;         /* '<S226>/blue' */
  uint8_T is_c13_VCU10;                /* '<S226>/blue' */
  uint8_T temporalCounter_i1_c;        /* '<S226>/blue' */
  uint8_T is_active_c6_VCU10;          /* '<S225>/display' */
  uint8_T is_c6_VCU10;                 /* '<S225>/display' */
  uint8_T temporalCounter_i1_gw;       /* '<S225>/display' */
  uint8_T is_active_c17_VCU10;         /* '<S225>/Shutdown_Button' */
  uint8_T is_c17_VCU10;                /* '<S225>/Shutdown_Button' */
  uint8_T temporalCounter_i1_ct;       /* '<S225>/Shutdown_Button' */
  uint8_T is_active_c20_VCU10;         /* '<S19>/Chart' */
  uint8_T is_c20_VCU10;                /* '<S19>/Chart' */
  uint8_T is_active_c11_VCU10;         /* '<S4>/Chart' */
  uint8_T is_c11_VCU10;                /* '<S4>/Chart' */
  uint8_T is_active_c19_VCU10;         /* '<S277>/xor_Check' */
  uint8_T is_c19_VCU10;                /* '<S277>/xor_Check' */
  uint8_T is_active_c10_VCU10;         /* '<S277>/heaartbeat_chart' */
  uint8_T is_c10_VCU10;                /* '<S277>/heaartbeat_chart' */
  uint8_T res_heartbeat_start;         /* '<S277>/heaartbeat_chart' */
  uint8_T is_active_c9_VCU10;          /* '<S17>/Chart2' */
  uint8_T is_c9_VCU10;                 /* '<S17>/Chart2' */
  uint8_T temporalCounter_i1_p;        /* '<S17>/Chart2' */
  uint8_T is_active_c8_VCU10;          /* '<S17>/Chart1' */
  uint8_T is_c8_VCU10;                 /* '<S17>/Chart1' */
  uint8_T is_Ignition_Check;           /* '<S17>/Chart1' */
  uint8_T is_Flameout_Check;           /* '<S17>/Chart1' */
  uint8_T is_active_c3_VCU10;          /* '<S17>/Chart' */
  uint8_T is_c3_VCU10;                 /* '<S17>/Chart' */
  uint8_T is_Ignition_Check_f;         /* '<S17>/Chart' */
  uint8_T is_Flameout_Check_i;         /* '<S17>/Chart' */
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
  boolean_T last_trigger;              /* '<S7>/EBS_Response_Monitor' */
  boolean_T waiting;                   /* '<S7>/EBS_Response_Monitor' */
  boolean_T fault_latched;             /* '<S7>/EBS_Response_Monitor' */
  boolean_T brake_fault;               /* '<S2>/FSEC_Sensor_Monitor' */
  boolean_T air_fault;                 /* '<S2>/FSEC_Sensor_Monitor' */
  boolean_T comm_fault;                /* '<S2>/FSEC_Sensor_Monitor' */
  boolean_T di8_flag;                  /* '<S17>/Chart' */
} DW_VCU10_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T MultiportSwitch[2];     /* '<S48>/Multiport Switch' */
  const real_T MultiportSwitch_e[2];   /* '<S51>/Multiport Switch' */
  const real_T Gain;                   /* '<S242>/Gain' */
  const real_T Gain1;                  /* '<S242>/Gain1' */
  const real_T Product;                /* '<S283>/Product' */
  const uint16_T DataTypeConversion8;  /* '<S242>/Data Type Conversion8' */
  const uint16_T Add2;                 /* '<S242>/Add2' */
  const uint16_T DataTypeConversion9;  /* '<S242>/Data Type Conversion9' */
  const uint16_T BitwiseAND7;          /* '<S242>/Bitwise AND7' */
  const uint16_T DataTypeConversion10; /* '<S242>/Data Type Conversion10' */
  const uint16_T BitwiseAND8;          /* '<S242>/Bitwise AND8' */
  const uint16_T BitwiseAND9;          /* '<S242>/Bitwise AND9' */
  const uint16_T BitwiseAND13;         /* '<S242>/Bitwise AND13' */
  const uint16_T BitwiseAND12;         /* '<S242>/Bitwise AND12' */
  const uint16_T BitwiseAND6;          /* '<S242>/Bitwise AND6' */
  const uint16_T DataTypeConversion5;  /* '<S243>/Data Type Conversion5' */
  const uint16_T BitwiseAND1;          /* '<S243>/Bitwise AND1' */
  const uint16_T DataTypeConversion1;  /* '<S243>/Data Type Conversion1' */
  const uint16_T BitwiseAND3;          /* '<S243>/Bitwise AND3' */
  const uint16_T BitwiseAND;           /* '<S243>/Bitwise AND' */
  const uint16_T BitwiseAND2;          /* '<S243>/Bitwise AND2' */
  const uint8_T BitwiseAND8_o;         /* '<S150>/Bitwise AND8' */
  const uint8_T DataTypeConversion1_c; /* '<S242>/Data Type Conversion1' */
  const uint8_T BitwiseAND1_a;         /* '<S242>/Bitwise AND1' */
  const uint8_T DataTypeConversion3;   /* '<S242>/Data Type Conversion3' */
  const uint8_T BitwiseAND2_o;         /* '<S242>/Bitwise AND2' */
  const uint8_T DataTypeConversion4;   /* '<S242>/Data Type Conversion4' */
  const uint8_T BitwiseAND3_o;         /* '<S242>/Bitwise AND3' */
  const uint8_T DataTypeConversion5_d; /* '<S242>/Data Type Conversion5' */
  const uint8_T BitwiseAND4;           /* '<S242>/Bitwise AND4' */
  const uint8_T DataTypeConversion6;   /* '<S242>/Data Type Conversion6' */
  const uint8_T BitwiseAND5;           /* '<S242>/Bitwise AND5' */
  const uint8_T MCU1_Rx_Commandbyte1;  /* '<S242>/Data Type Conversion11' */
  const uint8_T MCU1_Rx_Commandbyte6;  /* '<S242>/Data Type Conversion16' */
  const uint8_T MCU1_Rx_Command3byte0; /* '<S243>/Data Type Conversion2' */
  const uint8_T MCU1_Rx_Command3byte2; /* '<S243>/Data Type Conversion4' */
  const uint8_T bc2;                   /* '<S272>/bc2' */
} ConstB_VCU10_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S16>/1-D Lookup Table'
   *   '<S16>/1-D Lookup Table9'
   *   '<S48>/neg. edge'
   *   '<S51>/neg. edge'
   */
  real_T pooled22[2];

  /* Pooled Parameter (Expression: [252 2000])
   * Referenced by:
   *   '<S16>/1-D Lookup Table'
   *   '<S16>/1-D Lookup Table9'
   */
  uint16_T pooled38[2];
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
extern uint16_T airprs2;               /* '<S11>/Data Type Conversion' */
extern uint16_T airprs1;               /* '<S11>/Data Type Conversion1' */
extern uint16_T brkps;                 /* '<S11>/Data Type Conversion2' */
extern uint16_T apps2;                 /* '<S11>/Data Type Conversion3' */
extern uint16_T apps1;                 /* '<S11>/Data Type Conversion4' */
extern uint8_T canb_epsmsg[8];         /* '<S8>/EPS_TransmitMsg' */
extern uint8_T cana_motor_cmd[8];      /* '<S242>/Signal Conversion' */
extern uint8_T cana_motor_cmd3[8];     /* '<S13>/MCU1_Rx_Command3' */
extern uint8_T AMI_Rx[8];              /* '<S19>/Signal Conversion' */
extern uint8_T canb_ipcrxmsg[8];       /* '<S10>/IPC_ReceiveMsg' */
extern boolean_T ebs_driver_check;     /* '<S203>/Data Type Conversion' */
extern boolean_T shutdown_s;           /* '<S203>/Data Type Conversion1' */
extern boolean_T shutdown_e;           /* '<S203>/Data Type Conversion2' */
extern boolean_T di8_cockpit;          /* '<S203>/Data Type Conversion3' */
extern boolean_T di8_side;             /* '<S203>/Data Type Conversion4' */
extern boolean_T run_button;           /* '<S203>/Data Type Conversion5' */
extern boolean_T tsms;                 /* '<S203>/Data Type Conversion6' */
extern boolean_T asms;                 /* '<S203>/Data Type Conversion7' */
extern boolean_T ebs_watchdog;
     /* '<S7>/BufferToMakeInportVirtual_InsertedFor_ebs_watchdog_at_inport_0' */
extern boolean_T ebs_trig;             /* '<S7>/Logical Operator' */
extern boolean_T led_brake;            /* '<S12>/brake_on' */
extern boolean_T led_ebs_error;        /* '<S225>/Logical Operator' */
extern boolean_T led_assi_blue;        /* '<S226>/Data Type Conversion' */
extern boolean_T led_assi_yellow;      /* '<S227>/Data Type Conversion' */
extern boolean_T led_imd_error;        /* '<S12>/TSLED_Inspection' */
extern boolean_T led_bms_error;        /* '<S12>/TSLED_Inspection' */
extern boolean_T r2d_buzzer;           /* '<S4>/Switch1' */
extern boolean_T ebs_buzzer;           /* '<S4>/Switch' */
extern boolean_T res_error;            /*  */
extern boolean_T run;                  /* '<S17>/Chart1' */
extern boolean_T di8;                  /* '<S17>/Chart' */

/* Model entry point functions */
extern void VCU10_initialize(void);
extern void VCU10_step(void);
extern void VCU10_terminate(void);

/* Real-time Model object */
extern RT_MODEL_VCU10_T *const VCU10_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S56>/Add1' : Unused code path elimination
 * Block '<S56>/Constant' : Unused code path elimination
 * Block '<S56>/Data Type Conversion9' : Unused code path elimination
 * Block '<S56>/TorqueScale' : Unused code path elimination
 * Block '<S57>/Add1' : Unused code path elimination
 * Block '<S57>/Add2' : Unused code path elimination
 * Block '<S57>/Add5' : Unused code path elimination
 * Block '<S57>/Constant1' : Unused code path elimination
 * Block '<S57>/Constant2' : Unused code path elimination
 * Block '<S57>/Data Type Conversion1' : Unused code path elimination
 * Block '<S57>/Data Type Conversion10' : Unused code path elimination
 * Block '<S57>/Data Type Conversion2' : Unused code path elimination
 * Block '<S57>/Data Type Conversion4' : Unused code path elimination
 * Block '<S57>/Data Type Conversion5' : Unused code path elimination
 * Block '<S57>/Data Type Conversion6' : Unused code path elimination
 * Block '<S57>/Data Type Conversion8' : Unused code path elimination
 * Block '<S57>/Gain1' : Unused code path elimination
 * Block '<S57>/Gain2' : Unused code path elimination
 * Block '<S68>/Add' : Unused code path elimination
 * Block '<S68>/Add1' : Unused code path elimination
 * Block '<S68>/Add2' : Unused code path elimination
 * Block '<S68>/Add3' : Unused code path elimination
 * Block '<S68>/Bitwise AND' : Unused code path elimination
 * Block '<S68>/Bitwise AND19' : Unused code path elimination
 * Block '<S68>/Bitwise AND8' : Unused code path elimination
 * Block '<S68>/Data Type Conversion1' : Unused code path elimination
 * Block '<S68>/Data Type Conversion10' : Unused code path elimination
 * Block '<S68>/Data Type Conversion2' : Unused code path elimination
 * Block '<S68>/Data Type Conversion3' : Unused code path elimination
 * Block '<S68>/Data Type Conversion4' : Unused code path elimination
 * Block '<S68>/Data Type Conversion5' : Unused code path elimination
 * Block '<S68>/Data Type Conversion6' : Unused code path elimination
 * Block '<S68>/Data Type Conversion7' : Unused code path elimination
 * Block '<S68>/Data Type Conversion8' : Unused code path elimination
 * Block '<S68>/Data Type Conversion9' : Unused code path elimination
 * Block '<S68>/Gain' : Unused code path elimination
 * Block '<S70>/Add' : Unused code path elimination
 * Block '<S70>/Add1' : Unused code path elimination
 * Block '<S70>/Add2' : Unused code path elimination
 * Block '<S70>/Add3' : Unused code path elimination
 * Block '<S70>/Bitwise AND9' : Unused code path elimination
 * Block '<S71>/Add' : Unused code path elimination
 * Block '<S71>/Add1' : Unused code path elimination
 * Block '<S71>/Add2' : Unused code path elimination
 * Block '<S71>/Add3' : Unused code path elimination
 * Block '<S71>/Bitwise AND3' : Unused code path elimination
 * Block '<S71>/Bitwise AND7' : Unused code path elimination
 * Block '<S71>/Bitwise AND8' : Unused code path elimination
 * Block '<S71>/Data Type Conversion10' : Unused code path elimination
 * Block '<S71>/Data Type Conversion11' : Unused code path elimination
 * Block '<S71>/Data Type Conversion12' : Unused code path elimination
 * Block '<S71>/Data Type Conversion4' : Unused code path elimination
 * Block '<S71>/Data Type Conversion8' : Unused code path elimination
 * Block '<S71>/Data Type Conversion9' : Unused code path elimination
 * Block '<S71>/Gain' : Unused code path elimination
 * Block '<S71>/Gain1' : Unused code path elimination
 * Block '<S71>/Gain2' : Unused code path elimination
 * Block '<S71>/Gain3' : Unused code path elimination
 * Block '<S174>/Add1' : Unused code path elimination
 * Block '<S174>/Add2' : Unused code path elimination
 * Block '<S174>/Data Type Conversion5' : Unused code path elimination
 * Block '<S174>/Data Type Conversion7' : Unused code path elimination
 * Block '<S174>/Data Type Conversion9' : Unused code path elimination
 * Block '<S273>/Data Type Conversion1' : Unused code path elimination
 * Block '<S16>/1-D Lookup Table1' : Unused code path elimination
 * Block '<S16>/Data Type Conversion1' : Unused code path elimination
 * Block '<S16>/Data Type Conversion3' : Unused code path elimination
 * Block '<S16>/Data Type Conversion4' : Unused code path elimination
 * Block '<S16>/Saturation2' : Unused code path elimination
 * Block '<S48>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S51>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S56>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S55>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S55>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S55>/Data Type Conversion6' : Eliminate redundant data type conversion
 * Block '<S55>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S64>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S150>/Data Type Conversion12' : Eliminate redundant data type conversion
 * Block '<S241>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S16>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S16>/Data Type Conversion2' : Eliminate redundant data type conversion
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
 * '<S9>'   : 'VCU10/ESP'
 * '<S10>'  : 'VCU10/IPC'
 * '<S11>'  : 'VCU10/Input_Convert'
 * '<S12>'  : 'VCU10/LED_Control'
 * '<S13>'  : 'VCU10/Motor_Control'
 * '<S14>'  : 'VCU10/Output_Convert'
 * '<S15>'  : 'VCU10/Res'
 * '<S16>'  : 'VCU10/Sensor_Signal'
 * '<S17>'  : 'VCU10/TS_Activation'
 * '<S18>'  : 'VCU10/AMI_CAN/AMI_Receivemsg'
 * '<S19>'  : 'VCU10/AMI_CAN/AMI_Transmitmsg'
 * '<S20>'  : 'VCU10/AMI_CAN/Compare To Constant'
 * '<S21>'  : 'VCU10/AMI_CAN/Compare To Constant1'
 * '<S22>'  : 'VCU10/AMI_CAN/AMI_Receivemsg/Bit Shift'
 * '<S23>'  : 'VCU10/AMI_CAN/AMI_Receivemsg/Bit Shift/bit_shift'
 * '<S24>'  : 'VCU10/AMI_CAN/AMI_Transmitmsg/Bit Shift'
 * '<S25>'  : 'VCU10/AMI_CAN/AMI_Transmitmsg/Chart'
 * '<S26>'  : 'VCU10/AMI_CAN/AMI_Transmitmsg/Bit Shift/bit_shift'
 * '<S27>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check'
 * '<S28>'  : 'VCU10/ASB_Selfcheck/FSEC_Sensor_Monitor'
 * '<S29>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant'
 * '<S30>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant1'
 * '<S31>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant2'
 * '<S32>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant3'
 * '<S33>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant4'
 * '<S34>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant5'
 * '<S35>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant6'
 * '<S36>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant7'
 * '<S37>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant8'
 * '<S38>'  : 'VCU10/AS_Stateflow/Car_Spdzero_Check'
 * '<S39>'  : 'VCU10/AS_Stateflow/Chart'
 * '<S40>'  : 'VCU10/AS_Stateflow/Car_Spdzero_Check/Compare To Constant'
 * '<S41>'  : 'VCU10/AS_Stateflow/Car_Spdzero_Check/Compare To Constant1'
 * '<S42>'  : 'VCU10/Buzzer/Chart'
 * '<S43>'  : 'VCU10/EBS/Compare To Constant'
 * '<S44>'  : 'VCU10/EBS/Compare To Constant1'
 * '<S45>'  : 'VCU10/EBS/EBS_Response_Monitor'
 * '<S46>'  : 'VCU10/EBS/Edge Detector'
 * '<S47>'  : 'VCU10/EBS/Edge Detector2'
 * '<S48>'  : 'VCU10/EBS/Edge Detector/Model'
 * '<S49>'  : 'VCU10/EBS/Edge Detector/Model/NEGATIVE Edge'
 * '<S50>'  : 'VCU10/EBS/Edge Detector/Model/POSITIVE Edge'
 * '<S51>'  : 'VCU10/EBS/Edge Detector2/Model'
 * '<S52>'  : 'VCU10/EBS/Edge Detector2/Model/NEGATIVE Edge'
 * '<S53>'  : 'VCU10/EBS/Edge Detector2/Model/POSITIVE Edge'
 * '<S54>'  : 'VCU10/EPS/EPS_ReceiveMsg'
 * '<S55>'  : 'VCU10/EPS/EPS_TransmitMsg'
 * '<S56>'  : 'VCU10/EPS/EPS_ReceiveMsg/EPS_Send_Msg1'
 * '<S57>'  : 'VCU10/EPS/EPS_ReceiveMsg/EPS_Send_Msg2'
 * '<S58>'  : 'VCU10/EPS/EPS_ReceiveMsg/EPS_Send_Msg2/Bit Shift1'
 * '<S59>'  : 'VCU10/EPS/EPS_ReceiveMsg/EPS_Send_Msg2/Bit Shift1/bit_shift'
 * '<S60>'  : 'VCU10/EPS/EPS_TransmitMsg/Bit Shift'
 * '<S61>'  : 'VCU10/EPS/EPS_TransmitMsg/Compare To Constant2'
 * '<S62>'  : 'VCU10/EPS/EPS_TransmitMsg/Compare To Constant3'
 * '<S63>'  : 'VCU10/EPS/EPS_TransmitMsg/EPS_Stateflow1'
 * '<S64>'  : 'VCU10/EPS/EPS_TransmitMsg/Subsystem2'
 * '<S65>'  : 'VCU10/EPS/EPS_TransmitMsg/Bit Shift/bit_shift'
 * '<S66>'  : 'VCU10/ESP/ESP_ReceiveMsg'
 * '<S67>'  : 'VCU10/ESP/ESP_TransmitMsg'
 * '<S68>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01'
 * '<S69>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03'
 * '<S70>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06'
 * '<S71>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07'
 * '<S72>'  : 'VCU10/ESP/ESP_ReceiveMsg/Subsystem'
 * '<S73>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift'
 * '<S74>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift1'
 * '<S75>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift10'
 * '<S76>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift11'
 * '<S77>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift12'
 * '<S78>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift13'
 * '<S79>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift14'
 * '<S80>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift15'
 * '<S81>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift16'
 * '<S82>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift2'
 * '<S83>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift3'
 * '<S84>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift4'
 * '<S85>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift5'
 * '<S86>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift6'
 * '<S87>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift7'
 * '<S88>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift8'
 * '<S89>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift9'
 * '<S90>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift/bit_shift'
 * '<S91>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift1/bit_shift'
 * '<S92>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift10/bit_shift'
 * '<S93>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift11/bit_shift'
 * '<S94>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift12/bit_shift'
 * '<S95>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift13/bit_shift'
 * '<S96>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift14/bit_shift'
 * '<S97>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift15/bit_shift'
 * '<S98>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift16/bit_shift'
 * '<S99>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift2/bit_shift'
 * '<S100>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift3/bit_shift'
 * '<S101>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift4/bit_shift'
 * '<S102>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift5/bit_shift'
 * '<S103>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift6/bit_shift'
 * '<S104>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift7/bit_shift'
 * '<S105>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift8/bit_shift'
 * '<S106>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift9/bit_shift'
 * '<S107>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift'
 * '<S108>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift1'
 * '<S109>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift2'
 * '<S110>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift3'
 * '<S111>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift4'
 * '<S112>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift5'
 * '<S113>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift/bit_shift'
 * '<S114>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift1/bit_shift'
 * '<S115>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift2/bit_shift'
 * '<S116>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift3/bit_shift'
 * '<S117>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift4/bit_shift'
 * '<S118>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift5/bit_shift'
 * '<S119>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift'
 * '<S120>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift1'
 * '<S121>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift2'
 * '<S122>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift3'
 * '<S123>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift4'
 * '<S124>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift5'
 * '<S125>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift6'
 * '<S126>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift7'
 * '<S127>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift8'
 * '<S128>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift/bit_shift'
 * '<S129>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift1/bit_shift'
 * '<S130>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift2/bit_shift'
 * '<S131>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift3/bit_shift'
 * '<S132>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift4/bit_shift'
 * '<S133>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift5/bit_shift'
 * '<S134>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift6/bit_shift'
 * '<S135>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift7/bit_shift'
 * '<S136>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift8/bit_shift'
 * '<S137>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift'
 * '<S138>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift1'
 * '<S139>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift2'
 * '<S140>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift3'
 * '<S141>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift4'
 * '<S142>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift5'
 * '<S143>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift/bit_shift'
 * '<S144>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift1/bit_shift'
 * '<S145>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift2/bit_shift'
 * '<S146>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift3/bit_shift'
 * '<S147>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift4/bit_shift'
 * '<S148>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift5/bit_shift'
 * '<S149>' : 'VCU10/ESP/ESP_ReceiveMsg/Subsystem/brkmotor_check_system'
 * '<S150>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00'
 * '<S151>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift'
 * '<S152>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift1'
 * '<S153>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift2'
 * '<S154>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift3'
 * '<S155>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift4'
 * '<S156>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift5'
 * '<S157>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift6'
 * '<S158>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/ESP_Chart1'
 * '<S159>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift/bit_shift'
 * '<S160>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift1/bit_shift'
 * '<S161>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift2/bit_shift'
 * '<S162>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift3/bit_shift'
 * '<S163>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift4/bit_shift'
 * '<S164>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift5/bit_shift'
 * '<S165>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift6/bit_shift'
 * '<S166>' : 'VCU10/IPC/IPC_ReceiveMsg'
 * '<S167>' : 'VCU10/IPC/IPC_TransmitMsg'
 * '<S168>' : 'VCU10/IPC/IPC_ReceiveMsg/IPC_Rx_Msg'
 * '<S169>' : 'VCU10/IPC/IPC_ReceiveMsg/IPC_Rx_Msg/Bit Shift'
 * '<S170>' : 'VCU10/IPC/IPC_ReceiveMsg/IPC_Rx_Msg/Bit Shift1'
 * '<S171>' : 'VCU10/IPC/IPC_ReceiveMsg/IPC_Rx_Msg/Bit Shift/bit_shift'
 * '<S172>' : 'VCU10/IPC/IPC_ReceiveMsg/IPC_Rx_Msg/Bit Shift1/bit_shift'
 * '<S173>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1'
 * '<S174>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2'
 * '<S175>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift'
 * '<S176>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift1'
 * '<S177>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift2'
 * '<S178>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift3'
 * '<S179>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift4'
 * '<S180>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift5'
 * '<S181>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift6'
 * '<S182>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift8'
 * '<S183>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift/bit_shift'
 * '<S184>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift1/bit_shift'
 * '<S185>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift2/bit_shift'
 * '<S186>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift3/bit_shift'
 * '<S187>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift4/bit_shift'
 * '<S188>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift5/bit_shift'
 * '<S189>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift6/bit_shift'
 * '<S190>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift8/bit_shift'
 * '<S191>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift'
 * '<S192>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift1'
 * '<S193>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift2'
 * '<S194>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift3'
 * '<S195>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift4'
 * '<S196>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift5'
 * '<S197>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift/bit_shift'
 * '<S198>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift1/bit_shift'
 * '<S199>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift2/bit_shift'
 * '<S200>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift3/bit_shift'
 * '<S201>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift4/bit_shift'
 * '<S202>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift5/bit_shift'
 * '<S203>' : 'VCU10/Input_Convert/Data_Analysis'
 * '<S204>' : 'VCU10/Input_Convert/Pedal_AinConvert_APP1'
 * '<S205>' : 'VCU10/Input_Convert/Pedal_AinConvert_APP2'
 * '<S206>' : 'VCU10/Input_Convert/Pedal_AinConvert_Brake'
 * '<S207>' : 'VCU10/Input_Convert/Pressure_AinConvert1'
 * '<S208>' : 'VCU10/Input_Convert/Pressure_AinConvert2'
 * '<S209>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift'
 * '<S210>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift1'
 * '<S211>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift2'
 * '<S212>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift3'
 * '<S213>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift4'
 * '<S214>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift5'
 * '<S215>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift6'
 * '<S216>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift7'
 * '<S217>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift/bit_shift'
 * '<S218>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift1/bit_shift'
 * '<S219>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift2/bit_shift'
 * '<S220>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift3/bit_shift'
 * '<S221>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift4/bit_shift'
 * '<S222>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift5/bit_shift'
 * '<S223>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift6/bit_shift'
 * '<S224>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift7/bit_shift'
 * '<S225>' : 'VCU10/LED_Control/EBS_LED'
 * '<S226>' : 'VCU10/LED_Control/Subsystem'
 * '<S227>' : 'VCU10/LED_Control/Subsystem1'
 * '<S228>' : 'VCU10/LED_Control/TSLED_Inspection'
 * '<S229>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant'
 * '<S230>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant1'
 * '<S231>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant2'
 * '<S232>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant3'
 * '<S233>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant4'
 * '<S234>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant5'
 * '<S235>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant6'
 * '<S236>' : 'VCU10/LED_Control/EBS_LED/Enabled Subsystem'
 * '<S237>' : 'VCU10/LED_Control/EBS_LED/Shutdown_Button'
 * '<S238>' : 'VCU10/LED_Control/EBS_LED/display'
 * '<S239>' : 'VCU10/LED_Control/Subsystem/blue'
 * '<S240>' : 'VCU10/LED_Control/Subsystem1/yellow'
 * '<S241>' : 'VCU10/Motor_Control/ASTorque_Calculation'
 * '<S242>' : 'VCU10/Motor_Control/MCU1_Rx_Command'
 * '<S243>' : 'VCU10/Motor_Control/MCU1_Rx_Command3'
 * '<S244>' : 'VCU10/Motor_Control/ManualTorque_Calculation'
 * '<S245>' : 'VCU10/Motor_Control/Motor_Torque_Stateflow'
 * '<S246>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift'
 * '<S247>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift1'
 * '<S248>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift2'
 * '<S249>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift3'
 * '<S250>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift4'
 * '<S251>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift5'
 * '<S252>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift6'
 * '<S253>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift7'
 * '<S254>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift8'
 * '<S255>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift9'
 * '<S256>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift/bit_shift'
 * '<S257>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift1/bit_shift'
 * '<S258>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift2/bit_shift'
 * '<S259>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift3/bit_shift'
 * '<S260>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift4/bit_shift'
 * '<S261>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift5/bit_shift'
 * '<S262>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift6/bit_shift'
 * '<S263>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift7/bit_shift'
 * '<S264>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift8/bit_shift'
 * '<S265>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift9/bit_shift'
 * '<S266>' : 'VCU10/Motor_Control/MCU1_Rx_Command3/Bit Shift'
 * '<S267>' : 'VCU10/Motor_Control/MCU1_Rx_Command3/Bit Shift1'
 * '<S268>' : 'VCU10/Motor_Control/MCU1_Rx_Command3/Bit Shift/bit_shift'
 * '<S269>' : 'VCU10/Motor_Control/MCU1_Rx_Command3/Bit Shift1/bit_shift'
 * '<S270>' : 'VCU10/Motor_Control/ManualTorque_Calculation/Pedal_Fault_Check'
 * '<S271>' : 'VCU10/Output_Convert/Physical_HO1_8_Pack'
 * '<S272>' : 'VCU10/Output_Convert/Physical_OUT1_7_Pack'
 * '<S273>' : 'VCU10/Res/Res_Msg'
 * '<S274>' : 'VCU10/Res/Res_Msg/Bit Shift'
 * '<S275>' : 'VCU10/Res/Res_Msg/Bit Shift1'
 * '<S276>' : 'VCU10/Res/Res_Msg/Bit Shift2'
 * '<S277>' : 'VCU10/Res/Res_Msg/Subsystem'
 * '<S278>' : 'VCU10/Res/Res_Msg/Bit Shift/bit_shift'
 * '<S279>' : 'VCU10/Res/Res_Msg/Bit Shift1/bit_shift'
 * '<S280>' : 'VCU10/Res/Res_Msg/Bit Shift2/bit_shift'
 * '<S281>' : 'VCU10/Res/Res_Msg/Subsystem/heaartbeat_chart'
 * '<S282>' : 'VCU10/Res/Res_Msg/Subsystem/xor_Check'
 * '<S283>' : 'VCU10/Sensor_Signal/Subsystem'
 * '<S284>' : 'VCU10/TS_Activation/Chart'
 * '<S285>' : 'VCU10/TS_Activation/Chart1'
 * '<S286>' : 'VCU10/TS_Activation/Chart2'
 */
#endif                                 /* RTW_HEADER_VCU10_h_ */
