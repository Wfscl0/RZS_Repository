/*
 * File: rzs10thnew2021b.h
 *
 * Code generated for Simulink model 'rzs10thnew2021b'.
 *
 * Model version                  : 1.14
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue Apr 28 14:44:27 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_rzs10thnew2021b_h_
#define RTW_HEADER_rzs10thnew2021b_h_
#include <math.h>
#ifndef rzs10thnew2021b_COMMON_INCLUDES_
#define rzs10thnew2021b_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* rzs10thnew2021b_COMMON_INCLUDES_ */

#include "rzs10thnew2021b_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmCounterLimit
#define rtmCounterLimit(rtm, idx)      ((rtm)->Timing.TaskCounters.cLimit[(idx)])
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
#define rtmStepTask(rtm, idx)          ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* Exported data define */

/* Definition for custom storage class: Define */
#define F                              false                     /* Referenced by:
                                                                  * '<S4>/Chart'
                                                                  * '<S5>/Chart'
                                                                  * '<S14>/Chart'
                                                                  * '<S14>/Chart1'
                                                                  * '<S14>/Chart2'
                                                                  * '<S196>/BMS_LED'
                                                                  * '<S196>/IMD_LED'
                                                                  * '<S197>/Shutdown_Button'
                                                                  * '<S197>/display'
                                                                  * '<S73>/brkmotor_check_system'
                                                                  */
#define T                              true                      /* Referenced by:
                                                                  * '<S4>/Chart'
                                                                  * '<S5>/Chart'
                                                                  * '<S14>/Chart'
                                                                  * '<S14>/Chart1'
                                                                  * '<S14>/Chart2'
                                                                  * '<S196>/BMS_LED'
                                                                  * '<S196>/IMD_LED'
                                                                  * '<S197>/Shutdown_Button'
                                                                  * '<S197>/display'
                                                                  * '<S73>/brkmotor_check_system'
                                                                  */

/* Block signals (default storage) */
typedef struct {
  real_T tarPrsReqFL;                  /* '<S151>/ESP_Chart1' */
  real_T tarPrsReqFR;                  /* '<S151>/ESP_Chart1' */
  real_T tarPrsReqRL;                  /* '<S151>/ESP_Chart1' */
  real_T tarPrsReqRR;                  /* '<S151>/ESP_Chart1' */
  real_T as_ebs_trig;                  /* '<S4>/Chart' */
  real_T as_led_blue;                  /* '<S4>/Chart' */
  real_T as_led_yellow;                /* '<S4>/Chart' */
  real_T steering_flag_i;              /* '<S4>/Chart' */
  real_T brake_flag_b;                 /* '<S4>/Chart' */
  real_T manual_driving_flag_k;        /* '<S4>/Chart' */
  real_T as_emergency_flag_e;          /* '<S4>/Chart' */
  real_T as_off_flag_d;                /* '<S4>/Chart' */
  real_T as_ready_flag_p;              /* '<S4>/Chart' */
  real_T as_driving_flag_b;            /* '<S4>/Chart' */
  real_T as_finished_flag_g;           /* '<S4>/Chart' */
  real_T r2d_flag_l;                   /* '<S4>/Chart' */
  real_T ipc_astask;                   /* '<S3>/Chart' */
  real_T ami_inspection_signal;        /* '<S3>/Chart' */
  real_T motor_torque;                 /* '<S11>/Motor_Torque_Stateflow' */
  real_T Switch;                       /* '<S217>/Switch' */
  real_T pedal_error;                  /* '<S217>/Pedal_Fault_Check' */
  real_T DataTypeConversion;           /* '<S214>/Data Type Conversion' */
  real_T xorcheck;                     /* '<S248>/xor_Check' */
  real_T res_hbcheck;                  /* '<S248>/heaartbeat_chart' */
  real_T ts;                           /* '<S14>/Chart2' */
  real_T Product1;                     /* '<S254>/Product1' */
  real_T Product2;                     /* '<S254>/Product2' */
  real_T DataTypeConversion1;          /* '<S173>/Data Type Conversion1' */
  real_T y;                            /* '<S190>/bit_shift' */
  real_T ipc_esp_flprs;
  real_T ipc_eps_frprs;
  real_T ipc_esp_rlprs;
  real_T ipc_esp_rrprs;
  real_T d;
  uint8_T TmpSignalConversionAtDelay1[8];/* '<Root>/Motor_Control' */
  uint8_T OutportBufferForcana_motor_cmd3[8];
  uint16_T eps_cmdangle;               /* '<S56>/EPS_Stateflow1' */
  uint8_T eps_cmdworkmode;             /* '<S56>/EPS_Stateflow1' */
  uint8_T eps_cmdmiddle;               /* '<S56>/EPS_Stateflow1' */
  uint8_T eps_cmdvelocity;             /* '<S56>/EPS_Stateflow1' */
  uint8_T ami_process;                 /* '<S17>/Chart' */
  boolean_T brkmotor_check;            /* '<S73>/brkmotor_check_system' */
  boolean_T RelationalOperator1;       /* '<S54>/Relational Operator1' */
  boolean_T RelationalOperator1_k;     /* '<S53>/Relational Operator1' */
  boolean_T RelationalOperator1_i;     /* '<S51>/Relational Operator1' */
  boolean_T RelationalOperator1_c;     /* '<S50>/Relational Operator1' */
  boolean_T RelationalOperator1_h;     /* '<S48>/Relational Operator1' */
  boolean_T RelationalOperator1_n;     /* '<S47>/Relational Operator1' */
  boolean_T r2d_warning;               /* '<S4>/Chart' */
  boolean_T steer_return;              /* '<S4>/Chart' */
  boolean_T shutdown_flag;             /* '<S197>/Shutdown_Button' */
  boolean_T In1;                       /* '<S209>/In1' */
  boolean_T ts_warning;                /* '<S14>/Chart2' */
} B_rzs10thnew2021b_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T ts;                           /* '<Root>/Data Store Memory11' */
  real_T ipc_astask;                   /* '<Root>/Data Store Memory22' */
  real_T oilprs_frsensordata;          /* '<Root>/Data Store Memory24' */
  real_T lscnt;                        /* '<S73>/brkmotor_check_system' */
  real_T fault_count;                  /* '<S217>/Pedal_Fault_Check' */
  real_T shutdown_count;               /* '<S197>/Shutdown_Button' */
  real_T err_cnt;                      /* '<S248>/xor_Check' */
  real_T hbcnt;                        /* '<S248>/heaartbeat_chart' */
  real_T run_check_flag;               /* '<S14>/Chart1' */
  real_T run_offcheck_flag;            /* '<S14>/Chart1' */
  real_T run_flag;                     /* '<S14>/Chart1' */
  real_T di8_offcheck_flag;            /* '<S14>/Chart' */
  real_T di8_check_flag;               /* '<S14>/Chart' */
  int32_T clockTickCounter;            /* '<S6>/Pulse Generator' */
  int32_T clockTickCounter_i;          /* '<S198>/Pulse Generator' */
  int32_T clockTickCounter_o;          /* '<S199>/Pulse Generator' */
  int32_T clockTickCounter_l;          /* '<S5>/Pulse Generator' */
  uint32_T previousTicks;              /* '<S56>/EPS_Stateflow1' */
  uint32_T previousTicks_i;            /* '<S4>/Chart' */
  uint32_T previousTicks_n;            /* '<S199>/yellow' */
  uint32_T previousTicks_g;            /* '<S198>/blue' */
  uint32_T previousTicks_b;            /* '<S197>/display' */
  uint32_T previousTicks_c;            /* '<S197>/Shutdown_Button' */
  uint32_T previousTicks_a;            /* '<S196>/IMD_LED' */
  uint32_T previousTicks_d;            /* '<S196>/BMS_LED' */
  uint32_T previousTicks_dy;           /* '<S5>/Chart' */
  uint32_T previousTicks_l;            /* '<S14>/Chart2' */
  uint16_T temporalCounter_i1;         /* '<S4>/Chart' */
  uint16_T temporalCounter_i1_j;       /* '<S5>/Chart' */
  uint8_T Delay_DSTATE[8];             /* '<Root>/Delay' */
  uint8_T Delay1_DSTATE;               /* '<Root>/Delay1' */
  uint8_T Delay2_DSTATE;               /* '<Root>/Delay2' */
  boolean_T UnitDelay_DSTATE;          /* '<S46>/Unit Delay' */
  boolean_T UnitDelay_DSTATE_h;        /* '<S49>/Unit Delay' */
  boolean_T UnitDelay_DSTATE_f;        /* '<S52>/Unit Delay' */
  uint8_T ami_astask;                  /* '<Root>/Data Store Memory23' */
  uint8_T is_active_c15_rzs10thnew2021b;/* '<S56>/EPS_Stateflow1' */
  uint8_T is_c15_rzs10thnew2021b;      /* '<S56>/EPS_Stateflow1' */
  uint8_T temporalCounter_i1_a;        /* '<S56>/EPS_Stateflow1' */
  uint8_T is_active_c16_rzs10thnew2021b;/* '<S151>/ESP_Chart1' */
  uint8_T is_c16_rzs10thnew2021b;      /* '<S151>/ESP_Chart1' */
  uint8_T is_active_c18_rzs10thnew2021b;/* '<S73>/brkmotor_check_system' */
  uint8_T is_c18_rzs10thnew2021b;      /* '<S73>/brkmotor_check_system' */
  uint8_T lifesig_start;               /* '<S73>/brkmotor_check_system' */
  uint8_T is_active_c1_rzs10thnew2021b;/* '<S4>/Chart' */
  uint8_T is_c1_rzs10thnew2021b;       /* '<S4>/Chart' */
  uint8_T is_AS_Driving;               /* '<S4>/Chart' */
  uint8_T is_active_c7_rzs10thnew2021b;/* '<S3>/Chart' */
  uint8_T is_c7_rzs10thnew2021b;       /* '<S3>/Chart' */
  uint8_T is_active_c4_rzs10thnew2021b;/* '<S11>/Motor_Torque_Stateflow' */
  uint8_T is_c4_rzs10thnew2021b;       /* '<S11>/Motor_Torque_Stateflow' */
  uint8_T is_active_c14_rzs10thnew2021b;/* '<S199>/yellow' */
  uint8_T is_c14_rzs10thnew2021b;      /* '<S199>/yellow' */
  uint8_T temporalCounter_i1_h;        /* '<S199>/yellow' */
  uint8_T is_active_c13_rzs10thnew2021b;/* '<S198>/blue' */
  uint8_T is_c13_rzs10thnew2021b;      /* '<S198>/blue' */
  uint8_T temporalCounter_i1_m;        /* '<S198>/blue' */
  uint8_T is_active_c6_rzs10thnew2021b;/* '<S197>/display' */
  uint8_T is_c6_rzs10thnew2021b;       /* '<S197>/display' */
  uint8_T temporalCounter_i1_g;        /* '<S197>/display' */
  uint8_T is_active_c17_rzs10thnew2021b;/* '<S197>/Shutdown_Button' */
  uint8_T is_c17_rzs10thnew2021b;      /* '<S197>/Shutdown_Button' */
  uint8_T temporalCounter_i1_e;        /* '<S197>/Shutdown_Button' */
  uint8_T is_active_c12_rzs10thnew2021b;/* '<S196>/IMD_LED' */
  uint8_T is_c12_rzs10thnew2021b;      /* '<S196>/IMD_LED' */
  uint8_T temporalCounter_i1_h1;       /* '<S196>/IMD_LED' */
  uint8_T is_active_c5_rzs10thnew2021b;/* '<S196>/BMS_LED' */
  uint8_T is_c5_rzs10thnew2021b;       /* '<S196>/BMS_LED' */
  uint8_T temporalCounter_i1_d;        /* '<S196>/BMS_LED' */
  uint8_T is_active_c20_rzs10thnew2021b;/* '<S17>/Chart' */
  uint8_T is_c20_rzs10thnew2021b;      /* '<S17>/Chart' */
  uint8_T is_active_c11_rzs10thnew2021b;/* '<S5>/Chart' */
  uint8_T is_c11_rzs10thnew2021b;      /* '<S5>/Chart' */
  uint8_T is_active_c19_rzs10thnew2021b;/* '<S248>/xor_Check' */
  uint8_T is_c19_rzs10thnew2021b;      /* '<S248>/xor_Check' */
  uint8_T is_active_c10_rzs10thnew2021b;/* '<S248>/heaartbeat_chart' */
  uint8_T is_c10_rzs10thnew2021b;      /* '<S248>/heaartbeat_chart' */
  uint8_T res_heartbeat_start;         /* '<S248>/heaartbeat_chart' */
  uint8_T is_active_c9_rzs10thnew2021b;/* '<S14>/Chart2' */
  uint8_T is_c9_rzs10thnew2021b;       /* '<S14>/Chart2' */
  uint8_T temporalCounter_i1_i;        /* '<S14>/Chart2' */
  uint8_T is_active_c8_rzs10thnew2021b;/* '<S14>/Chart1' */
  uint8_T is_c8_rzs10thnew2021b;       /* '<S14>/Chart1' */
  uint8_T is_Ignition_Check;           /* '<S14>/Chart1' */
  uint8_T is_Flameout_Check;           /* '<S14>/Chart1' */
  uint8_T is_active_c3_rzs10thnew2021b;/* '<S14>/Chart' */
  uint8_T is_c3_rzs10thnew2021b;       /* '<S14>/Chart' */
  uint8_T is_Ignition_Check_c;         /* '<S14>/Chart' */
  uint8_T is_Flameout_Check_j;         /* '<S14>/Chart' */
  boolean_T brkmotor_check;            /* '<Root>/Data Store Memory' */
  boolean_T asb_check;                 /* '<Root>/Data Store Memory1' */
  boolean_T r2d_warning;               /* '<Root>/Data Store Memory12' */
  boolean_T steer_return;              /* '<Root>/Data Store Memory14' */
  boolean_T ebs_working;               /* '<Root>/Data Store Memory2' */
  boolean_T ebs_warning;               /* '<Root>/Data Store Memory20' */
  boolean_T task_finish;               /* '<Root>/Data Store Memory21' */
  boolean_T brake_on;                  /* '<Root>/Data Store Memory3' */
  boolean_T ebs_check;                 /* '<Root>/Data Store Memory4' */
  boolean_T steer_zero;                /* '<Root>/Data Store Memory9' */
  boolean_T di8_flag;                  /* '<S14>/Chart' */
} DW_rzs10thnew2021b_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T MultiportSwitch[2];     /* '<S46>/Multiport Switch' */
  const real_T MultiportSwitch_n[2];   /* '<S49>/Multiport Switch' */
  const real_T MultiportSwitch_p[2];   /* '<S52>/Multiport Switch' */
  const real_T Gain;                   /* '<S215>/Gain' */
  const real_T Gain1;                  /* '<S215>/Gain1' */
  const real_T Product;                /* '<S254>/Product' */
  const uint16_T DataTypeConversion8;  /* '<S215>/Data Type Conversion8' */
  const uint16_T Add2;                 /* '<S215>/Add2' */
  const uint16_T DataTypeConversion9;  /* '<S215>/Data Type Conversion9' */
  const uint16_T BitwiseAND7;          /* '<S215>/Bitwise AND7' */
  const uint16_T DataTypeConversion10; /* '<S215>/Data Type Conversion10' */
  const uint16_T BitwiseAND8;          /* '<S215>/Bitwise AND8' */
  const uint16_T BitwiseAND9;          /* '<S215>/Bitwise AND9' */
  const uint16_T BitwiseAND13;         /* '<S215>/Bitwise AND13' */
  const uint16_T BitwiseAND12;         /* '<S215>/Bitwise AND12' */
  const uint16_T BitwiseAND6;          /* '<S215>/Bitwise AND6' */
  const uint16_T DataTypeConversion5;  /* '<S216>/Data Type Conversion5' */
  const uint16_T BitwiseAND1;          /* '<S216>/Bitwise AND1' */
  const uint16_T DataTypeConversion1;  /* '<S216>/Data Type Conversion1' */
  const uint16_T BitwiseAND3;          /* '<S216>/Bitwise AND3' */
  const uint16_T BitwiseAND;           /* '<S216>/Bitwise AND' */
  const uint16_T BitwiseAND2;          /* '<S216>/Bitwise AND2' */
  const uint8_T BitwiseAND8_j;         /* '<S151>/Bitwise AND8' */
  const uint8_T DataTypeConversion1_n; /* '<S215>/Data Type Conversion1' */
  const uint8_T BitwiseAND1_o;         /* '<S215>/Bitwise AND1' */
  const uint8_T DataTypeConversion3;   /* '<S215>/Data Type Conversion3' */
  const uint8_T BitwiseAND2_l;         /* '<S215>/Bitwise AND2' */
  const uint8_T DataTypeConversion4;   /* '<S215>/Data Type Conversion4' */
  const uint8_T BitwiseAND3_i;         /* '<S215>/Bitwise AND3' */
  const uint8_T DataTypeConversion5_g; /* '<S215>/Data Type Conversion5' */
  const uint8_T BitwiseAND4;           /* '<S215>/Bitwise AND4' */
  const uint8_T DataTypeConversion6;   /* '<S215>/Data Type Conversion6' */
  const uint8_T BitwiseAND5;           /* '<S215>/Bitwise AND5' */
  const uint8_T MCU1_Rx_Command3byte0; /* '<S216>/Data Type Conversion2' */
  const uint8_T MCU1_Rx_Command3byte2; /* '<S216>/Data Type Conversion4' */
} ConstB_rzs10thnew2021b_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: [0 1])
   * Referenced by:
   *   '<S13>/1-D Lookup Table'
   *   '<S13>/1-D Lookup Table6'
   *   '<S13>/1-D Lookup Table7'
   *   '<S13>/1-D Lookup Table9'
   */
  uint16_T pooled32[2];

  /* Pooled Parameter (Expression: [252 2000])
   * Referenced by:
   *   '<S13>/1-D Lookup Table'
   *   '<S13>/1-D Lookup Table6'
   *   '<S13>/1-D Lookup Table7'
   *   '<S13>/1-D Lookup Table9'
   */
  uint16_T pooled33[2];
} ConstP_rzs10thnew2021b_T;

/* Real-time Model Data Structure */
struct tag_RTM_rzs10thnew2021b_T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick1;
    struct {
      uint8_T TID[2];
      uint8_T cLimit[2];
    } TaskCounters;
  } Timing;
};

/* Block signals (default storage) */
extern B_rzs10thnew2021b_T rzs10thnew2021b_B;

/* Block states (default storage) */
extern DW_rzs10thnew2021b_T rzs10thnew2021b_DW;
extern const ConstB_rzs10thnew2021b_T rzs10thnew2021b_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_rzs10thnew2021b_T rzs10thnew2021b_ConstP;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern boolean_T bms_error;            /* '<Root>/bms_error' */
extern boolean_T imd_error;            /* '<Root>/imd_error' */
extern uint8_T ESP_T_01[8];            /* '<Root>/ESP_T_01' */
extern uint8_T ESP_T_03[8];            /* '<Root>/ESP_T_03' */
extern uint8_T ESP_T_06[8];            /* '<Root>/ESP_T_06' */
extern uint8_T ESP_T_07[8];            /* '<Root>/ESP_T_07' */
extern uint8_T canb_epssendmsg1[8];    /* '<Root>/canb_epssendmsg1' */
extern uint8_T canb_epssendmsg2[8];    /* '<Root>/canb_epssendmsg2' */
extern uint8_T res_msg[8];             /* '<Root>/res_msg' */
extern uint8_T canb_ipctsmsg1[8];      /* '<Root>/canb_ipctsmsg1' */
extern uint8_T canb_ipctsmsg2[8];      /* '<Root>/canb_ipctsmsg2' */
extern uint8_T AMI_Tx[8];              /* '<Root>/AMI_Tx' */
extern VCU_IN_PAR digital_input;       /* '<Root>/Input' */
extern VCU_OUT_PAR digital_output;     /* '<S15>/Bus Creator' */
extern uint8_T ESP_R_00[8];            /* '<Root>/Delay' */
extern uint8_T cana_motor_cmd[8];      /* '<Root>/Delay1' */
extern uint8_T cana_motor_cmd3[8];     /* '<Root>/Delay2' */
extern uint8_T canb_epsmsg[8];         /* '<S7>/EPS_TransmitMsg' */
extern uint8_T AMI_Rx[8];              /* '<S17>/Signal Conversion' */
extern uint8_T canb_ipcrxmsg[8];       /* '<S9>/IPC_ReceiveMsg' */
extern boolean_T ebs_trig;             /* '<S6>/Logical Operator' */
extern boolean_T ebs_watchdog;         /* '<S6>/Data Type Conversion5' */
extern boolean_T led_brake;            /* '<S10>/brake_on' */
extern boolean_T led_ebs_error;        /* '<S197>/Logical Operator' */
extern boolean_T led_assi_blue;        /* '<S198>/Data Type Conversion' */
extern boolean_T led_assi_yellow;      /* '<S199>/Data Type Conversion' */
extern boolean_T led_imd_error;        /* '<S196>/IMD_LED' */
extern boolean_T led_bms_error;        /* '<S196>/BMS_LED' */
extern boolean_T r2d_buzzer;           /* '<S5>/r2d_warning' */
extern boolean_T ebs_buzzer;           /* '<S5>/Switch' */
extern boolean_T ts_buzzer;            /* '<S5>/ts_warning' */
extern boolean_T res_error;            /*  */
extern boolean_T run;                  /* '<S14>/Chart1' */
extern boolean_T di8;                  /* '<S14>/Chart' */

/* Model entry point functions */
extern void rzs10thnew2021b_initialize(void);
extern void rzs10thnew2021b_step0(void);
extern void rzs10thnew2021b_step1(void);
extern void rzs10thnew2021b_terminate(void);

/* Real-time Model object */
extern RT_MODEL_rzs10thnew2021b_T *const rzs10thnew2021b_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S57>/Add1' : Unused code path elimination
 * Block '<S57>/Constant' : Unused code path elimination
 * Block '<S57>/Data Type Conversion9' : Unused code path elimination
 * Block '<S58>/Add1' : Unused code path elimination
 * Block '<S58>/Add2' : Unused code path elimination
 * Block '<S58>/Add5' : Unused code path elimination
 * Block '<S58>/Constant1' : Unused code path elimination
 * Block '<S58>/Constant2' : Unused code path elimination
 * Block '<S58>/Data Type Conversion1' : Unused code path elimination
 * Block '<S58>/Data Type Conversion10' : Unused code path elimination
 * Block '<S58>/Data Type Conversion2' : Unused code path elimination
 * Block '<S58>/Data Type Conversion4' : Unused code path elimination
 * Block '<S58>/Data Type Conversion5' : Unused code path elimination
 * Block '<S58>/Data Type Conversion6' : Unused code path elimination
 * Block '<S58>/Data Type Conversion8' : Unused code path elimination
 * Block '<S58>/Gain1' : Unused code path elimination
 * Block '<S58>/Gain2' : Unused code path elimination
 * Block '<S69>/Add' : Unused code path elimination
 * Block '<S69>/Add1' : Unused code path elimination
 * Block '<S69>/Add2' : Unused code path elimination
 * Block '<S69>/Add3' : Unused code path elimination
 * Block '<S69>/Bitwise AND' : Unused code path elimination
 * Block '<S69>/Bitwise AND19' : Unused code path elimination
 * Block '<S69>/Bitwise AND8' : Unused code path elimination
 * Block '<S69>/Data Type Conversion1' : Unused code path elimination
 * Block '<S69>/Data Type Conversion10' : Unused code path elimination
 * Block '<S69>/Data Type Conversion2' : Unused code path elimination
 * Block '<S69>/Data Type Conversion3' : Unused code path elimination
 * Block '<S69>/Data Type Conversion4' : Unused code path elimination
 * Block '<S69>/Data Type Conversion5' : Unused code path elimination
 * Block '<S69>/Data Type Conversion6' : Unused code path elimination
 * Block '<S69>/Data Type Conversion7' : Unused code path elimination
 * Block '<S69>/Data Type Conversion8' : Unused code path elimination
 * Block '<S69>/Data Type Conversion9' : Unused code path elimination
 * Block '<S69>/Gain' : Unused code path elimination
 * Block '<S71>/Add' : Unused code path elimination
 * Block '<S71>/Add1' : Unused code path elimination
 * Block '<S71>/Add2' : Unused code path elimination
 * Block '<S71>/Add3' : Unused code path elimination
 * Block '<S71>/Bitwise AND9' : Unused code path elimination
 * Block '<S72>/Add' : Unused code path elimination
 * Block '<S72>/Add1' : Unused code path elimination
 * Block '<S72>/Add2' : Unused code path elimination
 * Block '<S72>/Add3' : Unused code path elimination
 * Block '<S72>/Bitwise AND3' : Unused code path elimination
 * Block '<S72>/Bitwise AND7' : Unused code path elimination
 * Block '<S72>/Bitwise AND8' : Unused code path elimination
 * Block '<S72>/Data Type Conversion10' : Unused code path elimination
 * Block '<S72>/Data Type Conversion11' : Unused code path elimination
 * Block '<S72>/Data Type Conversion12' : Unused code path elimination
 * Block '<S72>/Data Type Conversion4' : Unused code path elimination
 * Block '<S72>/Data Type Conversion8' : Unused code path elimination
 * Block '<S72>/Data Type Conversion9' : Unused code path elimination
 * Block '<S72>/Gain' : Unused code path elimination
 * Block '<S72>/Gain1' : Unused code path elimination
 * Block '<S72>/Gain2' : Unused code path elimination
 * Block '<S72>/Gain3' : Unused code path elimination
 * Block '<S244>/Data Type Conversion1' : Unused code path elimination
 * Block '<S13>/1-D Lookup Table1' : Unused code path elimination
 * Block '<S13>/Data Type Conversion1' : Unused code path elimination
 * Block '<S13>/Data Type Conversion3' : Unused code path elimination
 * Block '<S13>/Data Type Conversion4' : Unused code path elimination
 * Block '<S13>/Data Type Conversion5' : Unused code path elimination
 * Block '<S13>/Saturation2' : Unused code path elimination
 * Block '<S46>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S49>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S52>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S57>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S56>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S56>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S56>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S65>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S151>/Data Type Conversion12' : Eliminate redundant data type conversion
 * Block '<S15>/Data Type Conversion5' : Eliminate redundant data type conversion
 * Block '<S15>/Data Type Conversion6' : Eliminate redundant data type conversion
 * Block '<S15>/Data Type Conversion7' : Eliminate redundant data type conversion
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
 * '<Root>' : 'rzs10thnew2021b'
 * '<S1>'   : 'rzs10thnew2021b/AMI_CAN'
 * '<S2>'   : 'rzs10thnew2021b/ASB_Selfcheck'
 * '<S3>'   : 'rzs10thnew2021b/AS_AMI'
 * '<S4>'   : 'rzs10thnew2021b/AS_Stateflow'
 * '<S5>'   : 'rzs10thnew2021b/Buzzer'
 * '<S6>'   : 'rzs10thnew2021b/EBS'
 * '<S7>'   : 'rzs10thnew2021b/EPS'
 * '<S8>'   : 'rzs10thnew2021b/ESP'
 * '<S9>'   : 'rzs10thnew2021b/IPC'
 * '<S10>'  : 'rzs10thnew2021b/LED_Control'
 * '<S11>'  : 'rzs10thnew2021b/Motor_Control'
 * '<S12>'  : 'rzs10thnew2021b/Res'
 * '<S13>'  : 'rzs10thnew2021b/Sensor_Signal'
 * '<S14>'  : 'rzs10thnew2021b/TS_Activation'
 * '<S15>'  : 'rzs10thnew2021b/analysis'
 * '<S16>'  : 'rzs10thnew2021b/AMI_CAN/AMI_Receivemsg'
 * '<S17>'  : 'rzs10thnew2021b/AMI_CAN/AMI_Transmitmsg'
 * '<S18>'  : 'rzs10thnew2021b/AMI_CAN/AMI_Receivemsg/Bit Shift'
 * '<S19>'  : 'rzs10thnew2021b/AMI_CAN/AMI_Receivemsg/Bit Shift/bit_shift'
 * '<S20>'  : 'rzs10thnew2021b/AMI_CAN/AMI_Transmitmsg/Bit Shift'
 * '<S21>'  : 'rzs10thnew2021b/AMI_CAN/AMI_Transmitmsg/Chart'
 * '<S22>'  : 'rzs10thnew2021b/AMI_CAN/AMI_Transmitmsg/Bit Shift/bit_shift'
 * '<S23>'  : 'rzs10thnew2021b/ASB_Selfcheck/Brake_Sensor_Check'
 * '<S24>'  : 'rzs10thnew2021b/ASB_Selfcheck/Compare To Constant'
 * '<S25>'  : 'rzs10thnew2021b/ASB_Selfcheck/Compare To Constant1'
 * '<S26>'  : 'rzs10thnew2021b/ASB_Selfcheck/EBS_On_Check'
 * '<S27>'  : 'rzs10thnew2021b/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant'
 * '<S28>'  : 'rzs10thnew2021b/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant1'
 * '<S29>'  : 'rzs10thnew2021b/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant2'
 * '<S30>'  : 'rzs10thnew2021b/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant3'
 * '<S31>'  : 'rzs10thnew2021b/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant4'
 * '<S32>'  : 'rzs10thnew2021b/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant5'
 * '<S33>'  : 'rzs10thnew2021b/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant6'
 * '<S34>'  : 'rzs10thnew2021b/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant7'
 * '<S35>'  : 'rzs10thnew2021b/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant8'
 * '<S36>'  : 'rzs10thnew2021b/ASB_Selfcheck/EBS_On_Check/Compare To Constant'
 * '<S37>'  : 'rzs10thnew2021b/AS_AMI/Chart'
 * '<S38>'  : 'rzs10thnew2021b/AS_Stateflow/Car_Spdzero_Check'
 * '<S39>'  : 'rzs10thnew2021b/AS_Stateflow/Chart'
 * '<S40>'  : 'rzs10thnew2021b/AS_Stateflow/Car_Spdzero_Check/Compare To Constant'
 * '<S41>'  : 'rzs10thnew2021b/AS_Stateflow/Car_Spdzero_Check/Compare To Constant1'
 * '<S42>'  : 'rzs10thnew2021b/Buzzer/Chart'
 * '<S43>'  : 'rzs10thnew2021b/EBS/Edge Detector'
 * '<S44>'  : 'rzs10thnew2021b/EBS/Edge Detector1'
 * '<S45>'  : 'rzs10thnew2021b/EBS/Edge Detector2'
 * '<S46>'  : 'rzs10thnew2021b/EBS/Edge Detector/Model'
 * '<S47>'  : 'rzs10thnew2021b/EBS/Edge Detector/Model/NEGATIVE Edge'
 * '<S48>'  : 'rzs10thnew2021b/EBS/Edge Detector/Model/POSITIVE Edge'
 * '<S49>'  : 'rzs10thnew2021b/EBS/Edge Detector1/Model'
 * '<S50>'  : 'rzs10thnew2021b/EBS/Edge Detector1/Model/NEGATIVE Edge'
 * '<S51>'  : 'rzs10thnew2021b/EBS/Edge Detector1/Model/POSITIVE Edge'
 * '<S52>'  : 'rzs10thnew2021b/EBS/Edge Detector2/Model'
 * '<S53>'  : 'rzs10thnew2021b/EBS/Edge Detector2/Model/NEGATIVE Edge'
 * '<S54>'  : 'rzs10thnew2021b/EBS/Edge Detector2/Model/POSITIVE Edge'
 * '<S55>'  : 'rzs10thnew2021b/EPS/EPS_ReceiveMsg'
 * '<S56>'  : 'rzs10thnew2021b/EPS/EPS_TransmitMsg'
 * '<S57>'  : 'rzs10thnew2021b/EPS/EPS_ReceiveMsg/EPS_Send_Msg1'
 * '<S58>'  : 'rzs10thnew2021b/EPS/EPS_ReceiveMsg/EPS_Send_Msg2'
 * '<S59>'  : 'rzs10thnew2021b/EPS/EPS_ReceiveMsg/EPS_Send_Msg2/Bit Shift1'
 * '<S60>'  : 'rzs10thnew2021b/EPS/EPS_ReceiveMsg/EPS_Send_Msg2/Bit Shift1/bit_shift'
 * '<S61>'  : 'rzs10thnew2021b/EPS/EPS_TransmitMsg/Bit Shift'
 * '<S62>'  : 'rzs10thnew2021b/EPS/EPS_TransmitMsg/Compare To Constant2'
 * '<S63>'  : 'rzs10thnew2021b/EPS/EPS_TransmitMsg/Compare To Constant3'
 * '<S64>'  : 'rzs10thnew2021b/EPS/EPS_TransmitMsg/EPS_Stateflow1'
 * '<S65>'  : 'rzs10thnew2021b/EPS/EPS_TransmitMsg/Subsystem2'
 * '<S66>'  : 'rzs10thnew2021b/EPS/EPS_TransmitMsg/Bit Shift/bit_shift'
 * '<S67>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg'
 * '<S68>'  : 'rzs10thnew2021b/ESP/ESP_TransmitMsg'
 * '<S69>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01'
 * '<S70>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_03'
 * '<S71>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06'
 * '<S72>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_07'
 * '<S73>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/Subsystem'
 * '<S74>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift'
 * '<S75>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift1'
 * '<S76>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift10'
 * '<S77>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift11'
 * '<S78>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift12'
 * '<S79>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift13'
 * '<S80>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift14'
 * '<S81>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift15'
 * '<S82>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift16'
 * '<S83>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift2'
 * '<S84>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift3'
 * '<S85>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift4'
 * '<S86>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift5'
 * '<S87>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift6'
 * '<S88>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift7'
 * '<S89>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift8'
 * '<S90>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift9'
 * '<S91>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift/bit_shift'
 * '<S92>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift1/bit_shift'
 * '<S93>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift10/bit_shift'
 * '<S94>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift11/bit_shift'
 * '<S95>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift12/bit_shift'
 * '<S96>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift13/bit_shift'
 * '<S97>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift14/bit_shift'
 * '<S98>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift15/bit_shift'
 * '<S99>'  : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift16/bit_shift'
 * '<S100>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift2/bit_shift'
 * '<S101>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift3/bit_shift'
 * '<S102>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift4/bit_shift'
 * '<S103>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift5/bit_shift'
 * '<S104>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift6/bit_shift'
 * '<S105>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift7/bit_shift'
 * '<S106>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift8/bit_shift'
 * '<S107>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift9/bit_shift'
 * '<S108>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift'
 * '<S109>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift1'
 * '<S110>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift2'
 * '<S111>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift3'
 * '<S112>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift4'
 * '<S113>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift5'
 * '<S114>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift/bit_shift'
 * '<S115>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift1/bit_shift'
 * '<S116>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift2/bit_shift'
 * '<S117>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift3/bit_shift'
 * '<S118>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift4/bit_shift'
 * '<S119>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift5/bit_shift'
 * '<S120>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift'
 * '<S121>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift1'
 * '<S122>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift2'
 * '<S123>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift3'
 * '<S124>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift4'
 * '<S125>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift5'
 * '<S126>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift6'
 * '<S127>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift7'
 * '<S128>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift8'
 * '<S129>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift/bit_shift'
 * '<S130>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift1/bit_shift'
 * '<S131>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift2/bit_shift'
 * '<S132>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift3/bit_shift'
 * '<S133>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift4/bit_shift'
 * '<S134>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift5/bit_shift'
 * '<S135>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift6/bit_shift'
 * '<S136>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift7/bit_shift'
 * '<S137>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift8/bit_shift'
 * '<S138>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift'
 * '<S139>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift1'
 * '<S140>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift2'
 * '<S141>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift3'
 * '<S142>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift4'
 * '<S143>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift5'
 * '<S144>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift/bit_shift'
 * '<S145>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift1/bit_shift'
 * '<S146>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift2/bit_shift'
 * '<S147>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift3/bit_shift'
 * '<S148>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift4/bit_shift'
 * '<S149>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift5/bit_shift'
 * '<S150>' : 'rzs10thnew2021b/ESP/ESP_ReceiveMsg/Subsystem/brkmotor_check_system'
 * '<S151>' : 'rzs10thnew2021b/ESP/ESP_TransmitMsg/ESP_R_00'
 * '<S152>' : 'rzs10thnew2021b/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift'
 * '<S153>' : 'rzs10thnew2021b/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift1'
 * '<S154>' : 'rzs10thnew2021b/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift2'
 * '<S155>' : 'rzs10thnew2021b/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift3'
 * '<S156>' : 'rzs10thnew2021b/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift4'
 * '<S157>' : 'rzs10thnew2021b/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift5'
 * '<S158>' : 'rzs10thnew2021b/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift6'
 * '<S159>' : 'rzs10thnew2021b/ESP/ESP_TransmitMsg/ESP_R_00/ESP_Chart1'
 * '<S160>' : 'rzs10thnew2021b/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift/bit_shift'
 * '<S161>' : 'rzs10thnew2021b/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift1/bit_shift'
 * '<S162>' : 'rzs10thnew2021b/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift2/bit_shift'
 * '<S163>' : 'rzs10thnew2021b/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift3/bit_shift'
 * '<S164>' : 'rzs10thnew2021b/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift4/bit_shift'
 * '<S165>' : 'rzs10thnew2021b/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift5/bit_shift'
 * '<S166>' : 'rzs10thnew2021b/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift6/bit_shift'
 * '<S167>' : 'rzs10thnew2021b/IPC/IPC_ReceiveMsg'
 * '<S168>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg'
 * '<S169>' : 'rzs10thnew2021b/IPC/IPC_ReceiveMsg/IPC_Rx_Msg'
 * '<S170>' : 'rzs10thnew2021b/IPC/IPC_ReceiveMsg/IPC_Rx_Msg/Bit Shift'
 * '<S171>' : 'rzs10thnew2021b/IPC/IPC_ReceiveMsg/IPC_Rx_Msg/Bit Shift/bit_shift'
 * '<S172>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg1'
 * '<S173>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg2'
 * '<S174>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift'
 * '<S175>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift1'
 * '<S176>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift2'
 * '<S177>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift3'
 * '<S178>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift4'
 * '<S179>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift5'
 * '<S180>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift6'
 * '<S181>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift8'
 * '<S182>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift/bit_shift'
 * '<S183>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift1/bit_shift'
 * '<S184>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift2/bit_shift'
 * '<S185>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift3/bit_shift'
 * '<S186>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift4/bit_shift'
 * '<S187>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift5/bit_shift'
 * '<S188>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift6/bit_shift'
 * '<S189>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift8/bit_shift'
 * '<S190>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift'
 * '<S191>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift1'
 * '<S192>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift2'
 * '<S193>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift/bit_shift'
 * '<S194>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift1/bit_shift'
 * '<S195>' : 'rzs10thnew2021b/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift2/bit_shift'
 * '<S196>' : 'rzs10thnew2021b/LED_Control/BMS_LED'
 * '<S197>' : 'rzs10thnew2021b/LED_Control/EBS_LED'
 * '<S198>' : 'rzs10thnew2021b/LED_Control/Subsystem'
 * '<S199>' : 'rzs10thnew2021b/LED_Control/Subsystem1'
 * '<S200>' : 'rzs10thnew2021b/LED_Control/BMS_LED/BMS_LED'
 * '<S201>' : 'rzs10thnew2021b/LED_Control/BMS_LED/IMD_LED'
 * '<S202>' : 'rzs10thnew2021b/LED_Control/EBS_LED/Compare To Constant'
 * '<S203>' : 'rzs10thnew2021b/LED_Control/EBS_LED/Compare To Constant1'
 * '<S204>' : 'rzs10thnew2021b/LED_Control/EBS_LED/Compare To Constant2'
 * '<S205>' : 'rzs10thnew2021b/LED_Control/EBS_LED/Compare To Constant3'
 * '<S206>' : 'rzs10thnew2021b/LED_Control/EBS_LED/Compare To Constant4'
 * '<S207>' : 'rzs10thnew2021b/LED_Control/EBS_LED/Compare To Constant5'
 * '<S208>' : 'rzs10thnew2021b/LED_Control/EBS_LED/Compare To Constant6'
 * '<S209>' : 'rzs10thnew2021b/LED_Control/EBS_LED/Enabled Subsystem'
 * '<S210>' : 'rzs10thnew2021b/LED_Control/EBS_LED/Shutdown_Button'
 * '<S211>' : 'rzs10thnew2021b/LED_Control/EBS_LED/display'
 * '<S212>' : 'rzs10thnew2021b/LED_Control/Subsystem/blue'
 * '<S213>' : 'rzs10thnew2021b/LED_Control/Subsystem1/yellow'
 * '<S214>' : 'rzs10thnew2021b/Motor_Control/AS_Torque_Calculation'
 * '<S215>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command'
 * '<S216>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command3'
 * '<S217>' : 'rzs10thnew2021b/Motor_Control/Manual_Torque_Calculation'
 * '<S218>' : 'rzs10thnew2021b/Motor_Control/Motor_Torque_Stateflow'
 * '<S219>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift'
 * '<S220>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift1'
 * '<S221>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift2'
 * '<S222>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift3'
 * '<S223>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift4'
 * '<S224>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift5'
 * '<S225>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift6'
 * '<S226>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift7'
 * '<S227>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift8'
 * '<S228>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift9'
 * '<S229>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift/bit_shift'
 * '<S230>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift1/bit_shift'
 * '<S231>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift2/bit_shift'
 * '<S232>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift3/bit_shift'
 * '<S233>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift4/bit_shift'
 * '<S234>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift5/bit_shift'
 * '<S235>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift6/bit_shift'
 * '<S236>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift7/bit_shift'
 * '<S237>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift8/bit_shift'
 * '<S238>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command/Bit Shift9/bit_shift'
 * '<S239>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command3/Bit Shift'
 * '<S240>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command3/Bit Shift1'
 * '<S241>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command3/Bit Shift/bit_shift'
 * '<S242>' : 'rzs10thnew2021b/Motor_Control/MCU1_Rx_Command3/Bit Shift1/bit_shift'
 * '<S243>' : 'rzs10thnew2021b/Motor_Control/Manual_Torque_Calculation/Pedal_Fault_Check'
 * '<S244>' : 'rzs10thnew2021b/Res/Res_Msg'
 * '<S245>' : 'rzs10thnew2021b/Res/Res_Msg/Bit Shift'
 * '<S246>' : 'rzs10thnew2021b/Res/Res_Msg/Bit Shift1'
 * '<S247>' : 'rzs10thnew2021b/Res/Res_Msg/Bit Shift2'
 * '<S248>' : 'rzs10thnew2021b/Res/Res_Msg/Subsystem'
 * '<S249>' : 'rzs10thnew2021b/Res/Res_Msg/Bit Shift/bit_shift'
 * '<S250>' : 'rzs10thnew2021b/Res/Res_Msg/Bit Shift1/bit_shift'
 * '<S251>' : 'rzs10thnew2021b/Res/Res_Msg/Bit Shift2/bit_shift'
 * '<S252>' : 'rzs10thnew2021b/Res/Res_Msg/Subsystem/heaartbeat_chart'
 * '<S253>' : 'rzs10thnew2021b/Res/Res_Msg/Subsystem/xor_Check'
 * '<S254>' : 'rzs10thnew2021b/Sensor_Signal/Subsystem'
 * '<S255>' : 'rzs10thnew2021b/TS_Activation/Chart'
 * '<S256>' : 'rzs10thnew2021b/TS_Activation/Chart1'
 * '<S257>' : 'rzs10thnew2021b/TS_Activation/Chart2'
 * '<S258>' : 'rzs10thnew2021b/analysis/Bit Shift1'
 * '<S259>' : 'rzs10thnew2021b/analysis/Bit Shift10'
 * '<S260>' : 'rzs10thnew2021b/analysis/Bit Shift11'
 * '<S261>' : 'rzs10thnew2021b/analysis/Bit Shift12'
 * '<S262>' : 'rzs10thnew2021b/analysis/Bit Shift13'
 * '<S263>' : 'rzs10thnew2021b/analysis/Bit Shift14'
 * '<S264>' : 'rzs10thnew2021b/analysis/Bit Shift15'
 * '<S265>' : 'rzs10thnew2021b/analysis/Bit Shift16'
 * '<S266>' : 'rzs10thnew2021b/analysis/Bit Shift17'
 * '<S267>' : 'rzs10thnew2021b/analysis/Bit Shift18'
 * '<S268>' : 'rzs10thnew2021b/analysis/Bit Shift19'
 * '<S269>' : 'rzs10thnew2021b/analysis/Bit Shift2'
 * '<S270>' : 'rzs10thnew2021b/analysis/Bit Shift3'
 * '<S271>' : 'rzs10thnew2021b/analysis/Bit Shift4'
 * '<S272>' : 'rzs10thnew2021b/analysis/Bit Shift5'
 * '<S273>' : 'rzs10thnew2021b/analysis/Bit Shift6'
 * '<S274>' : 'rzs10thnew2021b/analysis/Bit Shift7'
 * '<S275>' : 'rzs10thnew2021b/analysis/Bit Shift9'
 * '<S276>' : 'rzs10thnew2021b/analysis/Bit Shift1/bit_shift'
 * '<S277>' : 'rzs10thnew2021b/analysis/Bit Shift10/bit_shift'
 * '<S278>' : 'rzs10thnew2021b/analysis/Bit Shift11/bit_shift'
 * '<S279>' : 'rzs10thnew2021b/analysis/Bit Shift12/bit_shift'
 * '<S280>' : 'rzs10thnew2021b/analysis/Bit Shift13/bit_shift'
 * '<S281>' : 'rzs10thnew2021b/analysis/Bit Shift14/bit_shift'
 * '<S282>' : 'rzs10thnew2021b/analysis/Bit Shift15/bit_shift'
 * '<S283>' : 'rzs10thnew2021b/analysis/Bit Shift16/bit_shift'
 * '<S284>' : 'rzs10thnew2021b/analysis/Bit Shift17/bit_shift'
 * '<S285>' : 'rzs10thnew2021b/analysis/Bit Shift18/bit_shift'
 * '<S286>' : 'rzs10thnew2021b/analysis/Bit Shift19/bit_shift'
 * '<S287>' : 'rzs10thnew2021b/analysis/Bit Shift2/bit_shift'
 * '<S288>' : 'rzs10thnew2021b/analysis/Bit Shift3/bit_shift'
 * '<S289>' : 'rzs10thnew2021b/analysis/Bit Shift4/bit_shift'
 * '<S290>' : 'rzs10thnew2021b/analysis/Bit Shift5/bit_shift'
 * '<S291>' : 'rzs10thnew2021b/analysis/Bit Shift6/bit_shift'
 * '<S292>' : 'rzs10thnew2021b/analysis/Bit Shift7/bit_shift'
 * '<S293>' : 'rzs10thnew2021b/analysis/Bit Shift9/bit_shift'
 */
#endif                                 /* RTW_HEADER_rzs10thnew2021b_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
