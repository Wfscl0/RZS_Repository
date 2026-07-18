/*
 * File: VCU10.h
 *
 * Code generated for Simulink model 'VCU10'.
 *
 * Model version                  : 1.20
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Thu Jul 16 15:49:44 2026
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
                                                                  * '<S10>/TSLED_Inspection'
                                                                  * '<S15>/Chart'
                                                                  * '<S15>/Chart1'
                                                                  * '<S15>/Chart2'
                                                                  * '<S221>/Shutdown_Button'
                                                                  * '<S221>/display'
                                                                  * '<S68>/brkmotor_check_system'
                                                                  */
#define T                              true                      /* Referenced by:
                                                                  * '<S3>/Chart'
                                                                  * '<S4>/Chart'
                                                                  * '<S10>/TSLED_Inspection'
                                                                  * '<S15>/Chart'
                                                                  * '<S15>/Chart1'
                                                                  * '<S15>/Chart2'
                                                                  * '<S221>/Shutdown_Button'
                                                                  * '<S221>/display'
                                                                  * '<S68>/brkmotor_check_system'
                                                                  */

/* Block signals (default storage) */
typedef struct {
  real_T oilprs_flsensor;              /* '<S65>/Gain' */
  real_T oilprs_rrsensor;              /* '<S65>/Gain1' */
  real_T oilprs_frsensor;              /* '<S65>/Gain2' */
  real_T oilprs_rlsensor;              /* '<S65>/Gain3' */
  real_T tarPrsReqFL;                  /* '<S146>/ESP_Chart1' */
  real_T tarPrsReqFR;                  /* '<S146>/ESP_Chart1' */
  real_T tarPrsReqRL;                  /* '<S146>/ESP_Chart1' */
  real_T tarPrsReqRR;                  /* '<S146>/ESP_Chart1' */
  real_T steering_flag;                /* '<S3>/Data Store Read1' */
  real_T manual_driving_flag;          /* '<S3>/Data Store Read3' */
  real_T as_emergency_flag;            /* '<S3>/Data Store Read4' */
  real_T as_ebs_trig;                  /* '<S3>/Chart' */
  real_T as_led_blue;                  /* '<S3>/Chart' */
  real_T as_led_yellow;                /* '<S3>/Chart' */
  real_T steering_flag_o;              /* '<S3>/Chart' */
  real_T brake_flag_i;                 /* '<S3>/Chart' */
  real_T manual_driving_flag_k;        /* '<S3>/Chart' */
  real_T as_emergency_flag_e;          /* '<S3>/Chart' */
  real_T as_off_flag_p;                /* '<S3>/Chart' */
  real_T as_ready_flag_c;              /* '<S3>/Chart' */
  real_T as_driving_flag_a;            /* '<S3>/Chart' */
  real_T as_finished_flag_c;           /* '<S3>/Chart' */
  real_T r2d_flag_c;                   /* '<S3>/Chart' */
  real_T motor_torque;                 /* '<S11>/Motor_Torque_Stateflow' */
  real_T pedal_error;                  /* '<S240>/Pedal_Fault_Check' */
  real_T ipc_motor_torque;             /* '<S169>/Add4' */
  real_T Add;                          /* '<S170>/Add' */
  real_T xorcheck;                     /* '<S273>/xor_Check' */
  real_T res_hbcheck;                  /* '<S273>/heaartbeat_chart' */
  real_T ts;                           /* '<S15>/Chart2' */
  real_T airprs_sensor1;               /* '<S14>/Data Type Conversion12' */
  real_T airprs_sensor2;               /* '<S14>/Data Type Conversion15' */
  real_T apps1_01;                     /* '<S14>/Saturation' */
  real_T apps2_01;                     /* '<S14>/Saturation1' */
  uint32_T eps_cmdangle;               /* '<S51>/EPS_Stateflow1' */
  uint8_T eps_cmdworkmode;             /* '<S51>/EPS_Stateflow1' */
  uint8_T eps_cmdmiddle;               /* '<S51>/EPS_Stateflow1' */
  uint8_T eps_cmdvelocity;             /* '<S51>/EPS_Stateflow1' */
  uint8_T ami_process;                 /* '<S17>/Chart' */
  uint8_T canb_ipctsmsg2_j[8];         /* '<S8>/canb_ipctsmsg2' */
  boolean_T brkmotor_check;            /* '<S68>/brkmotor_check_system' */
  boolean_T LogicalOperator2;          /* '<S5>/Logical Operator2' */
  boolean_T RelationalOperator1;       /* '<S49>/Relational Operator1' */
  boolean_T RelationalOperator1_n;     /* '<S48>/Relational Operator1' */
  boolean_T RelationalOperator1_no;    /* '<S46>/Relational Operator1' */
  boolean_T RelationalOperator1_k;     /* '<S45>/Relational Operator1' */
  boolean_T r2d_warning;               /* '<S3>/Chart' */
  boolean_T steer_return;              /* '<S3>/Chart' */
  boolean_T LogicalOperator1_n;        /* '<S25>/Logical Operator1' */
  boolean_T shutdown_flag;             /* '<S221>/Shutdown_Button' */
  boolean_T In1;                       /* '<S232>/In1' */
  boolean_T res_stop;                  /* '<S269>/Data Type Conversion7' */
  boolean_T res_communication;         /* '<S269>/Data Type Conversion2' */
  boolean_T ts_warning;                /* '<S15>/Chart2' */
} B_VCU10_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T oilprs_frsensordata;          /* '<Root>/Data Store Memory24' */
  real_T ts;                           /* '<Root>/Data Store Memory11' */
  real_T ipc_astask;                   /* '<Root>/Data Store Memory22' */
  real_T lscnt;                        /* '<S68>/brkmotor_check_system' */
  real_T fault_count;                  /* '<S240>/Pedal_Fault_Check' */
  real_T shutdown_count;               /* '<S221>/Shutdown_Button' */
  real_T err_cnt;                      /* '<S273>/xor_Check' */
  real_T hbcnt;                        /* '<S273>/heaartbeat_chart' */
  real_T run_check_flag;               /* '<S15>/Chart1' */
  real_T run_offcheck_flag;            /* '<S15>/Chart1' */
  real_T run_flag;                     /* '<S15>/Chart1' */
  real_T di8_offcheck_flag;            /* '<S15>/Chart' */
  real_T di8_check_flag;               /* '<S15>/Chart' */
  int32_T clockTickCounter;            /* '<S222>/Pulse Generator' */
  int32_T clockTickCounter_a;          /* '<S223>/Pulse Generator' */
  int32_T clockTickCounter_a2;         /* '<S4>/Pulse Generator' */
  uint32_T previousTicks;              /* '<S51>/EPS_Stateflow1' */
  uint32_T previousTicks_g;            /* '<S3>/Chart' */
  uint32_T previousTicks_o;            /* '<S10>/TSLED_Inspection' */
  uint32_T previousTicks_a;            /* '<S223>/yellow' */
  uint32_T previousTicks_av;           /* '<S222>/blue' */
  uint32_T previousTicks_ag;           /* '<S221>/display' */
  uint32_T previousTicks_f;            /* '<S221>/Shutdown_Button' */
  uint32_T previousTicks_c;            /* '<S4>/Chart' */
  uint32_T previousTicks_gm;           /* '<S15>/Chart2' */
  uint16_T temporalCounter_i1;         /* '<S3>/Chart' */
  uint16_T temporalCounter_i1_m;       /* '<S4>/Chart' */
  boolean_T UnitDelay_DSTATE;          /* '<S44>/Unit Delay' */
  boolean_T UnitDelay_DSTATE_e;        /* '<S47>/Unit Delay' */
  uint8_T is_active_c15_VCU10;         /* '<S51>/EPS_Stateflow1' */
  uint8_T is_c15_VCU10;                /* '<S51>/EPS_Stateflow1' */
  uint8_T temporalCounter_i1_g;        /* '<S51>/EPS_Stateflow1' */
  uint8_T is_active_c16_VCU10;         /* '<S146>/ESP_Chart1' */
  uint8_T is_c16_VCU10;                /* '<S146>/ESP_Chart1' */
  uint8_T is_active_c18_VCU10;         /* '<S68>/brkmotor_check_system' */
  uint8_T is_c18_VCU10;                /* '<S68>/brkmotor_check_system' */
  uint8_T lifesig_start;               /* '<S68>/brkmotor_check_system' */
  uint8_T is_active_c1_VCU10;          /* '<S3>/Chart' */
  uint8_T is_c1_VCU10;                 /* '<S3>/Chart' */
  uint8_T is_AS_Driving;               /* '<S3>/Chart' */
  uint8_T is_active_c4_VCU10;          /* '<S11>/Motor_Torque_Stateflow' */
  uint8_T is_c4_VCU10;                 /* '<S11>/Motor_Torque_Stateflow' */
  uint8_T is_active_c2_VCU10;          /* '<S10>/TSLED_Inspection' */
  uint8_T is_c2_VCU10;                 /* '<S10>/TSLED_Inspection' */
  uint8_T temporalCounter_i1_o;        /* '<S10>/TSLED_Inspection' */
  uint8_T is_active_c14_VCU10;         /* '<S223>/yellow' */
  uint8_T is_c14_VCU10;                /* '<S223>/yellow' */
  uint8_T temporalCounter_i1_j;        /* '<S223>/yellow' */
  uint8_T is_active_c13_VCU10;         /* '<S222>/blue' */
  uint8_T is_c13_VCU10;                /* '<S222>/blue' */
  uint8_T temporalCounter_i1_c;        /* '<S222>/blue' */
  uint8_T is_active_c6_VCU10;          /* '<S221>/display' */
  uint8_T is_c6_VCU10;                 /* '<S221>/display' */
  uint8_T temporalCounter_i1_gw;       /* '<S221>/display' */
  uint8_T is_active_c17_VCU10;         /* '<S221>/Shutdown_Button' */
  uint8_T is_c17_VCU10;                /* '<S221>/Shutdown_Button' */
  uint8_T temporalCounter_i1_ct;       /* '<S221>/Shutdown_Button' */
  uint8_T is_active_c20_VCU10;         /* '<S17>/Chart' */
  uint8_T is_c20_VCU10;                /* '<S17>/Chart' */
  uint8_T is_active_c11_VCU10;         /* '<S4>/Chart' */
  uint8_T is_c11_VCU10;                /* '<S4>/Chart' */
  uint8_T is_active_c19_VCU10;         /* '<S273>/xor_Check' */
  uint8_T is_c19_VCU10;                /* '<S273>/xor_Check' */
  uint8_T is_active_c10_VCU10;         /* '<S273>/heaartbeat_chart' */
  uint8_T is_c10_VCU10;                /* '<S273>/heaartbeat_chart' */
  uint8_T res_heartbeat_start;         /* '<S273>/heaartbeat_chart' */
  uint8_T is_active_c9_VCU10;          /* '<S15>/Chart2' */
  uint8_T is_c9_VCU10;                 /* '<S15>/Chart2' */
  uint8_T temporalCounter_i1_p;        /* '<S15>/Chart2' */
  uint8_T is_active_c8_VCU10;          /* '<S15>/Chart1' */
  uint8_T is_c8_VCU10;                 /* '<S15>/Chart1' */
  uint8_T is_Ignition_Check;           /* '<S15>/Chart1' */
  uint8_T is_Flameout_Check;           /* '<S15>/Chart1' */
  uint8_T is_active_c3_VCU10;          /* '<S15>/Chart' */
  uint8_T is_c3_VCU10;                 /* '<S15>/Chart' */
  uint8_T is_Ignition_Check_f;         /* '<S15>/Chart' */
  uint8_T is_Flameout_Check_i;         /* '<S15>/Chart' */
  boolean_T brkmotor_check;            /* '<Root>/Data Store Memory' */
  boolean_T asb_check;                 /* '<Root>/Data Store Memory1' */
  boolean_T r2d_warning;               /* '<Root>/Data Store Memory12' */
  boolean_T steer_return;              /* '<Root>/Data Store Memory14' */
  boolean_T ebs_working;               /* '<Root>/Data Store Memory2' */
  boolean_T ebs_warning;               /* '<Root>/Data Store Memory20' */
  boolean_T task_finish;               /* '<Root>/Data Store Memory21' */
  boolean_T inspection_flag;           /* '<Root>/Data Store Memory25' */
  boolean_T astask_flag;               /* '<Root>/Data Store Memory26' */
  boolean_T as_flag;                   /* '<Root>/Data Store Memory27' */
  boolean_T brake_on;                  /* '<Root>/Data Store Memory3' */
  boolean_T ebs_check;                 /* '<Root>/Data Store Memory4' */
  boolean_T steer_zero;                /* '<Root>/Data Store Memory9' */
  boolean_T di8_flag;                  /* '<S15>/Chart' */
} DW_VCU10_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T MultiportSwitch[2];     /* '<S44>/Multiport Switch' */
  const real_T MultiportSwitch_e[2];   /* '<S47>/Multiport Switch' */
  const real_T Gain;                   /* '<S238>/Gain' */
  const real_T Gain1;                  /* '<S238>/Gain1' */
  const real_T Product;                /* '<S279>/Product' */
  const uint16_T DataTypeConversion8;  /* '<S238>/Data Type Conversion8' */
  const uint16_T Add2;                 /* '<S238>/Add2' */
  const uint16_T DataTypeConversion9;  /* '<S238>/Data Type Conversion9' */
  const uint16_T BitwiseAND7;          /* '<S238>/Bitwise AND7' */
  const uint16_T DataTypeConversion10; /* '<S238>/Data Type Conversion10' */
  const uint16_T BitwiseAND8;          /* '<S238>/Bitwise AND8' */
  const uint16_T BitwiseAND9;          /* '<S238>/Bitwise AND9' */
  const uint16_T BitwiseAND13;         /* '<S238>/Bitwise AND13' */
  const uint16_T BitwiseAND12;         /* '<S238>/Bitwise AND12' */
  const uint16_T BitwiseAND6;          /* '<S238>/Bitwise AND6' */
  const uint16_T DataTypeConversion5;  /* '<S239>/Data Type Conversion5' */
  const uint16_T BitwiseAND1;          /* '<S239>/Bitwise AND1' */
  const uint16_T DataTypeConversion1;  /* '<S239>/Data Type Conversion1' */
  const uint16_T BitwiseAND3;          /* '<S239>/Bitwise AND3' */
  const uint16_T BitwiseAND;           /* '<S239>/Bitwise AND' */
  const uint16_T BitwiseAND2;          /* '<S239>/Bitwise AND2' */
  const uint8_T BitwiseAND8_o;         /* '<S146>/Bitwise AND8' */
  const uint8_T DataTypeConversion1_c; /* '<S238>/Data Type Conversion1' */
  const uint8_T BitwiseAND1_a;         /* '<S238>/Bitwise AND1' */
  const uint8_T DataTypeConversion3;   /* '<S238>/Data Type Conversion3' */
  const uint8_T BitwiseAND2_o;         /* '<S238>/Bitwise AND2' */
  const uint8_T DataTypeConversion4;   /* '<S238>/Data Type Conversion4' */
  const uint8_T BitwiseAND3_o;         /* '<S238>/Bitwise AND3' */
  const uint8_T DataTypeConversion5_d; /* '<S238>/Data Type Conversion5' */
  const uint8_T BitwiseAND4;           /* '<S238>/Bitwise AND4' */
  const uint8_T DataTypeConversion6;   /* '<S238>/Data Type Conversion6' */
  const uint8_T BitwiseAND5;           /* '<S238>/Bitwise AND5' */
  const uint8_T MCU1_Rx_Commandbyte1;  /* '<S238>/Data Type Conversion11' */
  const uint8_T MCU1_Rx_Commandbyte6;  /* '<S238>/Data Type Conversion16' */
  const uint8_T MCU1_Rx_Command3byte0; /* '<S239>/Data Type Conversion2' */
  const uint8_T MCU1_Rx_Command3byte2; /* '<S239>/Data Type Conversion4' */
} ConstB_VCU10_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: [0 1])
   * Referenced by:
   *   '<S14>/1-D Lookup Table'
   *   '<S14>/1-D Lookup Table6'
   *   '<S14>/1-D Lookup Table7'
   *   '<S14>/1-D Lookup Table9'
   */
  uint16_T pooled37[2];

  /* Pooled Parameter (Expression: [252 2000])
   * Referenced by:
   *   '<S14>/1-D Lookup Table'
   *   '<S14>/1-D Lookup Table6'
   *   '<S14>/1-D Lookup Table7'
   *   '<S14>/1-D Lookup Table9'
   */
  uint16_T pooled38[2];
} ConstP_VCU10_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint8_T model_lox;                   /* '<Root>/model_lox' */
  uint8_T model_hox;                   /* '<Root>/model_hox' */
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
    uint32_T clockTick1;
    struct {
      uint16_T TID[3];
    } TaskCounters;
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
extern uint16_T airprs2;               /* '<S9>/Data Type Conversion' */
extern uint16_T airprs1;               /* '<S9>/Data Type Conversion1' */
extern uint16_T brkps;                 /* '<S9>/Data Type Conversion2' */
extern uint16_T apps2;                 /* '<S9>/Data Type Conversion3' */
extern uint16_T apps1;                 /* '<S9>/Data Type Conversion4' */
extern uint8_T canb_epsmsg[8];         /* '<S6>/EPS_TransmitMsg' */
extern uint8_T ESP_R_00[8];            /* '<S146>/Signal Conversion' */
extern uint8_T cana_motor_cmd[8];      /* '<S238>/Signal Conversion' */
extern uint8_T AMI_Rx[8];              /* '<S17>/Signal Conversion' */
extern uint8_T canb_ipcrxmsg[8];       /* '<S8>/IPC_ReceiveMsg' */
extern boolean_T ebs_driver_check;     /* '<S201>/Data Type Conversion' */
extern boolean_T shutdown_s;           /* '<S201>/Data Type Conversion1' */
extern boolean_T shutdown_e;           /* '<S201>/Data Type Conversion2' */
extern boolean_T di8_cockpit;          /* '<S201>/Data Type Conversion3' */
extern boolean_T di8_side;             /* '<S201>/Data Type Conversion4' */
extern boolean_T run_button;           /* '<S201>/Data Type Conversion5' */
extern boolean_T tsms;                 /* '<S201>/Data Type Conversion6' */
extern boolean_T asms;                 /* '<S201>/Data Type Conversion7' */
extern boolean_T ebs_trig;             /* '<S5>/Logical Operator' */
extern boolean_T ebs_watchdog;
     /* '<S5>/BufferToMakeInportVirtual_InsertedFor_ebs_watchdog_at_inport_0' */
extern boolean_T led_brake;            /* '<S10>/brake_on' */
extern boolean_T led_ebs_error;        /* '<S221>/Logical Operator' */
extern boolean_T led_assi_blue;        /* '<S222>/Data Type Conversion' */
extern boolean_T led_assi_yellow;      /* '<S223>/Data Type Conversion' */
extern boolean_T led_imd_error;        /* '<S10>/TSLED_Inspection' */
extern boolean_T led_bms_error;        /* '<S10>/TSLED_Inspection' */
extern boolean_T r2d_buzzer;           /* '<S4>/Switch1' */
extern boolean_T ebs_buzzer;           /* '<S4>/Switch' */
extern boolean_T res_error;            /*  */
extern boolean_T run;                  /* '<S15>/Chart1' */
extern boolean_T di8;                  /* '<S15>/Chart' */

/* Model entry point functions */
extern void VCU10_initialize(void);
extern void VCU10_step(void);
extern void VCU10_terminate(void);

/* Exported data declaration */

/* Declaration for custom storage class: ExportToFile */
extern uint8_T cana_motor_cmd3[8];     /* '<S11>/MCU1_Rx_Command3' */

/* Real-time Model object */
extern RT_MODEL_VCU10_T *const VCU10_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S52>/Add1' : Unused code path elimination
 * Block '<S52>/Constant' : Unused code path elimination
 * Block '<S52>/Data Type Conversion9' : Unused code path elimination
 * Block '<S53>/Add1' : Unused code path elimination
 * Block '<S53>/Add2' : Unused code path elimination
 * Block '<S53>/Add5' : Unused code path elimination
 * Block '<S53>/Constant1' : Unused code path elimination
 * Block '<S53>/Constant2' : Unused code path elimination
 * Block '<S53>/Data Type Conversion1' : Unused code path elimination
 * Block '<S53>/Data Type Conversion10' : Unused code path elimination
 * Block '<S53>/Data Type Conversion2' : Unused code path elimination
 * Block '<S53>/Data Type Conversion4' : Unused code path elimination
 * Block '<S53>/Data Type Conversion5' : Unused code path elimination
 * Block '<S53>/Data Type Conversion6' : Unused code path elimination
 * Block '<S53>/Data Type Conversion8' : Unused code path elimination
 * Block '<S53>/Gain1' : Unused code path elimination
 * Block '<S53>/Gain2' : Unused code path elimination
 * Block '<S64>/Add' : Unused code path elimination
 * Block '<S64>/Add1' : Unused code path elimination
 * Block '<S64>/Add2' : Unused code path elimination
 * Block '<S64>/Add3' : Unused code path elimination
 * Block '<S64>/Bitwise AND' : Unused code path elimination
 * Block '<S64>/Bitwise AND19' : Unused code path elimination
 * Block '<S64>/Bitwise AND8' : Unused code path elimination
 * Block '<S64>/Data Type Conversion1' : Unused code path elimination
 * Block '<S64>/Data Type Conversion10' : Unused code path elimination
 * Block '<S64>/Data Type Conversion2' : Unused code path elimination
 * Block '<S64>/Data Type Conversion3' : Unused code path elimination
 * Block '<S64>/Data Type Conversion4' : Unused code path elimination
 * Block '<S64>/Data Type Conversion5' : Unused code path elimination
 * Block '<S64>/Data Type Conversion6' : Unused code path elimination
 * Block '<S64>/Data Type Conversion7' : Unused code path elimination
 * Block '<S64>/Data Type Conversion8' : Unused code path elimination
 * Block '<S64>/Data Type Conversion9' : Unused code path elimination
 * Block '<S64>/Gain' : Unused code path elimination
 * Block '<S66>/Add' : Unused code path elimination
 * Block '<S66>/Add1' : Unused code path elimination
 * Block '<S66>/Add2' : Unused code path elimination
 * Block '<S66>/Add3' : Unused code path elimination
 * Block '<S66>/Bitwise AND9' : Unused code path elimination
 * Block '<S67>/Add' : Unused code path elimination
 * Block '<S67>/Add1' : Unused code path elimination
 * Block '<S67>/Add2' : Unused code path elimination
 * Block '<S67>/Add3' : Unused code path elimination
 * Block '<S67>/Bitwise AND3' : Unused code path elimination
 * Block '<S67>/Bitwise AND7' : Unused code path elimination
 * Block '<S67>/Bitwise AND8' : Unused code path elimination
 * Block '<S67>/Data Type Conversion10' : Unused code path elimination
 * Block '<S67>/Data Type Conversion11' : Unused code path elimination
 * Block '<S67>/Data Type Conversion12' : Unused code path elimination
 * Block '<S67>/Data Type Conversion4' : Unused code path elimination
 * Block '<S67>/Data Type Conversion8' : Unused code path elimination
 * Block '<S67>/Data Type Conversion9' : Unused code path elimination
 * Block '<S67>/Gain' : Unused code path elimination
 * Block '<S67>/Gain1' : Unused code path elimination
 * Block '<S67>/Gain2' : Unused code path elimination
 * Block '<S67>/Gain3' : Unused code path elimination
 * Block '<S170>/Add1' : Unused code path elimination
 * Block '<S170>/Add2' : Unused code path elimination
 * Block '<S170>/Data Type Conversion5' : Unused code path elimination
 * Block '<S170>/Data Type Conversion7' : Unused code path elimination
 * Block '<S170>/Data Type Conversion9' : Unused code path elimination
 * Block '<S269>/Data Type Conversion1' : Unused code path elimination
 * Block '<S14>/1-D Lookup Table1' : Unused code path elimination
 * Block '<S14>/Data Type Conversion1' : Unused code path elimination
 * Block '<S14>/Data Type Conversion3' : Unused code path elimination
 * Block '<S14>/Data Type Conversion4' : Unused code path elimination
 * Block '<S14>/Data Type Conversion5' : Unused code path elimination
 * Block '<S14>/Saturation2' : Unused code path elimination
 * Block '<S44>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S47>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S52>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S51>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S51>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S51>/Data Type Conversion9' : Eliminate redundant data type conversion
 * Block '<S60>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<S146>/Data Type Conversion12' : Eliminate redundant data type conversion
 * Block '<S146>/Data Type Conversion13' : Eliminate redundant data type conversion
 * Block '<S146>/Data Type Conversion14' : Eliminate redundant data type conversion
 * Block '<S237>/Data Type Conversion' : Eliminate redundant data type conversion
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
 * '<S5>'   : 'VCU10/EBS'
 * '<S6>'   : 'VCU10/EPS'
 * '<S7>'   : 'VCU10/ESP'
 * '<S8>'   : 'VCU10/IPC'
 * '<S9>'   : 'VCU10/Input_Convert'
 * '<S10>'  : 'VCU10/LED_Control'
 * '<S11>'  : 'VCU10/Motor_Control'
 * '<S12>'  : 'VCU10/Output_Convert'
 * '<S13>'  : 'VCU10/Res'
 * '<S14>'  : 'VCU10/Sensor_Signal'
 * '<S15>'  : 'VCU10/TS_Activation'
 * '<S16>'  : 'VCU10/AMI_CAN/AMI_Receivemsg'
 * '<S17>'  : 'VCU10/AMI_CAN/AMI_Transmitmsg'
 * '<S18>'  : 'VCU10/AMI_CAN/Compare To Constant'
 * '<S19>'  : 'VCU10/AMI_CAN/Compare To Constant1'
 * '<S20>'  : 'VCU10/AMI_CAN/AMI_Receivemsg/Bit Shift'
 * '<S21>'  : 'VCU10/AMI_CAN/AMI_Receivemsg/Bit Shift/bit_shift'
 * '<S22>'  : 'VCU10/AMI_CAN/AMI_Transmitmsg/Bit Shift'
 * '<S23>'  : 'VCU10/AMI_CAN/AMI_Transmitmsg/Chart'
 * '<S24>'  : 'VCU10/AMI_CAN/AMI_Transmitmsg/Bit Shift/bit_shift'
 * '<S25>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check'
 * '<S26>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant'
 * '<S27>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant1'
 * '<S28>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant2'
 * '<S29>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant3'
 * '<S30>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant4'
 * '<S31>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant5'
 * '<S32>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant6'
 * '<S33>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant7'
 * '<S34>'  : 'VCU10/ASB_Selfcheck/Brake_Sensor_Check/Compare To Constant8'
 * '<S35>'  : 'VCU10/AS_Stateflow/Car_Spdzero_Check'
 * '<S36>'  : 'VCU10/AS_Stateflow/Chart'
 * '<S37>'  : 'VCU10/AS_Stateflow/Car_Spdzero_Check/Compare To Constant'
 * '<S38>'  : 'VCU10/AS_Stateflow/Car_Spdzero_Check/Compare To Constant1'
 * '<S39>'  : 'VCU10/Buzzer/Chart'
 * '<S40>'  : 'VCU10/EBS/Compare To Constant'
 * '<S41>'  : 'VCU10/EBS/Compare To Constant1'
 * '<S42>'  : 'VCU10/EBS/Edge Detector'
 * '<S43>'  : 'VCU10/EBS/Edge Detector2'
 * '<S44>'  : 'VCU10/EBS/Edge Detector/Model'
 * '<S45>'  : 'VCU10/EBS/Edge Detector/Model/NEGATIVE Edge'
 * '<S46>'  : 'VCU10/EBS/Edge Detector/Model/POSITIVE Edge'
 * '<S47>'  : 'VCU10/EBS/Edge Detector2/Model'
 * '<S48>'  : 'VCU10/EBS/Edge Detector2/Model/NEGATIVE Edge'
 * '<S49>'  : 'VCU10/EBS/Edge Detector2/Model/POSITIVE Edge'
 * '<S50>'  : 'VCU10/EPS/EPS_ReceiveMsg'
 * '<S51>'  : 'VCU10/EPS/EPS_TransmitMsg'
 * '<S52>'  : 'VCU10/EPS/EPS_ReceiveMsg/EPS_Send_Msg1'
 * '<S53>'  : 'VCU10/EPS/EPS_ReceiveMsg/EPS_Send_Msg2'
 * '<S54>'  : 'VCU10/EPS/EPS_ReceiveMsg/EPS_Send_Msg2/Bit Shift1'
 * '<S55>'  : 'VCU10/EPS/EPS_ReceiveMsg/EPS_Send_Msg2/Bit Shift1/bit_shift'
 * '<S56>'  : 'VCU10/EPS/EPS_TransmitMsg/Bit Shift'
 * '<S57>'  : 'VCU10/EPS/EPS_TransmitMsg/Compare To Constant2'
 * '<S58>'  : 'VCU10/EPS/EPS_TransmitMsg/Compare To Constant3'
 * '<S59>'  : 'VCU10/EPS/EPS_TransmitMsg/EPS_Stateflow1'
 * '<S60>'  : 'VCU10/EPS/EPS_TransmitMsg/Subsystem2'
 * '<S61>'  : 'VCU10/EPS/EPS_TransmitMsg/Bit Shift/bit_shift'
 * '<S62>'  : 'VCU10/ESP/ESP_ReceiveMsg'
 * '<S63>'  : 'VCU10/ESP/ESP_TransmitMsg'
 * '<S64>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01'
 * '<S65>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03'
 * '<S66>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06'
 * '<S67>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07'
 * '<S68>'  : 'VCU10/ESP/ESP_ReceiveMsg/Subsystem'
 * '<S69>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift'
 * '<S70>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift1'
 * '<S71>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift10'
 * '<S72>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift11'
 * '<S73>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift12'
 * '<S74>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift13'
 * '<S75>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift14'
 * '<S76>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift15'
 * '<S77>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift16'
 * '<S78>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift2'
 * '<S79>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift3'
 * '<S80>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift4'
 * '<S81>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift5'
 * '<S82>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift6'
 * '<S83>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift7'
 * '<S84>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift8'
 * '<S85>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift9'
 * '<S86>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift/bit_shift'
 * '<S87>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift1/bit_shift'
 * '<S88>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift10/bit_shift'
 * '<S89>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift11/bit_shift'
 * '<S90>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift12/bit_shift'
 * '<S91>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift13/bit_shift'
 * '<S92>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift14/bit_shift'
 * '<S93>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift15/bit_shift'
 * '<S94>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift16/bit_shift'
 * '<S95>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift2/bit_shift'
 * '<S96>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift3/bit_shift'
 * '<S97>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift4/bit_shift'
 * '<S98>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift5/bit_shift'
 * '<S99>'  : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift6/bit_shift'
 * '<S100>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift7/bit_shift'
 * '<S101>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift8/bit_shift'
 * '<S102>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_01/Bit Shift9/bit_shift'
 * '<S103>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift'
 * '<S104>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift1'
 * '<S105>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift2'
 * '<S106>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift3'
 * '<S107>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift4'
 * '<S108>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift5'
 * '<S109>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift/bit_shift'
 * '<S110>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift1/bit_shift'
 * '<S111>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift2/bit_shift'
 * '<S112>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift3/bit_shift'
 * '<S113>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift4/bit_shift'
 * '<S114>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_03/Bit Shift5/bit_shift'
 * '<S115>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift'
 * '<S116>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift1'
 * '<S117>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift2'
 * '<S118>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift3'
 * '<S119>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift4'
 * '<S120>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift5'
 * '<S121>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift6'
 * '<S122>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift7'
 * '<S123>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift8'
 * '<S124>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift/bit_shift'
 * '<S125>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift1/bit_shift'
 * '<S126>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift2/bit_shift'
 * '<S127>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift3/bit_shift'
 * '<S128>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift4/bit_shift'
 * '<S129>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift5/bit_shift'
 * '<S130>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift6/bit_shift'
 * '<S131>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift7/bit_shift'
 * '<S132>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_06/Bit Shift8/bit_shift'
 * '<S133>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift'
 * '<S134>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift1'
 * '<S135>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift2'
 * '<S136>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift3'
 * '<S137>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift4'
 * '<S138>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift5'
 * '<S139>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift/bit_shift'
 * '<S140>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift1/bit_shift'
 * '<S141>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift2/bit_shift'
 * '<S142>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift3/bit_shift'
 * '<S143>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift4/bit_shift'
 * '<S144>' : 'VCU10/ESP/ESP_ReceiveMsg/ESP_T_07/Bit Shift5/bit_shift'
 * '<S145>' : 'VCU10/ESP/ESP_ReceiveMsg/Subsystem/brkmotor_check_system'
 * '<S146>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00'
 * '<S147>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift'
 * '<S148>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift1'
 * '<S149>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift2'
 * '<S150>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift3'
 * '<S151>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift4'
 * '<S152>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift5'
 * '<S153>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift6'
 * '<S154>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/ESP_Chart1'
 * '<S155>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift/bit_shift'
 * '<S156>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift1/bit_shift'
 * '<S157>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift2/bit_shift'
 * '<S158>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift3/bit_shift'
 * '<S159>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift4/bit_shift'
 * '<S160>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift5/bit_shift'
 * '<S161>' : 'VCU10/ESP/ESP_TransmitMsg/ESP_R_00/Bit Shift6/bit_shift'
 * '<S162>' : 'VCU10/IPC/IPC_ReceiveMsg'
 * '<S163>' : 'VCU10/IPC/IPC_TransmitMsg'
 * '<S164>' : 'VCU10/IPC/IPC_ReceiveMsg/IPC_Rx_Msg'
 * '<S165>' : 'VCU10/IPC/IPC_ReceiveMsg/IPC_Rx_Msg/Bit Shift'
 * '<S166>' : 'VCU10/IPC/IPC_ReceiveMsg/IPC_Rx_Msg/Bit Shift1'
 * '<S167>' : 'VCU10/IPC/IPC_ReceiveMsg/IPC_Rx_Msg/Bit Shift/bit_shift'
 * '<S168>' : 'VCU10/IPC/IPC_ReceiveMsg/IPC_Rx_Msg/Bit Shift1/bit_shift'
 * '<S169>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1'
 * '<S170>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2'
 * '<S171>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift'
 * '<S172>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift1'
 * '<S173>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift2'
 * '<S174>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift3'
 * '<S175>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift4'
 * '<S176>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift5'
 * '<S177>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift6'
 * '<S178>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift8'
 * '<S179>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift/bit_shift'
 * '<S180>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift1/bit_shift'
 * '<S181>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift2/bit_shift'
 * '<S182>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift3/bit_shift'
 * '<S183>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift4/bit_shift'
 * '<S184>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift5/bit_shift'
 * '<S185>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift6/bit_shift'
 * '<S186>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg1/Bit Shift8/bit_shift'
 * '<S187>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift'
 * '<S188>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift1'
 * '<S189>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift2'
 * '<S190>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift3'
 * '<S191>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift4'
 * '<S192>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift5'
 * '<S193>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift/bit_shift'
 * '<S194>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift1/bit_shift'
 * '<S195>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift2/bit_shift'
 * '<S196>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift3/bit_shift'
 * '<S197>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift4/bit_shift'
 * '<S198>' : 'VCU10/IPC/IPC_TransmitMsg/IPC_Tx_Msg2/Bit Shift5/bit_shift'
 * '<S199>' : 'VCU10/Input_Convert/ADS1115_AinConvert'
 * '<S200>' : 'VCU10/Input_Convert/ADS1115_AinConvert1'
 * '<S201>' : 'VCU10/Input_Convert/Data_Analysis'
 * '<S202>' : 'VCU10/Input_Convert/MCU_AinConvert'
 * '<S203>' : 'VCU10/Input_Convert/MCU_AinConvert1'
 * '<S204>' : 'VCU10/Input_Convert/MCU_AinConvert2'
 * '<S205>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift'
 * '<S206>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift1'
 * '<S207>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift2'
 * '<S208>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift3'
 * '<S209>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift4'
 * '<S210>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift5'
 * '<S211>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift6'
 * '<S212>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift7'
 * '<S213>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift/bit_shift'
 * '<S214>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift1/bit_shift'
 * '<S215>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift2/bit_shift'
 * '<S216>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift3/bit_shift'
 * '<S217>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift4/bit_shift'
 * '<S218>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift5/bit_shift'
 * '<S219>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift6/bit_shift'
 * '<S220>' : 'VCU10/Input_Convert/Data_Analysis/Bit Shift7/bit_shift'
 * '<S221>' : 'VCU10/LED_Control/EBS_LED'
 * '<S222>' : 'VCU10/LED_Control/Subsystem'
 * '<S223>' : 'VCU10/LED_Control/Subsystem1'
 * '<S224>' : 'VCU10/LED_Control/TSLED_Inspection'
 * '<S225>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant'
 * '<S226>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant1'
 * '<S227>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant2'
 * '<S228>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant3'
 * '<S229>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant4'
 * '<S230>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant5'
 * '<S231>' : 'VCU10/LED_Control/EBS_LED/Compare To Constant6'
 * '<S232>' : 'VCU10/LED_Control/EBS_LED/Enabled Subsystem'
 * '<S233>' : 'VCU10/LED_Control/EBS_LED/Shutdown_Button'
 * '<S234>' : 'VCU10/LED_Control/EBS_LED/display'
 * '<S235>' : 'VCU10/LED_Control/Subsystem/blue'
 * '<S236>' : 'VCU10/LED_Control/Subsystem1/yellow'
 * '<S237>' : 'VCU10/Motor_Control/ASTorque_Calculation'
 * '<S238>' : 'VCU10/Motor_Control/MCU1_Rx_Command'
 * '<S239>' : 'VCU10/Motor_Control/MCU1_Rx_Command3'
 * '<S240>' : 'VCU10/Motor_Control/ManualTorque_Calculation'
 * '<S241>' : 'VCU10/Motor_Control/Motor_Torque_Stateflow'
 * '<S242>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift'
 * '<S243>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift1'
 * '<S244>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift2'
 * '<S245>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift3'
 * '<S246>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift4'
 * '<S247>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift5'
 * '<S248>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift6'
 * '<S249>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift7'
 * '<S250>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift8'
 * '<S251>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift9'
 * '<S252>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift/bit_shift'
 * '<S253>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift1/bit_shift'
 * '<S254>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift2/bit_shift'
 * '<S255>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift3/bit_shift'
 * '<S256>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift4/bit_shift'
 * '<S257>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift5/bit_shift'
 * '<S258>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift6/bit_shift'
 * '<S259>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift7/bit_shift'
 * '<S260>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift8/bit_shift'
 * '<S261>' : 'VCU10/Motor_Control/MCU1_Rx_Command/Bit Shift9/bit_shift'
 * '<S262>' : 'VCU10/Motor_Control/MCU1_Rx_Command3/Bit Shift'
 * '<S263>' : 'VCU10/Motor_Control/MCU1_Rx_Command3/Bit Shift1'
 * '<S264>' : 'VCU10/Motor_Control/MCU1_Rx_Command3/Bit Shift/bit_shift'
 * '<S265>' : 'VCU10/Motor_Control/MCU1_Rx_Command3/Bit Shift1/bit_shift'
 * '<S266>' : 'VCU10/Motor_Control/ManualTorque_Calculation/Pedal_Fault_Check'
 * '<S267>' : 'VCU10/Output_Convert/Bit Concat'
 * '<S268>' : 'VCU10/Output_Convert/Bit Concat1'
 * '<S269>' : 'VCU10/Res/Res_Msg'
 * '<S270>' : 'VCU10/Res/Res_Msg/Bit Shift'
 * '<S271>' : 'VCU10/Res/Res_Msg/Bit Shift1'
 * '<S272>' : 'VCU10/Res/Res_Msg/Bit Shift2'
 * '<S273>' : 'VCU10/Res/Res_Msg/Subsystem'
 * '<S274>' : 'VCU10/Res/Res_Msg/Bit Shift/bit_shift'
 * '<S275>' : 'VCU10/Res/Res_Msg/Bit Shift1/bit_shift'
 * '<S276>' : 'VCU10/Res/Res_Msg/Bit Shift2/bit_shift'
 * '<S277>' : 'VCU10/Res/Res_Msg/Subsystem/heaartbeat_chart'
 * '<S278>' : 'VCU10/Res/Res_Msg/Subsystem/xor_Check'
 * '<S279>' : 'VCU10/Sensor_Signal/Subsystem'
 * '<S280>' : 'VCU10/TS_Activation/Chart'
 * '<S281>' : 'VCU10/TS_Activation/Chart1'
 * '<S282>' : 'VCU10/TS_Activation/Chart2'
 */
#endif                                 /* RTW_HEADER_VCU10_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
