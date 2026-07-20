/*
 * VCU10.c
 *
 * Code generation for model "VCU10".
 *
 * Model version              : 1.31
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Sun Jul 19 00:53:26 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "VCU10.h"
#include "VCU10_private.h"

/* Named constants for Chart: '<S15>/Chart' */
#define VCU10_IN_Check                 ((uint8_T)1U)
#define VCU10_IN_Checkoff              ((uint8_T)1U)
#define VCU10_IN_DI8_Check_Flag        ((uint8_T)2U)
#define VCU10_IN_DI8_Offcheck_Flag     ((uint8_T)2U)
#define VCU10_IN_Flameout_Check        ((uint8_T)1U)
#define VCU10_IN_Ignition_Check        ((uint8_T)2U)
#define VCU10_IN_NO_ACTIVE_CHILD       ((uint8_T)0U)
#define VCU10_IN_begin                 ((uint8_T)3U)

/* Named constants for Chart: '<S15>/Chart1' */
#define VCU10_IN_Run_Check_Flag        ((uint8_T)2U)
#define VCU10_IN_Run_Offcheck_Flag     ((uint8_T)2U)

/* Named constants for Chart: '<S15>/Chart2' */
#define VCU10_IN_begin_f               ((uint8_T)1U)
#define VCU10_IN_delay                 ((uint8_T)2U)

/* Named constants for Chart: '<S273>/heaartbeat_chart' */
#define VCU10_IN_compare               ((uint8_T)2U)
#define VCU10_IN_judge                 ((uint8_T)3U)
#define VCU10_IN_same                  ((uint8_T)4U)

/* Named constants for Chart: '<S273>/xor_Check' */
#define VCU10_IN_Init                  ((uint8_T)1U)
#define VCU10_IN_different             ((uint8_T)3U)
#define VCU10_IN_judge_c               ((uint8_T)4U)

/* Named constants for Chart: '<S4>/Chart' */
#define VCU10_IN_Default               ((uint8_T)1U)
#define VCU10_IN_Emergency             ((uint8_T)2U)

/* Named constants for Chart: '<S17>/Chart' */
#define VCU10_IN_as_driving            ((uint8_T)1U)
#define VCU10_IN_as_emergency          ((uint8_T)2U)
#define VCU10_IN_as_finished           ((uint8_T)3U)
#define VCU10_IN_as_off                ((uint8_T)4U)
#define VCU10_IN_as_ready              ((uint8_T)5U)
#define VCU10_IN_begin_g               ((uint8_T)6U)
#define VCU10_IN_munual_driving        ((uint8_T)7U)
#define VCU10_IN_r2d                   ((uint8_T)8U)

/* Named constants for Chart: '<S221>/Shutdown_Button' */
#define VCU10_IN_same1                 ((uint8_T)4U)

/* Named constants for Chart: '<S221>/display' */
#define VCU10_IN_end                   ((uint8_T)2U)

/* Named constants for Chart: '<S222>/blue' */
#define VCU10_IN_Blink                 ((uint8_T)1U)
#define VCU10_IN_Close                 ((uint8_T)2U)
#define VCU10_IN_Delay                 ((uint8_T)3U)
#define VCU10_IN_Node                  ((uint8_T)4U)
#define VCU10_IN_On                    ((uint8_T)5U)

/* Named constants for Chart: '<S223>/yellow' */
#define VCU10_IN_On_o                  ((uint8_T)3U)
#define VCU10_IN_delay_j               ((uint8_T)4U)
#define VCU10_IN_node                  ((uint8_T)5U)

/* Named constants for Chart: '<S10>/TSLED_Inspection' */
#define VCU10_IN_Inspection            ((uint8_T)1U)
#define VCU10_IN_Normal                ((uint8_T)2U)

/* Named constants for Chart: '<S11>/Motor_Torque_Stateflow' */
#define VCU10_IN_AS_Driving            ((uint8_T)1U)
#define VCU10_IN_Default_m             ((uint8_T)2U)
#define VCU10_IN_Manual_Driving        ((uint8_T)3U)

/* Named constants for Chart: '<S3>/Chart' */
#define VCU10_IN_AS_Emergency          ((uint8_T)2U)
#define VCU10_IN_AS_Finished           ((uint8_T)3U)
#define VCU10_IN_AS_Off                ((uint8_T)4U)
#define VCU10_IN_AS_Ready              ((uint8_T)5U)
#define VCU10_IN_Manual_Driving_n      ((uint8_T)6U)
#define VCU10_IN_R2D                   ((uint8_T)1U)
#define VCU10_IN_go                    ((uint8_T)2U)
#define VCU10_IN_transition            ((uint8_T)7U)

/* Named constants for Chart: '<S146>/ESP_Chart1' */
#define VCU10_IN_ESC_Able              ((uint8_T)1U)
#define VCU10_IN_ESC_Engage            ((uint8_T)2U)
#define VCU10_IN_ESC_Unable            ((uint8_T)3U)

/* Named constants for Chart: '<S51>/EPS_Stateflow1' */
#define VCU10_IN_EPS_Enable            ((uint8_T)1U)
#define VCU10_IN_EPS_Return            ((uint8_T)2U)
#define VCU10_IN_EPS_Unable            ((uint8_T)3U)

/* Exported block signals */
uint16_T model_hin;                    /* '<Root>/model_hin' */
uint16_T model_ain[5];                 /* '<Root>/model_ain' */
real32_T wlspd_fsensor;                /* '<Root>/wlspd_fsensor' */
real32_T wlspd_hsensor;                /* '<Root>/wlspd_hsensor' */
uint8_T AMI_Tx[8];                     /* '<Root>/AMI_Tx' */
uint8_T ESP_T_01[8];                   /* '<Root>/ESP_T_01' */
uint8_T ESP_T_03[8];                   /* '<Root>/ESP_T_03' */
uint8_T ESP_T_06[8];                   /* '<Root>/ESP_T_06' */
uint8_T ESP_T_07[8];                   /* '<Root>/ESP_T_07' */
uint8_T canb_epssendmsg1[8];           /* '<Root>/canb_epssendmsg1' */
uint8_T canb_epssendmsg2[8];           /* '<Root>/canb_epssendmsg2' */
uint8_T res_msg[8];                    /* '<Root>/res_msg' */
uint8_T canb_ipctsmsg1[8];             /* '<Root>/canb_ipctsmsg1' */
uint8_T canb_ipctsmsg2[8];             /* '<Root>/canb_ipctsmsg2' */
uint16_T airprs2;                      /* '<S9>/Data Type Conversion' */
uint16_T airprs1;                      /* '<S9>/Data Type Conversion1' */
uint16_T brkps;                        /* '<S9>/Data Type Conversion2' */
uint16_T apps2;                        /* '<S9>/Data Type Conversion3' */
uint16_T apps1;                        /* '<S9>/Data Type Conversion4' */
uint8_T canb_epsmsg[8];                /* '<S6>/EPS_TransmitMsg' */
uint8_T cana_motor_cmd[8];             /* '<S238>/Signal Conversion' */
uint8_T cana_motor_cmd3[8];            /* '<S11>/MCU1_Rx_Command3' */
uint8_T AMI_Rx[8];                     /* '<S17>/Signal Conversion' */
uint8_T canb_ipcrxmsg[8];              /* '<S8>/IPC_ReceiveMsg' */
boolean_T ebs_driver_check;            /* '<S201>/Data Type Conversion' */
boolean_T shutdown_s;                  /* '<S201>/Data Type Conversion1' */
boolean_T shutdown_e;                  /* '<S201>/Data Type Conversion2' */
boolean_T di8_cockpit;                 /* '<S201>/Data Type Conversion3' */
boolean_T di8_side;                    /* '<S201>/Data Type Conversion4' */
boolean_T run_button;                  /* '<S201>/Data Type Conversion5' */
boolean_T tsms;                        /* '<S201>/Data Type Conversion6' */
boolean_T asms;                        /* '<S201>/Data Type Conversion7' */
boolean_T ebs_trig;                    /* '<S5>/Logical Operator' */
boolean_T ebs_watchdog;
     /* '<S5>/BufferToMakeInportVirtual_InsertedFor_ebs_watchdog_at_inport_0' */
boolean_T led_brake;                   /* '<S10>/brake_on' */
boolean_T led_ebs_error;               /* '<S221>/Logical Operator' */
boolean_T led_assi_blue;               /* '<S222>/Data Type Conversion' */
boolean_T led_assi_yellow;             /* '<S223>/Data Type Conversion' */
boolean_T led_imd_error;               /* '<S10>/TSLED_Inspection' */
boolean_T led_bms_error;               /* '<S10>/TSLED_Inspection' */
boolean_T r2d_buzzer;                  /* '<S4>/Switch1' */
boolean_T ebs_buzzer;                  /* '<S4>/Switch' */
boolean_T res_error;                   /*  */
boolean_T run;                         /* '<S15>/Chart1' */
boolean_T di8;                         /* '<S15>/Chart' */

/* Block signals (default storage) */
B_VCU10_T VCU10_B;

/* Block states (default storage) */
DW_VCU10_T VCU10_DW;

/* External outputs (root outports fed by signals with default storage) */
ExtY_VCU10_T VCU10_Y;

/* Real-time model */
static RT_MODEL_VCU10_T VCU10_M_;
RT_MODEL_VCU10_T *const VCU10_M = &VCU10_M_;

/* Forward declaration for local functions */
static void VCU10_enter_atomic_AS_Emergency(void);
static void VCU10_AS_Driving(const boolean_T *LogicalOperator_o);
static void VCU10_enter_atomic_AS_Off(void);
real_T look1_iu16td_linlcapw(uint16_T u0, const uint16_T bp0[], const real_T
  table[], uint32_T maxIndex)
{
  real_T frac;
  real_T y;
  uint32_T bpIdx;

  /* Column-major Lookup 1-D
     Search method: 'linear'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'linear'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    bpIdx = 0U;
    frac = 0.0;
  } else if (u0 < bp0[maxIndex]) {
    /* Linear Search */
    for (bpIdx = maxIndex >> 1U; u0 < bp0[bpIdx]; bpIdx--) {
    }

    while (u0 >= bp0[bpIdx + 1U]) {
      bpIdx++;
    }

    uint16_T bpLeftVar;
    bpLeftVar = bp0[bpIdx];
    frac = (real_T)(uint16_T)((uint32_T)u0 - bpLeftVar) / (real_T)(uint16_T)
      ((uint32_T)bp0[bpIdx + 1U] - bpLeftVar);
  } else {
    bpIdx = maxIndex;
    frac = 0.0;
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'on'
     Overflow mode: 'portable wrapping'
   */
  if (bpIdx == maxIndex) {
    y = table[bpIdx];
  } else {
    real_T yL_0d0;
    yL_0d0 = table[bpIdx];
    y = (table[bpIdx + 1U] - yL_0d0) * frac + yL_0d0;
  }

  return y;
}

/*
 * Output and update for atomic system:
 *    '<S269>/Bit Shift'
 *    '<S64>/Bit Shift15'
 *    '<S64>/Bit Shift8'
 */
void VCU10_BitShift(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S270>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 1);
}

/*
 * Output and update for atomic system:
 *    '<S269>/Bit Shift1'
 *    '<S170>/Bit Shift3'
 *    '<S64>/Bit Shift1'
 *    '<S64>/Bit Shift9'
 */
void VCU10_BitShift1(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S271>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 2);
}

/*
 * Output and update for atomic system:
 *    '<S269>/Bit Shift2'
 *    '<S16>/Bit Shift'
 *    '<S64>/Bit Shift11'
 *    '<S64>/Bit Shift5'
 *    '<S64>/Bit Shift7'
 */
void VCU10_BitShift2(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S272>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 4);
}

/*
 * Output and update for atomic system:
 *    '<S164>/Bit Shift'
 *    '<S17>/Bit Shift'
 *    '<S238>/Bit Shift'
 */
void VCU10_BitShift_a(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S165>/bit_shift' */
  *rty_y = (uint8_T)(rtu_u << 1);
}

/*
 * Output and update for atomic system:
 *    '<S169>/Bit Shift'
 *    '<S170>/Bit Shift4'
 *    '<S170>/Bit Shift5'
 *    '<S65>/Bit Shift2'
 *    '<S65>/Bit Shift5'
 *    '<S67>/Bit Shift2'
 *    '<S67>/Bit Shift5'
 *    '<S53>/Bit Shift1'
 */
void VCU10_BitShift_p(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S171>/bit_shift' */
  *rty_y = (uint16_T)(rtu_u << 8);
}

/*
 * Output and update for atomic system:
 *    '<S169>/Bit Shift1'
 *    '<S66>/Bit Shift3'
 */
void VCU10_BitShift1_j(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S172>/bit_shift' */
  *rty_y = (uint16_T)((uint32_T)rtu_u >> 2);
}

/*
 * Output and update for atomic system:
 *    '<S169>/Bit Shift2'
 *    '<S66>/Bit Shift2'
 */
void VCU10_BitShift2_b(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S173>/bit_shift' */
  *rty_y = (uint16_T)(rtu_u << 6);
}

/*
 * Output and update for atomic system:
 *    '<S169>/Bit Shift3'
 *    '<S65>/Bit Shift1'
 *    '<S65>/Bit Shift4'
 *    '<S66>/Bit Shift8'
 *    '<S67>/Bit Shift1'
 *    '<S67>/Bit Shift4'
 */
void VCU10_BitShift3(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S174>/bit_shift' */
  *rty_y = (uint16_T)((uint32_T)rtu_u >> 4);
}

/*
 * Output and update for atomic system:
 *    '<S169>/Bit Shift4'
 *    '<S65>/Bit Shift'
 *    '<S65>/Bit Shift3'
 *    '<S66>/Bit Shift7'
 *    '<S67>/Bit Shift'
 *    '<S67>/Bit Shift3'
 */
void VCU10_BitShift4(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S175>/bit_shift' */
  *rty_y = (uint16_T)(rtu_u << 4);
}

/*
 * Output and update for atomic system:
 *    '<S169>/Bit Shift8'
 *    '<S170>/Bit Shift'
 */
void VCU10_BitShift8(real_T rtu_u, real_T *rty_y)
{
  /* MATLAB Function: '<S178>/bit_shift' */
  *rty_y = ldexp(rtu_u, 8);
}

/*
 * Output and update for atomic system:
 *    '<S170>/Bit Shift1'
 *    '<S64>/Bit Shift14'
 *    '<S64>/Bit Shift16'
 */
void VCU10_BitShift1_i(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S188>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 7);
}

/*
 * Output and update for atomic system:
 *    '<S170>/Bit Shift2'
 *    '<S64>/Bit Shift13'
 */
void VCU10_BitShift2_e(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S189>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 6);
}

/*
 * Output and update for atomic system:
 *    '<S238>/Bit Shift3'
 *    '<S146>/Bit Shift6'
 */
void VCU10_BitShift3_m(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S245>/bit_shift' */
  *rty_y = (uint8_T)(rtu_u << 6);
}

/*
 * Output and update for atomic system:
 *    '<S238>/Bit Shift5'
 *    '<S238>/Bit Shift8'
 *    '<S238>/Bit Shift9'
 *    '<S239>/Bit Shift'
 *    '<S239>/Bit Shift1'
 *    '<S146>/Bit Shift2'
 *    '<S146>/Bit Shift5'
 *    '<S51>/Bit Shift'
 */
void VCU10_BitShift5(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S247>/bit_shift' */
  *rty_y = (uint16_T)((uint32_T)rtu_u >> 8);
}

/*
 * Output and update for atomic system:
 *    '<S238>/Bit Shift6'
 *    '<S146>/Bit Shift1'
 *    '<S146>/Bit Shift4'
 */
void VCU10_BitShift6(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S248>/bit_shift' */
  *rty_y = (uint16_T)(rtu_u << 4);
}

/*
 * Output and update for atomic system:
 *    '<S238>/Bit Shift7'
 *    '<S146>/Bit Shift'
 *    '<S146>/Bit Shift3'
 *    '<S201>/Bit Shift5'
 */
void VCU10_BitShift7(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S249>/bit_shift' */
  *rty_y = (uint16_T)((uint32_T)rtu_u >> 4);
}

/*
 * Output and update for enable system:
 *    '<S44>/NEGATIVE Edge'
 *    '<S47>/NEGATIVE Edge'
 */
void VCU10_NEGATIVEEdge(real_T rtu_Enable, boolean_T rtu_IN, boolean_T
  rtu_INprevious, boolean_T *rty_OUT)
{
  /* Outputs for Enabled SubSystem: '<S44>/NEGATIVE Edge' incorporates:
   *  EnablePort: '<S45>/Enable'
   */
  if (rtu_Enable > 0.0) {
    /* RelationalOperator: '<S45>/Relational Operator1' */
    *rty_OUT = ((int32_T)rtu_INprevious > (int32_T)rtu_IN);
  }

  /* End of Outputs for SubSystem: '<S44>/NEGATIVE Edge' */
}

/*
 * Output and update for enable system:
 *    '<S44>/POSITIVE Edge'
 *    '<S47>/POSITIVE Edge'
 */
void VCU10_POSITIVEEdge(real_T rtu_Enable, boolean_T rtu_IN, boolean_T
  rtu_INprevious, boolean_T *rty_OUT)
{
  /* Outputs for Enabled SubSystem: '<S44>/POSITIVE Edge' incorporates:
   *  EnablePort: '<S46>/Enable'
   */
  if (rtu_Enable > 0.0) {
    /* RelationalOperator: '<S46>/Relational Operator1' */
    *rty_OUT = ((int32_T)rtu_IN > (int32_T)rtu_INprevious);
  }

  /* End of Outputs for SubSystem: '<S44>/POSITIVE Edge' */
}

/*
 * Output and update for atomic system:
 *    '<S64>/Bit Shift10'
 *    '<S64>/Bit Shift3'
 */
void VCU10_BitShift10(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S71>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 3);
}

/*
 * Output and update for atomic system:
 *    '<S64>/Bit Shift4'
 *    '<S64>/Bit Shift6'
 */
void VCU10_BitShift4_h(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S80>/bit_shift' */
  *rty_y = (uint8_T)(rtu_u << 4);
}

/* Function for Chart: '<S3>/Chart' */
static void VCU10_enter_atomic_AS_Emergency(void)
{
  VCU10_B.r2d_flag_c = 0.0;
  VCU10_B.steering_flag_o = 0.0;
  VCU10_B.brake_flag_i = 0.0;
  VCU10_B.as_led_yellow = 0.0;
  VCU10_B.as_led_blue = 2.0;
  VCU10_B.as_off_flag_p = 0.0;
  VCU10_B.as_ready_flag_c = 0.0;
  VCU10_B.as_driving_flag_a = 0.0;
  VCU10_B.as_finished_flag_c = 0.0;
  VCU10_B.as_emergency_flag_e = 1.0;
  VCU10_B.manual_driving_flag_k = 0.0;
}

/* Function for Chart: '<S3>/Chart' */
static void VCU10_AS_Driving(const boolean_T *LogicalOperator_o)
{
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T guard3 = false;

  /* DataStoreRead: '<Root>/Data Store Read7' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read10'
   */
  guard1 = false;
  guard2 = false;
  guard3 = false;
  if (VCU10_DW.ebs_working) {
    guard2 = true;
  } else if ((*LogicalOperator_o) && VCU10_DW.task_finish) {
    VCU10_B.as_ebs_trig = 1.0;
    guard3 = true;
  } else if (VCU10_DW.inspection_flag) {
    if (VCU10_DW.ebs_working) {
      guard2 = true;
    } else if (VCU10_DW.temporalCounter_i1 >= 2700U) {
      VCU10_B.as_ebs_trig = 1.0;
      guard3 = true;
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard3) {
    VCU10_DW.is_AS_Driving = VCU10_IN_NO_ACTIVE_CHILD;
    VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Finished;
    VCU10_B.r2d_flag_c = 0.0;
    VCU10_B.steering_flag_o = 0.0;
    VCU10_B.brake_flag_i = 0.0;
    VCU10_B.as_led_yellow = 0.0;
    VCU10_B.as_led_blue = 1.0;
    VCU10_B.as_off_flag_p = 0.0;
    VCU10_B.as_ready_flag_c = 0.0;
    VCU10_B.as_driving_flag_a = 0.0;
    VCU10_B.as_finished_flag_c = 1.0;
    VCU10_B.as_emergency_flag_e = 0.0;
    VCU10_B.manual_driving_flag_k = 0.0;
  }

  if (guard2) {
    VCU10_DW.is_AS_Driving = VCU10_IN_NO_ACTIVE_CHILD;
    VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Emergency;
    VCU10_enter_atomic_AS_Emergency();
  }

  if (guard1) {
    if (VCU10_DW.is_AS_Driving == VCU10_IN_R2D) {
      if (VCU10_DW.steer_zero) {
        VCU10_B.steer_return = F;
        VCU10_B.r2d_warning = F;
        VCU10_DW.is_AS_Driving = VCU10_IN_go;
        VCU10_B.r2d_flag_c = 0.0;
        VCU10_B.steering_flag_o = 1.0;
        VCU10_B.brake_flag_i = 1.0;
        VCU10_B.as_led_yellow = 2.0;
        VCU10_B.as_led_blue = 0.0;
        VCU10_B.as_off_flag_p = 0.0;
        VCU10_B.as_ready_flag_c = 0.0;
        VCU10_B.as_driving_flag_a = 1.0;
        VCU10_B.as_finished_flag_c = 0.0;
        VCU10_B.as_emergency_flag_e = 0.0;
        VCU10_B.manual_driving_flag_k = 0.0;
      }
    } else {
      /* case IN_go: */
      VCU10_B.r2d_flag_c = 0.0;
      VCU10_B.steering_flag_o = 1.0;
      VCU10_B.brake_flag_i = 1.0;
      VCU10_B.as_led_yellow = 2.0;
      VCU10_B.as_led_blue = 0.0;
      VCU10_B.as_off_flag_p = 0.0;
      VCU10_B.as_ready_flag_c = 0.0;
      VCU10_B.as_driving_flag_a = 1.0;
      VCU10_B.as_finished_flag_c = 0.0;
      VCU10_B.as_emergency_flag_e = 0.0;
      VCU10_B.manual_driving_flag_k = 0.0;
    }
  }

  /* End of DataStoreRead: '<Root>/Data Store Read7' */
}

/* Function for Chart: '<S3>/Chart' */
static void VCU10_enter_atomic_AS_Off(void)
{
  VCU10_B.r2d_flag_c = 0.0;
  VCU10_B.steering_flag_o = 0.0;
  VCU10_B.brake_flag_i = 0.0;
  VCU10_B.as_led_yellow = 0.0;
  VCU10_B.as_led_blue = 0.0;
  VCU10_B.as_off_flag_p = 1.0;
  VCU10_B.as_ready_flag_c = 0.0;
  VCU10_B.as_driving_flag_a = 0.0;
  VCU10_B.as_finished_flag_c = 0.0;
  VCU10_B.as_emergency_flag_e = 0.0;
  VCU10_B.manual_driving_flag_k = 0.0;
}

/* Model step function */
void VCU10_step(void)
{
  real_T airprs_sensor1;
  real_T airprs_sensor2_tmp;
  real_T apps1_01;
  real_T apps2_01;
  real_T ipc_eps_frprs;
  real_T ipc_esp_flprs;
  real_T ipc_esp_rlprs;
  real_T ipc_esp_rrprs;
  real_T rtb_DataTypeConversion1;
  real_T rtb_Product1;
  real_T rtb_Product2;
  real_T rtb_y;
  real_T tmp;
  int32_T rtb_Add_f;
  int32_T rtb_blue_0;
  real32_T u0;
  uint32_T elapsedTicks;
  uint32_T elapsedTicks_m;
  uint16_T rtb_Add1_a;
  uint16_T rtb_Add2_g;
  uint16_T rtb_y_as;
  uint16_T rtb_y_cq;
  uint16_T rtb_y_ej;
  uint16_T rtb_y_em;
  uint16_T rtb_y_fb;
  uint16_T rtb_y_hf;
  uint16_T rtb_y_md;
  uint16_T rtb_y_mj;
  uint16_T rtb_y_mn;
  uint16_T rtb_y_ns;
  uint8_T res_heartbeat_prev;
  uint8_T rtb_BitwiseAND_mj;
  uint8_T rtb_xor_consequence;
  uint8_T rtb_y_cf;
  uint8_T rtb_y_ch;
  uint8_T rtb_y_hw;
  boolean_T LogicalOperator_o;
  boolean_T guard1 = false;
  boolean_T res_stop;

  /* S-Function (fcgen): '<Root>/Function-Call Generator' incorporates:
   *  SubSystem: '<Root>/Input_Convert'
   */
  /* Outputs for Atomic SubSystem: '<S201>/Bit Shift5' */
  /* S-Function (sfix_bitop): '<S201>/Bitwise AND4' incorporates:
   *  Inport: '<Root>/model_hin'
   */
  VCU10_BitShift7((uint16_T)(model_hin & 16), &rtb_y_hf);

  /* End of Outputs for SubSystem: '<S201>/Bit Shift5' */

  /* DataTypeConversion: '<S201>/Data Type Conversion' incorporates:
   *  Inport: '<Root>/model_hin'
   *  S-Function (sfix_bitop): '<S201>/Bitwise AND7'
   */
  ebs_driver_check = ((model_hin & 1U) != 0U);

  /* Outputs for Atomic SubSystem: '<S201>/Bit Shift1' */
  /* DataTypeConversion: '<S201>/Data Type Conversion1' incorporates:
   *  Inport: '<Root>/model_hin'
   *  MATLAB Function: '<S206>/bit_shift'
   *  S-Function (sfix_bitop): '<S201>/Bitwise AND1'
   */
  shutdown_s = ((int32_T)((uint32_T)(model_hin & 2) >> 1) != 0);

  /* End of Outputs for SubSystem: '<S201>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S201>/Bit Shift2' */
  /* DataTypeConversion: '<S201>/Data Type Conversion2' incorporates:
   *  Inport: '<Root>/model_hin'
   *  MATLAB Function: '<S207>/bit_shift'
   *  S-Function (sfix_bitop): '<S201>/Bitwise AND2'
   */
  shutdown_e = ((int32_T)((uint32_T)(model_hin & 4) >> 2) != 0);

  /* End of Outputs for SubSystem: '<S201>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S201>/Bit Shift4' */
  /* DataTypeConversion: '<S201>/Data Type Conversion3' incorporates:
   *  Inport: '<Root>/model_hin'
   *  MATLAB Function: '<S209>/bit_shift'
   *  S-Function (sfix_bitop): '<S201>/Bitwise AND3'
   */
  di8_cockpit = ((int32_T)((uint32_T)(model_hin & 8) >> 3) != 0);

  /* End of Outputs for SubSystem: '<S201>/Bit Shift4' */

  /* DataTypeConversion: '<S201>/Data Type Conversion4' */
  di8_side = (rtb_y_hf != 0);

  /* Outputs for Atomic SubSystem: '<S201>/Bit Shift6' */
  /* DataTypeConversion: '<S201>/Data Type Conversion5' incorporates:
   *  Inport: '<Root>/model_hin'
   *  MATLAB Function: '<S211>/bit_shift'
   *  S-Function (sfix_bitop): '<S201>/Bitwise AND5'
   */
  run_button = ((int32_T)((uint32_T)(model_hin & 32) >> 5) != 0);

  /* End of Outputs for SubSystem: '<S201>/Bit Shift6' */

  /* Outputs for Atomic SubSystem: '<S201>/Bit Shift7' */
  /* DataTypeConversion: '<S201>/Data Type Conversion6' incorporates:
   *  Inport: '<Root>/model_hin'
   *  MATLAB Function: '<S212>/bit_shift'
   *  S-Function (sfix_bitop): '<S201>/Bitwise AND6'
   */
  tsms = ((int32_T)((uint32_T)(model_hin & 64) >> 6) != 0);

  /* End of Outputs for SubSystem: '<S201>/Bit Shift7' */

  /* Outputs for Atomic SubSystem: '<S201>/Bit Shift3' */
  /* DataTypeConversion: '<S201>/Data Type Conversion7' incorporates:
   *  Inport: '<Root>/model_hin'
   *  MATLAB Function: '<S208>/bit_shift'
   *  S-Function (sfix_bitop): '<S201>/Bitwise AND8'
   */
  asms = ((int32_T)((uint32_T)(model_hin & 128) >> 7) != 0);

  /* End of Outputs for SubSystem: '<S201>/Bit Shift3' */

  /* Gain: '<S200>/Gain' incorporates:
   *  DataTypeConversion: '<S200>/Data Type Conversion'
   *  Inport: '<Root>/model_ain'
   */
  u0 = 0.0001875F * (real32_T)model_ain[4];

  /* Saturate: '<S200>/Saturation' */
  if (u0 > 5.0F) {
    u0 = 5.0F;
  }

  /* End of Saturate: '<S200>/Saturation' */

  /* DataTypeConversion: '<S9>/Data Type Conversion' incorporates:
   *  Gain: '<S9>/Gain'
   */
  airprs2 = (uint16_T)(int32_T)fmodf((real32_T)(int32_T)floorf(1000.0F * u0),
    65536.0F);

  /* Gain: '<S199>/Gain' incorporates:
   *  DataTypeConversion: '<S199>/Data Type Conversion'
   *  Inport: '<Root>/model_ain'
   */
  u0 = 0.0001875F * (real32_T)model_ain[3];

  /* Saturate: '<S199>/Saturation' */
  if (u0 > 5.0F) {
    u0 = 5.0F;
  }

  /* End of Saturate: '<S199>/Saturation' */

  /* DataTypeConversion: '<S9>/Data Type Conversion1' incorporates:
   *  Gain: '<S9>/Gain1'
   */
  airprs1 = (uint16_T)(int32_T)fmodf((real32_T)(int32_T)floorf(1000.0F * u0),
    65536.0F);

  /* Gain: '<S204>/Gain' incorporates:
   *  DataTypeConversion: '<S204>/Data Type Conversion'
   *  Inport: '<Root>/model_ain'
   */
  u0 = 0.00241699209F * (real32_T)model_ain[2];

  /* Saturate: '<S204>/Saturation' */
  if (u0 > 10.0F) {
    u0 = 10.0F;
  }

  /* End of Saturate: '<S204>/Saturation' */

  /* DataTypeConversion: '<S9>/Data Type Conversion2' incorporates:
   *  Gain: '<S9>/Gain2'
   */
  brkps = (uint16_T)(int32_T)fmodf((real32_T)(int32_T)floorf(1000.0F * u0),
    65536.0F);

  /* Gain: '<S203>/Gain' incorporates:
   *  DataTypeConversion: '<S203>/Data Type Conversion'
   *  Inport: '<Root>/model_ain'
   */
  u0 = 0.00241699209F * (real32_T)model_ain[1];

  /* Saturate: '<S203>/Saturation' */
  if (u0 > 10.0F) {
    u0 = 10.0F;
  }

  /* End of Saturate: '<S203>/Saturation' */

  /* DataTypeConversion: '<S9>/Data Type Conversion3' incorporates:
   *  Gain: '<S9>/Gain3'
   */
  apps2 = (uint16_T)(int32_T)fmodf((real32_T)(int32_T)floorf(1000.0F * u0),
    65536.0F);

  /* Gain: '<S202>/Gain' incorporates:
   *  DataTypeConversion: '<S202>/Data Type Conversion'
   *  Inport: '<Root>/model_ain'
   */
  u0 = 0.00241699209F * (real32_T)model_ain[0];

  /* Saturate: '<S202>/Saturation' */
  if (u0 > 10.0F) {
    u0 = 10.0F;
  }

  /* End of Saturate: '<S202>/Saturation' */

  /* DataTypeConversion: '<S9>/Data Type Conversion4' incorporates:
   *  Gain: '<S9>/Gain4'
   */
  apps1 = (uint16_T)(int32_T)fmodf((real32_T)(int32_T)floorf(1000.0F * u0),
    65536.0F);

  /* End of Outputs for S-Function (fcgen): '<Root>/Function-Call Generator' */

  /* S-Function (fcgen): '<Root>/10ms' incorporates:
   *  SubSystem: '<Root>/Sensor_Signal'
   */
  /* DataTypeConversion: '<S14>/Data Type Conversion12' incorporates:
   *  Gain: '<S14>/Gain'
   */
  airprs_sensor1 = 33554.0 * (real_T)airprs1 * 2.9802322387695312E-8;

  /* DataTypeConversion: '<S14>/Data Type Conversion15' incorporates:
   *  Gain: '<S14>/Gain1'
   */
  airprs_sensor2_tmp = 33554.0 * (real_T)airprs2 * 2.9802322387695312E-8;

  /* Product: '<S279>/Product1' incorporates:
   *  Constant: '<S279>/Constant'
   *  DataTypeConversion: '<S14>/Data Type Conversion6'
   *  Gain: '<S279>/Gain'
   *  Gain: '<S279>/Gain1'
   *  Inport: '<Root>/wlspd_fsensor'
   *  Product: '<S279>/Divide'
   */
  rtb_Product1 = 36.0 * wlspd_fsensor * 3.1415 / 180.0 * VCU10_ConstB.Product;

  /* Product: '<S279>/Product2' incorporates:
   *  Constant: '<S279>/Constant3'
   *  DataTypeConversion: '<S14>/Data Type Conversion7'
   *  Gain: '<S279>/Gain2'
   *  Gain: '<S279>/Gain3'
   *  Inport: '<Root>/wlspd_hsensor'
   *  Product: '<S279>/Divide1'
   */
  rtb_Product2 = 36.0 * wlspd_hsensor * 3.1415 / 180.0 * VCU10_ConstB.Product;

  /* Lookup_n-D: '<S14>/1-D Lookup Table' incorporates:
   *  DataTypeConversion: '<S9>/Data Type Conversion4'
   */
  apps1_01 = look1_iu16td_linlcapw(apps1, VCU10_ConstP.pooled38,
    VCU10_ConstP.pooled22, 1U);

  /* Saturate: '<S14>/Saturation' */
  if (apps1_01 > 1.0) {
    /* Saturate: '<S14>/Saturation' */
    apps1_01 = 1.0;
  } else if (apps1_01 < 0.0) {
    /* Saturate: '<S14>/Saturation' */
    apps1_01 = 0.0;
  }

  /* End of Saturate: '<S14>/Saturation' */

  /* Lookup_n-D: '<S14>/1-D Lookup Table9' incorporates:
   *  DataTypeConversion: '<S9>/Data Type Conversion3'
   */
  apps2_01 = look1_iu16td_linlcapw(apps2, VCU10_ConstP.pooled38,
    VCU10_ConstP.pooled22, 1U);

  /* Saturate: '<S14>/Saturation1' */
  if (apps2_01 > 1.0) {
    /* Saturate: '<S14>/Saturation1' */
    apps2_01 = 1.0;
  } else if (apps2_01 < 0.0) {
    /* Saturate: '<S14>/Saturation1' */
    apps2_01 = 0.0;
  }

  /* End of Saturate: '<S14>/Saturation1' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */

  /* S-Function (fcgen): '<Root>/10ms10' incorporates:
   *  SubSystem: '<Root>/Res'
   */
  /* S-Function (sfix_bitop): '<S269>/Bitwise AND' incorporates:
   *  Inport: '<Root>/res_msg'
   */
  rtb_BitwiseAND_mj = (uint8_T)(res_msg[0] & 1);

  /* DataTypeConversion: '<S269>/Data Type Conversion7' incorporates:
   *  Inport: '<Root>/res_msg'
   *  S-Function (sfix_bitop): '<S269>/Bitwise AND'
   */
  res_stop = ((res_msg[0] & 1U) != 0U);

  /* SignalConversion generated from: '<S13>/res_error' incorporates:
   *  DataTypeConversion: '<S269>/Data Type Conversion7'
   */
  res_error = (rtb_BitwiseAND_mj != 0);

  /* Outputs for Atomic SubSystem: '<S269>/Bit Shift' */
  /* S-Function (sfix_bitop): '<S269>/Bitwise AND1' incorporates:
   *  Inport: '<Root>/res_msg'
   */
  VCU10_BitShift((uint8_T)(res_msg[0] & 2), &rtb_y_hw);

  /* End of Outputs for SubSystem: '<S269>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S269>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S269>/Bitwise AND2' incorporates:
   *  Inport: '<Root>/res_msg'
   */
  VCU10_BitShift1((uint8_T)(res_msg[0] & 4), &rtb_y_hw);

  /* End of Outputs for SubSystem: '<S269>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S269>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S269>/Bitwise AND3' incorporates:
   *  Inport: '<Root>/res_msg'
   */
  VCU10_BitShift2((uint8_T)(res_msg[0] & 16), &rtb_y_cf);

  /* End of Outputs for SubSystem: '<S269>/Bit Shift2' */

  /* S-Function (sfix_bitop): '<S269>/Logical Operator' incorporates:
   *  Inport: '<Root>/res_msg'
   */
  rtb_xor_consequence = (uint8_T)(res_msg[0] ^ res_msg[1]);

  /* Chart: '<S273>/heaartbeat_chart' incorporates:
   *  Inport: '<Root>/res_msg'
   *  S-Function (sfix_bitop): '<S269>/Bitwise AND4'
   */
  res_heartbeat_prev = VCU10_DW.res_heartbeat_start;
  VCU10_DW.res_heartbeat_start = res_msg[1];
  if (VCU10_DW.is_active_c10_VCU10 == 0U) {
    VCU10_DW.is_active_c10_VCU10 = 1U;
    VCU10_DW.is_c10_VCU10 = VCU10_IN_begin_f;
  } else {
    switch (VCU10_DW.is_c10_VCU10) {
     case VCU10_IN_begin_f:
      if (res_heartbeat_prev != VCU10_DW.res_heartbeat_start) {
        VCU10_DW.is_c10_VCU10 = VCU10_IN_compare;
        VCU10_B.res_hbcheck = 1.0;
      }
      break;

     case VCU10_IN_compare:
      if (res_heartbeat_prev == VCU10_DW.res_heartbeat_start) {
        VCU10_DW.is_c10_VCU10 = VCU10_IN_same;
        VCU10_DW.hbcnt++;
      } else {
        VCU10_B.res_hbcheck = 1.0;
      }
      break;

     case VCU10_IN_judge:
      if (res_heartbeat_prev != VCU10_DW.res_heartbeat_start) {
        VCU10_DW.is_c10_VCU10 = VCU10_IN_compare;
        VCU10_B.res_hbcheck = 1.0;
      } else {
        VCU10_B.res_hbcheck = 0.0;
      }
      break;

     default:
      /* case IN_same: */
      if (VCU10_DW.hbcnt > 10.0) {
        VCU10_DW.is_c10_VCU10 = VCU10_IN_judge;
        VCU10_B.res_hbcheck = 0.0;
      } else if (res_heartbeat_prev != VCU10_DW.res_heartbeat_start) {
        VCU10_DW.hbcnt = 0.0;
        VCU10_DW.is_c10_VCU10 = VCU10_IN_compare;
        VCU10_B.res_hbcheck = 1.0;
      } else {
        VCU10_DW.hbcnt++;
      }
      break;
    }
  }

  /* End of Chart: '<S273>/heaartbeat_chart' */

  /* Chart: '<S273>/xor_Check' incorporates:
   *  Inport: '<Root>/res_msg'
   *  S-Function (sfix_bitop): '<S269>/Bitwise AND5'
   */
  if (VCU10_DW.is_active_c19_VCU10 == 0U) {
    VCU10_DW.is_active_c19_VCU10 = 1U;
    VCU10_DW.is_c19_VCU10 = VCU10_IN_Init;
    VCU10_DW.err_cnt = 0.0;
  } else {
    switch (VCU10_DW.is_c19_VCU10) {
     case VCU10_IN_Init:
      if (res_msg[2] == rtb_xor_consequence) {
        VCU10_DW.is_c19_VCU10 = VCU10_IN_compare;
        VCU10_B.xorcheck = 1.0;
      }
      break;

     case VCU10_IN_compare:
      VCU10_B.xorcheck = 1.0;
      if (res_msg[2] != rtb_xor_consequence) {
        VCU10_DW.is_c19_VCU10 = VCU10_IN_different;
        VCU10_DW.err_cnt++;
      }
      break;

     case VCU10_IN_different:
      if (VCU10_DW.err_cnt >= 10.0) {
        VCU10_DW.is_c19_VCU10 = VCU10_IN_judge_c;
        VCU10_B.xorcheck = 0.0;
      } else if (res_msg[2] == rtb_xor_consequence) {
        VCU10_DW.err_cnt = 0.0;
        VCU10_DW.is_c19_VCU10 = VCU10_IN_compare;
        VCU10_B.xorcheck = 1.0;
      }
      break;

     default:
      /* case IN_judge: */
      VCU10_B.xorcheck = 0.0;
      if (res_msg[2] == rtb_xor_consequence) {
        VCU10_DW.err_cnt = 0.0;
        VCU10_DW.is_c19_VCU10 = VCU10_IN_compare;
        VCU10_B.xorcheck = 1.0;
      }
      break;
    }
  }

  /* End of Chart: '<S273>/xor_Check' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms10' */

  /* S-Function (fcgen): '<Root>/10ms11' incorporates:
   *  SubSystem: '<Root>/IPC'
   */
  /* Outputs for Atomic SubSystem: '<S169>/Bit Shift' */
  /* S-Function (sfix_bitop): '<S169>/Bitwise AND' incorporates:
   *  DataTypeConversion: '<S169>/Data Type Conversion1'
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  VCU10_BitShift_p((uint16_T)(canb_ipctsmsg1[1] & 3), &rtb_y_hf);

  /* End of Outputs for SubSystem: '<S169>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S169>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S169>/Bitwise AND1' incorporates:
   *  DataTypeConversion: '<S169>/Data Type Conversion1'
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  VCU10_BitShift1_j((uint16_T)(canb_ipctsmsg1[1] & 252), &rtb_y_mn);

  /* End of Outputs for SubSystem: '<S169>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S169>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S169>/Bitwise AND2' incorporates:
   *  DataTypeConversion: '<S169>/Data Type Conversion2'
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  VCU10_BitShift2_b((uint16_T)(canb_ipctsmsg1[2] & 15), &rtb_y_ej);

  /* End of Outputs for SubSystem: '<S169>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S169>/Bit Shift3' */
  /* S-Function (sfix_bitop): '<S169>/Bitwise AND3' incorporates:
   *  DataTypeConversion: '<S169>/Data Type Conversion2'
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  VCU10_BitShift3((uint16_T)(canb_ipctsmsg1[2] & 240), &rtb_y_mj);

  /* End of Outputs for SubSystem: '<S169>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S169>/Bit Shift4' */
  /* S-Function (sfix_bitop): '<S169>/Bitwise AND4' incorporates:
   *  DataTypeConversion: '<S169>/Data Type Conversion3'
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  VCU10_BitShift4((uint16_T)(canb_ipctsmsg1[3] & 63), &rtb_y_cq);

  /* End of Outputs for SubSystem: '<S169>/Bit Shift4' */

  /* Outputs for Atomic SubSystem: '<S169>/Bit Shift8' */
  /* DataTypeConversion: '<S169>/Data Type Conversion7' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  VCU10_BitShift8((real_T)canb_ipctsmsg1[7], &rtb_DataTypeConversion1);

  /* End of Outputs for SubSystem: '<S169>/Bit Shift8' */

  /* DataTypeConversion: '<S169>/Data Type Conversion8' incorporates:
   *  DataTypeConversion: '<S169>/Data Type Conversion4'
   *  Inport: '<Root>/canb_ipctsmsg1'
   *  Sum: '<S169>/Add'
   */
  rtb_y = (uint16_T)((uint32_T)canb_ipctsmsg1[0] + rtb_y_hf);

  /* Gain: '<S169>/Gain' */
  ipc_esp_flprs = rtb_y * 0.01;

  /* Gain: '<S169>/Gain1' incorporates:
   *  DataTypeConversion: '<S169>/Data Type Conversion9'
   *  Sum: '<S169>/Add1'
   */
  ipc_eps_frprs = (real_T)(uint16_T)((uint32_T)rtb_y_mn + rtb_y_ej) * 0.01;

  /* Gain: '<S169>/Gain2' incorporates:
   *  DataTypeConversion: '<S169>/Data Type Conversion10'
   *  Sum: '<S169>/Add2'
   */
  ipc_esp_rlprs = (real_T)(uint16_T)((uint32_T)rtb_y_mj + rtb_y_cq) * 0.01;

  /* Outputs for Atomic SubSystem: '<S169>/Bit Shift5' */
  /* Outputs for Atomic SubSystem: '<S169>/Bit Shift6' */
  /* Gain: '<S169>/Gain3' incorporates:
   *  DataTypeConversion: '<S169>/Data Type Conversion11'
   *  DataTypeConversion: '<S169>/Data Type Conversion3'
   *  DataTypeConversion: '<S169>/Data Type Conversion5'
   *  Inport: '<Root>/canb_ipctsmsg1'
   *  MATLAB Function: '<S176>/bit_shift'
   *  MATLAB Function: '<S177>/bit_shift'
   *  S-Function (sfix_bitop): '<S169>/Bitwise AND5'
   *  Sum: '<S169>/Add3'
   */
  ipc_esp_rrprs = (real_T)((int32_T)((uint32_T)(canb_ipctsmsg1[3] & 192) >> 6) +
    (canb_ipctsmsg1[4] << 2)) * 0.01;

  /* End of Outputs for SubSystem: '<S169>/Bit Shift6' */
  /* End of Outputs for SubSystem: '<S169>/Bit Shift5' */

  /* Outputs for Atomic SubSystem: '<S170>/Bit Shift' */
  /* DataTypeConversion: '<S170>/Data Type Conversion2' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S8>/canb_ipctsmsg2'
   */
  VCU10_BitShift8((real_T)canb_ipctsmsg2[0], &rtb_y);

  /* End of Outputs for SubSystem: '<S170>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S170>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S170>/Bitwise AND' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S8>/canb_ipctsmsg2'
   */
  VCU10_BitShift1_i((uint8_T)(canb_ipctsmsg2[3] & 128), &res_heartbeat_prev);

  /* End of Outputs for SubSystem: '<S170>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S170>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S170>/Bitwise AND1' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S8>/canb_ipctsmsg2'
   */
  VCU10_BitShift2_e((uint8_T)(canb_ipctsmsg2[3] & 64), &rtb_xor_consequence);

  /* End of Outputs for SubSystem: '<S170>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S170>/Bit Shift3' */
  /* S-Function (sfix_bitop): '<S170>/Bitwise AND2' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S8>/canb_ipctsmsg2'
   */
  VCU10_BitShift1((uint8_T)(canb_ipctsmsg2[3] & 60), &rtb_y_ch);

  /* End of Outputs for SubSystem: '<S170>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S170>/Bit Shift4' */
  /* DataTypeConversion: '<S170>/Data Type Conversion6' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S8>/canb_ipctsmsg2'
   */
  VCU10_BitShift_p((uint16_T)canb_ipctsmsg2[4], &rtb_y_hf);

  /* End of Outputs for SubSystem: '<S170>/Bit Shift4' */

  /* Outputs for Atomic SubSystem: '<S170>/Bit Shift5' */
  /* DataTypeConversion: '<S170>/Data Type Conversion8' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S8>/canb_ipctsmsg2'
   */
  VCU10_BitShift_p((uint16_T)canb_ipctsmsg2[6], &rtb_y_hf);

  /* End of Outputs for SubSystem: '<S170>/Bit Shift5' */

  /* Outputs for Atomic SubSystem: '<S164>/Bit Shift' */
  /* S-Function (fcgen): '<Root>/10ms10' incorporates:
   *  SubSystem: '<Root>/Res'
   */
  /* DataTypeConversion: '<S164>/Data Type Conversion2' incorporates:
   *  DataTypeConversion: '<S269>/Data Type Conversion3'
   *  S-Function (sfix_bitop): '<S164>/Bitwise AND1'
   */
  VCU10_BitShift_a((uint8_T)(rtb_y_cf != 0), &rtb_y_ch);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms10' */
  /* End of Outputs for SubSystem: '<S164>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S164>/Bit Shift1' */
  /* SignalConversion generated from: '<S8>/canb_ipcrxmsg' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read19'
   *  DataTypeConversion: '<S164>/Data Type Conversion1'
   *  DataTypeConversion: '<S164>/Data Type Conversion4'
   *  MATLAB Function: '<S166>/bit_shift'
   *  S-Function (sfix_bitop): '<S164>/Bitwise AND2'
   *  Sum: '<S164>/Add'
   */
  canb_ipcrxmsg[0] = (uint8_T)((uint32_T)(uint8_T)((uint32_T)
    VCU10_DW.steer_return + rtb_y_ch) + (res_stop << 2));

  /* End of Outputs for SubSystem: '<S164>/Bit Shift1' */

  /* DataTypeConversion: '<S164>/Data Type Conversion3' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read17'
   */
  tmp = floor(VCU10_DW.ipc_astask);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 256.0);
  }

  /* SignalConversion generated from: '<S8>/canb_ipcrxmsg' incorporates:
   *  DataTypeConversion: '<S164>/Data Type Conversion3'
   */
  canb_ipcrxmsg[1] = (uint8_T)(tmp < 0.0 ? (int32_T)(uint8_T)-(int8_T)(uint8_T)
    -tmp : (int32_T)(uint8_T)tmp);
  canb_ipcrxmsg[2] = ((uint8_T)0U);
  canb_ipcrxmsg[3] = ((uint8_T)0U);
  canb_ipcrxmsg[4] = ((uint8_T)0U);
  canb_ipcrxmsg[5] = ((uint8_T)0U);
  canb_ipcrxmsg[6] = ((uint8_T)0U);
  canb_ipcrxmsg[7] = ((uint8_T)0U);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */

  /* S-Function (fcgen): '<Root>/10ms6' incorporates:
   *  SubSystem: '<Root>/AS_Stateflow'
   */
  /* S-Function (fcgen): '<Root>/10ms' incorporates:
   *  SubSystem: '<Root>/Sensor_Signal'
   */
  /* DeadZone: '<S35>/Dead Zone' incorporates:
   *  DataTypeConversion: '<S14>/Data Type Conversion8'
   */
  if (rtb_Product1 > 0.5) {
    rtb_Product1 -= 0.5;
  } else if (rtb_Product1 >= -0.5) {
    rtb_Product1 = 0.0;
  } else {
    rtb_Product1 -= -0.5;
  }

  /* End of DeadZone: '<S35>/Dead Zone' */

  /* DeadZone: '<S35>/Dead Zone1' incorporates:
   *  DataTypeConversion: '<S14>/Data Type Conversion9'
   */
  if (rtb_Product2 > 0.5) {
    rtb_Product2 -= 0.5;
  } else if (rtb_Product2 >= -0.5) {
    rtb_Product2 = 0.0;
  } else {
    rtb_Product2 -= -0.5;
  }

  /* End of DeadZone: '<S35>/Dead Zone1' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */

  /* Logic: '<S35>/Logical Operator' incorporates:
   *  Constant: '<S37>/Constant'
   *  Constant: '<S38>/Constant'
   *  RelationalOperator: '<S37>/Compare'
   *  RelationalOperator: '<S38>/Compare'
   */
  LogicalOperator_o = ((rtb_Product1 == 0.0) && (rtb_Product2 == 0.0));

  /* Chart: '<S3>/Chart' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read16'
   *  DataStoreRead: '<Root>/Data Store Read4'
   *  DataStoreRead: '<Root>/Data Store Read6'
   *  DataStoreRead: '<Root>/Data Store Read8'
   *  DataTypeConversion: '<S269>/Data Type Conversion7'
   *  Logic: '<S3>/Logical Operator'
   */
  elapsedTicks_m = VCU10_M->Timing.clockTick0 - VCU10_DW.previousTicks_g;
  VCU10_DW.previousTicks_g = VCU10_M->Timing.clockTick0;
  if (VCU10_DW.temporalCounter_i1 + elapsedTicks_m <= 4095U) {
    VCU10_DW.temporalCounter_i1 = (uint16_T)(VCU10_DW.temporalCounter_i1 +
      elapsedTicks_m);
  } else {
    VCU10_DW.temporalCounter_i1 = 4095U;
  }

  if (VCU10_DW.is_active_c1_VCU10 == 0U) {
    VCU10_DW.is_active_c1_VCU10 = 1U;
    VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Off;
    VCU10_enter_atomic_AS_Off();
  } else {
    boolean_T guard2 = false;
    boolean_T guard3 = false;
    boolean_T guard4 = false;
    guard1 = false;
    guard2 = false;
    guard3 = false;
    guard4 = false;
    switch (VCU10_DW.is_c1_VCU10) {
     case VCU10_IN_AS_Driving:
      VCU10_AS_Driving(&LogicalOperator_o);
      break;

     case VCU10_IN_AS_Emergency:
      if ((!VCU10_DW.ebs_warning) && ((!asms) && (!VCU10_DW.brake_on))) {
        VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Off;
        VCU10_enter_atomic_AS_Off();
      } else {
        VCU10_B.r2d_flag_c = 0.0;
        VCU10_B.steering_flag_o = 0.0;
        VCU10_B.brake_flag_i = 0.0;
        VCU10_B.as_led_yellow = 0.0;
        VCU10_B.as_led_blue = 2.0;
        VCU10_B.as_off_flag_p = 0.0;
        VCU10_B.as_ready_flag_c = 0.0;
        VCU10_B.as_driving_flag_a = 0.0;
        VCU10_B.as_finished_flag_c = 0.0;
        VCU10_B.as_emergency_flag_e = 1.0;
        VCU10_B.manual_driving_flag_k = 0.0;
      }
      break;

     case VCU10_IN_AS_Finished:
      /* S-Function (fcgen): '<Root>/10ms10' incorporates:
       *  SubSystem: '<Root>/Res'
       */
      if (rtb_BitwiseAND_mj != 0) {
        VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Emergency;
        VCU10_enter_atomic_AS_Emergency();
      } else if ((!asms) && (!VCU10_DW.brake_on)) {
        VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Off;
        VCU10_enter_atomic_AS_Off();
      } else {
        VCU10_B.r2d_flag_c = 0.0;
        VCU10_B.steering_flag_o = 0.0;
        VCU10_B.brake_flag_i = 0.0;
        VCU10_B.as_led_yellow = 0.0;
        VCU10_B.as_led_blue = 1.0;
        VCU10_B.as_off_flag_p = 0.0;
        VCU10_B.as_ready_flag_c = 0.0;
        VCU10_B.as_driving_flag_a = 0.0;
        VCU10_B.as_finished_flag_c = 1.0;
        VCU10_B.as_emergency_flag_e = 0.0;
        VCU10_B.manual_driving_flag_k = 0.0;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms10' */
      break;

     case VCU10_IN_AS_Off:
      if (!asms) {
        if ((!VCU10_DW.ebs_check) && (VCU10_DW.ts == 1.0)) {
          VCU10_DW.is_c1_VCU10 = VCU10_IN_Manual_Driving_n;
          VCU10_B.r2d_flag_c = 0.0;
          VCU10_B.steering_flag_o = 0.0;
          VCU10_B.brake_flag_i = 0.0;
          VCU10_B.as_led_yellow = 0.0;
          VCU10_B.as_led_blue = 0.0;
          VCU10_B.as_off_flag_p = 0.0;
          VCU10_B.as_ready_flag_c = 0.0;
          VCU10_B.as_driving_flag_a = 0.0;
          VCU10_B.as_finished_flag_c = 0.0;
          VCU10_B.as_emergency_flag_e = 0.0;
          VCU10_B.manual_driving_flag_k = 1.0;
        } else {
          VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Off;
          VCU10_enter_atomic_AS_Off();
        }
      } else if (VCU10_DW.astask_flag && asms) {
        VCU10_B.brake_flag_i = 2.0;
        VCU10_DW.is_c1_VCU10 = VCU10_IN_transition;
      } else {
        VCU10_B.r2d_flag_c = 0.0;
        VCU10_B.steering_flag_o = 0.0;
        VCU10_B.brake_flag_i = 0.0;
        VCU10_B.as_led_yellow = 0.0;
        VCU10_B.as_led_blue = 0.0;
        VCU10_B.as_off_flag_p = 1.0;
        VCU10_B.as_ready_flag_c = 0.0;
        VCU10_B.as_driving_flag_a = 0.0;
        VCU10_B.as_finished_flag_c = 0.0;
        VCU10_B.as_emergency_flag_e = 0.0;
        VCU10_B.manual_driving_flag_k = 0.0;
      }
      break;

     case VCU10_IN_AS_Ready:
      if (VCU10_DW.ebs_working) {
        guard3 = true;
      } else if (VCU10_DW.temporalCounter_i1 >= 500U) {
        if (VCU10_DW.ebs_working) {
          guard3 = true;
        } else if (rtb_y_cf != 0) {
          VCU10_B.r2d_warning = T;
          VCU10_B.steer_return = T;
          VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Driving;
          VCU10_DW.temporalCounter_i1 = 0U;
          VCU10_DW.is_AS_Driving = VCU10_IN_R2D;
          VCU10_B.r2d_flag_c = 1.0;
          VCU10_B.as_ready_flag_c = 0.0;
          VCU10_B.as_driving_flag_a = 1.0;
        } else {
          guard2 = true;
        }
      } else {
        guard2 = true;
      }
      break;

     case VCU10_IN_Manual_Driving_n:
      if (VCU10_DW.ts == 0.0) {
        VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Off;
        VCU10_enter_atomic_AS_Off();
      } else {
        VCU10_B.r2d_flag_c = 0.0;
        VCU10_B.steering_flag_o = 0.0;
        VCU10_B.brake_flag_i = 0.0;
        VCU10_B.as_led_yellow = 0.0;
        VCU10_B.as_led_blue = 0.0;
        VCU10_B.as_off_flag_p = 0.0;
        VCU10_B.as_ready_flag_c = 0.0;
        VCU10_B.as_driving_flag_a = 0.0;
        VCU10_B.as_finished_flag_c = 0.0;
        VCU10_B.as_emergency_flag_e = 0.0;
        VCU10_B.manual_driving_flag_k = 1.0;
      }
      break;

     default:
      /* case IN_transition: */
      if (VCU10_DW.ts == 1.0) {
        if (VCU10_DW.ebs_working) {
          guard1 = true;
        } else if (VCU10_DW.asb_check) {
          VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Ready;
          VCU10_DW.temporalCounter_i1 = 0U;
          VCU10_B.r2d_flag_c = 0.0;
          VCU10_B.steering_flag_o = 1.0;
          VCU10_B.brake_flag_i = 2.0;
          VCU10_B.as_led_yellow = 1.0;
          VCU10_B.as_led_blue = 0.0;
          VCU10_B.as_off_flag_p = 0.0;
          VCU10_B.as_ready_flag_c = 1.0;
          VCU10_B.as_driving_flag_a = 0.0;
          VCU10_B.as_finished_flag_c = 0.0;
          VCU10_B.as_emergency_flag_e = 0.0;
          VCU10_B.manual_driving_flag_k = 0.0;
        } else {
          guard4 = true;
        }
      } else {
        guard4 = true;
      }
      break;
    }

    if (guard4) {
      if (VCU10_DW.ebs_working) {
        guard1 = true;
      }
    }

    if (guard3) {
      VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Emergency;
      VCU10_enter_atomic_AS_Emergency();
    }

    if (guard2) {
      VCU10_B.r2d_flag_c = 0.0;
      VCU10_B.steering_flag_o = 1.0;
      VCU10_B.brake_flag_i = 2.0;
      VCU10_B.as_led_yellow = 1.0;
      VCU10_B.as_led_blue = 0.0;
      VCU10_B.as_off_flag_p = 0.0;
      VCU10_B.as_ready_flag_c = 1.0;
      VCU10_B.as_driving_flag_a = 0.0;
      VCU10_B.as_finished_flag_c = 0.0;
      VCU10_B.as_emergency_flag_e = 0.0;
      VCU10_B.manual_driving_flag_k = 0.0;
    }

    if (guard1) {
      VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Emergency;
      VCU10_enter_atomic_AS_Emergency();
    }
  }

  /* End of Chart: '<S3>/Chart' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */

  /* S-Function (fcgen): '<Root>/10ms8' incorporates:
   *  SubSystem: '<Root>/ESP'
   */
  /* Chart: '<S146>/ESP_Chart1' incorporates:
   *  DataStoreWrite: '<S3>/Data Store Write1'
   */
  if (VCU10_DW.is_active_c16_VCU10 == 0U) {
    VCU10_DW.is_active_c16_VCU10 = 1U;
    VCU10_DW.is_c16_VCU10 = VCU10_IN_ESC_Unable;
    VCU10_B.mode = 0.0;
  } else {
    switch (VCU10_DW.is_c16_VCU10) {
     case VCU10_IN_ESC_Able:
      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (VCU10_B.brake_flag_i == 0.0) {
        VCU10_DW.is_c16_VCU10 = VCU10_IN_ESC_Unable;
        VCU10_B.mode = 0.0;
      } else {
        VCU10_B.mode = 1.0;
        VCU10_B.tarPrsReqFL = ipc_esp_flprs;
        VCU10_B.tarPrsReqFR = ipc_eps_frprs;
        VCU10_B.tarPrsReqRL = ipc_esp_rlprs;
        VCU10_B.tarPrsReqRR = ipc_esp_rrprs;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case VCU10_IN_ESC_Engage:
      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (VCU10_B.brake_flag_i == 1.0) {
        VCU10_DW.is_c16_VCU10 = VCU10_IN_ESC_Able;
        VCU10_B.mode = 1.0;
        VCU10_B.tarPrsReqFL = ipc_esp_flprs;
        VCU10_B.tarPrsReqFR = ipc_eps_frprs;
        VCU10_B.tarPrsReqRL = ipc_esp_rlprs;
        VCU10_B.tarPrsReqRR = ipc_esp_rrprs;
      } else {
        VCU10_B.mode = 1.0;
        VCU10_B.tarPrsReqFL = ipc_esp_flprs;
        VCU10_B.tarPrsReqFR = ipc_eps_frprs;
        VCU10_B.tarPrsReqRL = ipc_esp_rlprs;
        VCU10_B.tarPrsReqRR = ipc_esp_rrprs;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     default:
      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      /* case IN_ESC_Unable: */
      if (VCU10_B.brake_flag_i == 2.0) {
        VCU10_DW.is_c16_VCU10 = VCU10_IN_ESC_Engage;
        VCU10_B.mode = 1.0;
        VCU10_B.tarPrsReqFL = ipc_esp_flprs;
        VCU10_B.tarPrsReqFR = ipc_eps_frprs;
        VCU10_B.tarPrsReqRL = ipc_esp_rlprs;
        VCU10_B.tarPrsReqRR = ipc_esp_rrprs;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;
    }
  }

  /* End of Chart: '<S146>/ESP_Chart1' */

  /* DataTypeConversion: '<S146>/Data Type Conversion5' incorporates:
   *  Gain: '<S146>/Gain'
   */
  tmp = floor(100.0 * VCU10_B.tarPrsReqFL);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 65536.0);
  }

  rtb_y_hf = (uint16_T)(tmp < 0.0 ? (int32_T)(uint16_T)-(int16_T)(uint16_T)-tmp :
                        (int32_T)(uint16_T)tmp);

  /* End of DataTypeConversion: '<S146>/Data Type Conversion5' */

  /* Outputs for Atomic SubSystem: '<S146>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S146>/Bitwise AND1' */
  VCU10_BitShift6((uint16_T)(rtb_y_hf & 15), &rtb_y_mn);

  /* End of Outputs for SubSystem: '<S146>/Bit Shift1' */

  /* DataTypeConversion: '<S146>/Data Type Conversion8' incorporates:
   *  Gain: '<S146>/Gain1'
   */
  tmp = floor(100.0 * VCU10_B.tarPrsReqFR);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 65536.0);
  }

  rtb_y_ej = (uint16_T)(tmp < 0.0 ? (int32_T)(uint16_T)-(int16_T)(uint16_T)-tmp :
                        (int32_T)(uint16_T)tmp);

  /* End of DataTypeConversion: '<S146>/Data Type Conversion8' */

  /* Outputs for Atomic SubSystem: '<S146>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S146>/Bitwise AND2' */
  VCU10_BitShift5((uint16_T)(rtb_y_ej & 3840), &rtb_y_mj);

  /* End of Outputs for SubSystem: '<S146>/Bit Shift2' */

  /* Sum: '<S146>/Add' */
  rtb_y_cq = (uint16_T)((uint32_T)rtb_y_mn + rtb_y_mj);

  /* DataTypeConversion: '<S146>/Data Type Conversion9' incorporates:
   *  Gain: '<S146>/Gain2'
   */
  tmp = floor(100.0 * VCU10_B.tarPrsReqRL);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 65536.0);
  }

  rtb_Add2_g = (uint16_T)(tmp < 0.0 ? (int32_T)(uint16_T)-(int16_T)(uint16_T)
    -tmp : (int32_T)(uint16_T)tmp);

  /* End of DataTypeConversion: '<S146>/Data Type Conversion9' */

  /* Outputs for Atomic SubSystem: '<S146>/Bit Shift4' */
  /* S-Function (sfix_bitop): '<S146>/Bitwise AND5' */
  VCU10_BitShift6((uint16_T)(rtb_Add2_g & 15), &rtb_y_mj);

  /* End of Outputs for SubSystem: '<S146>/Bit Shift4' */

  /* DataTypeConversion: '<S146>/Data Type Conversion10' incorporates:
   *  Gain: '<S146>/Gain3'
   */
  tmp = floor(100.0 * VCU10_B.tarPrsReqRR);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 65536.0);
  }

  rtb_Add1_a = (uint16_T)(tmp < 0.0 ? (int32_T)(uint16_T)-(int16_T)(uint16_T)
    -tmp : (int32_T)(uint16_T)tmp);

  /* End of DataTypeConversion: '<S146>/Data Type Conversion10' */

  /* Outputs for Atomic SubSystem: '<S146>/Bit Shift5' */
  /* S-Function (sfix_bitop): '<S146>/Bitwise AND6' */
  VCU10_BitShift5((uint16_T)(rtb_Add1_a & 3840), &rtb_y_mn);

  /* End of Outputs for SubSystem: '<S146>/Bit Shift5' */

  /* Sum: '<S146>/Add1' */
  rtb_y_mn = (uint16_T)((uint32_T)rtb_y_mj + rtb_y_mn);

  /* DataTypeConversion: '<S146>/Data Type Conversion11' */
  tmp = floor(VCU10_B.mode);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 256.0);
  }

  rtb_BitwiseAND_mj = (uint8_T)(tmp < 0.0 ? (int32_T)(uint8_T)-(int8_T)(uint8_T)
    -tmp : (int32_T)(uint8_T)tmp);

  /* End of DataTypeConversion: '<S146>/Data Type Conversion11' */

  /* Outputs for Atomic SubSystem: '<S146>/Bit Shift6' */
  /* S-Function (sfix_bitop): '<S146>/Bitwise AND9' */
  VCU10_BitShift3_m((uint8_T)(rtb_BitwiseAND_mj & 3), &rtb_BitwiseAND_mj);

  /* End of Outputs for SubSystem: '<S146>/Bit Shift6' */

  /* Outputs for Atomic SubSystem: '<S146>/Bit Shift' */
  /* S-Function (sfix_bitop): '<S146>/Bitwise AND' */
  VCU10_BitShift7((uint16_T)(rtb_y_hf & 4080), &rtb_y_hf);

  /* End of Outputs for SubSystem: '<S146>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S146>/Bit Shift3' */
  /* S-Function (sfix_bitop): '<S146>/Bitwise AND4' */
  VCU10_BitShift7((uint16_T)(rtb_Add2_g & 4080), &rtb_y_mj);

  /* End of Outputs for SubSystem: '<S146>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND12' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift1((uint8_T)(ESP_T_01[3] & 252), &rtb_y_cf);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift10' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND3' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift10((uint8_T)(ESP_T_01[0] & 4), &rtb_y_cf);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift10' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift11' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND4' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift2((uint8_T)(ESP_T_01[0] & 5), &rtb_y_cf);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift11' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift13' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND6' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift2_e((uint8_T)(ESP_T_01[0] & 7), &rtb_y_cf);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift13' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift14' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND7' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift1_i((uint8_T)(ESP_T_01[0] & 8), &rtb_y_cf);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift14' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift15' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND10' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift((uint8_T)(ESP_T_01[2] & 254), &rtb_y_cf);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift15' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift16' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND9' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift1_i((uint8_T)(ESP_T_01[1] & 128), &rtb_y_cf);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift16' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift3' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND14' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift10((uint8_T)(ESP_T_01[4] & 248), &rtb_y_cf);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift4' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND15' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift4_h((uint8_T)(ESP_T_01[4] & 7), &rtb_y_cf);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift4' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift5' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND16' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift2((uint8_T)(ESP_T_01[5] & 240), &rtb_y_cf);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift5' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift6' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND17' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift4_h((uint8_T)(ESP_T_01[5] & 15), &rtb_y_cf);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift6' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift7' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND18' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift2((uint8_T)(ESP_T_01[6] & 240), &rtb_y_cf);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift7' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift8' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND1' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift((uint8_T)(ESP_T_01[0] & 2), &rtb_y_cf);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift8' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift9' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND2' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift1((uint8_T)(ESP_T_01[0] & 3), &rtb_y_cf);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift9' */

  /* Outputs for Atomic SubSystem: '<S65>/Bit Shift' */
  /* DataTypeConversion: '<S65>/Data Type Conversion1' incorporates:
   *  Inport: '<Root>/ESP_T_03'
   */
  VCU10_BitShift4((uint16_T)ESP_T_03[0], &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S65>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S65>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S65>/Bitwise AND1' incorporates:
   *  DataTypeConversion: '<S65>/Data Type Conversion3'
   *  Inport: '<Root>/ESP_T_03'
   */
  VCU10_BitShift3((uint16_T)(ESP_T_03[1] & 240), &rtb_y_em);

  /* End of Outputs for SubSystem: '<S65>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S65>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S65>/Bitwise AND2' incorporates:
   *  DataTypeConversion: '<S65>/Data Type Conversion4'
   *  Inport: '<Root>/ESP_T_03'
   */
  VCU10_BitShift_p((uint16_T)(ESP_T_03[1] & 15), &rtb_y_fb);

  /* End of Outputs for SubSystem: '<S65>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S65>/Bit Shift3' */
  /* DataTypeConversion: '<S65>/Data Type Conversion6' incorporates:
   *  Inport: '<Root>/ESP_T_03'
   */
  VCU10_BitShift4((uint16_T)ESP_T_03[3], &rtb_y_md);

  /* End of Outputs for SubSystem: '<S65>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S65>/Bit Shift4' */
  /* S-Function (sfix_bitop): '<S65>/Bitwise AND5' incorporates:
   *  DataTypeConversion: '<S65>/Data Type Conversion7'
   *  Inport: '<Root>/ESP_T_03'
   */
  VCU10_BitShift3((uint16_T)(ESP_T_03[4] & 240), &rtb_y_ns);

  /* End of Outputs for SubSystem: '<S65>/Bit Shift4' */

  /* Outputs for Atomic SubSystem: '<S65>/Bit Shift5' */
  /* S-Function (sfix_bitop): '<S65>/Bitwise AND6' incorporates:
   *  DataTypeConversion: '<S65>/Data Type Conversion8'
   *  Inport: '<Root>/ESP_T_03'
   */
  VCU10_BitShift_p((uint16_T)(ESP_T_03[4] & 15), &rtb_y_as);

  /* End of Outputs for SubSystem: '<S65>/Bit Shift5' */

  /* Gain: '<S65>/Gain' incorporates:
   *  DataTypeConversion: '<S65>/Data Type Conversion2'
   *  Sum: '<S65>/Add'
   */
  rtb_Product1 = (real_T)(uint16_T)((uint32_T)rtb_Add2_g + rtb_y_em) * 0.01;

  /* Gain: '<S65>/Gain1' incorporates:
   *  DataTypeConversion: '<S65>/Data Type Conversion12'
   *  DataTypeConversion: '<S65>/Data Type Conversion9'
   *  Inport: '<Root>/ESP_T_03'
   *  Sum: '<S65>/Add3'
   */
  rtb_Product2 = (real_T)(uint16_T)((uint32_T)rtb_y_as + ESP_T_03[5]) * 0.01;

  /* Gain: '<S65>/Gain2' incorporates:
   *  DataTypeConversion: '<S65>/Data Type Conversion10'
   *  DataTypeConversion: '<S65>/Data Type Conversion5'
   *  Inport: '<Root>/ESP_T_03'
   *  Sum: '<S65>/Add1'
   */
  ipc_esp_flprs = (real_T)(uint16_T)((uint32_T)rtb_y_fb + ESP_T_03[2]) * 0.01;

  /* Gain: '<S65>/Gain3' incorporates:
   *  DataTypeConversion: '<S65>/Data Type Conversion11'
   *  Sum: '<S65>/Add2'
   */
  ipc_eps_frprs = (real_T)(uint16_T)((uint32_T)rtb_y_md + rtb_y_ns) * 0.01;

  /* Chart: '<S68>/brkmotor_check_system' incorporates:
   *  Inport: '<Root>/ESP_T_03'
   *  S-Function (sfix_bitop): '<S65>/LifeSig Mask'
   */
  rtb_y_cf = VCU10_DW.lifesig_start;
  VCU10_DW.lifesig_start = (uint8_T)(ESP_T_03[6] & 15);
  if (VCU10_DW.is_active_c18_VCU10 == 0U) {
    VCU10_DW.is_active_c18_VCU10 = 1U;
    VCU10_DW.is_c18_VCU10 = VCU10_IN_begin_f;
  } else {
    switch (VCU10_DW.is_c18_VCU10) {
     case VCU10_IN_begin_f:
      if (rtb_y_cf != VCU10_DW.lifesig_start) {
        VCU10_DW.is_c18_VCU10 = VCU10_IN_compare;
        VCU10_B.brkmotor_check = T;
      }
      break;

     case VCU10_IN_compare:
      if (rtb_y_cf == VCU10_DW.lifesig_start) {
        VCU10_DW.is_c18_VCU10 = VCU10_IN_same;
        VCU10_DW.lscnt++;
      } else {
        VCU10_B.brkmotor_check = T;
      }
      break;

     case VCU10_IN_judge:
      if (rtb_y_cf != VCU10_DW.lifesig_start) {
        VCU10_DW.is_c18_VCU10 = VCU10_IN_compare;
        VCU10_B.brkmotor_check = T;
      } else {
        VCU10_B.brkmotor_check = F;
      }
      break;

     default:
      /* case IN_same: */
      if (VCU10_DW.lscnt > 10.0) {
        VCU10_DW.is_c18_VCU10 = VCU10_IN_judge;
        VCU10_B.brkmotor_check = F;
      } else if (rtb_y_cf != VCU10_DW.lifesig_start) {
        VCU10_DW.lscnt = 0.0;
        VCU10_DW.is_c18_VCU10 = VCU10_IN_compare;
        VCU10_B.brkmotor_check = T;
      } else {
        VCU10_DW.lscnt++;
      }
      break;
    }
  }

  /* End of Chart: '<S68>/brkmotor_check_system' */

  /* Outputs for Atomic SubSystem: '<S66>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S66>/Bitwise AND2' incorporates:
   *  DataTypeConversion: '<S66>/Data Type Conversion3'
   *  Inport: '<Root>/ESP_T_06'
   */
  VCU10_BitShift2_b((uint16_T)(ESP_T_06[1] & 31), &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S66>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S66>/Bit Shift3' */
  /* S-Function (sfix_bitop): '<S66>/Bitwise AND3' incorporates:
   *  DataTypeConversion: '<S66>/Data Type Conversion4'
   *  Inport: '<Root>/ESP_T_06'
   */
  VCU10_BitShift1_j((uint16_T)(ESP_T_06[2] & 252), &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S66>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S66>/Bit Shift7' */
  /* S-Function (sfix_bitop): '<S66>/Bitwise AND7' incorporates:
   *  DataTypeConversion: '<S66>/Data Type Conversion8'
   *  Inport: '<Root>/ESP_T_06'
   */
  VCU10_BitShift4((uint16_T)(ESP_T_06[4] & 127), &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S66>/Bit Shift7' */

  /* Outputs for Atomic SubSystem: '<S66>/Bit Shift8' */
  /* S-Function (sfix_bitop): '<S66>/Bitwise AND8' incorporates:
   *  DataTypeConversion: '<S66>/Data Type Conversion9'
   *  Inport: '<Root>/ESP_T_06'
   */
  VCU10_BitShift3((uint16_T)(ESP_T_06[5] & 240), &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S66>/Bit Shift8' */

  /* Outputs for Atomic SubSystem: '<S67>/Bit Shift' */
  /* DataTypeConversion: '<S67>/Data Type Conversion2' incorporates:
   *  Inport: '<Root>/ESP_T_07'
   */
  VCU10_BitShift4((uint16_T)ESP_T_07[0], &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S67>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S67>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S67>/Bitwise AND1' incorporates:
   *  DataTypeConversion: '<S67>/Data Type Conversion1'
   *  Inport: '<Root>/ESP_T_07'
   */
  VCU10_BitShift3((uint16_T)(ESP_T_07[1] & 240), &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S67>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S67>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S67>/Bitwise AND2' incorporates:
   *  DataTypeConversion: '<S67>/Data Type Conversion3'
   *  Inport: '<Root>/ESP_T_07'
   */
  VCU10_BitShift_p((uint16_T)(ESP_T_07[1] & 15), &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S67>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S67>/Bit Shift3' */
  /* DataTypeConversion: '<S67>/Data Type Conversion5' incorporates:
   *  Inport: '<Root>/ESP_T_07'
   */
  VCU10_BitShift4((uint16_T)ESP_T_07[3], &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S67>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S67>/Bit Shift4' */
  /* S-Function (sfix_bitop): '<S67>/Bitwise AND5' incorporates:
   *  DataTypeConversion: '<S67>/Data Type Conversion6'
   *  Inport: '<Root>/ESP_T_07'
   */
  VCU10_BitShift3((uint16_T)(ESP_T_07[4] & 240), &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S67>/Bit Shift4' */

  /* Outputs for Atomic SubSystem: '<S67>/Bit Shift5' */
  /* S-Function (sfix_bitop): '<S67>/Bitwise AND6' incorporates:
   *  DataTypeConversion: '<S67>/Data Type Conversion7'
   *  Inport: '<Root>/ESP_T_07'
   */
  VCU10_BitShift_p((uint16_T)(ESP_T_07[4] & 15), &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S67>/Bit Shift5' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms8' */

  /* S-Function (fcgen): '<Root>/10ms3' incorporates:
   *  SubSystem: '<Root>/ASB_Selfcheck'
   */
  /* S-Function (fcgen): '<Root>/10ms10' incorporates:
   *  SubSystem: '<Root>/Res'
   */
  /* DataStoreWrite: '<Root>/Data Store Write' incorporates:
   *  Constant: '<S26>/Constant'
   *  Constant: '<S27>/Constant'
   *  Constant: '<S28>/Constant'
   *  Constant: '<S29>/Constant'
   *  Constant: '<S30>/Constant'
   *  DataStoreRead: '<Root>/Data Store Read'
   *  DataTypeConversion: '<S269>/Data Type Conversion2'
   *  Logic: '<S25>/Logical Operator'
   *  Logic: '<S273>/Logical Operator'
   *  Logic: '<S2>/Logical Operator'
   *  RelationalOperator: '<S26>/Compare'
   *  RelationalOperator: '<S27>/Compare'
   *  RelationalOperator: '<S28>/Compare'
   *  RelationalOperator: '<S29>/Compare'
   *  RelationalOperator: '<S30>/Compare'
   */
  VCU10_DW.asb_check = (ebs_driver_check && ((rtb_y_hw != 0) &&
    (VCU10_B.res_hbcheck != 0.0) && (VCU10_B.xorcheck != 0.0)) &&
                        ((airprs_sensor1 >= 3.5) && (rtb_Product1 >= 0.848) &&
    (ipc_esp_flprs >= 0.848) && (ipc_eps_frprs >= 0.742) && (rtb_Product2 >=
    0.742)) && VCU10_DW.brkmotor_check);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms10' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms3' */

  /* S-Function (fcgen): '<Root>/10ms7' incorporates:
   *  SubSystem: '<Root>/EBS'
   */
  /* Outputs for Enabled SubSystem: '<S44>/POSITIVE Edge' */
  /* DataStoreRead: '<Root>/Data Store Read1' incorporates:
   *  UnitDelay: '<S44>/Unit Delay'
   */
  VCU10_POSITIVEEdge(VCU10_ConstB.MultiportSwitch[0], VCU10_DW.asb_check,
                     VCU10_DW.UnitDelay_DSTATE, &VCU10_B.RelationalOperator1_no);

  /* End of Outputs for SubSystem: '<S44>/POSITIVE Edge' */

  /* Outputs for Enabled SubSystem: '<S44>/NEGATIVE Edge' */
  VCU10_NEGATIVEEdge(VCU10_ConstB.MultiportSwitch[1], VCU10_DW.asb_check,
                     VCU10_DW.UnitDelay_DSTATE, &VCU10_B.RelationalOperator1_k);

  /* End of Outputs for SubSystem: '<S44>/NEGATIVE Edge' */

  /* Outputs for Enabled SubSystem: '<S47>/POSITIVE Edge' */
  /* S-Function (fcgen): '<Root>/10ms11' incorporates:
   *  SubSystem: '<Root>/IPC'
   */
  /* DataTypeConversion: '<S170>/Data Type Conversion3' incorporates:
   *  UnitDelay: '<S47>/Unit Delay'
   */
  VCU10_POSITIVEEdge(VCU10_ConstB.MultiportSwitch_e[0], res_heartbeat_prev != 0,
                     VCU10_DW.UnitDelay_DSTATE_e, &VCU10_B.RelationalOperator1);

  /* End of Outputs for SubSystem: '<S47>/POSITIVE Edge' */

  /* Outputs for Enabled SubSystem: '<S47>/NEGATIVE Edge' */
  VCU10_NEGATIVEEdge(VCU10_ConstB.MultiportSwitch_e[1], res_heartbeat_prev != 0,
                     VCU10_DW.UnitDelay_DSTATE_e, &VCU10_B.RelationalOperator1_n);

  /* End of Outputs for SubSystem: '<S47>/NEGATIVE Edge' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */

  /* Logic: '<S5>/Logical Operator' incorporates:
   *  Logic: '<S44>/Logical Operator1'
   *  Logic: '<S47>/Logical Operator1'
   */
  ebs_trig = (VCU10_B.RelationalOperator1_no || VCU10_B.RelationalOperator1_k ||
              (VCU10_B.RelationalOperator1 || VCU10_B.RelationalOperator1_n) ||
              (VCU10_B.as_ebs_trig != 0.0));

  /* SignalConversion generated from: '<S5>/ebs_watchdog' */
  ebs_watchdog = asms;

  /* Logic: '<S5>/Logical Operator1' incorporates:
   *  Constant: '<S40>/Constant'
   *  RelationalOperator: '<S40>/Compare'
   */
  VCU10_DW.ebs_working = (ebs_driver_check && (airprs_sensor1 >= 6.0));

  /* Update for UnitDelay: '<S44>/Unit Delay' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read1'
   */
  VCU10_DW.UnitDelay_DSTATE = VCU10_DW.asb_check;

  /* S-Function (fcgen): '<Root>/10ms11' incorporates:
   *  SubSystem: '<Root>/IPC'
   */
  /* Update for UnitDelay: '<S47>/Unit Delay' incorporates:
   *  DataTypeConversion: '<S170>/Data Type Conversion3'
   */
  VCU10_DW.UnitDelay_DSTATE_e = (res_heartbeat_prev != 0);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms7' */

  /* S-Function (fcgen): '<Root>/10ms13' incorporates:
   *  SubSystem: '<Root>/AMI_CAN'
   */
  /* Chart: '<S17>/Chart' incorporates:
   *  DataStoreWrite: '<S3>/Data Store Write10'
   *  DataStoreWrite: '<S3>/Data Store Write2'
   *  DataStoreWrite: '<S3>/Data Store Write3'
   *  DataStoreWrite: '<S3>/Data Store Write6'
   *  DataStoreWrite: '<S3>/Data Store Write7'
   *  DataStoreWrite: '<S3>/Data Store Write8'
   *  DataStoreWrite: '<S3>/Data Store Write9'
   */
  if (VCU10_DW.is_active_c20_VCU10 == 0U) {
    VCU10_DW.is_active_c20_VCU10 = 1U;
    VCU10_DW.is_c20_VCU10 = VCU10_IN_begin_g;
  } else {
    switch (VCU10_DW.is_c20_VCU10) {
     case VCU10_IN_as_driving:
      VCU10_B.ami_process = 16U;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (VCU10_B.as_driving_flag_a != 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_begin_g;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case VCU10_IN_as_emergency:
      VCU10_B.ami_process = 64U;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (VCU10_B.as_emergency_flag_e != 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_begin_g;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case VCU10_IN_as_finished:
      VCU10_B.ami_process = 32U;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (VCU10_B.as_finished_flag_c != 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_begin_g;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case VCU10_IN_as_off:
      VCU10_B.ami_process = 1U;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (VCU10_B.as_off_flag_p != 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_begin_g;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case VCU10_IN_as_ready:
      VCU10_B.ami_process = 4U;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (VCU10_B.as_ready_flag_c != 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_begin_g;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case VCU10_IN_begin_g:
      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (VCU10_B.as_off_flag_p == 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_as_off;
        VCU10_B.ami_process = 1U;
      } else if (VCU10_B.manual_driving_flag_k == 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_munual_driving;
        VCU10_B.ami_process = 2U;
      } else if (VCU10_B.as_ready_flag_c == 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_as_ready;
        VCU10_B.ami_process = 4U;
      } else if (VCU10_B.r2d_flag_c == 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_r2d;
        VCU10_B.ami_process = 8U;
      } else if (VCU10_B.as_driving_flag_a == 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_as_driving;
        VCU10_B.ami_process = 16U;
      } else if (VCU10_B.as_finished_flag_c == 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_as_finished;
        VCU10_B.ami_process = 32U;
      } else if (VCU10_B.as_emergency_flag_e == 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_as_emergency;
        VCU10_B.ami_process = 64U;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case VCU10_IN_munual_driving:
      VCU10_B.ami_process = 2U;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (VCU10_B.manual_driving_flag_k != 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_begin_g;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     default:
      /* case IN_r2d: */
      VCU10_B.ami_process = 8U;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (VCU10_B.r2d_flag_c != 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_begin_g;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;
    }
  }

  /* End of Chart: '<S17>/Chart' */

  /* Outputs for Atomic SubSystem: '<S17>/Bit Shift' */
  /* S-Function (sfix_bitop): '<S17>/Bitwise AND' */
  VCU10_BitShift_a((uint8_T)(VCU10_B.ami_process & 127), &res_heartbeat_prev);

  /* End of Outputs for SubSystem: '<S17>/Bit Shift' */

  /* SignalConversion: '<S17>/Signal Conversion' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read12'
   *  Sum: '<S17>/Add1'
   */
  AMI_Rx[0] = (uint8_T)((uint32_T)res_heartbeat_prev + VCU10_DW.task_finish);
  AMI_Rx[1] = ((uint8_T)0U);
  AMI_Rx[2] = ((uint8_T)0U);
  AMI_Rx[3] = ((uint8_T)0U);
  AMI_Rx[4] = ((uint8_T)0U);
  AMI_Rx[5] = ((uint8_T)0U);
  AMI_Rx[6] = ((uint8_T)0U);
  AMI_Rx[7] = ((uint8_T)0U);

  /* Outputs for Atomic SubSystem: '<S16>/Bit Shift' */
  /* S-Function (sfix_bitop): '<S16>/Bitwise AND' incorporates:
   *  Inport: '<Root>/AMI_Tx'
   */
  VCU10_BitShift2((uint8_T)(AMI_Tx[0] & 240), &res_heartbeat_prev);

  /* End of Outputs for SubSystem: '<S16>/Bit Shift' */

  /* DataStoreWrite: '<Root>/Data Store Write10' incorporates:
   *  Constant: '<S18>/Constant'
   *  RelationalOperator: '<S18>/Compare'
   */
  VCU10_DW.inspection_flag = (res_heartbeat_prev == 5);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms13' */

  /* S-Function (fcgen): '<Root>/10ms11' incorporates:
   *  SubSystem: '<Root>/IPC'
   */
  /* DataStoreWrite: '<Root>/Data Store Write11' incorporates:
   *  DataTypeConversion: '<S170>/Data Type Conversion4'
   */
  VCU10_DW.task_finish = (rtb_xor_consequence != 0);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */

  /* S-Function (fcgen): '<Root>/10ms13' incorporates:
   *  SubSystem: '<Root>/AMI_CAN'
   */
  /* DataStoreWrite: '<Root>/Data Store Write13' incorporates:
   *  Constant: '<S19>/Constant'
   *  RelationalOperator: '<S19>/Compare'
   */
  VCU10_DW.astask_flag = (res_heartbeat_prev > 0);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms13' */

  /* S-Function (fcgen): '<Root>/10ms3' incorporates:
   *  SubSystem: '<Root>/ASB_Selfcheck'
   */
  /* DataStoreWrite: '<Root>/Data Store Write2' incorporates:
   *  Constant: '<S31>/Constant'
   *  Constant: '<S32>/Constant'
   *  Constant: '<S33>/Constant'
   *  Constant: '<S34>/Constant'
   *  Logic: '<S25>/Logical Operator1'
   *  RelationalOperator: '<S31>/Compare'
   *  RelationalOperator: '<S32>/Compare'
   *  RelationalOperator: '<S33>/Compare'
   *  RelationalOperator: '<S34>/Compare'
   */
  VCU10_DW.brake_on = ((rtb_Product1 >= 0.848) && (ipc_esp_flprs >= 0.848) &&
                       (ipc_eps_frprs >= 0.742) && (rtb_Product2 >= 0.742));

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms3' */

  /* S-Function (fcgen): '<Root>/10ms7' incorporates:
   *  SubSystem: '<Root>/EBS'
   */
  /* S-Function (fcgen): '<Root>/10ms' incorporates:
   *  SubSystem: '<Root>/Sensor_Signal'
   */
  /* DataStoreWrite: '<Root>/Data Store Write3' incorporates:
   *  Constant: '<S41>/Constant'
   *  Logic: '<S5>/Logical Operator2'
   *  Logic: '<S5>/Logical Operator3'
   *  RelationalOperator: '<S41>/Compare'
   */
  VCU10_DW.ebs_check = ((!VCU10_DW.ebs_working) && (airprs_sensor2_tmp <= 5.5));

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms7' */

  /* DataStoreWrite: '<Root>/Data Store Write4' */
  VCU10_DW.brkmotor_check = VCU10_B.brkmotor_check;

  /* S-Function (fcgen): '<Root>/10ms9' incorporates:
   *  SubSystem: '<Root>/EPS'
   */
  /* Sum: '<S52>/Add' incorporates:
   *  Constant: '<S52>/Constant1'
   *  DataTypeConversion: '<S52>/Data Type Conversion1'
   *  DataTypeConversion: '<S52>/Data Type Conversion2'
   *  Gain: '<S52>/Gain1'
   *  Inport: '<Root>/canb_epssendmsg1'
   */
  rtb_Add_f = ((canb_epssendmsg1[3] << 8) + canb_epssendmsg1[4]) - 1024;

  /* Outputs for Atomic SubSystem: '<S53>/Bit Shift1' */
  /* DataTypeConversion: '<S53>/Data Type Conversion3' incorporates:
   *  Inport: '<Root>/canb_epssendmsg2'
   */
  VCU10_BitShift_p((uint16_T)canb_epssendmsg2[1], &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S53>/Bit Shift1' */

  /* S-Function (fcgen): '<Root>/10ms11' incorporates:
   *  SubSystem: '<Root>/IPC'
   */
  /* DataTypeConversion: '<S60>/Data Type Conversion5' incorporates:
   *  Constant: '<S170>/Constant'
   *  Constant: '<S60>/Constant1'
   *  DataTypeConversion: '<S170>/Data Type Conversion1'
   *  Gain: '<S60>/Gain1'
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S8>/canb_ipctsmsg2'
   *  Sum: '<S170>/Add'
   *  Sum: '<S60>/Add1'
   */
  tmp = floor(((rtb_y + (real_T)canb_ipctsmsg2[1]) - 1024.0) * 5.0 + 1024.0);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 4.294967296E+9);
  }

  elapsedTicks_m = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)
    tmp;

  /* End of DataTypeConversion: '<S60>/Data Type Conversion5' */

  /* Logic: '<S51>/Logical Operator3' incorporates:
   *  Constant: '<S57>/Constant'
   *  Constant: '<S58>/Constant'
   *  RelationalOperator: '<S57>/Compare'
   *  RelationalOperator: '<S58>/Compare'
   */
  VCU10_DW.steer_zero = ((rtb_Add_f >= -2) && (rtb_Add_f <= 2));

  /* Chart: '<S51>/EPS_Stateflow1' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read2'
   *  DataStoreWrite: '<S3>/Data Store Write4'
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S8>/canb_ipctsmsg2'
   */
  elapsedTicks = VCU10_M->Timing.clockTick0 - VCU10_DW.previousTicks;
  VCU10_DW.previousTicks = VCU10_M->Timing.clockTick0;
  if (VCU10_DW.temporalCounter_i1_g + elapsedTicks <= 1U) {
    VCU10_DW.temporalCounter_i1_g = (uint8_T)(VCU10_DW.temporalCounter_i1_g +
      elapsedTicks);
  } else {
    VCU10_DW.temporalCounter_i1_g = 1U;
  }

  if (VCU10_DW.is_active_c15_VCU10 == 0U) {
    VCU10_DW.is_active_c15_VCU10 = 1U;
    VCU10_DW.is_c15_VCU10 = VCU10_IN_EPS_Unable;
    VCU10_B.eps_cmdworkmode = 0U;
    VCU10_B.eps_cmdmiddle = 0U;
  } else {
    switch (VCU10_DW.is_c15_VCU10) {
     case VCU10_IN_EPS_Enable:
      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (VCU10_B.steering_flag_o == 0.0) {
        VCU10_DW.is_c15_VCU10 = VCU10_IN_EPS_Unable;
        VCU10_B.eps_cmdworkmode = 0U;
        VCU10_B.eps_cmdmiddle = 0U;
      } else if ((VCU10_DW.temporalCounter_i1_g >= 1U) && VCU10_DW.steer_return)
      {
        VCU10_DW.is_c15_VCU10 = VCU10_IN_EPS_Return;
        VCU10_B.eps_cmdworkmode = 32U;
        VCU10_B.eps_cmdangle = 4U;
        VCU10_B.eps_cmdmiddle = 85U;
        VCU10_B.eps_cmdvelocity = 20U;
      } else {
        VCU10_B.eps_cmdworkmode = 32U;
        VCU10_B.eps_cmdangle = elapsedTicks_m;
        VCU10_B.eps_cmdmiddle = 0U;

        /* S-Function (fcgen): '<Root>/10ms11' incorporates:
         *  SubSystem: '<Root>/IPC'
         */
        VCU10_B.eps_cmdvelocity = canb_ipctsmsg2[2];

        /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case VCU10_IN_EPS_Return:
      if (VCU10_DW.steer_zero) {
        VCU10_DW.is_c15_VCU10 = VCU10_IN_EPS_Enable;
        VCU10_DW.temporalCounter_i1_g = 0U;
        VCU10_B.eps_cmdworkmode = 32U;
        VCU10_B.eps_cmdangle = elapsedTicks_m;
        VCU10_B.eps_cmdmiddle = 0U;

        /* S-Function (fcgen): '<Root>/10ms11' incorporates:
         *  SubSystem: '<Root>/IPC'
         */
        VCU10_B.eps_cmdvelocity = canb_ipctsmsg2[2];

        /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */
      } else {
        VCU10_B.eps_cmdworkmode = 32U;
        VCU10_B.eps_cmdangle = 4U;
        VCU10_B.eps_cmdmiddle = 85U;
        VCU10_B.eps_cmdvelocity = 20U;
      }
      break;

     default:
      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      /* case IN_EPS_Unable: */
      if (VCU10_B.steering_flag_o == 1.0) {
        VCU10_DW.is_c15_VCU10 = VCU10_IN_EPS_Enable;
        VCU10_DW.temporalCounter_i1_g = 0U;
        VCU10_B.eps_cmdworkmode = 32U;
        VCU10_B.eps_cmdangle = elapsedTicks_m;
        VCU10_B.eps_cmdmiddle = 0U;

        /* S-Function (fcgen): '<Root>/10ms11' incorporates:
         *  SubSystem: '<Root>/IPC'
         */
        VCU10_B.eps_cmdvelocity = canb_ipctsmsg2[2];

        /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;
    }
  }

  /* End of Chart: '<S51>/EPS_Stateflow1' */

  /* Switch: '<S51>/Switch' incorporates:
   *  Bias: '<S51>/InspectionAngleOffset'
   *  DataStoreRead: '<Root>/Data Store Read14'
   *  Rounding: '<S51>/Rounding Function'
   *  Sin: '<S51>/Sine Wave1'
   */
  if (VCU10_DW.inspection_flag) {
    rtb_y = floor(sin(((VCU10_M->Timing.clockTick0) * 0.01)) * 90.0) + 1024.0;
  } else {
    rtb_y = VCU10_B.eps_cmdangle;
  }

  /* End of Switch: '<S51>/Switch' */

  /* DataTypeConversion: '<S51>/Data Type Conversion1' */
  if (rtIsNaN(rtb_y)) {
    tmp = 0.0;
  } else {
    tmp = fmod(rtb_y, 65536.0);
  }

  /* Outputs for Atomic SubSystem: '<S51>/Bit Shift' */
  /* S-Function (sfix_bitop): '<S51>/Bitwise AND' incorporates:
   *  DataTypeConversion: '<S51>/Data Type Conversion1'
   */
  VCU10_BitShift5((uint16_T)((uint16_T)tmp & 65280), &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S51>/Bit Shift' */

  /* DataTypeConversion: '<S51>/Data Type Conversion5' incorporates:
   *  DataTypeConversion: '<S51>/Data Type Conversion1'
   *  S-Function (sfix_bitop): '<S51>/Bitwise AND1'
   */
  rtb_xor_consequence = (uint8_T)((uint16_T)tmp & 255);

  /* SignalConversion generated from: '<S6>/canb_epsmsg' incorporates:
   *  Constant: '<S51>/Constant'
   *  Constant: '<S51>/Constant1'
   *  DataTypeConversion: '<S51>/Data Type Conversion4'
   *  S-Function (sfix_bitop): '<S51>/Bitwise AND2'
   *  S-Function (sfix_bitop): '<S51>/Bitwise AND3'
   *  S-Function (sfix_bitop): '<S51>/Logical Operator2'
   */
  canb_epsmsg[0] = VCU10_B.eps_cmdworkmode;
  canb_epsmsg[1] = 0U;
  canb_epsmsg[2] = 0U;
  canb_epsmsg[3] = (uint8_T)rtb_Add2_g;
  canb_epsmsg[4] = rtb_xor_consequence;
  canb_epsmsg[5] = VCU10_B.eps_cmdmiddle;
  canb_epsmsg[6] = VCU10_B.eps_cmdvelocity;
  canb_epsmsg[7] = (uint8_T)(VCU10_B.eps_cmdworkmode ^ (uint8_T)rtb_Add2_g ^
    rtb_xor_consequence ^ VCU10_B.eps_cmdmiddle ^ VCU10_B.eps_cmdvelocity);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms9' */

  /* S-Function (fcgen): '<Root>/10ms1' incorporates:
   *  SubSystem: '<Root>/TS_Activation'
   */
  /* Switch: '<S15>/Switch' incorporates:
   *  DataStoreWrite: '<Root>/Data Store Write14'
   *  Logic: '<S15>/Logical Operator'
   *  Logic: '<S15>/Logical Operator2'
   */
  if (asms) {
    LogicalOperator_o = !di8_side;
  } else {
    LogicalOperator_o = !di8_cockpit;
  }

  /* End of Switch: '<S15>/Switch' */

  /* Chart: '<S15>/Chart' */
  if (VCU10_DW.is_active_c3_VCU10 == 0U) {
    VCU10_DW.is_active_c3_VCU10 = 1U;
    VCU10_DW.is_c3_VCU10 = VCU10_IN_Ignition_Check;
    VCU10_DW.is_Ignition_Check_f = VCU10_IN_begin;
    VCU10_DW.di8_flag = F;
  } else if (VCU10_DW.is_c3_VCU10 == 1) {
    if (VCU10_DW.di8_flag == F) {
      VCU10_DW.is_Flameout_Check_i = VCU10_IN_NO_ACTIVE_CHILD;
      VCU10_DW.is_c3_VCU10 = VCU10_IN_Ignition_Check;
      VCU10_DW.is_Ignition_Check_f = VCU10_IN_begin;
      VCU10_DW.di8_flag = F;
    } else {
      switch (VCU10_DW.is_Flameout_Check_i) {
       case VCU10_IN_Checkoff:
        break;

       default:
        /* case IN_DI8_Offcheck_Flag: */
        if (VCU10_DW.di8_offcheck_flag == 0.0) {
          VCU10_DW.is_Flameout_Check_i = VCU10_IN_DI8_Offcheck_Flag;
          if (!LogicalOperator_o) {
            VCU10_DW.di8_offcheck_flag = 1.0;
          }
        } else {
          VCU10_DW.is_Flameout_Check_i = VCU10_IN_Checkoff;
          if (LogicalOperator_o) {
            VCU10_DW.di8_flag = F;
            di8 = F;
          }
        }
        break;
      }
    }

    /* case IN_Ignition_Check: */
  } else if (VCU10_DW.di8_flag == T) {
    VCU10_DW.is_Ignition_Check_f = VCU10_IN_NO_ACTIVE_CHILD;
    VCU10_DW.is_c3_VCU10 = VCU10_IN_Flameout_Check;
    VCU10_DW.is_Flameout_Check_i = VCU10_IN_DI8_Offcheck_Flag;
    if (!LogicalOperator_o) {
      VCU10_DW.di8_offcheck_flag = 1.0;
    }
  } else {
    switch (VCU10_DW.is_Ignition_Check_f) {
     case VCU10_IN_Check:
      if (VCU10_DW.di8_check_flag == 0.0) {
        VCU10_DW.is_Ignition_Check_f = VCU10_IN_DI8_Check_Flag;
        VCU10_DW.di8_check_flag = !LogicalOperator_o;
      } else if (VCU10_DW.di8_check_flag == 1.0) {
        VCU10_DW.is_Ignition_Check_f = VCU10_IN_Check;
        if (LogicalOperator_o) {
          VCU10_DW.di8_flag = T;
          di8 = T;
        }
      }
      break;

     case VCU10_IN_DI8_Check_Flag:
      if (VCU10_DW.di8_check_flag == 0.0) {
        VCU10_DW.is_Ignition_Check_f = VCU10_IN_DI8_Check_Flag;
        VCU10_DW.di8_check_flag = !LogicalOperator_o;
      } else if (VCU10_DW.di8_check_flag == 1.0) {
        VCU10_DW.is_Ignition_Check_f = VCU10_IN_Check;
        if (LogicalOperator_o) {
          VCU10_DW.di8_flag = T;
          di8 = T;
        }
      }
      break;

     default:
      /* case IN_begin: */
      VCU10_DW.is_Ignition_Check_f = VCU10_IN_DI8_Check_Flag;
      VCU10_DW.di8_check_flag = !LogicalOperator_o;
      break;
    }
  }

  /* End of Chart: '<S15>/Chart' */

  /* Logic: '<S15>/Logical Operator1' */
  LogicalOperator_o = !run_button;

  /* Chart: '<S15>/Chart1' */
  if (VCU10_DW.is_active_c8_VCU10 == 0U) {
    VCU10_DW.is_active_c8_VCU10 = 1U;
    VCU10_DW.is_c8_VCU10 = VCU10_IN_Ignition_Check;
    VCU10_DW.is_Ignition_Check = VCU10_IN_begin;
    VCU10_DW.run_flag = 0.0;
  } else if (VCU10_DW.is_c8_VCU10 == 1) {
    if (VCU10_DW.run_flag == 0.0) {
      VCU10_DW.is_Flameout_Check = VCU10_IN_NO_ACTIVE_CHILD;
      VCU10_DW.is_c8_VCU10 = VCU10_IN_Ignition_Check;
      VCU10_DW.is_Ignition_Check = VCU10_IN_begin;
      VCU10_DW.run_flag = 0.0;
    } else {
      switch (VCU10_DW.is_Flameout_Check) {
       case VCU10_IN_Checkoff:
        break;

       default:
        /* case IN_Run_Offcheck_Flag: */
        if (VCU10_DW.run_offcheck_flag == 0.0) {
          VCU10_DW.is_Flameout_Check = VCU10_IN_Run_Offcheck_Flag;
          if (!LogicalOperator_o) {
            VCU10_DW.run_offcheck_flag = 1.0;
          }
        } else {
          VCU10_DW.is_Flameout_Check = VCU10_IN_Checkoff;
          if (LogicalOperator_o) {
            VCU10_DW.run_flag = 0.0;
            run = F;
          }
        }
        break;
      }
    }

    /* case IN_Ignition_Check: */
  } else if (VCU10_DW.run_flag == 1.0) {
    VCU10_DW.is_Ignition_Check = VCU10_IN_NO_ACTIVE_CHILD;
    VCU10_DW.is_c8_VCU10 = VCU10_IN_Flameout_Check;
    VCU10_DW.is_Flameout_Check = VCU10_IN_Run_Offcheck_Flag;
    if (!LogicalOperator_o) {
      VCU10_DW.run_offcheck_flag = 1.0;
    }
  } else {
    switch (VCU10_DW.is_Ignition_Check) {
     case VCU10_IN_Check:
      if (VCU10_DW.run_check_flag == 1.0) {
        VCU10_DW.is_Ignition_Check = VCU10_IN_Check;
        if (LogicalOperator_o) {
          VCU10_DW.run_flag = 1.0;
          run = T;
        }
      } else if (VCU10_DW.run_check_flag == 0.0) {
        VCU10_DW.is_Ignition_Check = VCU10_IN_Run_Check_Flag;
        VCU10_DW.run_check_flag = !LogicalOperator_o;
      }
      break;

     case VCU10_IN_Run_Check_Flag:
      if (VCU10_DW.run_check_flag == 1.0) {
        VCU10_DW.is_Ignition_Check = VCU10_IN_Check;
        if (LogicalOperator_o) {
          VCU10_DW.run_flag = 1.0;
          run = T;
        }
      } else if (VCU10_DW.run_check_flag == 0.0) {
        VCU10_DW.is_Ignition_Check = VCU10_IN_Run_Check_Flag;
        VCU10_DW.run_check_flag = !LogicalOperator_o;
      }
      break;

     default:
      /* case IN_begin: */
      VCU10_DW.is_Ignition_Check = VCU10_IN_Run_Check_Flag;
      VCU10_DW.run_check_flag = !LogicalOperator_o;
      break;
    }
  }

  /* End of Chart: '<S15>/Chart1' */

  /* Chart: '<S15>/Chart2' incorporates:
   *  DataStoreWrite: '<Root>/Data Store Write14'
   */
  elapsedTicks_m = VCU10_M->Timing.clockTick0 - VCU10_DW.previousTicks_gm;
  VCU10_DW.previousTicks_gm = VCU10_M->Timing.clockTick0;
  if (VCU10_DW.temporalCounter_i1_p + elapsedTicks_m <= 255U) {
    VCU10_DW.temporalCounter_i1_p = (uint8_T)(VCU10_DW.temporalCounter_i1_p +
      elapsedTicks_m);
  } else {
    VCU10_DW.temporalCounter_i1_p = MAX_uint8_T;
  }

  if (VCU10_DW.is_active_c9_VCU10 == 0U) {
    VCU10_DW.is_active_c9_VCU10 = 1U;
    VCU10_DW.is_c9_VCU10 = VCU10_IN_begin_f;
  } else if (VCU10_DW.is_c9_VCU10 == 1) {
    VCU10_B.ts = 0.0;
    if (tsms && di8) {
      guard1 = false;
      if ((!asms) && (run && VCU10_DW.brake_on)) {
        VCU10_B.ts = 1.0;
        VCU10_B.ts_warning = T;
        guard1 = true;
      } else if (asms) {
        VCU10_B.ts = 1.0;
        guard1 = true;
      }

      if (guard1) {
        VCU10_DW.is_c9_VCU10 = VCU10_IN_delay;
        VCU10_DW.temporalCounter_i1_p = 0U;
      }
    }

    /* case IN_delay: */
  } else if (VCU10_DW.temporalCounter_i1_p >= 200U) {
    VCU10_B.ts_warning = F;
    if ((!tsms) || (!di8) || (!run)) {
      VCU10_B.ts = 0.0;
    }
  }

  /* End of Chart: '<S15>/Chart2' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms1' */

  /* DataStoreWrite: '<Root>/Data Store Write6' */
  VCU10_DW.ts = VCU10_B.ts;

  /* S-Function (fcgen): '<Root>/10ms12' incorporates:
   *  SubSystem: '<Root>/Buzzer'
   */
  /* Switch: '<S4>/Switch1' incorporates:
   *  DataStoreWrite: '<Root>/Data Store Write14'
   */
  if (asms) {
    /* Switch: '<S4>/Switch1' incorporates:
     *  DataStoreRead: '<Root>/Data Store Read3'
     */
    r2d_buzzer = VCU10_DW.r2d_warning;
  } else {
    /* Switch: '<S4>/Switch1' */
    r2d_buzzer = VCU10_B.ts_warning;
  }

  /* End of Switch: '<S4>/Switch1' */

  /* Chart: '<S4>/Chart' incorporates:
   *  DataStoreWrite: '<S3>/Data Store Write3'
   */
  elapsedTicks_m = VCU10_M->Timing.clockTick0 - VCU10_DW.previousTicks_c;
  VCU10_DW.previousTicks_c = VCU10_M->Timing.clockTick0;
  if (VCU10_DW.temporalCounter_i1_m + elapsedTicks_m <= 1023U) {
    VCU10_DW.temporalCounter_i1_m = (uint16_T)(VCU10_DW.temporalCounter_i1_m +
      elapsedTicks_m);
  } else {
    VCU10_DW.temporalCounter_i1_m = 1023U;
  }

  if (VCU10_DW.is_active_c11_VCU10 == 0U) {
    VCU10_DW.is_active_c11_VCU10 = 1U;
    VCU10_DW.is_c11_VCU10 = VCU10_IN_Default;
    LogicalOperator_o = F;
  } else if (VCU10_DW.is_c11_VCU10 == 1) {
    LogicalOperator_o = F;

    /* S-Function (fcgen): '<Root>/10ms6' incorporates:
     *  SubSystem: '<Root>/AS_Stateflow'
     */
    if (VCU10_B.as_emergency_flag_e == 1.0) {
      VCU10_DW.is_c11_VCU10 = VCU10_IN_Emergency;
      VCU10_DW.temporalCounter_i1_m = 0U;
      LogicalOperator_o = T;
    }

    /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
  } else {
    /* case IN_Emergency: */
    LogicalOperator_o = T;
    if (VCU10_DW.temporalCounter_i1_m >= 900U) {
      VCU10_DW.is_c11_VCU10 = VCU10_IN_Default;
      LogicalOperator_o = F;
    }
  }

  /* End of Chart: '<S4>/Chart' */

  /* DiscretePulseGenerator: '<S4>/Pulse Generator' */
  rtb_Add_f = ((VCU10_DW.clockTickCounter_a2 < 50) &&
               (VCU10_DW.clockTickCounter_a2 >= 0));
  if (VCU10_DW.clockTickCounter_a2 >= 99) {
    VCU10_DW.clockTickCounter_a2 = 0;
  } else {
    VCU10_DW.clockTickCounter_a2++;
  }

  /* End of DiscretePulseGenerator: '<S4>/Pulse Generator' */

  /* Switch: '<S4>/Switch' */
  if (LogicalOperator_o) {
    /* Switch: '<S4>/Switch' incorporates:
     *  DataTypeConversion: '<S4>/Data Type Conversion6'
     */
    ebs_buzzer = (rtb_Add_f != 0);
  } else {
    /* Switch: '<S4>/Switch' incorporates:
     *  Constant: '<S4>/Constant'
     */
    ebs_buzzer = false;
  }

  /* End of Switch: '<S4>/Switch' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms12' */

  /* DataStoreWrite: '<Root>/Data Store Write7' */
  VCU10_DW.ebs_warning = ebs_buzzer;

  /* DataStoreWrite: '<Root>/Data Store Write8' */
  VCU10_DW.r2d_warning = VCU10_B.r2d_warning;

  /* DataStoreWrite: '<Root>/Data Store Write9' */
  VCU10_DW.steer_return = VCU10_B.steer_return;

  /* S-Function (fcgen): '<Root>/10ms2' incorporates:
   *  SubSystem: '<Root>/LED_Control'
   */
  /* Inport: '<S10>/brake_on' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read13'
   */
  led_brake = VCU10_DW.brake_on;

  /* Chart: '<S221>/Shutdown_Button' */
  elapsedTicks_m = VCU10_M->Timing.clockTick0 - VCU10_DW.previousTicks_f;
  VCU10_DW.previousTicks_f = VCU10_M->Timing.clockTick0;
  if (VCU10_DW.temporalCounter_i1_ct + elapsedTicks_m <= 127U) {
    VCU10_DW.temporalCounter_i1_ct = (uint8_T)(VCU10_DW.temporalCounter_i1_ct +
      elapsedTicks_m);
  } else {
    VCU10_DW.temporalCounter_i1_ct = 127U;
  }

  if (VCU10_DW.is_active_c17_VCU10 == 0U) {
    VCU10_DW.is_active_c17_VCU10 = 1U;
    VCU10_DW.is_c17_VCU10 = VCU10_IN_begin_f;
    VCU10_DW.temporalCounter_i1_ct = 0U;
  } else {
    switch (VCU10_DW.is_c17_VCU10) {
     case VCU10_IN_begin_f:
      if ((VCU10_DW.temporalCounter_i1_ct >= 100U) && (shutdown_s == shutdown_e))
      {
        VCU10_DW.is_c17_VCU10 = VCU10_IN_same1;
        VCU10_B.shutdown_flag = T;
      }
      break;

     case VCU10_IN_compare:
      if (VCU10_DW.shutdown_count > 10.0) {
        VCU10_DW.is_c17_VCU10 = VCU10_IN_judge;
        VCU10_B.shutdown_flag = F;
      } else if (shutdown_s == shutdown_e) {
        VCU10_DW.shutdown_count = 0.0;
        VCU10_DW.is_c17_VCU10 = VCU10_IN_same1;
        VCU10_B.shutdown_flag = T;
      } else {
        VCU10_DW.shutdown_count++;
      }
      break;

     case VCU10_IN_judge:
      if (shutdown_s == shutdown_e) {
        VCU10_DW.is_c17_VCU10 = VCU10_IN_same1;
        VCU10_B.shutdown_flag = T;
      } else {
        VCU10_B.shutdown_flag = F;
      }
      break;

     default:
      /* case IN_same1: */
      if (shutdown_s != shutdown_e) {
        VCU10_DW.is_c17_VCU10 = VCU10_IN_compare;
        VCU10_DW.shutdown_count++;
      } else {
        VCU10_B.shutdown_flag = T;
      }
      break;
    }
  }

  /* End of Chart: '<S221>/Shutdown_Button' */

  /* Outputs for Enabled SubSystem: '<S221>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S232>/Enable'
   */
  /* S-Function (fcgen): '<Root>/10ms10' incorporates:
   *  SubSystem: '<Root>/Res'
   */
  /* Logic: '<S221>/Logical Operator2' incorporates:
   *  Constant: '<S227>/Constant'
   *  DataStoreWrite: '<Root>/Data Store Write14'
   *  DataTypeConversion: '<S14>/Data Type Conversion15'
   *  DataTypeConversion: '<S269>/Data Type Conversion2'
   *  Inport: '<S232>/In1'
   *  RelationalOperator: '<S227>/Compare'
   */
  if (res_stop && (rtb_y_hw != 0) && VCU10_B.shutdown_flag && asms) {
    /* S-Function (fcgen): '<Root>/10ms' incorporates:
     *  SubSystem: '<Root>/Sensor_Signal'
     */
    VCU10_B.In1 = (airprs_sensor2_tmp >= 3.5);

    /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */
  }

  /* End of Logic: '<S221>/Logical Operator2' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms10' */
  /* End of Outputs for SubSystem: '<S221>/Enabled Subsystem' */

  /* Chart: '<S221>/display' */
  elapsedTicks_m = VCU10_M->Timing.clockTick0 - VCU10_DW.previousTicks_ag;
  VCU10_DW.previousTicks_ag = VCU10_M->Timing.clockTick0;
  if (VCU10_DW.temporalCounter_i1_gw + elapsedTicks_m <= 255U) {
    VCU10_DW.temporalCounter_i1_gw = (uint8_T)(VCU10_DW.temporalCounter_i1_gw +
      elapsedTicks_m);
  } else {
    VCU10_DW.temporalCounter_i1_gw = MAX_uint8_T;
  }

  if (VCU10_DW.is_active_c6_VCU10 == 0U) {
    VCU10_DW.is_active_c6_VCU10 = 1U;
    VCU10_DW.is_c6_VCU10 = VCU10_IN_begin_f;
    VCU10_DW.temporalCounter_i1_gw = 0U;
    res_stop = T;
  } else if (VCU10_DW.is_c6_VCU10 == 1) {
    if (VCU10_DW.temporalCounter_i1_gw >= 200U) {
      VCU10_DW.is_c6_VCU10 = VCU10_IN_end;
      res_stop = F;
    } else {
      res_stop = T;
    }
  } else {
    /* case IN_end: */
    res_stop = F;
  }

  /* End of Chart: '<S221>/display' */

  /* S-Function (fcgen): '<Root>/10ms' incorporates:
   *  SubSystem: '<Root>/Sensor_Signal'
   */
  /* Logic: '<S221>/Logical Operator' incorporates:
   *  Constant: '<S225>/Constant'
   *  Constant: '<S226>/Constant'
   *  Constant: '<S228>/Constant'
   *  Constant: '<S229>/Constant'
   *  Constant: '<S230>/Constant'
   *  Constant: '<S231>/Constant'
   *  DataTypeConversion: '<S14>/Data Type Conversion15'
   *  Logic: '<S221>/Logical Operator3'
   *  RelationalOperator: '<S225>/Compare'
   *  RelationalOperator: '<S226>/Compare'
   *  RelationalOperator: '<S228>/Compare'
   *  RelationalOperator: '<S229>/Compare'
   *  RelationalOperator: '<S230>/Compare'
   *  RelationalOperator: '<S231>/Compare'
   */
  led_ebs_error = ((airprs_sensor1 <= 1.0) || (airprs_sensor2_tmp <= 1.0) ||
                   VCU10_B.In1 || ((rtb_Product1 <= 0.11) || (ipc_esp_flprs <=
    0.11) || (ipc_eps_frprs <= 0.11) || (rtb_Product2 <= 0.11)) || res_stop);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */

  /* Chart: '<S222>/blue' incorporates:
   *  DataStoreWrite: '<Root>/Data Store Write14'
   */
  elapsedTicks_m = VCU10_M->Timing.clockTick0 - VCU10_DW.previousTicks_av;
  VCU10_DW.previousTicks_av = VCU10_M->Timing.clockTick0;
  if (VCU10_DW.temporalCounter_i1_c + elapsedTicks_m <= 255U) {
    VCU10_DW.temporalCounter_i1_c = (uint8_T)(VCU10_DW.temporalCounter_i1_c +
      elapsedTicks_m);
  } else {
    VCU10_DW.temporalCounter_i1_c = MAX_uint8_T;
  }

  if (VCU10_DW.is_active_c13_VCU10 == 0U) {
    VCU10_DW.is_active_c13_VCU10 = 1U;
    VCU10_DW.is_c13_VCU10 = VCU10_IN_Delay;
    VCU10_DW.temporalCounter_i1_c = 0U;
    rtb_Add2_g = 60000U;
  } else {
    switch (VCU10_DW.is_c13_VCU10) {
     case VCU10_IN_Blink:
      rtb_Add2_g = 30000U;
      res_stop = !asms;
      if ((VCU10_B.as_led_blue == 0.0) || res_stop) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_Close;
        rtb_Add2_g = 0U;
      } else if ((VCU10_B.as_led_blue == 1.0) || res_stop) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_On;
        rtb_Add2_g = 60000U;
      }
      break;

     case VCU10_IN_Close:
      rtb_Add2_g = 0U;
      if ((VCU10_B.as_led_blue == 1.0) && asms) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_On;
        rtb_Add2_g = 60000U;
      } else if ((VCU10_B.as_led_blue == 2.0) && asms) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_Blink;
        rtb_Add2_g = 30000U;
      }
      break;

     case VCU10_IN_Delay:
      rtb_Add2_g = 60000U;
      if (VCU10_DW.temporalCounter_i1_c >= 200U) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_Node;
        rtb_Add2_g = 0U;
      }
      break;

     case VCU10_IN_Node:
      rtb_Add2_g = 0U;
      if ((VCU10_B.as_led_blue == 1.0) && asms) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_On;
        rtb_Add2_g = 60000U;
      } else if ((VCU10_B.as_led_blue == 0.0) || (!asms)) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_Close;
      } else if ((VCU10_B.as_led_blue == 2.0) && asms) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_Blink;
        rtb_Add2_g = 30000U;
      }
      break;

     default:
      /* case IN_On: */
      rtb_Add2_g = 60000U;
      if ((VCU10_B.as_led_blue == 2.0) && asms) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_Blink;
        rtb_Add2_g = 30000U;
      } else if ((VCU10_B.as_led_blue == 0.0) || (!asms)) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_Close;
        rtb_Add2_g = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<S222>/blue' */

  /* DiscretePulseGenerator: '<S222>/Pulse Generator' */
  rtb_Add_f = ((VCU10_DW.clockTickCounter < 50) && (VCU10_DW.clockTickCounter >=
    0));
  if (VCU10_DW.clockTickCounter >= 99) {
    VCU10_DW.clockTickCounter = 0;
  } else {
    VCU10_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<S222>/Pulse Generator' */

  /* Switch: '<S222>/Switch' incorporates:
   *  Constant: '<S222>/Constant'
   */
  if (rtb_Add2_g > 10) {
    rtb_blue_0 = rtb_Add2_g;
  } else {
    rtb_blue_0 = 0;
  }

  /* End of Switch: '<S222>/Switch' */

  /* Switch: '<S222>/Switch2' incorporates:
   *  Constant: '<S222>/Constant1'
   *  Constant: '<S222>/Constant2'
   *  Switch: '<S222>/Switch1'
   */
  if (rtb_blue_0 > 40000) {
    rtb_Add_f = 1;
  } else if (rtb_Add2_g <= 10) {
    rtb_Add_f = 0;
  }

  /* End of Switch: '<S222>/Switch2' */

  /* DataTypeConversion: '<S222>/Data Type Conversion' */
  led_assi_blue = (rtb_Add_f != 0);

  /* Chart: '<S223>/yellow' incorporates:
   *  DataStoreWrite: '<Root>/Data Store Write14'
   */
  elapsedTicks_m = VCU10_M->Timing.clockTick0 - VCU10_DW.previousTicks_a;
  VCU10_DW.previousTicks_a = VCU10_M->Timing.clockTick0;
  if (VCU10_DW.temporalCounter_i1_j + elapsedTicks_m <= 255U) {
    VCU10_DW.temporalCounter_i1_j = (uint8_T)(VCU10_DW.temporalCounter_i1_j +
      elapsedTicks_m);
  } else {
    VCU10_DW.temporalCounter_i1_j = MAX_uint8_T;
  }

  if (VCU10_DW.is_active_c14_VCU10 == 0U) {
    VCU10_DW.is_active_c14_VCU10 = 1U;
    VCU10_DW.is_c14_VCU10 = VCU10_IN_delay_j;
    VCU10_DW.temporalCounter_i1_j = 0U;
    rtb_Add2_g = 60000U;
  } else {
    switch (VCU10_DW.is_c14_VCU10) {
     case VCU10_IN_Blink:
      rtb_Add2_g = 30000U;
      res_stop = !asms;
      if ((VCU10_B.as_led_yellow == 0.0) || res_stop) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_Close;
        rtb_Add2_g = 0U;
      } else if ((VCU10_B.as_led_yellow == 1.0) || res_stop) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_On_o;
        rtb_Add2_g = 60000U;
      }
      break;

     case VCU10_IN_Close:
      rtb_Add2_g = 0U;
      if ((VCU10_B.as_led_yellow == 1.0) && asms) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_On_o;
        rtb_Add2_g = 60000U;
      } else if ((VCU10_B.as_led_yellow == 2.0) && asms) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_Blink;
        rtb_Add2_g = 30000U;
      }
      break;

     case VCU10_IN_On_o:
      rtb_Add2_g = 60000U;
      if ((VCU10_B.as_led_yellow == 2.0) && asms) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_Blink;
        rtb_Add2_g = 30000U;
      } else if ((VCU10_B.as_led_yellow == 0.0) || (!asms)) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_Close;
        rtb_Add2_g = 0U;
      }
      break;

     case VCU10_IN_delay_j:
      rtb_Add2_g = 60000U;
      if (VCU10_DW.temporalCounter_i1_j >= 200U) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_node;
        rtb_Add2_g = 0U;
      }
      break;

     default:
      /* case IN_node: */
      rtb_Add2_g = 0U;
      if ((VCU10_B.as_led_yellow == 1.0) && asms) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_On_o;
        rtb_Add2_g = 60000U;
      } else if ((VCU10_B.as_led_yellow == 0.0) || (!asms)) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_Close;
      } else if ((VCU10_B.as_led_yellow == 2.0) && asms) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_Blink;
        rtb_Add2_g = 30000U;
      }
      break;
    }
  }

  /* End of Chart: '<S223>/yellow' */

  /* DiscretePulseGenerator: '<S223>/Pulse Generator' */
  rtb_Add_f = ((VCU10_DW.clockTickCounter_a < 50) &&
               (VCU10_DW.clockTickCounter_a >= 0));
  if (VCU10_DW.clockTickCounter_a >= 99) {
    VCU10_DW.clockTickCounter_a = 0;
  } else {
    VCU10_DW.clockTickCounter_a++;
  }

  /* End of DiscretePulseGenerator: '<S223>/Pulse Generator' */

  /* Switch: '<S223>/Switch' incorporates:
   *  Constant: '<S223>/Constant'
   */
  if (rtb_Add2_g > 10) {
    rtb_blue_0 = rtb_Add2_g;
  } else {
    rtb_blue_0 = 0;
  }

  /* End of Switch: '<S223>/Switch' */

  /* Switch: '<S223>/Switch2' incorporates:
   *  Constant: '<S223>/Constant1'
   *  Constant: '<S223>/Constant3'
   *  Switch: '<S223>/Switch1'
   */
  if (rtb_blue_0 > 40000) {
    rtb_Add_f = 1;
  } else if (rtb_Add2_g <= 10) {
    rtb_Add_f = 0;
  }

  /* End of Switch: '<S223>/Switch2' */

  /* DataTypeConversion: '<S223>/Data Type Conversion' */
  led_assi_yellow = (rtb_Add_f != 0);

  /* Chart: '<S10>/TSLED_Inspection' */
  elapsedTicks_m = VCU10_M->Timing.clockTick0 - VCU10_DW.previousTicks_o;
  VCU10_DW.previousTicks_o = VCU10_M->Timing.clockTick0;
  if (VCU10_DW.temporalCounter_i1_o + elapsedTicks_m <= 255U) {
    VCU10_DW.temporalCounter_i1_o = (uint8_T)(VCU10_DW.temporalCounter_i1_o +
      elapsedTicks_m);
  } else {
    VCU10_DW.temporalCounter_i1_o = MAX_uint8_T;
  }

  if (VCU10_DW.is_active_c2_VCU10 == 0U) {
    VCU10_DW.is_active_c2_VCU10 = 1U;
    VCU10_DW.is_c2_VCU10 = VCU10_IN_Inspection;
    VCU10_DW.temporalCounter_i1_o = 0U;
    led_imd_error = T;
    led_bms_error = T;
  } else if (VCU10_DW.is_c2_VCU10 == 1) {
    led_imd_error = T;
    led_bms_error = T;
    if (VCU10_DW.temporalCounter_i1_o >= 200U) {
      VCU10_DW.is_c2_VCU10 = VCU10_IN_Normal;
      led_imd_error = F;
      led_bms_error = F;
    }
  } else {
    /* case IN_Normal: */
    led_imd_error = F;
    led_bms_error = F;
  }

  /* End of Chart: '<S10>/TSLED_Inspection' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms2' */

  /* S-Function (fcgen): '<Root>/Function-Call Generator1' incorporates:
   *  SubSystem: '<Root>/Output_Convert'
   */
  /* Outport: '<Root>/model_lox' incorporates:
   *  BitConcat: '<S267>/bc2'
   *  BitConcat: '<S267>/bc3'
   *  BitConcat: '<S267>/bc4'
   *  BitConcat: '<S267>/bc5'
   */
  VCU10_Y.model_lox = (uint8_T)((uint8_T)((uint8_T)((uint8_T)(res_error << 1 |
    led_ebs_error) << 1 | led_assi_blue) << 1 | led_assi_yellow) << 1 |
    led_brake);

  /* Outport: '<Root>/model_hox' incorporates:
   *  BitConcat: '<S268>/bc2'
   *  BitConcat: '<S268>/bc3'
   *  BitConcat: '<S268>/bc4'
   *  BitConcat: '<S268>/bc5'
   *  BitConcat: '<S268>/bc6'
   *  BitConcat: '<S268>/bc7'
   */
  VCU10_Y.model_hox = (uint8_T)((uint8_T)((uint8_T)((uint8_T)((uint8_T)((uint8_T)
    (ebs_buzzer << 1 | r2d_buzzer) << 1 | run) << 1 | di8) << 1 | led_imd_error)
    << 1 | led_bms_error) << 1 | ebs_trig);

  /* End of Outputs for S-Function (fcgen): '<Root>/Function-Call Generator1' */

  /* S-Function (fcgen): '<Root>/10ms8' incorporates:
   *  SubSystem: '<Root>/ESP'
   */
  /* Outport: '<Root>/ESP_R_00' incorporates:
   *  DataTypeConversion: '<S146>/Data Type Conversion1'
   *  DataTypeConversion: '<S146>/Data Type Conversion13'
   *  DataTypeConversion: '<S146>/Data Type Conversion2'
   *  DataTypeConversion: '<S146>/Data Type Conversion4'
   *  DataTypeConversion: '<S146>/Data Type Conversion6'
   *  S-Function (sfix_bitop): '<S146>/Bitwise AND3'
   *  S-Function (sfix_bitop): '<S146>/Bitwise AND7'
   *  Sum: '<S146>/Add2'
   */
  VCU10_Y.ESP_R_00[0] = (uint8_T)rtb_y_hf;
  VCU10_Y.ESP_R_00[1] = (uint8_T)rtb_y_cq;
  VCU10_Y.ESP_R_00[2] = (uint8_T)(rtb_y_ej & 255);
  VCU10_Y.ESP_R_00[3] = (uint8_T)rtb_y_mj;
  VCU10_Y.ESP_R_00[4] = (uint8_T)rtb_y_mn;
  VCU10_Y.ESP_R_00[5] = (uint8_T)(rtb_Add1_a & 255);
  VCU10_Y.ESP_R_00[6] = (uint8_T)((uint32_T)rtb_BitwiseAND_mj +
    VCU10_ConstB.BitwiseAND8_o);
  VCU10_Y.ESP_R_00[7] = 0U;

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms8' */

  /* S-Function (fcgen): '<Root>/10ms11' incorporates:
   *  SubSystem: '<Root>/IPC'
   */
  /* Sum: '<S169>/Add4' incorporates:
   *  Constant: '<S169>/Constant'
   *  DataTypeConversion: '<S169>/Data Type Conversion6'
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  airprs_sensor1 = ((real_T)canb_ipctsmsg1[6] + rtb_DataTypeConversion1) -
    5000.0;

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */

  /* S-Function (fcgen): '<Root>/10ms4' incorporates:
   *  SubSystem: '<Root>/Motor_Control'
   */
  /* Saturate: '<S237>/Saturation' */
  if (airprs_sensor1 > 55.0) {
    airprs_sensor1 = 55.0;
  } else if (airprs_sensor1 < 0.0) {
    airprs_sensor1 = 0.0;
  }

  /* End of Saturate: '<S237>/Saturation' */

  /* Outputs for Atomic SubSystem: '<S238>/Bit Shift' */
  VCU10_BitShift_a(VCU10_ConstB.BitwiseAND1_a, &rtb_y_hw);

  /* End of Outputs for SubSystem: '<S238>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S238>/Bit Shift3' */
  VCU10_BitShift3_m(VCU10_ConstB.BitwiseAND4, &rtb_xor_consequence);

  /* End of Outputs for SubSystem: '<S238>/Bit Shift3' */

  /* Chart: '<S240>/Pedal_Fault_Check' */
  if (fabs(apps1_01 - apps2_01) >= 0.1) {
    VCU10_DW.fault_count++;
    if (VCU10_DW.fault_count >= 3.0) {
      VCU10_B.pedal_error = 1.0;
    }
  } else {
    VCU10_DW.fault_count = 0.0;
    VCU10_B.pedal_error = 0.0;
  }

  /* End of Chart: '<S240>/Pedal_Fault_Check' */

  /* Switch: '<S240>/Switch' incorporates:
   *  Constant: '<S240>/Constant'
   *  Constant: '<S240>/Constant1'
   *  Constant: '<S240>/max_torque'
   *  Logic: '<S240>/Logical Operator'
   *  Product: '<S240>/Divide'
   *  Product: '<S240>/Product'
   *  Sum: '<S240>/Add'
   */
  if (!(VCU10_B.pedal_error != 0.0)) {
    apps1_01 = (apps1_01 + apps2_01) / 2.0 * 50.0;
  } else {
    apps1_01 = 0.0;
  }

  /* End of Switch: '<S240>/Switch' */

  /* Chart: '<S11>/Motor_Torque_Stateflow' incorporates:
   *  DataStoreWrite: '<Root>/Data Store Write14'
   *  DataStoreWrite: '<S3>/Data Store Write2'
   */
  if (VCU10_DW.is_active_c4_VCU10 == 0U) {
    VCU10_DW.is_active_c4_VCU10 = 1U;
    VCU10_DW.is_c4_VCU10 = VCU10_IN_Default_m;
    apps1_01 = 0.0;
  } else {
    switch (VCU10_DW.is_c4_VCU10) {
     case VCU10_IN_AS_Driving:
      if (!asms) {
        VCU10_DW.is_c4_VCU10 = VCU10_IN_Default_m;
        apps1_01 = 0.0;
      } else {
        apps1_01 = airprs_sensor1;
      }
      break;

     case VCU10_IN_Default_m:
      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (VCU10_B.manual_driving_flag_k == 1.0) {
        VCU10_DW.is_c4_VCU10 = VCU10_IN_Manual_Driving;
      } else if (asms) {
        VCU10_DW.is_c4_VCU10 = VCU10_IN_AS_Driving;
        apps1_01 = airprs_sensor1;
      } else {
        apps1_01 = 0.0;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     default:
      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      /* case IN_Manual_Driving: */
      if (VCU10_B.manual_driving_flag_k == 0.0) {
        VCU10_DW.is_c4_VCU10 = VCU10_IN_Default_m;
        apps1_01 = 0.0;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;
    }
  }

  /* End of Chart: '<S11>/Motor_Torque_Stateflow' */

  /* DataTypeConversion: '<S238>/Data Type Conversion7' */
  tmp = floor(apps1_01);

  /* Outputs for Atomic SubSystem: '<S238>/Bit Shift5' */
  VCU10_BitShift5(VCU10_ConstB.BitwiseAND7, &rtb_y_hf);

  /* End of Outputs for SubSystem: '<S238>/Bit Shift5' */

  /* Outputs for Atomic SubSystem: '<S238>/Bit Shift6' */
  VCU10_BitShift6(VCU10_ConstB.BitwiseAND8, &rtb_y_mn);

  /* End of Outputs for SubSystem: '<S238>/Bit Shift6' */

  /* Sum: '<S238>/Add3' */
  rtb_y_ej = (uint16_T)((uint32_T)rtb_y_hf + rtb_y_mn);

  /* Outputs for Atomic SubSystem: '<S238>/Bit Shift7' */
  VCU10_BitShift7(VCU10_ConstB.BitwiseAND9, &rtb_y_mn);

  /* End of Outputs for SubSystem: '<S238>/Bit Shift7' */

  /* Outputs for Atomic SubSystem: '<S238>/Bit Shift8' */
  /* S-Function (sfix_bitop): '<S238>/Bitwise AND11' */
  VCU10_BitShift5(4864, &rtb_y_hf);

  /* End of Outputs for SubSystem: '<S238>/Bit Shift8' */

  /* Outputs for Atomic SubSystem: '<S238>/Bit Shift9' */
  VCU10_BitShift5(VCU10_ConstB.BitwiseAND13, &rtb_y_mj);

  /* End of Outputs for SubSystem: '<S238>/Bit Shift9' */

  /* DataTypeConversion: '<S238>/Data Type Conversion7' */
  if (rtIsNaN(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 65536.0);
  }

  /* S-Function (sfix_bitop): '<S238>/Bitwise AND10' incorporates:
   *  Constant: '<S238>/constant'
   *  DataTypeConversion: '<S238>/Data Type Conversion7'
   *  Sum: '<S238>/Add1'
   */
  rtb_y_cq = (uint16_T)((uint16_T)((uint16_T)tmp + 5000U) & 255);

  /* DataTypeConversion: '<S238>/Data Type Conversion2' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read15'
   */
  tmp = floor(VCU10_DW.ts);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 256.0);
  }

  /* Outputs for Atomic SubSystem: '<S238>/Bit Shift1' */
  /* Outputs for Atomic SubSystem: '<S238>/Bit Shift2' */
  /* Outputs for Atomic SubSystem: '<S238>/Bit Shift4' */
  /* SignalConversion: '<S238>/Signal Conversion' incorporates:
   *  DataTypeConversion: '<S238>/Data Type Conversion12'
   *  DataTypeConversion: '<S238>/Data Type Conversion13'
   *  DataTypeConversion: '<S238>/Data Type Conversion14'
   *  DataTypeConversion: '<S238>/Data Type Conversion15'
   *  DataTypeConversion: '<S238>/Data Type Conversion17'
   *  DataTypeConversion: '<S238>/Data Type Conversion2'
   *  MATLAB Function: '<S243>/bit_shift'
   *  MATLAB Function: '<S244>/bit_shift'
   *  MATLAB Function: '<S246>/bit_shift'
   *  S-Function (sfix_bitop): '<S238>/Bitwise AND'
   *  S-Function (sfix_bitop): '<S238>/Bitwise AND2'
   *  S-Function (sfix_bitop): '<S238>/Bitwise AND3'
   *  S-Function (sfix_bitop): '<S238>/Bitwise AND5'
   *  Sum: '<S238>/Add'
   */
  cana_motor_cmd[0] = (uint8_T)((uint32_T)(uint8_T)((uint32_T)(uint8_T)
    ((uint32_T)(uint8_T)((uint32_T)(uint8_T)((uint32_T)((tmp < 0.0 ? (int32_T)
    (uint8_T)-(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp) & 1) + rtb_y_hw) +
    (uint8_T)(VCU10_ConstB.BitwiseAND2_o << 2)) + (uint8_T)
     (VCU10_ConstB.BitwiseAND3_o << 4)) + rtb_xor_consequence) + (uint8_T)
    (VCU10_ConstB.BitwiseAND5 << 7));

  /* End of Outputs for SubSystem: '<S238>/Bit Shift4' */
  /* End of Outputs for SubSystem: '<S238>/Bit Shift2' */
  /* End of Outputs for SubSystem: '<S238>/Bit Shift1' */
  cana_motor_cmd[1] = VCU10_ConstB.MCU1_Rx_Commandbyte1;
  cana_motor_cmd[2] = (uint8_T)rtb_y_ej;
  cana_motor_cmd[3] = (uint8_T)rtb_y_mn;
  cana_motor_cmd[4] = (uint8_T)rtb_y_cq;
  cana_motor_cmd[5] = (uint8_T)rtb_y_hf;
  cana_motor_cmd[6] = VCU10_ConstB.MCU1_Rx_Commandbyte6;
  cana_motor_cmd[7] = (uint8_T)rtb_y_mj;

  /* Outputs for Atomic SubSystem: '<S239>/Bit Shift' */
  VCU10_BitShift5(VCU10_ConstB.BitwiseAND1, &rtb_y_ej);

  /* End of Outputs for SubSystem: '<S239>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S239>/Bit Shift1' */
  VCU10_BitShift5(VCU10_ConstB.BitwiseAND3, &rtb_y_cq);

  /* End of Outputs for SubSystem: '<S239>/Bit Shift1' */

  /* SignalConversion generated from: '<S11>/cana_motor_cmd3' incorporates:
   *  Constant: '<S239>/constant'
   *  DataTypeConversion: '<S239>/Data Type Conversion3'
   *  DataTypeConversion: '<S239>/Data Type Conversion6'
   */
  cana_motor_cmd3[0] = VCU10_ConstB.MCU1_Rx_Command3byte0;
  cana_motor_cmd3[1] = (uint8_T)rtb_y_ej;
  cana_motor_cmd3[2] = VCU10_ConstB.MCU1_Rx_Command3byte2;
  cana_motor_cmd3[3] = (uint8_T)rtb_y_cq;
  cana_motor_cmd3[4] = 0U;
  cana_motor_cmd3[5] = 0U;
  cana_motor_cmd3[6] = 0U;
  cana_motor_cmd3[7] = 0U;

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms4' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.01, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
  VCU10_M->Timing.clockTick0++;
}

/* Model initialize function */
void VCU10_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* Enable for S-Function (fcgen): '<Root>/10ms6' incorporates:
   *  SubSystem: '<Root>/AS_Stateflow'
   */
  /* Enable for Chart: '<S3>/Chart' */
  VCU10_DW.previousTicks_g = VCU10_M->Timing.clockTick0;

  /* End of Enable for S-Function (fcgen): '<Root>/10ms6' */

  /* Enable for S-Function (fcgen): '<Root>/10ms9' incorporates:
   *  SubSystem: '<Root>/EPS'
   */
  /* Enable for Chart: '<S51>/EPS_Stateflow1' */
  VCU10_DW.previousTicks = VCU10_M->Timing.clockTick0;

  /* End of Enable for S-Function (fcgen): '<Root>/10ms9' */

  /* Enable for S-Function (fcgen): '<Root>/10ms1' incorporates:
   *  SubSystem: '<Root>/TS_Activation'
   */
  /* Enable for Chart: '<S15>/Chart2' */
  VCU10_DW.previousTicks_gm = VCU10_M->Timing.clockTick0;

  /* End of Enable for S-Function (fcgen): '<Root>/10ms1' */

  /* Enable for S-Function (fcgen): '<Root>/10ms12' incorporates:
   *  SubSystem: '<Root>/Buzzer'
   */
  /* Enable for Chart: '<S4>/Chart' */
  VCU10_DW.previousTicks_c = VCU10_M->Timing.clockTick0;

  /* End of Enable for S-Function (fcgen): '<Root>/10ms12' */

  /* Enable for S-Function (fcgen): '<Root>/10ms2' incorporates:
   *  SubSystem: '<Root>/LED_Control'
   */
  /* Enable for Chart: '<S221>/Shutdown_Button' */
  VCU10_DW.previousTicks_f = VCU10_M->Timing.clockTick0;

  /* Enable for Chart: '<S221>/display' */
  VCU10_DW.previousTicks_ag = VCU10_M->Timing.clockTick0;

  /* Enable for Chart: '<S222>/blue' */
  VCU10_DW.previousTicks_av = VCU10_M->Timing.clockTick0;

  /* Enable for Chart: '<S223>/yellow' */
  VCU10_DW.previousTicks_a = VCU10_M->Timing.clockTick0;

  /* Enable for Chart: '<S10>/TSLED_Inspection' */
  VCU10_DW.previousTicks_o = VCU10_M->Timing.clockTick0;

  /* End of Enable for S-Function (fcgen): '<Root>/10ms2' */
}

/* Model terminate function */
void VCU10_terminate(void)
{
  /* (no terminate code required) */
}
