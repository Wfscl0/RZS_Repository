/*
 * VCU10.c
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

#include "VCU10.h"
#include "VCU10_private.h"

/* Named constants for Chart: '<S18>/Chart' */
#define VCU10_IN_Check                 ((uint8_T)1U)
#define VCU10_IN_Checkoff              ((uint8_T)1U)
#define VCU10_IN_DI8_Check_Flag        ((uint8_T)2U)
#define VCU10_IN_DI8_Offcheck_Flag     ((uint8_T)2U)
#define VCU10_IN_Flameout_Check        ((uint8_T)1U)
#define VCU10_IN_Ignition_Check        ((uint8_T)2U)
#define VCU10_IN_NO_ACTIVE_CHILD       ((uint8_T)0U)
#define VCU10_IN_begin                 ((uint8_T)3U)

/* Named constants for Chart: '<S18>/Chart1' */
#define VCU10_IN_Run_Check_Flag        ((uint8_T)2U)
#define VCU10_IN_Run_Offcheck_Flag     ((uint8_T)2U)

/* Named constants for Chart: '<S18>/Chart2' */
#define VCU10_IN_begin_f               ((uint8_T)1U)
#define VCU10_IN_delay                 ((uint8_T)2U)

/* Named constants for Chart: '<S271>/heaartbeat_chart' */
#define VCU10_IN_compare               ((uint8_T)2U)
#define VCU10_IN_judge                 ((uint8_T)3U)
#define VCU10_IN_same                  ((uint8_T)4U)

/* Named constants for Chart: '<S271>/xor_Check' */
#define VCU10_IN_Init                  ((uint8_T)1U)
#define VCU10_IN_different             ((uint8_T)3U)
#define VCU10_IN_judge_c               ((uint8_T)4U)

/* Named constants for Chart: '<S4>/Chart' */
#define VCU10_IN_Default               ((uint8_T)1U)
#define VCU10_IN_Emergency             ((uint8_T)2U)

/* Named constants for Chart: '<S20>/Chart' */
#define VCU10_IN_as_driving            ((uint8_T)1U)
#define VCU10_IN_as_emergency          ((uint8_T)2U)
#define VCU10_IN_as_finished           ((uint8_T)3U)
#define VCU10_IN_as_off                ((uint8_T)4U)
#define VCU10_IN_as_ready              ((uint8_T)5U)
#define VCU10_IN_begin_g               ((uint8_T)6U)
#define VCU10_IN_munual_driving        ((uint8_T)7U)
#define VCU10_IN_r2d                   ((uint8_T)8U)

/* Named constants for Chart: '<S218>/Shutdown_Button' */
#define VCU10_IN_same1                 ((uint8_T)4U)

/* Named constants for Chart: '<S218>/display' */
#define VCU10_IN_end                   ((uint8_T)2U)

/* Named constants for Chart: '<S219>/blue' */
#define VCU10_IN_Blink                 ((uint8_T)1U)
#define VCU10_IN_Close                 ((uint8_T)2U)
#define VCU10_IN_Delay                 ((uint8_T)3U)
#define VCU10_IN_Node                  ((uint8_T)4U)
#define VCU10_IN_On                    ((uint8_T)5U)

/* Named constants for Chart: '<S220>/yellow' */
#define VCU10_IN_On_o                  ((uint8_T)3U)
#define VCU10_IN_delay_j               ((uint8_T)4U)
#define VCU10_IN_node                  ((uint8_T)5U)

/* Named constants for Chart: '<S13>/TSLED_Inspection' */
#define VCU10_IN_Inspection            ((uint8_T)1U)
#define VCU10_IN_Normal                ((uint8_T)2U)

/* Named constants for Chart: '<S14>/Motor_Torque_Stateflow' */
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

/* Named constants for Chart: '<S143>/ESP_Chart1' */
#define VCU10_IN_ESC_Able              ((uint8_T)1U)
#define VCU10_IN_ESC_Engage            ((uint8_T)2U)
#define VCU10_IN_ESC_Unable            ((uint8_T)3U)

/* Named constants for Chart: '<S48>/EPS_Stateflow1' */
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
uint8_T vcu_dbg_control[8];            /* '<Root>/vcu_dbg_control' */
uint8_T vcu_dbg_pedal_adc[8];          /* '<Root>/vcu_dbg_pedal_adc' */
uint8_T vcu_dbg_air_wheel[8];          /* '<Root>/vcu_dbg_air_wheel' */
uint8_T vcu_dbg_digital[8];            /* '<Root>/vcu_dbg_digital' */
uint8_T vcu_dbg_rx_count[4];           /* '<Root>/vcu_dbg_rx_count' */
uint16_T airprs2;                      /* '<S12>/Data Type Conversion' */
uint16_T airprs1;                      /* '<S12>/Data Type Conversion1' */
uint16_T brkps;                        /* '<S12>/Data Type Conversion2' */
uint16_T apps2;                        /* '<S12>/Data Type Conversion3' */
uint16_T apps1;                        /* '<S12>/Data Type Conversion4' */
uint8_T canb_epsmsg[8];                /* '<S8>/EPS_TransmitMsg' */
uint8_T cana_motor_cmd[8];             /* '<S235>/Signal Conversion' */
uint8_T cana_motor_cmd3[8];            /* '<S14>/MCU1_Rx_Command3' */
uint8_T AMI_Rx[8];                     /* '<S20>/Signal Conversion' */
uint8_T canb_ipcrxmsg[8];              /* '<S11>/IPC_ReceiveMsg' */
boolean_T ebs_driver_check;            /* '<S196>/Data Type Conversion' */
boolean_T shutdown_s;                  /* '<S196>/Data Type Conversion1' */
boolean_T shutdown_e;                  /* '<S196>/Data Type Conversion2' */
boolean_T di8_cockpit;                 /* '<S196>/Data Type Conversion3' */
boolean_T di8_side;                    /* '<S196>/Data Type Conversion4' */
boolean_T run_button;                  /* '<S196>/Data Type Conversion5' */
boolean_T tsms;                        /* '<S196>/Data Type Conversion6' */
boolean_T asms;                        /* '<S196>/Data Type Conversion7' */
boolean_T ebs_watchdog;
     /* '<S7>/BufferToMakeInportVirtual_InsertedFor_ebs_watchdog_at_inport_0' */
boolean_T ebs_trig;                    /* '<S7>/EBS_Trigger_ASMS_Gate' */
boolean_T led_brake;                   /* '<S13>/brake_on' */
boolean_T led_ebs_error;               /* '<S218>/Logical Operator' */
boolean_T led_assi_blue;               /* '<S219>/Data Type Conversion' */
boolean_T led_assi_yellow;             /* '<S220>/Data Type Conversion' */
boolean_T led_imd_error;               /* '<S13>/TSLED_Inspection' */
boolean_T led_bms_error;               /* '<S13>/TSLED_Inspection' */
boolean_T r2d_buzzer;                  /* '<S4>/Switch1' */
boolean_T ebs_buzzer;                  /* '<S4>/Switch' */
boolean_T res_error;                   /*  */
boolean_T run;                         /* '<S18>/Chart1' */
boolean_T di8;                         /* '<S18>/Chart' */

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
static void VCU10_AS_Driving(const boolean_T *FSEC_Safety_Fault_Delay, const
  boolean_T *res_stop, const boolean_T *LogicalOperator_o);
static void VCU10_enter_atomic_AS_Off(void);
static void VCU10_AS_Off(const boolean_T *FSEC_Safety_Fault_Delay, const
  boolean_T *LogicalOperator);
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
 *    '<S267>/Bit Shift'
 *    '<S61>/Bit Shift15'
 *    '<S61>/Bit Shift8'
 */
void VCU10_BitShift(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S268>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 1);
}

/*
 * Output and update for atomic system:
 *    '<S267>/Bit Shift1'
 *    '<S167>/Bit Shift3'
 *    '<S61>/Bit Shift1'
 *    '<S61>/Bit Shift9'
 */
void VCU10_BitShift1(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S269>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 2);
}

/*
 * Output and update for atomic system:
 *    '<S267>/Bit Shift2'
 *    '<S19>/Bit Shift'
 *    '<S61>/Bit Shift11'
 *    '<S61>/Bit Shift5'
 *    '<S61>/Bit Shift7'
 */
void VCU10_BitShift2(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S270>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 4);
}

/*
 * Output and update for atomic system:
 *    '<S161>/Bit Shift'
 *    '<S20>/Bit Shift'
 *    '<S235>/Bit Shift'
 */
void VCU10_BitShift_a(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S162>/bit_shift' */
  *rty_y = (uint8_T)(rtu_u << 1);
}

/*
 * Output and update for atomic system:
 *    '<S166>/Bit Shift'
 *    '<S167>/Bit Shift4'
 *    '<S167>/Bit Shift5'
 *    '<S62>/Bit Shift2'
 *    '<S62>/Bit Shift5'
 *    '<S64>/Bit Shift2'
 *    '<S64>/Bit Shift5'
 *    '<S50>/Bit Shift1'
 */
void VCU10_BitShift_p(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S168>/bit_shift' */
  *rty_y = (uint16_T)(rtu_u << 8);
}

/*
 * Output and update for atomic system:
 *    '<S166>/Bit Shift1'
 *    '<S63>/Bit Shift3'
 */
void VCU10_BitShift1_j(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S169>/bit_shift' */
  *rty_y = (uint16_T)((uint32_T)rtu_u >> 2);
}

/*
 * Output and update for atomic system:
 *    '<S166>/Bit Shift2'
 *    '<S63>/Bit Shift2'
 */
void VCU10_BitShift2_b(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S170>/bit_shift' */
  *rty_y = (uint16_T)(rtu_u << 6);
}

/*
 * Output and update for atomic system:
 *    '<S166>/Bit Shift3'
 *    '<S62>/Bit Shift1'
 *    '<S62>/Bit Shift4'
 *    '<S63>/Bit Shift8'
 *    '<S64>/Bit Shift1'
 *    '<S64>/Bit Shift4'
 */
void VCU10_BitShift3(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S171>/bit_shift' */
  *rty_y = (uint16_T)((uint32_T)rtu_u >> 4);
}

/*
 * Output and update for atomic system:
 *    '<S166>/Bit Shift4'
 *    '<S62>/Bit Shift'
 *    '<S62>/Bit Shift3'
 *    '<S63>/Bit Shift7'
 *    '<S64>/Bit Shift'
 *    '<S64>/Bit Shift3'
 */
void VCU10_BitShift4(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S172>/bit_shift' */
  *rty_y = (uint16_T)(rtu_u << 4);
}

/*
 * Output and update for atomic system:
 *    '<S166>/Bit Shift8'
 *    '<S167>/Bit Shift'
 */
void VCU10_BitShift8(real_T rtu_u, real_T *rty_y)
{
  /* MATLAB Function: '<S175>/bit_shift' */
  *rty_y = ldexp(rtu_u, 8);
}

/*
 * Output and update for atomic system:
 *    '<S167>/Bit Shift1'
 *    '<S61>/Bit Shift14'
 *    '<S61>/Bit Shift16'
 */
void VCU10_BitShift1_i(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S185>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 7);
}

/*
 * Output and update for atomic system:
 *    '<S167>/Bit Shift2'
 *    '<S61>/Bit Shift13'
 */
void VCU10_BitShift2_e(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S186>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 6);
}

/*
 * Output and update for atomic system:
 *    '<S235>/Bit Shift3'
 *    '<S143>/Bit Shift6'
 */
void VCU10_BitShift3_m(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S242>/bit_shift' */
  *rty_y = (uint8_T)(rtu_u << 6);
}

/*
 * Output and update for atomic system:
 *    '<S235>/Bit Shift5'
 *    '<S235>/Bit Shift8'
 *    '<S235>/Bit Shift9'
 *    '<S236>/Bit Shift'
 *    '<S236>/Bit Shift1'
 *    '<S143>/Bit Shift2'
 *    '<S143>/Bit Shift5'
 *    '<S48>/Bit Shift'
 */
void VCU10_BitShift5(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S244>/bit_shift' */
  *rty_y = (uint16_T)((uint32_T)rtu_u >> 8);
}

/*
 * Output and update for atomic system:
 *    '<S235>/Bit Shift6'
 *    '<S143>/Bit Shift1'
 *    '<S143>/Bit Shift4'
 */
void VCU10_BitShift6(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S245>/bit_shift' */
  *rty_y = (uint16_T)(rtu_u << 4);
}

/*
 * Output and update for atomic system:
 *    '<S235>/Bit Shift7'
 *    '<S143>/Bit Shift'
 *    '<S143>/Bit Shift3'
 *    '<S196>/Bit Shift5'
 */
void VCU10_BitShift7(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S246>/bit_shift' */
  *rty_y = (uint16_T)((uint32_T)rtu_u >> 4);
}

/*
 * Output and update for atomic system:
 *    '<S61>/Bit Shift10'
 *    '<S61>/Bit Shift3'
 */
void VCU10_BitShift10(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S68>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 3);
}

/*
 * Output and update for atomic system:
 *    '<S61>/Bit Shift4'
 *    '<S61>/Bit Shift6'
 */
void VCU10_BitShift4_h(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S77>/bit_shift' */
  *rty_y = (uint8_T)(rtu_u << 4);
}

/* Function for Chart: '<S3>/Chart' */
static void VCU10_enter_atomic_AS_Emergency(void)
{
  VCU10_B.r2d_flag_a = 0.0;
  VCU10_B.steering_flag_o = 1.0;
  VCU10_B.brake_flag_p = 1.0;
  VCU10_B.as_ebs_trig = 1.0;
  VCU10_B.as_led_yellow = 0.0;
  VCU10_B.as_led_blue = 2.0;
  VCU10_B.as_off_flag_g = 0.0;
  VCU10_B.as_ready_flag_a = 0.0;
  VCU10_B.as_driving_flag_a = 0.0;
  VCU10_B.as_finished_flag_a = 0.0;
  VCU10_B.as_emergency_flag_m = 1.0;
  VCU10_B.manual_driving_flag_j = 0.0;
  VCU10_B.safety_lock = 1.0;
}

/* Function for Chart: '<S3>/Chart' */
static void VCU10_AS_Driving(const boolean_T *FSEC_Safety_Fault_Delay, const
  boolean_T *res_stop, const boolean_T *LogicalOperator_o)
{
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T guard3 = false;
  boolean_T tmp;

  /* DataStoreRead: '<Root>/Data Store Read7' */
  tmp = (VCU10_DW.ebs_working || (*FSEC_Safety_Fault_Delay) || (!asms));
  guard1 = false;
  guard2 = false;
  guard3 = false;
  if (tmp || (*res_stop)) {
    guard2 = true;
  } else {
    boolean_T tmp_0;
    boolean_T tmp_1;
    tmp_0 = !*FSEC_Safety_Fault_Delay;
    tmp_1 = !*res_stop;
    if ((*LogicalOperator_o) && VCU10_DW.task_finish && tmp_0 && asms && tmp_1)
    {
      guard3 = true;
    } else if (VCU10_DW.inspection_flag) {
      if (tmp || (*res_stop)) {
        guard2 = true;
      } else if ((VCU10_DW.temporalCounter_i1 >= 2700U) && tmp_0 && asms &&
                 tmp_1) {
        guard3 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
  }

  if (guard3) {
    VCU10_DW.is_AS_Driving = VCU10_IN_NO_ACTIVE_CHILD;
    VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Finished;
    VCU10_B.r2d_flag_a = 0.0;
    VCU10_B.steering_flag_o = 0.0;
    VCU10_B.brake_flag_p = 0.0;
    VCU10_B.as_ebs_trig = 1.0;
    VCU10_B.as_led_yellow = 0.0;
    VCU10_B.as_led_blue = 1.0;
    VCU10_B.as_off_flag_g = 0.0;
    VCU10_B.as_ready_flag_a = 0.0;
    VCU10_B.as_driving_flag_a = 0.0;
    VCU10_B.as_finished_flag_a = 1.0;
    VCU10_B.as_emergency_flag_m = 0.0;
    VCU10_B.manual_driving_flag_j = 0.0;
    VCU10_B.safety_lock = 1.0;
  }

  if (guard2) {
    VCU10_DW.is_AS_Driving = VCU10_IN_NO_ACTIVE_CHILD;
    VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Emergency;
    VCU10_enter_atomic_AS_Emergency();
  }

  if (guard1) {
    if (VCU10_DW.is_AS_Driving == VCU10_IN_R2D) {
      /* DataStoreRead: '<Root>/Data Store Read10' */
      if (VCU10_DW.steer_zero) {
        VCU10_B.steer_return = F;
        VCU10_B.r2d_warning = F;
        VCU10_DW.is_AS_Driving = VCU10_IN_go;
        VCU10_B.r2d_flag_a = 0.0;
        VCU10_B.steering_flag_o = 1.0;
        VCU10_B.brake_flag_p = 1.0;
        VCU10_B.as_led_yellow = 2.0;
        VCU10_B.as_led_blue = 0.0;
        VCU10_B.as_off_flag_g = 0.0;
        VCU10_B.as_ready_flag_a = 0.0;
        VCU10_B.as_driving_flag_a = 1.0;
        VCU10_B.as_finished_flag_a = 0.0;
        VCU10_B.as_emergency_flag_m = 0.0;
        VCU10_B.manual_driving_flag_j = 0.0;
      }

      /* End of DataStoreRead: '<Root>/Data Store Read10' */
    } else {
      /* case IN_go: */
      VCU10_B.r2d_flag_a = 0.0;
      VCU10_B.steering_flag_o = 1.0;
      VCU10_B.brake_flag_p = 1.0;
      VCU10_B.as_led_yellow = 2.0;
      VCU10_B.as_led_blue = 0.0;
      VCU10_B.as_off_flag_g = 0.0;
      VCU10_B.as_ready_flag_a = 0.0;
      VCU10_B.as_driving_flag_a = 1.0;
      VCU10_B.as_finished_flag_a = 0.0;
      VCU10_B.as_emergency_flag_m = 0.0;
      VCU10_B.manual_driving_flag_j = 0.0;
    }
  }
}

/* Function for Chart: '<S3>/Chart' */
static void VCU10_enter_atomic_AS_Off(void)
{
  VCU10_B.r2d_flag_a = 0.0;
  VCU10_B.steering_flag_o = 0.0;
  VCU10_B.brake_flag_p = 0.0;
  VCU10_B.as_led_yellow = 0.0;
  VCU10_B.as_led_blue = 0.0;
  VCU10_B.as_off_flag_g = 1.0;
  VCU10_B.as_ready_flag_a = 0.0;
  VCU10_B.as_driving_flag_a = 0.0;
  VCU10_B.as_finished_flag_a = 0.0;
  VCU10_B.as_emergency_flag_m = 0.0;
  VCU10_B.manual_driving_flag_j = 0.0;
  VCU10_B.as_ebs_trig = 0.0;
}

/* Function for Chart: '<S3>/Chart' */
static void VCU10_AS_Off(const boolean_T *FSEC_Safety_Fault_Delay, const
  boolean_T *LogicalOperator)
{
  boolean_T tmp;
  tmp = !*FSEC_Safety_Fault_Delay;
  if ((*LogicalOperator) && tmp && (VCU10_B.safety_lock == 0.0)) {
    /* DataStoreRead: '<Root>/Data Store Read4' incorporates:
     *  DataStoreRead: '<Root>/Data Store Read6'
     */
    if ((!VCU10_DW.ebs_check) && VCU10_DW.ts) {
      VCU10_DW.is_c1_VCU10 = VCU10_IN_Manual_Driving_n;
      VCU10_B.r2d_flag_a = 0.0;
      VCU10_B.steering_flag_o = 0.0;
      VCU10_B.brake_flag_p = 0.0;
      VCU10_B.as_led_yellow = 0.0;
      VCU10_B.as_led_blue = 0.0;
      VCU10_B.as_off_flag_g = 0.0;
      VCU10_B.as_ready_flag_a = 0.0;
      VCU10_B.as_driving_flag_a = 0.0;
      VCU10_B.as_finished_flag_a = 0.0;
      VCU10_B.as_emergency_flag_m = 0.0;
      VCU10_B.manual_driving_flag_j = 1.0;
      VCU10_B.as_ebs_trig = 0.0;
    } else {
      VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Off;
      VCU10_enter_atomic_AS_Off();
    }

    /* End of DataStoreRead: '<Root>/Data Store Read4' */
  } else if (VCU10_DW.astask_flag && asms && tmp && (VCU10_B.safety_lock == 0.0))
  {
    VCU10_B.brake_flag_p = 2.0;
    VCU10_DW.is_c1_VCU10 = VCU10_IN_transition;
  } else {
    VCU10_B.r2d_flag_a = 0.0;
    VCU10_B.steering_flag_o = 0.0;
    VCU10_B.brake_flag_p = 0.0;
    VCU10_B.as_led_yellow = 0.0;
    VCU10_B.as_led_blue = 0.0;
    VCU10_B.as_off_flag_g = 1.0;
    VCU10_B.as_ready_flag_a = 0.0;
    VCU10_B.as_driving_flag_a = 0.0;
    VCU10_B.as_finished_flag_a = 0.0;
    VCU10_B.as_emergency_flag_m = 0.0;
    VCU10_B.manual_driving_flag_j = 0.0;
    VCU10_B.as_ebs_trig = 0.0;
  }
}

/* Model step function */
void VCU10_step(void)
{
  real_T airprs_sensor1;
  real_T airprs_sensor2;
  real_T apps1_01;
  real_T apps2_01;
  real_T oilprs_rlsensor;
  real_T rtb_DataTypeConversion1;
  real_T rtb_Emergency_Pressure_Select_1;
  real_T rtb_Emergency_Pressure_Select_4;
  real_T rtb_Product1;
  real_T rtb_Product2;
  real_T rtb_y;
  int32_T i;
  int32_T rtb_blue_0;
  real32_T wheel_f_sel;
  real32_T wheel_h_sel;
  real32_T wheel_raw;
  uint32_T elapsedTicks;
  uint32_T elapsedTicks_m;
  uint16_T rtb_ain_sel[5];
  uint16_T rtb_Add1_a;
  uint16_T rtb_Add2_g;
  uint16_T rtb_y_cg;
  uint16_T rtb_y_dz;
  uint16_T rtb_y_ec;
  uint16_T rtb_y_gw;
  uint16_T rtb_y_ia;
  uint16_T rtb_y_ku;
  uint16_T rtb_y_ld;
  uint16_T rtb_y_nd;
  uint16_T rtb_y_po;
  uint16_T wheel_u16;
  uint8_T active;
  uint8_T requested;
  uint8_T rtb_y_ev;
  uint8_T rtb_y_in;
  uint8_T rtb_y_pq;
  boolean_T EBS_Sensor_Fault_Delay;
  boolean_T LogicalOperator_e;
  boolean_T LogicalOperator_o;
  boolean_T brake_now;
  boolean_T guard1 = false;
  boolean_T rtb_AS_Torque_Enable;

  /* MATLAB Function: '<Root>/DBC_Debug_Select' incorporates:
   *  Inport: '<Root>/model_ain'
   *  Inport: '<Root>/model_hin'
   *  Inport: '<Root>/vcu_dbg_air_wheel'
   *  Inport: '<Root>/vcu_dbg_control'
   *  Inport: '<Root>/vcu_dbg_digital'
   *  Inport: '<Root>/vcu_dbg_pedal_adc'
   *  Inport: '<Root>/vcu_dbg_rx_count'
   *  Inport: '<Root>/wlspd_fsensor'
   *  Inport: '<Root>/wlspd_hsensor'
   */
  rtb_y_ld = model_hin;
  for (i = 0; i < 5; i++) {
    rtb_ain_sel[i] = model_ain[i];
  }

  wheel_f_sel = wlspd_fsensor;
  wheel_h_sel = wlspd_hsensor;
  if (vcu_dbg_rx_count[0] != VCU10_DW.last_count[0]) {
    VCU10_DW.last_count[0] = vcu_dbg_rx_count[0];
    VCU10_DW.ages[0] = 0U;
  } else if (VCU10_DW.ages[0] < 50) {
    i = (int32_T)(VCU10_DW.ages[0] + 1U);
    if (VCU10_DW.ages[0] + 1U > 255U) {
      i = 255;
    }

    VCU10_DW.ages[0] = (uint8_T)i;
  }

  if (vcu_dbg_rx_count[1] != VCU10_DW.last_count[1]) {
    VCU10_DW.last_count[1] = vcu_dbg_rx_count[1];
    VCU10_DW.ages[1] = 0U;
  } else if (VCU10_DW.ages[1] < 50) {
    i = (int32_T)(VCU10_DW.ages[1] + 1U);
    if (VCU10_DW.ages[1] + 1U > 255U) {
      i = 255;
    }

    VCU10_DW.ages[1] = (uint8_T)i;
  }

  if (vcu_dbg_rx_count[2] != VCU10_DW.last_count[2]) {
    VCU10_DW.last_count[2] = vcu_dbg_rx_count[2];
    VCU10_DW.ages[2] = 0U;
  } else if (VCU10_DW.ages[2] < 50) {
    i = (int32_T)(VCU10_DW.ages[2] + 1U);
    if (VCU10_DW.ages[2] + 1U > 255U) {
      i = 255;
    }

    VCU10_DW.ages[2] = (uint8_T)i;
  }

  if (vcu_dbg_rx_count[3] != VCU10_DW.last_count[3]) {
    VCU10_DW.last_count[3] = vcu_dbg_rx_count[3];
    VCU10_DW.ages[3] = 0U;
  } else if (VCU10_DW.ages[3] < 50) {
    i = (int32_T)(VCU10_DW.ages[3] + 1U);
    if (VCU10_DW.ages[3] + 1U > 255U) {
      i = 255;
    }

    VCU10_DW.ages[3] = (uint8_T)i;
  }

  requested = 0U;
  if ((vcu_dbg_control[0] == 165) && (vcu_dbg_control[1] == 90) &&
      (VCU10_DW.ages[0] < 50)) {
    requested = (uint8_T)(vcu_dbg_control[2] & 15);
  }

  active = 0U;
  if ((requested & 1U) != 0U) {
    active = 1U;
    if (((requested & 2U) != 0U) && (VCU10_DW.ages[1] < 50)) {
      active = 3U;
    }

    if (((requested & 4U) != 0U) && (VCU10_DW.ages[2] < 50)) {
      active = (uint8_T)(active | 4);
    }

    if (((requested & 8U) != 0U) && (VCU10_DW.ages[3] < 50)) {
      active = (uint8_T)(active | 8);
      rtb_y_ld = (uint16_T)((vcu_dbg_digital[1] << 8) + vcu_dbg_digital[0]);
    }
  }

  elapsedTicks_m = active & 2U;
  if (elapsedTicks_m != 0U) {
    rtb_ain_sel[0] = (uint16_T)((vcu_dbg_pedal_adc[1] << 8) + vcu_dbg_pedal_adc
      [0]);
    rtb_ain_sel[1] = (uint16_T)((vcu_dbg_pedal_adc[3] << 8) + vcu_dbg_pedal_adc
      [2]);
    rtb_ain_sel[2] = (uint16_T)((vcu_dbg_pedal_adc[5] << 8) + vcu_dbg_pedal_adc
      [4]);
  }

  if ((active & 4U) != 0U) {
    rtb_ain_sel[3] = (uint16_T)((vcu_dbg_air_wheel[1] << 8) + vcu_dbg_air_wheel
      [0]);
    rtb_ain_sel[4] = (uint16_T)((vcu_dbg_air_wheel[3] << 8) + vcu_dbg_air_wheel
      [2]);
    wheel_f_sel = (real32_T)((vcu_dbg_air_wheel[5] << 8) + vcu_dbg_air_wheel[4])
      * 0.1F;
    wheel_h_sel = (real32_T)((vcu_dbg_air_wheel[7] << 8) + vcu_dbg_air_wheel[6])
      * 0.1F;
  }

  for (i = 0; i < 8; i++) {
    /* Outport: '<Root>/vcu_dbg_pedal_echo' incorporates:
     *  MATLAB Function: '<Root>/DBC_Debug_Select'
     */
    VCU10_Y.vcu_dbg_pedal_echo[i] = 0U;
  }

  /* MATLAB Function: '<Root>/DBC_Debug_Select' incorporates:
   *  Inport: '<Root>/vcu_dbg_rx_count'
   *  MATLAB Function: '<Root>/DBC_Debug_StatusPack'
   *  Outport: '<Root>/vcu_dbg_air_wheel_echo'
   *  Outport: '<Root>/vcu_dbg_pedal_echo'
   *  Outport: '<Root>/vcu_dbg_status'
   */
  VCU10_Y.vcu_dbg_status[0] = active;
  VCU10_Y.vcu_dbg_status[1] = requested;
  VCU10_Y.vcu_dbg_status[2] = (uint8_T)(rtb_y_ld & 255);
  VCU10_Y.vcu_dbg_status[3] = (uint8_T)((uint32_T)rtb_y_ld >> 8);
  VCU10_Y.vcu_dbg_status[6] = VCU10_DW.ages[0];
  VCU10_Y.vcu_dbg_status[7] = vcu_dbg_rx_count[0];
  VCU10_Y.vcu_dbg_pedal_echo[0] = (uint8_T)(rtb_ain_sel[0] & 255);
  VCU10_Y.vcu_dbg_pedal_echo[1] = (uint8_T)((uint32_T)rtb_ain_sel[0] >> 8);
  VCU10_Y.vcu_dbg_pedal_echo[2] = (uint8_T)(rtb_ain_sel[1] & 255);
  VCU10_Y.vcu_dbg_pedal_echo[3] = (uint8_T)((uint32_T)rtb_ain_sel[1] >> 8);
  VCU10_Y.vcu_dbg_pedal_echo[4] = (uint8_T)(rtb_ain_sel[2] & 255);
  VCU10_Y.vcu_dbg_pedal_echo[5] = (uint8_T)((uint32_T)rtb_ain_sel[2] >> 8);
  if (elapsedTicks_m != 0U) {
    VCU10_Y.vcu_dbg_pedal_echo[6] = 1U;
  }

  VCU10_Y.vcu_dbg_pedal_echo[7] = vcu_dbg_rx_count[1];
  VCU10_Y.vcu_dbg_air_wheel_echo[0] = (uint8_T)(rtb_ain_sel[3] & 255);
  VCU10_Y.vcu_dbg_air_wheel_echo[1] = (uint8_T)((uint32_T)rtb_ain_sel[3] >> 8);
  VCU10_Y.vcu_dbg_air_wheel_echo[2] = (uint8_T)(rtb_ain_sel[4] & 255);
  VCU10_Y.vcu_dbg_air_wheel_echo[3] = (uint8_T)((uint32_T)rtb_ain_sel[4] >> 8);
  wheel_raw = wheel_f_sel * 10.0F;
  if (wheel_raw <= 0.0F) {
    wheel_u16 = 0U;
  } else if (wheel_raw >= 65535.0F) {
    wheel_u16 = MAX_uint16_T;
  } else {
    wheel_raw = floorf(wheel_raw + 0.5F);
    if (wheel_raw < 65536.0F) {
      wheel_u16 = (uint16_T)wheel_raw;
    } else {
      wheel_u16 = MAX_uint16_T;
    }
  }

  VCU10_Y.vcu_dbg_air_wheel_echo[4] = (uint8_T)(wheel_u16 & 255);
  VCU10_Y.vcu_dbg_air_wheel_echo[5] = (uint8_T)((uint32_T)wheel_u16 >> 8);
  wheel_raw = wheel_h_sel * 10.0F;
  if (wheel_raw <= 0.0F) {
    wheel_u16 = 0U;
  } else if (wheel_raw >= 65535.0F) {
    wheel_u16 = MAX_uint16_T;
  } else {
    wheel_raw = floorf(wheel_raw + 0.5F);
    if (wheel_raw < 65536.0F) {
      wheel_u16 = (uint16_T)wheel_raw;
    } else {
      wheel_u16 = MAX_uint16_T;
    }
  }

  VCU10_Y.vcu_dbg_air_wheel_echo[6] = (uint8_T)(wheel_u16 & 255);
  VCU10_Y.vcu_dbg_air_wheel_echo[7] = (uint8_T)((uint32_T)wheel_u16 >> 8);

  /* S-Function (fcgen): '<Root>/Function-Call Generator' incorporates:
   *  SubSystem: '<Root>/Input_Convert'
   */
  /* Outputs for Atomic SubSystem: '<S196>/Bit Shift5' */
  /* S-Function (sfix_bitop): '<S196>/Bitwise AND4' incorporates:
   *  MATLAB Function: '<Root>/DBC_Debug_Select'
   */
  VCU10_BitShift7((uint16_T)(rtb_y_ld & 16), &wheel_u16);

  /* End of Outputs for SubSystem: '<S196>/Bit Shift5' */

  /* DataTypeConversion: '<S196>/Data Type Conversion' incorporates:
   *  MATLAB Function: '<Root>/DBC_Debug_Select'
   *  S-Function (sfix_bitop): '<S196>/Bitwise AND7'
   */
  ebs_driver_check = ((rtb_y_ld & 1U) != 0U);

  /* Outputs for Atomic SubSystem: '<S196>/Bit Shift1' */
  /* DataTypeConversion: '<S196>/Data Type Conversion1' incorporates:
   *  MATLAB Function: '<Root>/DBC_Debug_Select'
   *  MATLAB Function: '<S203>/bit_shift'
   *  S-Function (sfix_bitop): '<S196>/Bitwise AND1'
   */
  shutdown_s = ((int32_T)((uint32_T)(rtb_y_ld & 2) >> 1) != 0);

  /* End of Outputs for SubSystem: '<S196>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S196>/Bit Shift2' */
  /* DataTypeConversion: '<S196>/Data Type Conversion2' incorporates:
   *  MATLAB Function: '<Root>/DBC_Debug_Select'
   *  MATLAB Function: '<S204>/bit_shift'
   *  S-Function (sfix_bitop): '<S196>/Bitwise AND2'
   */
  shutdown_e = ((int32_T)((uint32_T)(rtb_y_ld & 4) >> 2) != 0);

  /* End of Outputs for SubSystem: '<S196>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S196>/Bit Shift4' */
  /* DataTypeConversion: '<S196>/Data Type Conversion3' incorporates:
   *  MATLAB Function: '<Root>/DBC_Debug_Select'
   *  MATLAB Function: '<S206>/bit_shift'
   *  S-Function (sfix_bitop): '<S196>/Bitwise AND3'
   */
  di8_cockpit = ((int32_T)((uint32_T)(rtb_y_ld & 8) >> 3) != 0);

  /* End of Outputs for SubSystem: '<S196>/Bit Shift4' */

  /* DataTypeConversion: '<S196>/Data Type Conversion4' */
  di8_side = (wheel_u16 != 0);

  /* Outputs for Atomic SubSystem: '<S196>/Bit Shift6' */
  /* DataTypeConversion: '<S196>/Data Type Conversion5' incorporates:
   *  MATLAB Function: '<Root>/DBC_Debug_Select'
   *  MATLAB Function: '<S208>/bit_shift'
   *  S-Function (sfix_bitop): '<S196>/Bitwise AND5'
   */
  run_button = ((int32_T)((uint32_T)(rtb_y_ld & 32) >> 5) != 0);

  /* End of Outputs for SubSystem: '<S196>/Bit Shift6' */

  /* Outputs for Atomic SubSystem: '<S196>/Bit Shift7' */
  /* DataTypeConversion: '<S196>/Data Type Conversion6' incorporates:
   *  MATLAB Function: '<Root>/DBC_Debug_Select'
   *  MATLAB Function: '<S209>/bit_shift'
   *  S-Function (sfix_bitop): '<S196>/Bitwise AND6'
   */
  tsms = ((int32_T)((uint32_T)(rtb_y_ld & 64) >> 6) != 0);

  /* End of Outputs for SubSystem: '<S196>/Bit Shift7' */

  /* Outputs for Atomic SubSystem: '<S196>/Bit Shift3' */
  /* DataTypeConversion: '<S196>/Data Type Conversion7' incorporates:
   *  MATLAB Function: '<Root>/DBC_Debug_Select'
   *  MATLAB Function: '<S205>/bit_shift'
   *  S-Function (sfix_bitop): '<S196>/Bitwise AND8'
   */
  asms = ((int32_T)((uint32_T)(rtb_y_ld & 128) >> 7) != 0);

  /* End of Outputs for SubSystem: '<S196>/Bit Shift3' */

  /* Gain: '<S201>/Gain' incorporates:
   *  DataTypeConversion: '<S201>/Data Type Conversion'
   */
  wheel_raw = 0.00241699209F * (real32_T)rtb_ain_sel[4];

  /* Saturate: '<S201>/Saturation' */
  if (wheel_raw > 10.0F) {
    wheel_raw = 10.0F;
  }

  /* End of Saturate: '<S201>/Saturation' */

  /* DataTypeConversion: '<S12>/Data Type Conversion' incorporates:
   *  Gain: '<S12>/Gain'
   */
  airprs2 = (uint16_T)(int32_T)fmodf((real32_T)(int32_T)floorf(1000.0F *
    wheel_raw), 65536.0F);

  /* Gain: '<S200>/Gain' incorporates:
   *  DataTypeConversion: '<S200>/Data Type Conversion'
   */
  wheel_raw = 0.00241699209F * (real32_T)rtb_ain_sel[3];

  /* Saturate: '<S200>/Saturation' */
  if (wheel_raw > 10.0F) {
    wheel_raw = 10.0F;
  }

  /* End of Saturate: '<S200>/Saturation' */

  /* DataTypeConversion: '<S12>/Data Type Conversion1' incorporates:
   *  Gain: '<S12>/Gain1'
   */
  airprs1 = (uint16_T)(int32_T)fmodf((real32_T)(int32_T)floorf(1000.0F *
    wheel_raw), 65536.0F);

  /* Gain: '<S199>/Gain' incorporates:
   *  DataTypeConversion: '<S199>/Data Type Conversion'
   */
  wheel_raw = 0.0001875F * (real32_T)rtb_ain_sel[2];

  /* Saturate: '<S199>/Saturation' */
  if (wheel_raw > 5.0F) {
    wheel_raw = 5.0F;
  }

  /* End of Saturate: '<S199>/Saturation' */

  /* DataTypeConversion: '<S12>/Data Type Conversion2' incorporates:
   *  Gain: '<S12>/Gain2'
   */
  brkps = (uint16_T)(int32_T)fmodf((real32_T)(int32_T)floorf(1000.0F * wheel_raw),
    65536.0F);

  /* Gain: '<S198>/Gain' incorporates:
   *  DataTypeConversion: '<S198>/Data Type Conversion'
   */
  wheel_raw = 0.0001875F * (real32_T)rtb_ain_sel[1];

  /* Saturate: '<S198>/Saturation' */
  if (wheel_raw > 5.0F) {
    wheel_raw = 5.0F;
  }

  /* End of Saturate: '<S198>/Saturation' */

  /* DataTypeConversion: '<S12>/Data Type Conversion3' incorporates:
   *  Gain: '<S12>/Gain3'
   */
  apps2 = (uint16_T)(int32_T)fmodf((real32_T)(int32_T)floorf(1000.0F * wheel_raw),
    65536.0F);

  /* Gain: '<S197>/Gain' incorporates:
   *  DataTypeConversion: '<S197>/Data Type Conversion'
   */
  wheel_raw = 0.0001875F * (real32_T)rtb_ain_sel[0];

  /* Saturate: '<S197>/Saturation' */
  if (wheel_raw > 5.0F) {
    wheel_raw = 5.0F;
  }

  /* End of Saturate: '<S197>/Saturation' */

  /* DataTypeConversion: '<S12>/Data Type Conversion4' incorporates:
   *  Gain: '<S12>/Gain4'
   */
  apps1 = (uint16_T)(int32_T)fmodf((real32_T)(int32_T)floorf(1000.0F * wheel_raw),
    65536.0F);

  /* End of Outputs for S-Function (fcgen): '<Root>/Function-Call Generator' */

  /* S-Function (fcgen): '<Root>/10ms' incorporates:
   *  SubSystem: '<Root>/Sensor_Signal'
   */
  /* DataTypeConversion: '<S17>/Data Type Conversion12' incorporates:
   *  Gain: '<S17>/Gain'
   */
  airprs_sensor1 = 33554.0 * (real_T)airprs1 * 2.9802322387695312E-8;

  /* DataTypeConversion: '<S17>/Data Type Conversion15' incorporates:
   *  Gain: '<S17>/Gain1'
   */
  airprs_sensor2 = 33554.0 * (real_T)airprs2 * 2.9802322387695312E-8;

  /* Product: '<S277>/Product1' incorporates:
   *  Constant: '<S277>/Constant'
   *  DataTypeConversion: '<S17>/Data Type Conversion6'
   *  Gain: '<S277>/Gain'
   *  Gain: '<S277>/Gain1'
   *  MATLAB Function: '<Root>/DBC_Debug_Select'
   *  Product: '<S277>/Divide'
   */
  rtb_Product1 = 36.0 * wheel_f_sel * 3.1415 / 180.0 * VCU10_ConstB.Product;

  /* Product: '<S277>/Product2' incorporates:
   *  Constant: '<S277>/Constant3'
   *  DataTypeConversion: '<S17>/Data Type Conversion7'
   *  Gain: '<S277>/Gain2'
   *  Gain: '<S277>/Gain3'
   *  MATLAB Function: '<Root>/DBC_Debug_Select'
   *  Product: '<S277>/Divide1'
   */
  rtb_Product2 = 36.0 * wheel_h_sel * 3.1415 / 180.0 * VCU10_ConstB.Product;

  /* Lookup_n-D: '<S17>/1-D Lookup Table' incorporates:
   *  DataTypeConversion: '<S12>/Data Type Conversion4'
   */
  apps1_01 = look1_iu16td_linlcapw(apps1, VCU10_ConstP.pooled37,
    VCU10_ConstP.pooled2, 1U);

  /* Saturate: '<S17>/Saturation' */
  if (apps1_01 > 1.0) {
    /* Saturate: '<S17>/Saturation' */
    apps1_01 = 1.0;
  } else if (apps1_01 < 0.0) {
    /* Saturate: '<S17>/Saturation' */
    apps1_01 = 0.0;
  }

  /* End of Saturate: '<S17>/Saturation' */

  /* Lookup_n-D: '<S17>/1-D Lookup Table9' incorporates:
   *  DataTypeConversion: '<S12>/Data Type Conversion3'
   */
  apps2_01 = look1_iu16td_linlcapw(apps2, VCU10_ConstP.pooled37,
    VCU10_ConstP.pooled2, 1U);

  /* Saturate: '<S17>/Saturation1' */
  if (apps2_01 > 1.0) {
    /* Saturate: '<S17>/Saturation1' */
    apps2_01 = 1.0;
  } else if (apps2_01 < 0.0) {
    /* Saturate: '<S17>/Saturation1' */
    apps2_01 = 0.0;
  }

  /* End of Saturate: '<S17>/Saturation1' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */

  /* S-Function (fcgen): '<Root>/10ms10' incorporates:
   *  SubSystem: '<Root>/Res'
   */
  /* Outputs for Atomic SubSystem: '<S267>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S267>/Bitwise AND2' incorporates:
   *  Inport: '<Root>/res_msg'
   */
  VCU10_BitShift1((uint8_T)(res_msg[0] & 4), &active);

  /* End of Outputs for SubSystem: '<S267>/Bit Shift1' */

  /* Chart: '<S271>/heaartbeat_chart' incorporates:
   *  Inport: '<Root>/res_msg'
   *  S-Function (sfix_bitop): '<S267>/Bitwise AND4'
   */
  requested = VCU10_DW.res_heartbeat_start;
  VCU10_DW.res_heartbeat_start = res_msg[1];
  if (VCU10_DW.is_active_c10_VCU10 == 0U) {
    VCU10_DW.is_active_c10_VCU10 = 1U;
    VCU10_DW.is_c10_VCU10 = VCU10_IN_begin_f;
  } else {
    switch (VCU10_DW.is_c10_VCU10) {
     case VCU10_IN_begin_f:
      if (requested != VCU10_DW.res_heartbeat_start) {
        VCU10_DW.is_c10_VCU10 = VCU10_IN_compare;
        VCU10_B.res_hbcheck = 1.0;
      }
      break;

     case VCU10_IN_compare:
      if (requested == VCU10_DW.res_heartbeat_start) {
        VCU10_DW.is_c10_VCU10 = VCU10_IN_same;
        VCU10_DW.hbcnt++;
      } else {
        VCU10_B.res_hbcheck = 1.0;
      }
      break;

     case VCU10_IN_judge:
      if (requested != VCU10_DW.res_heartbeat_start) {
        VCU10_DW.hbcnt = 0.0;
        VCU10_DW.is_c10_VCU10 = VCU10_IN_compare;
        VCU10_B.res_hbcheck = 1.0;
      } else {
        VCU10_B.res_hbcheck = 0.0;
      }
      break;

     default:
      /* case IN_same: */
      if (VCU10_DW.hbcnt > 30.0) {
        VCU10_DW.is_c10_VCU10 = VCU10_IN_judge;
        VCU10_B.res_hbcheck = 0.0;
      } else if (requested != VCU10_DW.res_heartbeat_start) {
        VCU10_DW.hbcnt = 0.0;
        VCU10_DW.is_c10_VCU10 = VCU10_IN_compare;
        VCU10_B.res_hbcheck = 1.0;
      } else {
        VCU10_DW.hbcnt++;
      }
      break;
    }
  }

  /* End of Chart: '<S271>/heaartbeat_chart' */

  /* S-Function (sfix_bitop): '<S267>/Logical Operator' incorporates:
   *  Inport: '<Root>/res_msg'
   */
  requested = (uint8_T)(res_msg[0] ^ res_msg[1]);

  /* Chart: '<S271>/xor_Check' incorporates:
   *  Inport: '<Root>/res_msg'
   *  S-Function (sfix_bitop): '<S267>/Bitwise AND5'
   */
  if (VCU10_DW.is_active_c19_VCU10 == 0U) {
    VCU10_DW.is_active_c19_VCU10 = 1U;
    VCU10_DW.is_c19_VCU10 = VCU10_IN_Init;
    VCU10_DW.err_cnt = 0.0;
  } else {
    switch (VCU10_DW.is_c19_VCU10) {
     case VCU10_IN_Init:
      if (res_msg[2] == requested) {
        VCU10_DW.is_c19_VCU10 = VCU10_IN_compare;
        VCU10_B.xorcheck = 1.0;
      }
      break;

     case VCU10_IN_compare:
      VCU10_B.xorcheck = 1.0;
      if (res_msg[2] != requested) {
        VCU10_DW.is_c19_VCU10 = VCU10_IN_different;
        VCU10_DW.err_cnt++;
      }
      break;

     case VCU10_IN_different:
      if (VCU10_DW.err_cnt >= 10.0) {
        VCU10_DW.is_c19_VCU10 = VCU10_IN_judge_c;
        VCU10_B.xorcheck = 0.0;
      } else if (res_msg[2] == requested) {
        VCU10_DW.err_cnt = 0.0;
        VCU10_DW.is_c19_VCU10 = VCU10_IN_compare;
        VCU10_B.xorcheck = 1.0;
      }
      break;

     default:
      /* case IN_judge: */
      VCU10_B.xorcheck = 0.0;
      if (res_msg[2] == requested) {
        VCU10_DW.err_cnt = 0.0;
        VCU10_DW.is_c19_VCU10 = VCU10_IN_compare;
        VCU10_B.xorcheck = 1.0;
      }
      break;
    }
  }

  /* End of Chart: '<S271>/xor_Check' */

  /* Logic: '<S271>/Logical Operator' incorporates:
   *  DataTypeConversion: '<S267>/Data Type Conversion2'
   */
  LogicalOperator_e = ((active != 0) && (VCU10_B.res_hbcheck != 0.0) &&
                       (VCU10_B.xorcheck != 0.0));

  /* Logic: '<S267>/Validated_Stop' incorporates:
   *  DataTypeConversion: '<S267>/Data Type Conversion7'
   *  Inport: '<Root>/res_msg'
   *  RelationalOperator: '<S267>/Stop_Checksum_Match'
   *  S-Function (sfix_bitop): '<S267>/Bitwise AND'
   *  S-Function (sfix_bitop): '<S267>/Bitwise AND5'
   */
  res_error = (((res_msg[0] & 1U) != 0U) && LogicalOperator_e && (res_msg[2] ==
    requested));

  /* Outputs for Atomic SubSystem: '<S267>/Bit Shift' */
  /* S-Function (sfix_bitop): '<S267>/Bitwise AND1' incorporates:
   *  Inport: '<Root>/res_msg'
   */
  VCU10_BitShift((uint8_T)(res_msg[0] & 2), &requested);

  /* End of Outputs for SubSystem: '<S267>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S267>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S267>/Bitwise AND3' incorporates:
   *  Inport: '<Root>/res_msg'
   */
  VCU10_BitShift2((uint8_T)(res_msg[0] & 16), &rtb_y_in);

  /* End of Outputs for SubSystem: '<S267>/Bit Shift2' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms10' */

  /* S-Function (fcgen): '<Root>/10ms11' incorporates:
   *  SubSystem: '<Root>/IPC'
   */
  /* Outputs for Atomic SubSystem: '<S166>/Bit Shift' */
  /* S-Function (sfix_bitop): '<S166>/Bitwise AND' incorporates:
   *  DataTypeConversion: '<S166>/Data Type Conversion1'
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  VCU10_BitShift_p((uint16_T)(canb_ipctsmsg1[1] & 3), &rtb_y_ec);

  /* End of Outputs for SubSystem: '<S166>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S166>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S166>/Bitwise AND1' incorporates:
   *  DataTypeConversion: '<S166>/Data Type Conversion1'
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  VCU10_BitShift1_j((uint16_T)(canb_ipctsmsg1[1] & 252), &rtb_y_ld);

  /* End of Outputs for SubSystem: '<S166>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S166>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S166>/Bitwise AND2' incorporates:
   *  DataTypeConversion: '<S166>/Data Type Conversion2'
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  VCU10_BitShift2_b((uint16_T)(canb_ipctsmsg1[2] & 15), &wheel_u16);

  /* End of Outputs for SubSystem: '<S166>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S166>/Bit Shift3' */
  /* S-Function (sfix_bitop): '<S166>/Bitwise AND3' incorporates:
   *  DataTypeConversion: '<S166>/Data Type Conversion2'
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  VCU10_BitShift3((uint16_T)(canb_ipctsmsg1[2] & 240), &rtb_y_gw);

  /* End of Outputs for SubSystem: '<S166>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S166>/Bit Shift4' */
  /* S-Function (sfix_bitop): '<S166>/Bitwise AND4' incorporates:
   *  DataTypeConversion: '<S166>/Data Type Conversion3'
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  VCU10_BitShift4((uint16_T)(canb_ipctsmsg1[3] & 63), &rtb_y_cg);

  /* End of Outputs for SubSystem: '<S166>/Bit Shift4' */

  /* Outputs for Atomic SubSystem: '<S166>/Bit Shift8' */
  /* DataTypeConversion: '<S166>/Data Type Conversion7' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  VCU10_BitShift8((real_T)canb_ipctsmsg1[7], &rtb_DataTypeConversion1);

  /* End of Outputs for SubSystem: '<S166>/Bit Shift8' */

  /* DataTypeConversion: '<S166>/Data Type Conversion8' incorporates:
   *  DataTypeConversion: '<S166>/Data Type Conversion4'
   *  Inport: '<Root>/canb_ipctsmsg1'
   *  Sum: '<S166>/Add'
   */
  rtb_Emergency_Pressure_Select_4 = (uint16_T)((uint32_T)canb_ipctsmsg1[0] +
    rtb_y_ec);
  rtb_y = rtb_Emergency_Pressure_Select_4;

  /* Outputs for Atomic SubSystem: '<S167>/Bit Shift' */
  /* DataTypeConversion: '<S167>/Data Type Conversion2' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S11>/canb_ipctsmsg2'
   */
  VCU10_BitShift8((real_T)canb_ipctsmsg2[0], &rtb_y);

  /* End of Outputs for SubSystem: '<S167>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S167>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S167>/Bitwise AND' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S11>/canb_ipctsmsg2'
   */
  VCU10_BitShift1_i((uint8_T)(canb_ipctsmsg2[3] & 128), &requested);

  /* End of Outputs for SubSystem: '<S167>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S167>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S167>/Bitwise AND1' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S11>/canb_ipctsmsg2'
   */
  VCU10_BitShift2_e((uint8_T)(canb_ipctsmsg2[3] & 64), &rtb_y_ev);

  /* End of Outputs for SubSystem: '<S167>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S167>/Bit Shift3' */
  /* S-Function (sfix_bitop): '<S167>/Bitwise AND2' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S11>/canb_ipctsmsg2'
   */
  VCU10_BitShift1((uint8_T)(canb_ipctsmsg2[3] & 60), &rtb_y_pq);

  /* End of Outputs for SubSystem: '<S167>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S167>/Bit Shift4' */
  /* DataTypeConversion: '<S167>/Data Type Conversion6' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S11>/canb_ipctsmsg2'
   */
  VCU10_BitShift_p((uint16_T)canb_ipctsmsg2[4], &rtb_y_ec);

  /* End of Outputs for SubSystem: '<S167>/Bit Shift4' */

  /* Outputs for Atomic SubSystem: '<S167>/Bit Shift5' */
  /* DataTypeConversion: '<S167>/Data Type Conversion8' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S11>/canb_ipctsmsg2'
   */
  VCU10_BitShift_p((uint16_T)canb_ipctsmsg2[6], &rtb_y_ec);

  /* End of Outputs for SubSystem: '<S167>/Bit Shift5' */

  /* Outputs for Atomic SubSystem: '<S161>/Bit Shift' */
  /* S-Function (fcgen): '<Root>/10ms10' incorporates:
   *  SubSystem: '<Root>/Res'
   */
  /* DataTypeConversion: '<S161>/Data Type Conversion2' incorporates:
   *  DataTypeConversion: '<S267>/Data Type Conversion3'
   *  S-Function (sfix_bitop): '<S161>/Bitwise AND1'
   */
  VCU10_BitShift_a((uint8_T)(rtb_y_in != 0), &rtb_y_pq);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms10' */
  /* End of Outputs for SubSystem: '<S161>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S161>/Bit Shift1' */
  /* SignalConversion generated from: '<S11>/canb_ipcrxmsg' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read19'
   *  DataTypeConversion: '<S161>/Data Type Conversion1'
   *  DataTypeConversion: '<S161>/Data Type Conversion4'
   *  MATLAB Function: '<S163>/bit_shift'
   *  S-Function (sfix_bitop): '<S161>/Bitwise AND2'
   *  Sum: '<S161>/Add'
   */
  canb_ipcrxmsg[0] = (uint8_T)((uint32_T)(uint8_T)((uint32_T)
    VCU10_DW.steer_return + rtb_y_pq) + (res_error << 2));

  /* End of Outputs for SubSystem: '<S161>/Bit Shift1' */

  /* DataTypeConversion: '<S161>/Data Type Conversion3' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read17'
   */
  rtb_Emergency_Pressure_Select_1 = floor(VCU10_DW.ipc_astask);
  if (rtIsNaN(rtb_Emergency_Pressure_Select_1) || rtIsInf
      (rtb_Emergency_Pressure_Select_1)) {
    rtb_Emergency_Pressure_Select_1 = 0.0;
  } else {
    rtb_Emergency_Pressure_Select_1 = fmod(rtb_Emergency_Pressure_Select_1,
      256.0);
  }

  /* SignalConversion generated from: '<S11>/canb_ipcrxmsg' incorporates:
   *  DataTypeConversion: '<S161>/Data Type Conversion3'
   */
  canb_ipcrxmsg[1] = (uint8_T)(rtb_Emergency_Pressure_Select_1 < 0.0 ? (int32_T)
    (uint8_T)-(int8_T)(uint8_T)-rtb_Emergency_Pressure_Select_1 : (int32_T)
    (uint8_T)rtb_Emergency_Pressure_Select_1);
  canb_ipcrxmsg[2] = ((uint8_T)0U);
  canb_ipcrxmsg[3] = ((uint8_T)0U);
  canb_ipcrxmsg[4] = ((uint8_T)0U);
  canb_ipcrxmsg[5] = ((uint8_T)0U);
  canb_ipcrxmsg[6] = ((uint8_T)0U);
  canb_ipcrxmsg[7] = ((uint8_T)0U);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */

  /* S-Function (fcgen): '<Root>/10ms7' incorporates:
   *  SubSystem: '<Root>/EBS'
   */
  /* S-Function (fcgen): '<Root>/10ms6' incorporates:
   *  SubSystem: '<Root>/AS_Stateflow'
   */
  /* Logic: '<S3>/Logical Operator' incorporates:
   *  Chart: '<S3>/Chart'
   *  MATLAB Function: '<S7>/EBS_Response_Monitor'
   */
  EBS_Sensor_Fault_Delay = !asms;

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms7' */

  /* S-Function (fcgen): '<Root>/10ms' incorporates:
   *  SubSystem: '<Root>/Sensor_Signal'
   */
  /* DeadZone: '<S39>/Dead Zone' incorporates:
   *  DataTypeConversion: '<S17>/Data Type Conversion8'
   */
  if (rtb_Product1 > 0.5) {
    rtb_Product1 -= 0.5;
  } else if (rtb_Product1 >= -0.5) {
    rtb_Product1 = 0.0;
  } else {
    rtb_Product1 -= -0.5;
  }

  /* End of DeadZone: '<S39>/Dead Zone' */

  /* DeadZone: '<S39>/Dead Zone1' incorporates:
   *  DataTypeConversion: '<S17>/Data Type Conversion9'
   */
  if (rtb_Product2 > 0.5) {
    rtb_Product2 -= 0.5;
  } else if (rtb_Product2 >= -0.5) {
    rtb_Product2 = 0.0;
  } else {
    rtb_Product2 -= -0.5;
  }

  /* End of DeadZone: '<S39>/Dead Zone1' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */

  /* Logic: '<S39>/Logical Operator' incorporates:
   *  Constant: '<S41>/Constant'
   *  Constant: '<S42>/Constant'
   *  RelationalOperator: '<S41>/Compare'
   *  RelationalOperator: '<S42>/Compare'
   */
  LogicalOperator_o = ((rtb_Product1 == 0.0) && (rtb_Product2 == 0.0));

  /* Chart: '<S3>/Chart' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read6'
   *  DataStoreRead: '<Root>/Data Store Read8'
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
      VCU10_AS_Driving(&VCU10_DW.FSEC_Safety_Fault_Delay_DSTATE, &res_error,
                       &LogicalOperator_o);
      break;

     case VCU10_IN_AS_Emergency:
      if ((!VCU10_DW.ebs_warning) && (EBS_Sensor_Fault_Delay &&
           (!VCU10_DW.brake_on))) {
        VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Off;
        VCU10_enter_atomic_AS_Off();
      } else {
        VCU10_B.r2d_flag_a = 0.0;
        VCU10_B.steering_flag_o = 1.0;
        VCU10_B.brake_flag_p = 1.0;
        VCU10_B.as_ebs_trig = 1.0;
        VCU10_B.as_led_yellow = 0.0;
        VCU10_B.as_led_blue = 2.0;
        VCU10_B.as_off_flag_g = 0.0;
        VCU10_B.as_ready_flag_a = 0.0;
        VCU10_B.as_driving_flag_a = 0.0;
        VCU10_B.as_finished_flag_a = 0.0;
        VCU10_B.as_emergency_flag_m = 1.0;
        VCU10_B.manual_driving_flag_j = 0.0;
        VCU10_B.safety_lock = 1.0;
      }
      break;

     case VCU10_IN_AS_Finished:
      if (res_error) {
        VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Emergency;
        VCU10_enter_atomic_AS_Emergency();
      } else if (EBS_Sensor_Fault_Delay && (!VCU10_DW.brake_on)) {
        VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Off;
        VCU10_enter_atomic_AS_Off();
      } else {
        VCU10_B.r2d_flag_a = 0.0;
        VCU10_B.steering_flag_o = 0.0;
        VCU10_B.brake_flag_p = 0.0;
        VCU10_B.as_ebs_trig = 1.0;
        VCU10_B.as_led_yellow = 0.0;
        VCU10_B.as_led_blue = 1.0;
        VCU10_B.as_off_flag_g = 0.0;
        VCU10_B.as_ready_flag_a = 0.0;
        VCU10_B.as_driving_flag_a = 0.0;
        VCU10_B.as_finished_flag_a = 1.0;
        VCU10_B.as_emergency_flag_m = 0.0;
        VCU10_B.manual_driving_flag_j = 0.0;
        VCU10_B.safety_lock = 1.0;
      }
      break;

     case VCU10_IN_AS_Off:
      VCU10_AS_Off(&VCU10_DW.FSEC_Safety_Fault_Delay_DSTATE,
                   &EBS_Sensor_Fault_Delay);
      break;

     case VCU10_IN_AS_Ready:
      if (VCU10_DW.ebs_working || VCU10_DW.FSEC_Safety_Fault_Delay_DSTATE ||
          EBS_Sensor_Fault_Delay || res_error) {
        guard3 = true;
      } else if (VCU10_DW.temporalCounter_i1 >= 500U) {
        if (VCU10_DW.ebs_working || VCU10_DW.FSEC_Safety_Fault_Delay_DSTATE || (
             !asms)) {
          guard3 = true;
        } else if ((rtb_y_in != 0) && (!VCU10_DW.FSEC_Safety_Fault_Delay_DSTATE)
                   && asms) {
          VCU10_B.r2d_warning = T;
          VCU10_B.steer_return = T;
          VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Driving;
          VCU10_DW.temporalCounter_i1 = 0U;
          VCU10_DW.is_AS_Driving = VCU10_IN_R2D;
          VCU10_B.r2d_flag_a = 1.0;
          VCU10_B.as_ready_flag_a = 0.0;
          VCU10_B.as_driving_flag_a = 1.0;
        } else {
          guard2 = true;
        }
      } else {
        guard2 = true;
      }
      break;

     case VCU10_IN_Manual_Driving_n:
      if (!VCU10_DW.ts) {
        VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Off;
        VCU10_enter_atomic_AS_Off();
      } else {
        VCU10_B.r2d_flag_a = 0.0;
        VCU10_B.steering_flag_o = 0.0;
        VCU10_B.brake_flag_p = 0.0;
        VCU10_B.as_led_yellow = 0.0;
        VCU10_B.as_led_blue = 0.0;
        VCU10_B.as_off_flag_g = 0.0;
        VCU10_B.as_ready_flag_a = 0.0;
        VCU10_B.as_driving_flag_a = 0.0;
        VCU10_B.as_finished_flag_a = 0.0;
        VCU10_B.as_emergency_flag_m = 0.0;
        VCU10_B.manual_driving_flag_j = 1.0;
        VCU10_B.as_ebs_trig = 0.0;
      }
      break;

     default:
      /* case IN_transition: */
      if (VCU10_DW.ts) {
        if (VCU10_DW.ebs_working || VCU10_DW.FSEC_Safety_Fault_Delay_DSTATE || (
             !asms) || res_error) {
          guard1 = true;
        } else if (VCU10_DW.asb_check &&
                   (!VCU10_DW.FSEC_Safety_Fault_Delay_DSTATE) &&
                   (VCU10_B.safety_lock == 0.0)) {
          VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Ready;
          VCU10_DW.temporalCounter_i1 = 0U;
          VCU10_B.r2d_flag_a = 0.0;
          VCU10_B.steering_flag_o = 1.0;
          VCU10_B.brake_flag_p = 2.0;
          VCU10_B.as_led_yellow = 1.0;
          VCU10_B.as_led_blue = 0.0;
          VCU10_B.as_off_flag_g = 0.0;
          VCU10_B.as_ready_flag_a = 1.0;
          VCU10_B.as_driving_flag_a = 0.0;
          VCU10_B.as_finished_flag_a = 0.0;
          VCU10_B.as_emergency_flag_m = 0.0;
          VCU10_B.manual_driving_flag_j = 0.0;
          VCU10_B.as_ebs_trig = 0.0;
        } else {
          guard4 = true;
        }
      } else {
        guard4 = true;
      }
      break;
    }

    if (guard4) {
      if (VCU10_DW.ebs_working || VCU10_DW.FSEC_Safety_Fault_Delay_DSTATE ||
          (!asms) || res_error) {
        guard1 = true;
      }
    }

    if (guard3) {
      VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Emergency;
      VCU10_enter_atomic_AS_Emergency();
    }

    if (guard2) {
      VCU10_B.r2d_flag_a = 0.0;
      VCU10_B.steering_flag_o = 1.0;
      VCU10_B.brake_flag_p = 2.0;
      VCU10_B.as_led_yellow = 1.0;
      VCU10_B.as_led_blue = 0.0;
      VCU10_B.as_off_flag_g = 0.0;
      VCU10_B.as_ready_flag_a = 1.0;
      VCU10_B.as_driving_flag_a = 0.0;
      VCU10_B.as_finished_flag_a = 0.0;
      VCU10_B.as_emergency_flag_m = 0.0;
      VCU10_B.manual_driving_flag_j = 0.0;
      VCU10_B.as_ebs_trig = 0.0;
    }

    if (guard1) {
      VCU10_DW.is_c1_VCU10 = VCU10_IN_AS_Emergency;
      VCU10_enter_atomic_AS_Emergency();
    }
  }

  /* S-Function (fcgen): '<Root>/10ms8' incorporates:
   *  SubSystem: '<Root>/ESP'
   */
  /* Switch: '<S143>/Emergency_Pressure_Select_1' incorporates:
   *  Constant: '<S143>/Emergency_Pressure_MPa'
   *  DataStoreWrite: '<S3>/Data Store Write3'
   *  DataTypeConversion: '<S166>/Data Type Conversion10'
   *  DataTypeConversion: '<S166>/Data Type Conversion11'
   *  DataTypeConversion: '<S166>/Data Type Conversion3'
   *  DataTypeConversion: '<S166>/Data Type Conversion5'
   *  DataTypeConversion: '<S166>/Data Type Conversion9'
   *  Gain: '<S166>/Gain'
   *  Gain: '<S166>/Gain1'
   *  Gain: '<S166>/Gain2'
   *  Gain: '<S166>/Gain3'
   *  Inport: '<Root>/canb_ipctsmsg1'
   *  Logic: '<S143>/Emergency_Hydraulic_Backup_Enable'
   *  MATLAB Function: '<S173>/bit_shift'
   *  MATLAB Function: '<S174>/bit_shift'
   *  S-Function (sfix_bitop): '<S166>/Bitwise AND5'
   *  Sum: '<S166>/Add1'
   *  Sum: '<S166>/Add2'
   *  Sum: '<S166>/Add3'
   *  Switch: '<S143>/Emergency_Pressure_Select_2'
   *  Switch: '<S143>/Emergency_Pressure_Select_3'
   *  Switch: '<S143>/Emergency_Pressure_Select_4'
   */
  if ((VCU10_B.as_emergency_flag_m != 0.0) && asms) {
    rtb_Emergency_Pressure_Select_1 = 8.0;
    rtb_Product1 = 8.0;
    rtb_Product2 = 8.0;
    rtb_Emergency_Pressure_Select_4 = 8.0;
  } else {
    /* S-Function (fcgen): '<Root>/10ms11' incorporates:
     *  SubSystem: '<Root>/IPC'
     */
    rtb_Emergency_Pressure_Select_1 = rtb_Emergency_Pressure_Select_4 * 0.01;
    rtb_Product1 = (real_T)(uint16_T)((uint32_T)rtb_y_ld + wheel_u16) * 0.01;
    rtb_Product2 = (real_T)(uint16_T)((uint32_T)rtb_y_gw + rtb_y_cg) * 0.01;

    /* Outputs for Atomic SubSystem: '<S166>/Bit Shift5' */
    /* Outputs for Atomic SubSystem: '<S166>/Bit Shift6' */
    rtb_Emergency_Pressure_Select_4 = (real_T)((int32_T)((uint32_T)
      (canb_ipctsmsg1[3] & 192) >> 6) + (canb_ipctsmsg1[4] << 2)) * 0.01;

    /* End of Outputs for SubSystem: '<S166>/Bit Shift6' */
    /* End of Outputs for SubSystem: '<S166>/Bit Shift5' */
    /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */
  }

  /* End of Switch: '<S143>/Emergency_Pressure_Select_1' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */

  /* Chart: '<S143>/ESP_Chart1' incorporates:
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
      if (VCU10_B.brake_flag_p == 0.0) {
        VCU10_DW.is_c16_VCU10 = VCU10_IN_ESC_Unable;
        VCU10_B.mode = 0.0;
      } else {
        VCU10_B.mode = 1.0;
        VCU10_B.tarPrsReqFL = rtb_Emergency_Pressure_Select_1;
        VCU10_B.tarPrsReqFR = rtb_Product1;
        VCU10_B.tarPrsReqRL = rtb_Product2;
        VCU10_B.tarPrsReqRR = rtb_Emergency_Pressure_Select_4;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case VCU10_IN_ESC_Engage:
      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (VCU10_B.brake_flag_p == 1.0) {
        VCU10_DW.is_c16_VCU10 = VCU10_IN_ESC_Able;
        VCU10_B.mode = 1.0;
        VCU10_B.tarPrsReqFL = rtb_Emergency_Pressure_Select_1;
        VCU10_B.tarPrsReqFR = rtb_Product1;
        VCU10_B.tarPrsReqRL = rtb_Product2;
        VCU10_B.tarPrsReqRR = rtb_Emergency_Pressure_Select_4;
      } else {
        VCU10_B.mode = 1.0;
        VCU10_B.tarPrsReqFL = rtb_Emergency_Pressure_Select_1;
        VCU10_B.tarPrsReqFR = rtb_Product1;
        VCU10_B.tarPrsReqRL = rtb_Product2;
        VCU10_B.tarPrsReqRR = rtb_Emergency_Pressure_Select_4;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     default:
      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      /* case IN_ESC_Unable: */
      if (VCU10_B.brake_flag_p == 2.0) {
        VCU10_DW.is_c16_VCU10 = VCU10_IN_ESC_Engage;
        VCU10_B.mode = 1.0;
        VCU10_B.tarPrsReqFL = rtb_Emergency_Pressure_Select_1;
        VCU10_B.tarPrsReqFR = rtb_Product1;
        VCU10_B.tarPrsReqRL = rtb_Product2;
        VCU10_B.tarPrsReqRR = rtb_Emergency_Pressure_Select_4;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;
    }
  }

  /* End of Chart: '<S143>/ESP_Chart1' */

  /* DataTypeConversion: '<S143>/Data Type Conversion5' incorporates:
   *  Gain: '<S143>/Gain'
   */
  rtb_Emergency_Pressure_Select_1 = floor(100.0 * VCU10_B.tarPrsReqFL);
  if (rtIsNaN(rtb_Emergency_Pressure_Select_1) || rtIsInf
      (rtb_Emergency_Pressure_Select_1)) {
    rtb_Emergency_Pressure_Select_1 = 0.0;
  } else {
    rtb_Emergency_Pressure_Select_1 = fmod(rtb_Emergency_Pressure_Select_1,
      65536.0);
  }

  rtb_y_ld = (uint16_T)(rtb_Emergency_Pressure_Select_1 < 0.0 ? (int32_T)
                        (uint16_T)-(int16_T)(uint16_T)
                        -rtb_Emergency_Pressure_Select_1 : (int32_T)(uint16_T)
                        rtb_Emergency_Pressure_Select_1);

  /* End of DataTypeConversion: '<S143>/Data Type Conversion5' */

  /* Outputs for Atomic SubSystem: '<S143>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S143>/Bitwise AND1' */
  VCU10_BitShift6((uint16_T)(rtb_y_ld & 15), &wheel_u16);

  /* End of Outputs for SubSystem: '<S143>/Bit Shift1' */

  /* DataTypeConversion: '<S143>/Data Type Conversion8' incorporates:
   *  Gain: '<S143>/Gain1'
   */
  rtb_Emergency_Pressure_Select_1 = floor(100.0 * VCU10_B.tarPrsReqFR);
  if (rtIsNaN(rtb_Emergency_Pressure_Select_1) || rtIsInf
      (rtb_Emergency_Pressure_Select_1)) {
    rtb_Emergency_Pressure_Select_1 = 0.0;
  } else {
    rtb_Emergency_Pressure_Select_1 = fmod(rtb_Emergency_Pressure_Select_1,
      65536.0);
  }

  rtb_y_gw = (uint16_T)(rtb_Emergency_Pressure_Select_1 < 0.0 ? (int32_T)
                        (uint16_T)-(int16_T)(uint16_T)
                        -rtb_Emergency_Pressure_Select_1 : (int32_T)(uint16_T)
                        rtb_Emergency_Pressure_Select_1);

  /* End of DataTypeConversion: '<S143>/Data Type Conversion8' */

  /* Outputs for Atomic SubSystem: '<S143>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S143>/Bitwise AND2' */
  VCU10_BitShift5((uint16_T)(rtb_y_gw & 3840), &rtb_y_cg);

  /* End of Outputs for SubSystem: '<S143>/Bit Shift2' */

  /* Sum: '<S143>/Add' */
  rtb_y_ec = (uint16_T)((uint32_T)wheel_u16 + rtb_y_cg);

  /* DataTypeConversion: '<S143>/Data Type Conversion9' incorporates:
   *  Gain: '<S143>/Gain2'
   */
  rtb_Emergency_Pressure_Select_1 = floor(100.0 * VCU10_B.tarPrsReqRL);
  if (rtIsNaN(rtb_Emergency_Pressure_Select_1) || rtIsInf
      (rtb_Emergency_Pressure_Select_1)) {
    rtb_Emergency_Pressure_Select_1 = 0.0;
  } else {
    rtb_Emergency_Pressure_Select_1 = fmod(rtb_Emergency_Pressure_Select_1,
      65536.0);
  }

  rtb_Add2_g = (uint16_T)(rtb_Emergency_Pressure_Select_1 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-rtb_Emergency_Pressure_Select_1 : (int32_T)
    (uint16_T)rtb_Emergency_Pressure_Select_1);

  /* End of DataTypeConversion: '<S143>/Data Type Conversion9' */

  /* Outputs for Atomic SubSystem: '<S143>/Bit Shift4' */
  /* S-Function (sfix_bitop): '<S143>/Bitwise AND5' */
  VCU10_BitShift6((uint16_T)(rtb_Add2_g & 15), &rtb_y_cg);

  /* End of Outputs for SubSystem: '<S143>/Bit Shift4' */

  /* DataTypeConversion: '<S143>/Data Type Conversion10' incorporates:
   *  Gain: '<S143>/Gain3'
   */
  rtb_Emergency_Pressure_Select_1 = floor(100.0 * VCU10_B.tarPrsReqRR);
  if (rtIsNaN(rtb_Emergency_Pressure_Select_1) || rtIsInf
      (rtb_Emergency_Pressure_Select_1)) {
    rtb_Emergency_Pressure_Select_1 = 0.0;
  } else {
    rtb_Emergency_Pressure_Select_1 = fmod(rtb_Emergency_Pressure_Select_1,
      65536.0);
  }

  rtb_Add1_a = (uint16_T)(rtb_Emergency_Pressure_Select_1 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-rtb_Emergency_Pressure_Select_1 : (int32_T)
    (uint16_T)rtb_Emergency_Pressure_Select_1);

  /* End of DataTypeConversion: '<S143>/Data Type Conversion10' */

  /* Outputs for Atomic SubSystem: '<S143>/Bit Shift5' */
  /* S-Function (sfix_bitop): '<S143>/Bitwise AND6' */
  VCU10_BitShift5((uint16_T)(rtb_Add1_a & 3840), &wheel_u16);

  /* End of Outputs for SubSystem: '<S143>/Bit Shift5' */

  /* Sum: '<S143>/Add1' */
  wheel_u16 = (uint16_T)((uint32_T)rtb_y_cg + wheel_u16);

  /* DataTypeConversion: '<S143>/Data Type Conversion11' */
  rtb_Emergency_Pressure_Select_1 = floor(VCU10_B.mode);
  if (rtIsNaN(rtb_Emergency_Pressure_Select_1) || rtIsInf
      (rtb_Emergency_Pressure_Select_1)) {
    rtb_Emergency_Pressure_Select_1 = 0.0;
  } else {
    rtb_Emergency_Pressure_Select_1 = fmod(rtb_Emergency_Pressure_Select_1,
      256.0);
  }

  rtb_y_in = (uint8_T)(rtb_Emergency_Pressure_Select_1 < 0.0 ? (int32_T)(uint8_T)
                       -(int8_T)(uint8_T)-rtb_Emergency_Pressure_Select_1 :
                       (int32_T)(uint8_T)rtb_Emergency_Pressure_Select_1);

  /* End of DataTypeConversion: '<S143>/Data Type Conversion11' */

  /* Outputs for Atomic SubSystem: '<S143>/Bit Shift6' */
  /* S-Function (sfix_bitop): '<S143>/Bitwise AND9' */
  VCU10_BitShift3_m((uint8_T)(rtb_y_in & 3), &rtb_y_in);

  /* End of Outputs for SubSystem: '<S143>/Bit Shift6' */

  /* Outputs for Atomic SubSystem: '<S143>/Bit Shift' */
  /* S-Function (sfix_bitop): '<S143>/Bitwise AND' */
  VCU10_BitShift7((uint16_T)(rtb_y_ld & 4080), &rtb_y_ld);

  /* End of Outputs for SubSystem: '<S143>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S143>/Bit Shift3' */
  /* S-Function (sfix_bitop): '<S143>/Bitwise AND4' */
  VCU10_BitShift7((uint16_T)(rtb_Add2_g & 4080), &rtb_y_cg);

  /* End of Outputs for SubSystem: '<S143>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S61>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S61>/Bitwise AND12' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift1((uint8_T)(ESP_T_01[3] & 252), &rtb_y_pq);

  /* End of Outputs for SubSystem: '<S61>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S61>/Bit Shift10' */
  /* S-Function (sfix_bitop): '<S61>/Bitwise AND3' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift10((uint8_T)(ESP_T_01[0] & 4), &rtb_y_pq);

  /* End of Outputs for SubSystem: '<S61>/Bit Shift10' */

  /* Outputs for Atomic SubSystem: '<S61>/Bit Shift11' */
  /* S-Function (sfix_bitop): '<S61>/Bitwise AND4' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift2((uint8_T)(ESP_T_01[0] & 5), &rtb_y_pq);

  /* End of Outputs for SubSystem: '<S61>/Bit Shift11' */

  /* Outputs for Atomic SubSystem: '<S61>/Bit Shift13' */
  /* S-Function (sfix_bitop): '<S61>/Bitwise AND6' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift2_e((uint8_T)(ESP_T_01[0] & 7), &rtb_y_pq);

  /* End of Outputs for SubSystem: '<S61>/Bit Shift13' */

  /* Outputs for Atomic SubSystem: '<S61>/Bit Shift14' */
  /* S-Function (sfix_bitop): '<S61>/Bitwise AND7' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift1_i((uint8_T)(ESP_T_01[0] & 8), &rtb_y_pq);

  /* End of Outputs for SubSystem: '<S61>/Bit Shift14' */

  /* Outputs for Atomic SubSystem: '<S61>/Bit Shift15' */
  /* S-Function (sfix_bitop): '<S61>/Bitwise AND10' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift((uint8_T)(ESP_T_01[2] & 254), &rtb_y_pq);

  /* End of Outputs for SubSystem: '<S61>/Bit Shift15' */

  /* Outputs for Atomic SubSystem: '<S61>/Bit Shift16' */
  /* S-Function (sfix_bitop): '<S61>/Bitwise AND9' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift1_i((uint8_T)(ESP_T_01[1] & 128), &rtb_y_pq);

  /* End of Outputs for SubSystem: '<S61>/Bit Shift16' */

  /* Outputs for Atomic SubSystem: '<S61>/Bit Shift3' */
  /* S-Function (sfix_bitop): '<S61>/Bitwise AND14' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift10((uint8_T)(ESP_T_01[4] & 248), &rtb_y_pq);

  /* End of Outputs for SubSystem: '<S61>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S61>/Bit Shift4' */
  /* S-Function (sfix_bitop): '<S61>/Bitwise AND15' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift4_h((uint8_T)(ESP_T_01[4] & 7), &rtb_y_pq);

  /* End of Outputs for SubSystem: '<S61>/Bit Shift4' */

  /* Outputs for Atomic SubSystem: '<S61>/Bit Shift5' */
  /* S-Function (sfix_bitop): '<S61>/Bitwise AND16' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift2((uint8_T)(ESP_T_01[5] & 240), &rtb_y_pq);

  /* End of Outputs for SubSystem: '<S61>/Bit Shift5' */

  /* Outputs for Atomic SubSystem: '<S61>/Bit Shift6' */
  /* S-Function (sfix_bitop): '<S61>/Bitwise AND17' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift4_h((uint8_T)(ESP_T_01[5] & 15), &rtb_y_pq);

  /* End of Outputs for SubSystem: '<S61>/Bit Shift6' */

  /* Outputs for Atomic SubSystem: '<S61>/Bit Shift7' */
  /* S-Function (sfix_bitop): '<S61>/Bitwise AND18' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift2((uint8_T)(ESP_T_01[6] & 240), &rtb_y_pq);

  /* End of Outputs for SubSystem: '<S61>/Bit Shift7' */

  /* Outputs for Atomic SubSystem: '<S61>/Bit Shift8' */
  /* S-Function (sfix_bitop): '<S61>/Bitwise AND1' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift((uint8_T)(ESP_T_01[0] & 2), &rtb_y_pq);

  /* End of Outputs for SubSystem: '<S61>/Bit Shift8' */

  /* Outputs for Atomic SubSystem: '<S61>/Bit Shift9' */
  /* S-Function (sfix_bitop): '<S61>/Bitwise AND2' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  VCU10_BitShift1((uint8_T)(ESP_T_01[0] & 3), &rtb_y_pq);

  /* End of Outputs for SubSystem: '<S61>/Bit Shift9' */

  /* Outputs for Atomic SubSystem: '<S62>/Bit Shift' */
  /* DataTypeConversion: '<S62>/Data Type Conversion1' incorporates:
   *  Inport: '<Root>/ESP_T_03'
   */
  VCU10_BitShift4((uint16_T)ESP_T_03[0], &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S62>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S62>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S62>/Bitwise AND1' incorporates:
   *  DataTypeConversion: '<S62>/Data Type Conversion3'
   *  Inport: '<Root>/ESP_T_03'
   */
  VCU10_BitShift3((uint16_T)(ESP_T_03[1] & 240), &rtb_y_po);

  /* End of Outputs for SubSystem: '<S62>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S62>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S62>/Bitwise AND2' incorporates:
   *  DataTypeConversion: '<S62>/Data Type Conversion4'
   *  Inport: '<Root>/ESP_T_03'
   */
  VCU10_BitShift_p((uint16_T)(ESP_T_03[1] & 15), &rtb_y_dz);

  /* End of Outputs for SubSystem: '<S62>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S62>/Bit Shift3' */
  /* DataTypeConversion: '<S62>/Data Type Conversion6' incorporates:
   *  Inport: '<Root>/ESP_T_03'
   */
  VCU10_BitShift4((uint16_T)ESP_T_03[3], &rtb_y_ia);

  /* End of Outputs for SubSystem: '<S62>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S62>/Bit Shift4' */
  /* S-Function (sfix_bitop): '<S62>/Bitwise AND5' incorporates:
   *  DataTypeConversion: '<S62>/Data Type Conversion7'
   *  Inport: '<Root>/ESP_T_03'
   */
  VCU10_BitShift3((uint16_T)(ESP_T_03[4] & 240), &rtb_y_nd);

  /* End of Outputs for SubSystem: '<S62>/Bit Shift4' */

  /* Outputs for Atomic SubSystem: '<S62>/Bit Shift5' */
  /* S-Function (sfix_bitop): '<S62>/Bitwise AND6' incorporates:
   *  DataTypeConversion: '<S62>/Data Type Conversion8'
   *  Inport: '<Root>/ESP_T_03'
   */
  VCU10_BitShift_p((uint16_T)(ESP_T_03[4] & 15), &rtb_y_ku);

  /* End of Outputs for SubSystem: '<S62>/Bit Shift5' */

  /* Gain: '<S62>/Gain' incorporates:
   *  DataTypeConversion: '<S62>/Data Type Conversion2'
   *  Sum: '<S62>/Add'
   */
  rtb_Product1 = (real_T)(uint16_T)((uint32_T)rtb_Add2_g + rtb_y_po) * 0.01;

  /* Gain: '<S62>/Gain1' incorporates:
   *  DataTypeConversion: '<S62>/Data Type Conversion12'
   *  DataTypeConversion: '<S62>/Data Type Conversion9'
   *  Inport: '<Root>/ESP_T_03'
   *  Sum: '<S62>/Add3'
   */
  rtb_Product2 = (real_T)(uint16_T)((uint32_T)rtb_y_ku + ESP_T_03[5]) * 0.01;

  /* Gain: '<S62>/Gain2' incorporates:
   *  DataTypeConversion: '<S62>/Data Type Conversion10'
   *  DataTypeConversion: '<S62>/Data Type Conversion5'
   *  Inport: '<Root>/ESP_T_03'
   *  Sum: '<S62>/Add1'
   */
  rtb_Emergency_Pressure_Select_4 = (real_T)(uint16_T)((uint32_T)rtb_y_dz +
    ESP_T_03[2]) * 0.01;

  /* Gain: '<S62>/Gain3' incorporates:
   *  DataTypeConversion: '<S62>/Data Type Conversion11'
   *  Sum: '<S62>/Add2'
   */
  oilprs_rlsensor = (real_T)(uint16_T)((uint32_T)rtb_y_ia + rtb_y_nd) * 0.01;

  /* Chart: '<S65>/brkmotor_check_system' incorporates:
   *  Inport: '<Root>/ESP_T_03'
   *  S-Function (sfix_bitop): '<S62>/LifeSig Mask'
   */
  rtb_y_pq = VCU10_DW.lifesig_start;
  VCU10_DW.lifesig_start = (uint8_T)(ESP_T_03[6] & 15);
  if (VCU10_DW.is_active_c18_VCU10 == 0U) {
    VCU10_DW.is_active_c18_VCU10 = 1U;
    VCU10_DW.is_c18_VCU10 = VCU10_IN_begin_f;
  } else {
    switch (VCU10_DW.is_c18_VCU10) {
     case VCU10_IN_begin_f:
      if (rtb_y_pq != VCU10_DW.lifesig_start) {
        VCU10_DW.is_c18_VCU10 = VCU10_IN_compare;
        VCU10_B.brkmotor_check = T;
      }
      break;

     case VCU10_IN_compare:
      if (rtb_y_pq == VCU10_DW.lifesig_start) {
        VCU10_DW.is_c18_VCU10 = VCU10_IN_same;
        VCU10_DW.lscnt++;
      } else {
        VCU10_B.brkmotor_check = T;
      }
      break;

     case VCU10_IN_judge:
      if (rtb_y_pq != VCU10_DW.lifesig_start) {
        VCU10_DW.lscnt = 0.0;
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
      } else if (rtb_y_pq != VCU10_DW.lifesig_start) {
        VCU10_DW.lscnt = 0.0;
        VCU10_DW.is_c18_VCU10 = VCU10_IN_compare;
        VCU10_B.brkmotor_check = T;
      } else {
        VCU10_DW.lscnt++;
      }
      break;
    }
  }

  /* End of Chart: '<S65>/brkmotor_check_system' */

  /* Outputs for Atomic SubSystem: '<S63>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S63>/Bitwise AND2' incorporates:
   *  DataTypeConversion: '<S63>/Data Type Conversion3'
   *  Inport: '<Root>/ESP_T_06'
   */
  VCU10_BitShift2_b((uint16_T)(ESP_T_06[1] & 31), &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S63>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S63>/Bit Shift3' */
  /* S-Function (sfix_bitop): '<S63>/Bitwise AND3' incorporates:
   *  DataTypeConversion: '<S63>/Data Type Conversion4'
   *  Inport: '<Root>/ESP_T_06'
   */
  VCU10_BitShift1_j((uint16_T)(ESP_T_06[2] & 252), &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S63>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S63>/Bit Shift7' */
  /* S-Function (sfix_bitop): '<S63>/Bitwise AND7' incorporates:
   *  DataTypeConversion: '<S63>/Data Type Conversion8'
   *  Inport: '<Root>/ESP_T_06'
   */
  VCU10_BitShift4((uint16_T)(ESP_T_06[4] & 127), &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S63>/Bit Shift7' */

  /* Outputs for Atomic SubSystem: '<S63>/Bit Shift8' */
  /* S-Function (sfix_bitop): '<S63>/Bitwise AND8' incorporates:
   *  DataTypeConversion: '<S63>/Data Type Conversion9'
   *  Inport: '<Root>/ESP_T_06'
   */
  VCU10_BitShift3((uint16_T)(ESP_T_06[5] & 240), &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S63>/Bit Shift8' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift' */
  /* DataTypeConversion: '<S64>/Data Type Conversion2' incorporates:
   *  Inport: '<Root>/ESP_T_07'
   */
  VCU10_BitShift4((uint16_T)ESP_T_07[0], &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND1' incorporates:
   *  DataTypeConversion: '<S64>/Data Type Conversion1'
   *  Inport: '<Root>/ESP_T_07'
   */
  VCU10_BitShift3((uint16_T)(ESP_T_07[1] & 240), &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND2' incorporates:
   *  DataTypeConversion: '<S64>/Data Type Conversion3'
   *  Inport: '<Root>/ESP_T_07'
   */
  VCU10_BitShift_p((uint16_T)(ESP_T_07[1] & 15), &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift3' */
  /* DataTypeConversion: '<S64>/Data Type Conversion5' incorporates:
   *  Inport: '<Root>/ESP_T_07'
   */
  VCU10_BitShift4((uint16_T)ESP_T_07[3], &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift4' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND5' incorporates:
   *  DataTypeConversion: '<S64>/Data Type Conversion6'
   *  Inport: '<Root>/ESP_T_07'
   */
  VCU10_BitShift3((uint16_T)(ESP_T_07[4] & 240), &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift4' */

  /* Outputs for Atomic SubSystem: '<S64>/Bit Shift5' */
  /* S-Function (sfix_bitop): '<S64>/Bitwise AND6' incorporates:
   *  DataTypeConversion: '<S64>/Data Type Conversion7'
   *  Inport: '<Root>/ESP_T_07'
   */
  VCU10_BitShift_p((uint16_T)(ESP_T_07[4] & 15), &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S64>/Bit Shift5' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms8' */

  /* S-Function (fcgen): '<Root>/10ms3' incorporates:
   *  SubSystem: '<Root>/ASB_Selfcheck'
   */
  /* S-Function (fcgen): '<Root>/10ms' incorporates:
   *  SubSystem: '<Root>/Sensor_Signal'
   */
  /* MATLAB Function: '<S2>/FSEC_Sensor_Monitor' incorporates:
   *  DataTypeConversion: '<S17>/Data Type Conversion5'
   */
  brake_now = ((brkps < 100) || (brkps > 4900));

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */
  if (brake_now) {
    VCU10_DW.brake_good = 0U;
    if (VCU10_DW.brake_bad < 1000) {
      elapsedTicks_m = VCU10_DW.brake_bad + 1U;
      if (VCU10_DW.brake_bad + 1U > 65535U) {
        elapsedTicks_m = 65535U;
      }

      VCU10_DW.brake_bad = (uint16_T)elapsedTicks_m;
    }

    VCU10_DW.brake_fault = ((VCU10_DW.brake_bad >= 10) || VCU10_DW.brake_fault);
  } else {
    VCU10_DW.brake_bad = 0U;
    if (VCU10_DW.brake_good < 1000) {
      elapsedTicks_m = VCU10_DW.brake_good + 1U;
      if (VCU10_DW.brake_good + 1U > 65535U) {
        elapsedTicks_m = 65535U;
      }

      VCU10_DW.brake_good = (uint16_T)elapsedTicks_m;
    }

    VCU10_DW.brake_fault = ((VCU10_DW.brake_good < 50) && VCU10_DW.brake_fault);
  }

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms3' */

  /* S-Function (fcgen): '<Root>/10ms' incorporates:
   *  SubSystem: '<Root>/Sensor_Signal'
   */
  /* DataTypeConversion: '<S17>/Data Type Conversion15' incorporates:
   *  Gain: '<S17>/Gain1'
   */
  rtb_Emergency_Pressure_Select_1 = (real_T)(33554U * airprs2) *
    2.9802322387695312E-8;

  /* S-Function (fcgen): '<Root>/10ms3' incorporates:
   *  SubSystem: '<Root>/ASB_Selfcheck'
   */
  /* MATLAB Function: '<S2>/FSEC_Sensor_Monitor' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read'
   *  DataTypeConversion: '<S17>/Data Type Conversion15'
   *  SignalConversion generated from: '<S17>/sensor_signal'
   */
  if ((airprs1 > 9800) || (airprs2 > 9800) || (airprs_sensor1 < 2.5) ||
      (rtb_Emergency_Pressure_Select_1 > airprs_sensor1 + 1.5)) {
    VCU10_DW.air_good = 0U;
    if (VCU10_DW.air_bad < 1000) {
      elapsedTicks_m = VCU10_DW.air_bad + 1U;
      if (VCU10_DW.air_bad + 1U > 65535U) {
        elapsedTicks_m = 65535U;
      }

      VCU10_DW.air_bad = (uint16_T)elapsedTicks_m;
    }

    VCU10_DW.air_fault = ((VCU10_DW.air_bad >= 50) || VCU10_DW.air_fault);
  } else {
    VCU10_DW.air_bad = 0U;
    if (VCU10_DW.air_good < 1000) {
      elapsedTicks_m = VCU10_DW.air_good + 1U;
      if (VCU10_DW.air_good + 1U > 65535U) {
        elapsedTicks_m = 65535U;
      }

      VCU10_DW.air_good = (uint16_T)elapsedTicks_m;
    }

    VCU10_DW.air_fault = ((VCU10_DW.air_good < 50) && VCU10_DW.air_fault);
  }

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */
  LogicalOperator_o = !VCU10_DW.brkmotor_check;
  if (LogicalOperator_o || (!LogicalOperator_e) || (!ebs_driver_check)) {
    VCU10_DW.comm_good = 0U;
    if (VCU10_DW.comm_bad < 1000) {
      elapsedTicks_m = VCU10_DW.comm_bad + 1U;
      if (VCU10_DW.comm_bad + 1U > 65535U) {
        elapsedTicks_m = 65535U;
      }

      VCU10_DW.comm_bad = (uint16_T)elapsedTicks_m;
    }

    VCU10_DW.comm_fault = ((VCU10_DW.comm_bad >= 30) || VCU10_DW.comm_fault);
  } else {
    VCU10_DW.comm_bad = 0U;
    if (VCU10_DW.comm_good < 1000) {
      elapsedTicks_m = VCU10_DW.comm_good + 1U;
      if (VCU10_DW.comm_good + 1U > 65535U) {
        elapsedTicks_m = 65535U;
      }

      VCU10_DW.comm_good = (uint16_T)elapsedTicks_m;
    }

    VCU10_DW.comm_fault = ((VCU10_DW.comm_good < 50) && VCU10_DW.comm_fault);
  }

  if (LogicalOperator_o || (!ebs_driver_check)) {
    VCU10_DW.ebs_good = 0U;
    if (VCU10_DW.ebs_bad < 1000) {
      elapsedTicks_m = VCU10_DW.ebs_bad + 1U;
      if (VCU10_DW.ebs_bad + 1U > 65535U) {
        elapsedTicks_m = 65535U;
      }

      VCU10_DW.ebs_bad = (uint16_T)elapsedTicks_m;
    }

    VCU10_DW.ebs_comm_fault = ((VCU10_DW.ebs_bad >= 30) ||
      VCU10_DW.ebs_comm_fault);
  } else {
    VCU10_DW.ebs_bad = 0U;
    if (VCU10_DW.ebs_good < 1000) {
      elapsedTicks_m = VCU10_DW.ebs_good + 1U;
      if (VCU10_DW.ebs_good + 1U > 65535U) {
        elapsedTicks_m = 65535U;
      }

      VCU10_DW.ebs_good = (uint16_T)elapsedTicks_m;
    }

    VCU10_DW.ebs_comm_fault = ((VCU10_DW.ebs_good < 50) &&
      VCU10_DW.ebs_comm_fault);
  }

  rtb_AS_Torque_Enable = (VCU10_DW.brake_fault || VCU10_DW.air_fault);
  LogicalOperator_o = (rtb_AS_Torque_Enable || VCU10_DW.comm_fault);

  /* DataStoreWrite: '<Root>/Data Store Write' incorporates:
   *  Constant: '<S30>/Constant'
   *  Constant: '<S31>/Constant'
   *  Constant: '<S32>/Constant'
   *  Constant: '<S33>/Constant'
   *  Constant: '<S34>/Constant'
   *  DataStoreRead: '<Root>/Data Store Read'
   *  Logic: '<S28>/Logical Operator'
   *  Logic: '<S2>/Logical Operator'
   *  Logic: '<S2>/No_FSEC_Safety_Fault'
   *  RelationalOperator: '<S30>/Compare'
   *  RelationalOperator: '<S31>/Compare'
   *  RelationalOperator: '<S32>/Compare'
   *  RelationalOperator: '<S33>/Compare'
   *  RelationalOperator: '<S34>/Compare'
   */
  VCU10_DW.asb_check = (ebs_driver_check && LogicalOperator_e &&
                        ((airprs_sensor1 >= 3.5) && (rtb_Product1 >= 0.848) &&
    (rtb_Emergency_Pressure_Select_4 >= 0.848) && (oilprs_rlsensor >= 0.742) &&
    (rtb_Product2 >= 0.742)) && VCU10_DW.brkmotor_check && (!LogicalOperator_o));

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms3' */

  /* S-Function (fcgen): '<Root>/10ms7' incorporates:
   *  SubSystem: '<Root>/EBS'
   */
  /* SignalConversion generated from: '<S7>/ebs_watchdog' */
  ebs_watchdog = asms;

  /* Logic: '<S7>/EBS_Trigger_ASMS_Gate' */
  ebs_trig = ((VCU10_B.as_ebs_trig != 0.0) && asms);

  /* MATLAB Function: '<S7>/EBS_Response_Monitor' */
  LogicalOperator_e = (ebs_trig && (!VCU10_DW.last_trigger));
  VCU10_DW.last_trigger = ebs_trig;

  /* S-Function (fcgen): '<Root>/10ms' incorporates:
   *  SubSystem: '<Root>/Sensor_Signal'
   */
  if (LogicalOperator_e && ebs_driver_check && (airprs_sensor1 >= 2.5) &&
      (rtb_Emergency_Pressure_Select_1 < 1.0)) {
    VCU10_DW.waiting = true;
    VCU10_DW.wait_count = 0U;
  }

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */
  if (VCU10_DW.waiting) {
    /* S-Function (fcgen): '<Root>/10ms' incorporates:
     *  SubSystem: '<Root>/Sensor_Signal'
     */
    if (rtb_Emergency_Pressure_Select_1 >= 1.0) {
      VCU10_DW.waiting = false;
      VCU10_DW.wait_count = 0U;
    } else {
      if (VCU10_DW.wait_count < 1000) {
        elapsedTicks_m = VCU10_DW.wait_count + 1U;
        if (VCU10_DW.wait_count + 1U > 65535U) {
          elapsedTicks_m = 65535U;
        }

        VCU10_DW.wait_count = (uint16_T)elapsedTicks_m;
      }

      if (VCU10_DW.wait_count >= 20) {
        VCU10_DW.fault_latched = true;
        VCU10_DW.waiting = false;
      }
    }

    /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */
  }

  /* S-Function (fcgen): '<Root>/10ms' incorporates:
   *  SubSystem: '<Root>/Sensor_Signal'
   */
  if (rtb_Emergency_Pressure_Select_1 > airprs_sensor1 + 1.5) {
    if (VCU10_DW.relation_count < 1000) {
      elapsedTicks_m = VCU10_DW.relation_count + 1U;
      if (VCU10_DW.relation_count + 1U > 65535U) {
        elapsedTicks_m = 65535U;
      }

      VCU10_DW.relation_count = (uint16_T)elapsedTicks_m;
    }

    VCU10_DW.fault_latched = ((VCU10_DW.relation_count >= 20) ||
      VCU10_DW.fault_latched);
  } else {
    VCU10_DW.relation_count = 0U;
  }

  if (EBS_Sensor_Fault_Delay && ebs_driver_check &&
      (rtb_Emergency_Pressure_Select_1 < 1.0) && (airprs_sensor1 >= 2.5)) {
    if (VCU10_DW.clear_count < 1000) {
      elapsedTicks_m = VCU10_DW.clear_count + 1U;
      if (VCU10_DW.clear_count + 1U > 65535U) {
        elapsedTicks_m = 65535U;
      }

      VCU10_DW.clear_count = (uint16_T)elapsedTicks_m;
    }

    VCU10_DW.fault_latched = ((VCU10_DW.clear_count < 100) &&
      VCU10_DW.fault_latched);
  } else {
    VCU10_DW.clear_count = 0U;
  }

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */

  /* UnitDelay: '<S7>/EBS_Sensor_Fault_Delay' */
  EBS_Sensor_Fault_Delay = VCU10_DW.EBS_Sensor_Fault_Delay_DSTATE;

  /* Logic: '<S7>/Logical Operator1' incorporates:
   *  Constant: '<S44>/Constant'
   *  RelationalOperator: '<S44>/Compare'
   */
  VCU10_DW.ebs_working = (ebs_driver_check && (airprs_sensor2 >= 6.0));

  /* Update for UnitDelay: '<S7>/EBS_Sensor_Fault_Delay' incorporates:
   *  MATLAB Function: '<S7>/EBS_Response_Monitor'
   */
  VCU10_DW.EBS_Sensor_Fault_Delay_DSTATE = VCU10_DW.fault_latched;

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms7' */

  /* S-Function (fcgen): '<Root>/10ms13' incorporates:
   *  SubSystem: '<Root>/AMI_CAN'
   */
  /* Chart: '<S20>/Chart' incorporates:
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
      if (VCU10_B.as_emergency_flag_m != 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_begin_g;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case VCU10_IN_as_finished:
      VCU10_B.ami_process = 32U;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (VCU10_B.as_finished_flag_a != 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_begin_g;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case VCU10_IN_as_off:
      VCU10_B.ami_process = 1U;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (VCU10_B.as_off_flag_g != 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_begin_g;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case VCU10_IN_as_ready:
      VCU10_B.ami_process = 4U;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (VCU10_B.as_ready_flag_a != 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_begin_g;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case VCU10_IN_begin_g:
      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (VCU10_B.as_off_flag_g == 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_as_off;
        VCU10_B.ami_process = 1U;
      } else if (VCU10_B.manual_driving_flag_j == 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_munual_driving;
        VCU10_B.ami_process = 2U;
      } else if (VCU10_B.as_ready_flag_a == 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_as_ready;
        VCU10_B.ami_process = 4U;
      } else if (VCU10_B.r2d_flag_a == 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_r2d;
        VCU10_B.ami_process = 8U;
      } else if (VCU10_B.as_driving_flag_a == 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_as_driving;
        VCU10_B.ami_process = 16U;
      } else if (VCU10_B.as_finished_flag_a == 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_as_finished;
        VCU10_B.ami_process = 32U;
      } else if (VCU10_B.as_emergency_flag_m == 1.0) {
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
      if (VCU10_B.manual_driving_flag_j != 1.0) {
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
      if (VCU10_B.r2d_flag_a != 1.0) {
        VCU10_DW.is_c20_VCU10 = VCU10_IN_begin_g;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;
    }
  }

  /* End of Chart: '<S20>/Chart' */

  /* Outputs for Atomic SubSystem: '<S20>/Bit Shift' */
  /* S-Function (sfix_bitop): '<S20>/Bitwise AND' */
  VCU10_BitShift_a((uint8_T)(VCU10_B.ami_process & 127), &rtb_y_pq);

  /* End of Outputs for SubSystem: '<S20>/Bit Shift' */

  /* SignalConversion: '<S20>/Signal Conversion' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read12'
   *  Sum: '<S20>/Add1'
   */
  AMI_Rx[0] = (uint8_T)((uint32_T)rtb_y_pq + VCU10_DW.task_finish);
  AMI_Rx[1] = ((uint8_T)0U);
  AMI_Rx[2] = ((uint8_T)0U);
  AMI_Rx[3] = ((uint8_T)0U);
  AMI_Rx[4] = ((uint8_T)0U);
  AMI_Rx[5] = ((uint8_T)0U);
  AMI_Rx[6] = ((uint8_T)0U);
  AMI_Rx[7] = ((uint8_T)0U);

  /* Outputs for Atomic SubSystem: '<S19>/Bit Shift' */
  /* S-Function (sfix_bitop): '<S19>/Bitwise AND' incorporates:
   *  Inport: '<Root>/AMI_Tx'
   */
  VCU10_BitShift2((uint8_T)(AMI_Tx[0] & 240), &rtb_y_pq);

  /* End of Outputs for SubSystem: '<S19>/Bit Shift' */

  /* DataStoreWrite: '<Root>/Data Store Write10' incorporates:
   *  Constant: '<S21>/Constant'
   *  RelationalOperator: '<S21>/Compare'
   */
  VCU10_DW.inspection_flag = (rtb_y_pq == 5);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms13' */

  /* S-Function (fcgen): '<Root>/10ms11' incorporates:
   *  SubSystem: '<Root>/IPC'
   */
  /* DataStoreWrite: '<Root>/Data Store Write11' incorporates:
   *  DataTypeConversion: '<S167>/Data Type Conversion4'
   */
  VCU10_DW.task_finish = (rtb_y_ev != 0);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */

  /* S-Function (fcgen): '<Root>/10ms13' incorporates:
   *  SubSystem: '<Root>/AMI_CAN'
   */
  /* DataStoreWrite: '<Root>/Data Store Write13' incorporates:
   *  Constant: '<S22>/Constant'
   *  RelationalOperator: '<S22>/Compare'
   */
  VCU10_DW.astask_flag = (rtb_y_pq > 0);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms13' */

  /* S-Function (fcgen): '<Root>/10ms3' incorporates:
   *  SubSystem: '<Root>/ASB_Selfcheck'
   */
  /* DataStoreWrite: '<Root>/Data Store Write2' incorporates:
   *  Constant: '<S35>/Constant'
   *  Constant: '<S36>/Constant'
   *  Constant: '<S37>/Constant'
   *  Constant: '<S38>/Constant'
   *  Logic: '<S28>/Logical Operator1'
   *  Logic: '<S2>/Brake_On_Valid_Gate'
   *  MATLAB Function: '<S2>/FSEC_Sensor_Monitor'
   *  RelationalOperator: '<S35>/Compare'
   *  RelationalOperator: '<S36>/Compare'
   *  RelationalOperator: '<S37>/Compare'
   *  RelationalOperator: '<S38>/Compare'
   */
  VCU10_DW.brake_on = ((rtb_Product1 >= 0.848) &&
                       (rtb_Emergency_Pressure_Select_4 >= 0.848) &&
                       (oilprs_rlsensor >= 0.742) && (rtb_Product2 >= 0.742) &&
                       ((!VCU10_DW.brake_fault) && (!brake_now)));

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms3' */

  /* S-Function (fcgen): '<Root>/10ms7' incorporates:
   *  SubSystem: '<Root>/EBS'
   */
  /* S-Function (fcgen): '<Root>/10ms' incorporates:
   *  SubSystem: '<Root>/Sensor_Signal'
   */
  /* DataStoreWrite: '<Root>/Data Store Write3' incorporates:
   *  Constant: '<S45>/Constant'
   *  Logic: '<S7>/Logical Operator2'
   *  Logic: '<S7>/Logical Operator3'
   *  RelationalOperator: '<S45>/Compare'
   */
  VCU10_DW.ebs_check = ((!VCU10_DW.ebs_working) &&
                        (rtb_Emergency_Pressure_Select_1 <= 5.5));

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms7' */

  /* DataStoreWrite: '<Root>/Data Store Write4' */
  VCU10_DW.brkmotor_check = VCU10_B.brkmotor_check;

  /* S-Function (fcgen): '<Root>/10ms9' incorporates:
   *  SubSystem: '<Root>/EPS'
   */
  /* Sum: '<S49>/Add' incorporates:
   *  Constant: '<S49>/Constant1'
   *  DataTypeConversion: '<S49>/Data Type Conversion1'
   *  DataTypeConversion: '<S49>/Data Type Conversion2'
   *  Gain: '<S49>/Gain1'
   *  Inport: '<Root>/canb_epssendmsg1'
   */
  i = ((canb_epssendmsg1[3] << 8) + canb_epssendmsg1[4]) - 1024;

  /* Outputs for Atomic SubSystem: '<S50>/Bit Shift1' */
  /* DataTypeConversion: '<S50>/Data Type Conversion3' incorporates:
   *  Inport: '<Root>/canb_epssendmsg2'
   */
  VCU10_BitShift_p((uint16_T)canb_epssendmsg2[1], &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S50>/Bit Shift1' */

  /* S-Function (fcgen): '<Root>/10ms11' incorporates:
   *  SubSystem: '<Root>/IPC'
   */
  /* DataTypeConversion: '<S57>/Data Type Conversion5' incorporates:
   *  Constant: '<S167>/Constant'
   *  Constant: '<S57>/Constant1'
   *  DataTypeConversion: '<S167>/Data Type Conversion1'
   *  Gain: '<S57>/Gain1'
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S11>/canb_ipctsmsg2'
   *  Sum: '<S167>/Add'
   *  Sum: '<S57>/Add1'
   */
  rtb_Emergency_Pressure_Select_1 = floor(((rtb_y + (real_T)canb_ipctsmsg2[1]) -
    1024.0) * 5.0 + 1024.0);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */
  if (rtIsNaN(rtb_Emergency_Pressure_Select_1) || rtIsInf
      (rtb_Emergency_Pressure_Select_1)) {
    rtb_Emergency_Pressure_Select_1 = 0.0;
  } else {
    rtb_Emergency_Pressure_Select_1 = fmod(rtb_Emergency_Pressure_Select_1,
      4.294967296E+9);
  }

  elapsedTicks_m = rtb_Emergency_Pressure_Select_1 < 0.0 ? (uint32_T)-(int32_T)
    (uint32_T)-rtb_Emergency_Pressure_Select_1 : (uint32_T)
    rtb_Emergency_Pressure_Select_1;

  /* End of DataTypeConversion: '<S57>/Data Type Conversion5' */

  /* Logic: '<S48>/Logical Operator3' incorporates:
   *  Constant: '<S54>/Constant'
   *  Constant: '<S55>/Constant'
   *  RelationalOperator: '<S54>/Compare'
   *  RelationalOperator: '<S55>/Compare'
   */
  VCU10_DW.steer_zero = ((i >= -2) && (i <= 2));

  /* Chart: '<S48>/EPS_Stateflow1' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read2'
   *  DataStoreWrite: '<S3>/Data Store Write4'
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S11>/canb_ipctsmsg2'
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
        VCU10_B.eps_cmdworkmode = 16U;
        VCU10_B.eps_cmdangle = 4U;
        VCU10_B.eps_cmdmiddle = 85U;
        VCU10_B.eps_cmdvelocity = 20U;
      } else {
        VCU10_B.eps_cmdworkmode = 16U;
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
        VCU10_B.eps_cmdworkmode = 16U;
        VCU10_B.eps_cmdangle = elapsedTicks_m;
        VCU10_B.eps_cmdmiddle = 0U;

        /* S-Function (fcgen): '<Root>/10ms11' incorporates:
         *  SubSystem: '<Root>/IPC'
         */
        VCU10_B.eps_cmdvelocity = canb_ipctsmsg2[2];

        /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */
      } else {
        VCU10_B.eps_cmdworkmode = 16U;
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
        VCU10_B.eps_cmdworkmode = 16U;
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

  /* End of Chart: '<S48>/EPS_Stateflow1' */

  /* Switch: '<S48>/Switch' incorporates:
   *  Bias: '<S48>/InspectionAngleOffset'
   *  DataStoreRead: '<Root>/Data Store Read14'
   *  Rounding: '<S48>/Rounding Function'
   *  Sin: '<S48>/Sine Wave1'
   */
  if (VCU10_DW.inspection_flag) {
    rtb_y = floor(sin(((VCU10_M->Timing.clockTick0) * 0.01)) * 90.0) + 1024.0;
  } else {
    rtb_y = VCU10_B.eps_cmdangle;
  }

  /* End of Switch: '<S48>/Switch' */

  /* DataTypeConversion: '<S48>/Data Type Conversion1' */
  if (rtIsNaN(rtb_y)) {
    rtb_Emergency_Pressure_Select_1 = 0.0;
  } else {
    rtb_Emergency_Pressure_Select_1 = fmod(rtb_y, 65536.0);
  }

  /* Outputs for Atomic SubSystem: '<S48>/Bit Shift' */
  /* S-Function (sfix_bitop): '<S48>/Bitwise AND' incorporates:
   *  DataTypeConversion: '<S48>/Data Type Conversion1'
   */
  VCU10_BitShift5((uint16_T)((uint16_T)rtb_Emergency_Pressure_Select_1 & 65280),
                  &rtb_Add2_g);

  /* End of Outputs for SubSystem: '<S48>/Bit Shift' */

  /* DataTypeConversion: '<S48>/Data Type Conversion5' incorporates:
   *  DataTypeConversion: '<S48>/Data Type Conversion1'
   *  S-Function (sfix_bitop): '<S48>/Bitwise AND1'
   */
  rtb_y_ev = (uint8_T)((uint16_T)rtb_Emergency_Pressure_Select_1 & 255);

  /* SignalConversion generated from: '<S8>/canb_epsmsg' incorporates:
   *  Constant: '<S48>/Constant'
   *  Constant: '<S48>/Constant1'
   *  DataTypeConversion: '<S48>/Data Type Conversion4'
   *  S-Function (sfix_bitop): '<S48>/Bitwise AND2'
   *  S-Function (sfix_bitop): '<S48>/Bitwise AND3'
   *  S-Function (sfix_bitop): '<S48>/Logical Operator2'
   */
  canb_epsmsg[0] = VCU10_B.eps_cmdworkmode;
  canb_epsmsg[1] = 0U;
  canb_epsmsg[2] = 0U;
  canb_epsmsg[3] = (uint8_T)rtb_Add2_g;
  canb_epsmsg[4] = rtb_y_ev;
  canb_epsmsg[5] = VCU10_B.eps_cmdmiddle;
  canb_epsmsg[6] = VCU10_B.eps_cmdvelocity;
  canb_epsmsg[7] = (uint8_T)(VCU10_B.eps_cmdworkmode ^ (uint8_T)rtb_Add2_g ^
    rtb_y_ev ^ VCU10_B.eps_cmdmiddle ^ VCU10_B.eps_cmdvelocity);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms9' */

  /* S-Function (fcgen): '<Root>/10ms1' incorporates:
   *  SubSystem: '<Root>/TS_Activation'
   */
  /* Switch: '<S18>/Switch' incorporates:
   *  DataStoreWrite: '<Root>/Data Store Write14'
   *  Logic: '<S18>/Logical Operator'
   *  Logic: '<S18>/Logical Operator2'
   */
  if (asms) {
    LogicalOperator_e = !di8_side;
  } else {
    LogicalOperator_e = !di8_cockpit;
  }

  /* End of Switch: '<S18>/Switch' */

  /* Chart: '<S18>/Chart' */
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
          if (!LogicalOperator_e) {
            VCU10_DW.di8_offcheck_flag = 1.0;
          }
        } else {
          VCU10_DW.is_Flameout_Check_i = VCU10_IN_Checkoff;
          if (LogicalOperator_e) {
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
    if (!LogicalOperator_e) {
      VCU10_DW.di8_offcheck_flag = 1.0;
    }
  } else {
    switch (VCU10_DW.is_Ignition_Check_f) {
     case VCU10_IN_Check:
      if (VCU10_DW.di8_check_flag == 0.0) {
        VCU10_DW.is_Ignition_Check_f = VCU10_IN_DI8_Check_Flag;
        VCU10_DW.di8_check_flag = !LogicalOperator_e;
      } else if (VCU10_DW.di8_check_flag == 1.0) {
        VCU10_DW.is_Ignition_Check_f = VCU10_IN_Check;
        if (LogicalOperator_e) {
          VCU10_DW.di8_flag = T;
          di8 = T;
        }
      }
      break;

     case VCU10_IN_DI8_Check_Flag:
      if (VCU10_DW.di8_check_flag == 0.0) {
        VCU10_DW.is_Ignition_Check_f = VCU10_IN_DI8_Check_Flag;
        VCU10_DW.di8_check_flag = !LogicalOperator_e;
      } else if (VCU10_DW.di8_check_flag == 1.0) {
        VCU10_DW.is_Ignition_Check_f = VCU10_IN_Check;
        if (LogicalOperator_e) {
          VCU10_DW.di8_flag = T;
          di8 = T;
        }
      }
      break;

     default:
      /* case IN_begin: */
      VCU10_DW.is_Ignition_Check_f = VCU10_IN_DI8_Check_Flag;
      VCU10_DW.di8_check_flag = !LogicalOperator_e;
      break;
    }
  }

  /* End of Chart: '<S18>/Chart' */

  /* Logic: '<S18>/Logical Operator1' */
  LogicalOperator_e = !run_button;

  /* Chart: '<S18>/Chart1' */
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
          if (!LogicalOperator_e) {
            VCU10_DW.run_offcheck_flag = 1.0;
          }
        } else {
          VCU10_DW.is_Flameout_Check = VCU10_IN_Checkoff;
          if (LogicalOperator_e) {
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
    if (!LogicalOperator_e) {
      VCU10_DW.run_offcheck_flag = 1.0;
    }
  } else {
    switch (VCU10_DW.is_Ignition_Check) {
     case VCU10_IN_Check:
      if (VCU10_DW.run_check_flag == 1.0) {
        VCU10_DW.is_Ignition_Check = VCU10_IN_Check;
        if (LogicalOperator_e) {
          VCU10_DW.run_flag = 1.0;
          run = T;
        }
      } else if (VCU10_DW.run_check_flag == 0.0) {
        VCU10_DW.is_Ignition_Check = VCU10_IN_Run_Check_Flag;
        VCU10_DW.run_check_flag = !LogicalOperator_e;
      }
      break;

     case VCU10_IN_Run_Check_Flag:
      if (VCU10_DW.run_check_flag == 1.0) {
        VCU10_DW.is_Ignition_Check = VCU10_IN_Check;
        if (LogicalOperator_e) {
          VCU10_DW.run_flag = 1.0;
          run = T;
        }
      } else if (VCU10_DW.run_check_flag == 0.0) {
        VCU10_DW.is_Ignition_Check = VCU10_IN_Run_Check_Flag;
        VCU10_DW.run_check_flag = !LogicalOperator_e;
      }
      break;

     default:
      /* case IN_begin: */
      VCU10_DW.is_Ignition_Check = VCU10_IN_Run_Check_Flag;
      VCU10_DW.run_check_flag = !LogicalOperator_e;
      break;
    }
  }

  /* End of Chart: '<S18>/Chart1' */

  /* Chart: '<S18>/Chart2' incorporates:
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

  /* End of Chart: '<S18>/Chart2' */

  /* S-Function (fcgen): '<Root>/10ms6' incorporates:
   *  SubSystem: '<Root>/AS_Stateflow'
   */
  /* DataStoreWrite: '<Root>/Data Store Write6' incorporates:
   *  DataStoreRead: '<S18>/FSEC_Safety_Lock_Read'
   *  DataStoreWrite: '<S3>/Data Store Write3'
   *  Logic: '<S18>/No_AS_Emergency'
   *  Logic: '<S18>/No_FSEC_Safety_Lock'
   *  Logic: '<S18>/TS_Safety_Gate'
   */
  VCU10_DW.ts = ((VCU10_B.ts != 0.0) && (!(VCU10_DW.safety_lock != 0.0)) &&
                 (!(VCU10_B.as_emergency_flag_m != 0.0)));

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms1' */

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
    LogicalOperator_e = F;
  } else if (VCU10_DW.is_c11_VCU10 == 1) {
    LogicalOperator_e = F;

    /* S-Function (fcgen): '<Root>/10ms6' incorporates:
     *  SubSystem: '<Root>/AS_Stateflow'
     */
    if (VCU10_B.as_emergency_flag_m == 1.0) {
      VCU10_DW.is_c11_VCU10 = VCU10_IN_Emergency;
      VCU10_DW.temporalCounter_i1_m = 0U;
      LogicalOperator_e = T;
    }

    /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
  } else {
    /* case IN_Emergency: */
    LogicalOperator_e = T;
    if (VCU10_DW.temporalCounter_i1_m >= 900U) {
      VCU10_DW.is_c11_VCU10 = VCU10_IN_Default;
      LogicalOperator_e = F;
    }
  }

  /* End of Chart: '<S4>/Chart' */

  /* DiscretePulseGenerator: '<S4>/Pulse Generator' */
  i = ((VCU10_DW.clockTickCounter_a2 < 50) && (VCU10_DW.clockTickCounter_a2 >= 0));
  if (VCU10_DW.clockTickCounter_a2 >= 99) {
    VCU10_DW.clockTickCounter_a2 = 0;
  } else {
    VCU10_DW.clockTickCounter_a2++;
  }

  /* End of DiscretePulseGenerator: '<S4>/Pulse Generator' */

  /* Switch: '<S4>/Switch' */
  if (LogicalOperator_e) {
    /* Switch: '<S4>/Switch' incorporates:
     *  DataTypeConversion: '<S4>/Data Type Conversion6'
     */
    ebs_buzzer = (i != 0);
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

  /* DataStoreWrite: '<Root>/FSEC_Safety_Lock_Write' */
  VCU10_DW.safety_lock = VCU10_B.safety_lock;

  /* S-Function (fcgen): '<Root>/10ms2' incorporates:
   *  SubSystem: '<Root>/LED_Control'
   */
  /* Inport: '<S13>/brake_on' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read13'
   */
  led_brake = VCU10_DW.brake_on;

  /* Chart: '<S218>/Shutdown_Button' */
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

  /* End of Chart: '<S218>/Shutdown_Button' */

  /* Outputs for Enabled SubSystem: '<S218>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S229>/Enable'
   */
  /* S-Function (fcgen): '<Root>/10ms10' incorporates:
   *  SubSystem: '<Root>/Res'
   */
  /* Logic: '<S218>/Logical Operator2' incorporates:
   *  Constant: '<S224>/Constant'
   *  DataStoreWrite: '<Root>/Data Store Write14'
   *  DataTypeConversion: '<S267>/Data Type Conversion2'
   *  Inport: '<S229>/In1'
   *  RelationalOperator: '<S224>/Compare'
   */
  if (res_error && (active != 0) && VCU10_B.shutdown_flag && asms) {
    VCU10_B.In1 = (airprs_sensor2 >= 3.5);
  }

  /* End of Logic: '<S218>/Logical Operator2' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms10' */
  /* End of Outputs for SubSystem: '<S218>/Enabled Subsystem' */

  /* Chart: '<S218>/display' */
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
    LogicalOperator_e = T;
  } else if (VCU10_DW.is_c6_VCU10 == 1) {
    if (VCU10_DW.temporalCounter_i1_gw >= 200U) {
      VCU10_DW.is_c6_VCU10 = VCU10_IN_end;
      LogicalOperator_e = F;
    } else {
      LogicalOperator_e = T;
    }
  } else {
    /* case IN_end: */
    LogicalOperator_e = F;
  }

  /* End of Chart: '<S218>/display' */

  /* Logic: '<S218>/Logical Operator' incorporates:
   *  Constant: '<S222>/Constant'
   *  Constant: '<S225>/Constant'
   *  Constant: '<S226>/Constant'
   *  Constant: '<S227>/Constant'
   *  Constant: '<S228>/Constant'
   *  Logic: '<S218>/Logical Operator3'
   *  RelationalOperator: '<S222>/Compare'
   *  RelationalOperator: '<S225>/Compare'
   *  RelationalOperator: '<S226>/Compare'
   *  RelationalOperator: '<S227>/Compare'
   *  RelationalOperator: '<S228>/Compare'
   */
  led_ebs_error = ((airprs_sensor1 <= 1.0) || VCU10_B.In1 || ((rtb_Product1 <=
    0.11) || (rtb_Emergency_Pressure_Select_4 <= 0.11) || (oilprs_rlsensor <=
    0.11) || (rtb_Product2 <= 0.11)) || LogicalOperator_e);

  /* Chart: '<S219>/blue' */
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
      if (VCU10_B.as_led_blue == 0.0) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_Close;
        rtb_Add2_g = 0U;
      } else if (VCU10_B.as_led_blue == 1.0) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_On;
        rtb_Add2_g = 60000U;
      }
      break;

     case VCU10_IN_Close:
      rtb_Add2_g = 0U;
      if (VCU10_B.as_led_blue == 1.0) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_On;
        rtb_Add2_g = 60000U;
      } else if (VCU10_B.as_led_blue == 2.0) {
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
      if (VCU10_B.as_led_blue == 1.0) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_On;
        rtb_Add2_g = 60000U;
      } else if (VCU10_B.as_led_blue == 0.0) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_Close;
      } else if (VCU10_B.as_led_blue == 2.0) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_Blink;
        rtb_Add2_g = 30000U;
      }
      break;

     default:
      /* case IN_On: */
      rtb_Add2_g = 60000U;
      if (VCU10_B.as_led_blue == 2.0) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_Blink;
        rtb_Add2_g = 30000U;
      } else if (VCU10_B.as_led_blue == 0.0) {
        VCU10_DW.is_c13_VCU10 = VCU10_IN_Close;
        rtb_Add2_g = 0U;
      }
      break;
    }
  }

  /* End of Chart: '<S219>/blue' */

  /* DiscretePulseGenerator: '<S219>/Pulse Generator' */
  i = ((VCU10_DW.clockTickCounter < 25) && (VCU10_DW.clockTickCounter >= 0));
  if (VCU10_DW.clockTickCounter >= 49) {
    VCU10_DW.clockTickCounter = 0;
  } else {
    VCU10_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<S219>/Pulse Generator' */

  /* Switch: '<S219>/Switch' incorporates:
   *  Constant: '<S219>/Constant'
   */
  if (rtb_Add2_g > 10) {
    rtb_blue_0 = rtb_Add2_g;
  } else {
    rtb_blue_0 = 0;
  }

  /* End of Switch: '<S219>/Switch' */

  /* Switch: '<S219>/Switch2' incorporates:
   *  Constant: '<S219>/Constant1'
   *  Constant: '<S219>/Constant2'
   *  Switch: '<S219>/Switch1'
   */
  if (rtb_blue_0 > 40000) {
    i = 1;
  } else if (rtb_Add2_g <= 10) {
    i = 0;
  }

  /* End of Switch: '<S219>/Switch2' */

  /* DataTypeConversion: '<S219>/Data Type Conversion' */
  led_assi_blue = (i != 0);

  /* Chart: '<S220>/yellow' */
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
      if (VCU10_B.as_led_yellow == 0.0) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_Close;
        rtb_Add2_g = 0U;
      } else if (VCU10_B.as_led_yellow == 1.0) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_On_o;
        rtb_Add2_g = 60000U;
      }
      break;

     case VCU10_IN_Close:
      rtb_Add2_g = 0U;
      if (VCU10_B.as_led_yellow == 1.0) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_On_o;
        rtb_Add2_g = 60000U;
      } else if (VCU10_B.as_led_yellow == 2.0) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_Blink;
        rtb_Add2_g = 30000U;
      }
      break;

     case VCU10_IN_On_o:
      rtb_Add2_g = 60000U;
      if (VCU10_B.as_led_yellow == 2.0) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_Blink;
        rtb_Add2_g = 30000U;
      } else if (VCU10_B.as_led_yellow == 0.0) {
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
      if (VCU10_B.as_led_yellow == 1.0) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_On_o;
        rtb_Add2_g = 60000U;
      } else if (VCU10_B.as_led_yellow == 0.0) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_Close;
      } else if (VCU10_B.as_led_yellow == 2.0) {
        VCU10_DW.is_c14_VCU10 = VCU10_IN_Blink;
        rtb_Add2_g = 30000U;
      }
      break;
    }
  }

  /* End of Chart: '<S220>/yellow' */

  /* DiscretePulseGenerator: '<S220>/Pulse Generator' */
  i = ((VCU10_DW.clockTickCounter_a < 25) && (VCU10_DW.clockTickCounter_a >= 0));
  if (VCU10_DW.clockTickCounter_a >= 49) {
    VCU10_DW.clockTickCounter_a = 0;
  } else {
    VCU10_DW.clockTickCounter_a++;
  }

  /* End of DiscretePulseGenerator: '<S220>/Pulse Generator' */

  /* Switch: '<S220>/Switch' incorporates:
   *  Constant: '<S220>/Constant'
   */
  if (rtb_Add2_g > 10) {
    rtb_blue_0 = rtb_Add2_g;
  } else {
    rtb_blue_0 = 0;
  }

  /* End of Switch: '<S220>/Switch' */

  /* Switch: '<S220>/Switch2' incorporates:
   *  Constant: '<S220>/Constant1'
   *  Constant: '<S220>/Constant3'
   *  Switch: '<S220>/Switch1'
   */
  if (rtb_blue_0 > 40000) {
    i = 1;
  } else if (rtb_Add2_g <= 10) {
    i = 0;
  }

  /* End of Switch: '<S220>/Switch2' */

  /* DataTypeConversion: '<S220>/Data Type Conversion' */
  led_assi_yellow = (i != 0);

  /* Chart: '<S13>/TSLED_Inspection' */
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

  /* End of Chart: '<S13>/TSLED_Inspection' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms2' */

  /* S-Function (fcgen): '<Root>/Function-Call Generator1' incorporates:
   *  SubSystem: '<Root>/Output_Convert'
   */
  /* S-Function (fcgen): '<Root>/10ms3' incorporates:
   *  SubSystem: '<Root>/ASB_Selfcheck'
   */
  /* Outport: '<Root>/model_lox' incorporates:
   *  BitConcat: '<S266>/bc2'
   *  BitConcat: '<S266>/bc3'
   *  BitConcat: '<S266>/bc4'
   *  BitConcat: '<S266>/bc5'
   *  BitConcat: '<S266>/bc6'
   *  BitConcat: '<S266>/bc7'
   *  Logic: '<Root>/FSEC_EBS_Error_OR'
   *  MATLAB Function: '<S2>/FSEC_Sensor_Monitor'
   */
  VCU10_Y.model_lox = (uint8_T)((uint8_T)((uint8_T)((uint8_T)((uint8_T)
    (((uint8_T)(VCU10_ConstB.bc2 << 1) & 7) | res_error) << 1 | (led_ebs_error ||
    (rtb_AS_Torque_Enable || VCU10_DW.ebs_comm_fault) || EBS_Sensor_Fault_Delay))
    << 1 | led_assi_yellow) << 1 | led_assi_blue) << 1 | led_brake);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms3' */

  /* Outport: '<Root>/model_hox' incorporates:
   *  BitConcat: '<S265>/bc2'
   *  BitConcat: '<S265>/bc3'
   *  BitConcat: '<S265>/bc4'
   *  BitConcat: '<S265>/bc5'
   *  BitConcat: '<S265>/bc6'
   *  BitConcat: '<S265>/bc7'
   *  BitConcat: '<S265>/bc8'
   */
  VCU10_Y.model_hox = (uint8_T)((uint8_T)((uint8_T)((uint8_T)((uint8_T)((uint8_T)
    (ebs_buzzer << 1 | r2d_buzzer) << 1 | run) << 1 | di8) << 1 | led_imd_error)
    << 1 | led_bms_error) << 1 | ebs_trig);

  /* End of Outputs for S-Function (fcgen): '<Root>/Function-Call Generator1' */

  /* S-Function (fcgen): '<Root>/10ms8' incorporates:
   *  SubSystem: '<Root>/ESP'
   */
  /* Outport: '<Root>/ESP_R_00' incorporates:
   *  DataTypeConversion: '<S143>/Data Type Conversion1'
   *  DataTypeConversion: '<S143>/Data Type Conversion13'
   *  DataTypeConversion: '<S143>/Data Type Conversion2'
   *  DataTypeConversion: '<S143>/Data Type Conversion4'
   *  DataTypeConversion: '<S143>/Data Type Conversion6'
   *  S-Function (sfix_bitop): '<S143>/Bitwise AND3'
   *  S-Function (sfix_bitop): '<S143>/Bitwise AND7'
   *  Sum: '<S143>/Add2'
   */
  VCU10_Y.ESP_R_00[0] = (uint8_T)rtb_y_ld;
  VCU10_Y.ESP_R_00[1] = (uint8_T)rtb_y_ec;
  VCU10_Y.ESP_R_00[2] = (uint8_T)(rtb_y_gw & 255);
  VCU10_Y.ESP_R_00[3] = (uint8_T)rtb_y_cg;
  VCU10_Y.ESP_R_00[4] = (uint8_T)wheel_u16;
  VCU10_Y.ESP_R_00[5] = (uint8_T)(rtb_Add1_a & 255);
  VCU10_Y.ESP_R_00[6] = (uint8_T)((uint32_T)rtb_y_in +
    VCU10_ConstB.BitwiseAND8_o);
  VCU10_Y.ESP_R_00[7] = 0U;

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms8' */

  /* S-Function (fcgen): '<Root>/10ms11' incorporates:
   *  SubSystem: '<Root>/IPC'
   */
  /* Sum: '<S166>/Add4' incorporates:
   *  Constant: '<S166>/Constant'
   *  DataTypeConversion: '<S166>/Data Type Conversion6'
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  airprs_sensor1 = ((real_T)canb_ipctsmsg1[6] + rtb_DataTypeConversion1) -
    5000.0;

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */

  /* S-Function (fcgen): '<Root>/10ms4' incorporates:
   *  SubSystem: '<Root>/Motor_Control'
   */
  /* Saturate: '<S234>/Saturation' */
  if (airprs_sensor1 > 55.0) {
    airprs_sensor1 = 55.0;
  } else if (airprs_sensor1 < 0.0) {
    airprs_sensor1 = 0.0;
  }

  /* End of Saturate: '<S234>/Saturation' */

  /* S-Function (fcgen): '<Root>/10ms6' incorporates:
   *  SubSystem: '<Root>/AS_Stateflow'
   */
  /* Logic: '<S14>/AS_Torque_Enable' incorporates:
   *  DataStoreRead: '<S14>/FSEC_Safety_Lock_Read'
   *  DataStoreWrite: '<Root>/Data Store Write14'
   *  DataStoreWrite: '<S3>/Data Store Write10'
   *  DataStoreWrite: '<S3>/Data Store Write8'
   *  Logic: '<S14>/No_FSEC_Safety_Lock'
   *  Logic: '<S14>/R2D_Complete'
   */
  rtb_AS_Torque_Enable = (asms && (VCU10_B.as_driving_flag_a != 0.0) &&
    (!(VCU10_B.r2d_flag_a != 0.0)) && (!(VCU10_DW.safety_lock != 0.0)));

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */

  /* Chart: '<S237>/Pedal_Fault_Check' */
  if (fabs(apps1_01 - apps2_01) >= 0.1) {
    VCU10_DW.fault_count++;
    if (VCU10_DW.fault_count >= 3.0) {
      VCU10_B.pedal_error = 1.0;
    }
  } else {
    VCU10_DW.fault_count = 0.0;
    VCU10_B.pedal_error = 0.0;
  }

  /* End of Chart: '<S237>/Pedal_Fault_Check' */

  /* S-Function (fcgen): '<Root>/10ms' incorporates:
   *  SubSystem: '<Root>/Sensor_Signal'
   */
  /* MATLAB Function: '<S237>/APPS_Electrical_Monitor' incorporates:
   *  DataTypeConversion: '<S17>/Data Type Conversion1'
   *  DataTypeConversion: '<S17>/Data Type Conversion3'
   */
  LogicalOperator_e = ((apps1 < 100) || (apps1 > 4900) || (apps2 < 100) ||
                       (apps2 > 4900));

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */
  if (LogicalOperator_e) {
    VCU10_DW.good_count_d = 0U;
    if (VCU10_DW.bad_count_b < 1000) {
      elapsedTicks_m = VCU10_DW.bad_count_b + 1U;
      if (VCU10_DW.bad_count_b + 1U > 65535U) {
        elapsedTicks_m = 65535U;
      }

      VCU10_DW.bad_count_b = (uint16_T)elapsedTicks_m;
    }

    VCU10_DW.fault_n = ((VCU10_DW.bad_count_b >= 10) || VCU10_DW.fault_n);
  } else {
    VCU10_DW.bad_count_b = 0U;
    if (VCU10_DW.good_count_d < 1000) {
      elapsedTicks_m = VCU10_DW.good_count_d + 1U;
      if (VCU10_DW.good_count_d + 1U > 65535U) {
        elapsedTicks_m = 65535U;
      }

      VCU10_DW.good_count_d = (uint16_T)elapsedTicks_m;
    }

    VCU10_DW.fault_n = ((VCU10_DW.good_count_d < 50) && VCU10_DW.fault_n);
  }

  /* Switch: '<S237>/Switch' incorporates:
   *  Constant: '<S237>/Constant'
   *  Constant: '<S237>/Constant1'
   *  Constant: '<S237>/max_torque'
   *  Logic: '<S237>/APPS_Torque_Valid_Gate'
   *  Logic: '<S237>/Logical Operator'
   *  MATLAB Function: '<S237>/APPS_Electrical_Monitor'
   *  Product: '<S237>/Divide'
   *  Product: '<S237>/Product'
   *  Sum: '<S237>/Add'
   */
  if ((!(VCU10_B.pedal_error != 0.0)) && ((!LogicalOperator_e) &&
       (!VCU10_DW.fault_n))) {
    apps1_01 = (apps1_01 + apps2_01) / 2.0 * 50.0;
  } else {
    apps1_01 = 0.0;
  }

  /* End of Switch: '<S237>/Switch' */

  /* Chart: '<S14>/Motor_Torque_Stateflow' incorporates:
   *  DataStoreWrite: '<S3>/Data Store Write2'
   */
  if (VCU10_DW.is_active_c4_VCU10 == 0U) {
    VCU10_DW.is_active_c4_VCU10 = 1U;
    VCU10_DW.is_c4_VCU10 = VCU10_IN_Default_m;
    apps1_01 = 0.0;
  } else {
    switch (VCU10_DW.is_c4_VCU10) {
     case VCU10_IN_AS_Driving:
      if (!rtb_AS_Torque_Enable) {
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
      if (VCU10_B.manual_driving_flag_j == 1.0) {
        VCU10_DW.is_c4_VCU10 = VCU10_IN_Manual_Driving;
      } else if (rtb_AS_Torque_Enable) {
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
      if (VCU10_B.manual_driving_flag_j == 0.0) {
        VCU10_DW.is_c4_VCU10 = VCU10_IN_Default_m;
        apps1_01 = 0.0;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;
    }
  }

  /* End of Chart: '<S14>/Motor_Torque_Stateflow' */

  /* Outputs for Atomic SubSystem: '<S235>/Bit Shift' */
  VCU10_BitShift_a(VCU10_ConstB.BitwiseAND1_a, &active);

  /* End of Outputs for SubSystem: '<S235>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S235>/Bit Shift3' */
  VCU10_BitShift3_m(VCU10_ConstB.BitwiseAND4, &rtb_y_ev);

  /* End of Outputs for SubSystem: '<S235>/Bit Shift3' */

  /* S-Function (fcgen): '<Root>/10ms6' incorporates:
   *  SubSystem: '<Root>/AS_Stateflow'
   */
  /* Switch: '<S14>/Emergency_Torque_Gate' incorporates:
   *  Constant: '<S14>/Emergency_Zero_Torque'
   *  DataStoreWrite: '<S3>/Data Store Write3'
   */
  if (VCU10_B.as_emergency_flag_m >= 0.5) {
    apps1_01 = 0.0;
  }

  /* End of Switch: '<S14>/Emergency_Torque_Gate' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */

  /* DataTypeConversion: '<S235>/Data Type Conversion7' */
  rtb_Emergency_Pressure_Select_1 = floor(apps1_01);

  /* Outputs for Atomic SubSystem: '<S235>/Bit Shift5' */
  VCU10_BitShift5(VCU10_ConstB.BitwiseAND7, &rtb_y_ld);

  /* End of Outputs for SubSystem: '<S235>/Bit Shift5' */

  /* Outputs for Atomic SubSystem: '<S235>/Bit Shift6' */
  VCU10_BitShift6(VCU10_ConstB.BitwiseAND8, &wheel_u16);

  /* End of Outputs for SubSystem: '<S235>/Bit Shift6' */

  /* Sum: '<S235>/Add3' */
  rtb_y_gw = (uint16_T)((uint32_T)rtb_y_ld + wheel_u16);

  /* Outputs for Atomic SubSystem: '<S235>/Bit Shift7' */
  VCU10_BitShift7(VCU10_ConstB.BitwiseAND9, &wheel_u16);

  /* End of Outputs for SubSystem: '<S235>/Bit Shift7' */

  /* Outputs for Atomic SubSystem: '<S235>/Bit Shift8' */
  /* S-Function (sfix_bitop): '<S235>/Bitwise AND11' */
  VCU10_BitShift5(4864, &rtb_y_ld);

  /* End of Outputs for SubSystem: '<S235>/Bit Shift8' */

  /* Outputs for Atomic SubSystem: '<S235>/Bit Shift9' */
  VCU10_BitShift5(VCU10_ConstB.BitwiseAND13, &rtb_y_cg);

  /* End of Outputs for SubSystem: '<S235>/Bit Shift9' */

  /* DataTypeConversion: '<S235>/Data Type Conversion7' */
  if (rtIsNaN(rtb_Emergency_Pressure_Select_1)) {
    rtb_Emergency_Pressure_Select_1 = 0.0;
  } else {
    rtb_Emergency_Pressure_Select_1 = fmod(rtb_Emergency_Pressure_Select_1,
      65536.0);
  }

  /* S-Function (sfix_bitop): '<S235>/Bitwise AND10' incorporates:
   *  Constant: '<S235>/constant'
   *  DataTypeConversion: '<S235>/Data Type Conversion7'
   *  Sum: '<S235>/Add1'
   */
  rtb_y_ec = (uint16_T)((uint16_T)((uint16_T)rtb_Emergency_Pressure_Select_1 +
    5000U) & 255);

  /* Outputs for Atomic SubSystem: '<S235>/Bit Shift1' */
  /* Outputs for Atomic SubSystem: '<S235>/Bit Shift2' */
  /* Outputs for Atomic SubSystem: '<S235>/Bit Shift4' */
  /* SignalConversion: '<S235>/Signal Conversion' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read15'
   *  DataTypeConversion: '<S235>/Data Type Conversion12'
   *  DataTypeConversion: '<S235>/Data Type Conversion13'
   *  DataTypeConversion: '<S235>/Data Type Conversion14'
   *  DataTypeConversion: '<S235>/Data Type Conversion15'
   *  DataTypeConversion: '<S235>/Data Type Conversion17'
   *  DataTypeConversion: '<S235>/Data Type Conversion2'
   *  MATLAB Function: '<S240>/bit_shift'
   *  MATLAB Function: '<S241>/bit_shift'
   *  MATLAB Function: '<S243>/bit_shift'
   *  S-Function (sfix_bitop): '<S235>/Bitwise AND2'
   *  S-Function (sfix_bitop): '<S235>/Bitwise AND3'
   *  S-Function (sfix_bitop): '<S235>/Bitwise AND5'
   *  Sum: '<S235>/Add'
   */
  cana_motor_cmd[0] = (uint8_T)((uint32_T)(uint8_T)((uint32_T)(uint8_T)
    ((uint32_T)(uint8_T)((uint32_T)(uint8_T)((uint32_T)VCU10_DW.ts + active) +
    (uint8_T)(VCU10_ConstB.BitwiseAND2_o << 2)) + (uint8_T)
     (VCU10_ConstB.BitwiseAND3_o << 4)) + rtb_y_ev) + (uint8_T)
    (VCU10_ConstB.BitwiseAND5 << 7));

  /* End of Outputs for SubSystem: '<S235>/Bit Shift4' */
  /* End of Outputs for SubSystem: '<S235>/Bit Shift2' */
  /* End of Outputs for SubSystem: '<S235>/Bit Shift1' */
  cana_motor_cmd[1] = VCU10_ConstB.MCU1_Rx_Commandbyte1;
  cana_motor_cmd[2] = (uint8_T)rtb_y_gw;
  cana_motor_cmd[3] = (uint8_T)wheel_u16;
  cana_motor_cmd[4] = (uint8_T)rtb_y_ec;
  cana_motor_cmd[5] = (uint8_T)rtb_y_ld;
  cana_motor_cmd[6] = VCU10_ConstB.MCU1_Rx_Commandbyte6;
  cana_motor_cmd[7] = (uint8_T)rtb_y_cg;

  /* Outputs for Atomic SubSystem: '<S236>/Bit Shift' */
  VCU10_BitShift5(VCU10_ConstB.BitwiseAND1, &rtb_y_gw);

  /* End of Outputs for SubSystem: '<S236>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S236>/Bit Shift1' */
  VCU10_BitShift5(VCU10_ConstB.BitwiseAND3, &rtb_y_ec);

  /* End of Outputs for SubSystem: '<S236>/Bit Shift1' */

  /* SignalConversion generated from: '<S14>/cana_motor_cmd3' incorporates:
   *  Constant: '<S236>/constant'
   *  DataTypeConversion: '<S236>/Data Type Conversion3'
   *  DataTypeConversion: '<S236>/Data Type Conversion6'
   */
  cana_motor_cmd3[0] = VCU10_ConstB.MCU1_Rx_Command3byte0;
  cana_motor_cmd3[1] = (uint8_T)rtb_y_gw;
  cana_motor_cmd3[2] = VCU10_ConstB.MCU1_Rx_Command3byte2;
  cana_motor_cmd3[3] = (uint8_T)rtb_y_ec;
  cana_motor_cmd3[4] = 0U;
  cana_motor_cmd3[5] = 0U;
  cana_motor_cmd3[6] = 0U;
  cana_motor_cmd3[7] = 0U;

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms4' */

  /* MATLAB Function: '<Root>/DBC_Debug_StatusPack' incorporates:
   *  BitConcat: '<S266>/bc7'
   *  Outport: '<Root>/model_hox'
   *  Outport: '<Root>/model_lox'
   *  Outport: '<Root>/vcu_dbg_status'
   */
  VCU10_Y.vcu_dbg_status[4] = VCU10_Y.model_lox;
  VCU10_Y.vcu_dbg_status[5] = VCU10_Y.model_hox;

  /* MATLAB Function: '<Root>/EPS_SCS_Monitor' incorporates:
   *  Inport: '<Root>/canb_epssendmsg1'
   *  Inport: '<Root>/canb_epssendmsg2'
   */
  if (!VCU10_DW.last_counter_not_empty) {
    VCU10_DW.last_counter = canb_epssendmsg2[1];
    VCU10_DW.last_counter_not_empty = true;
  }

  if (canb_epssendmsg2[1] != VCU10_DW.last_counter) {
    VCU10_DW.last_counter = canb_epssendmsg2[1];
    VCU10_DW.stale_count = 0U;
    if (VCU10_DW.seen_count < 1000) {
      elapsedTicks_m = VCU10_DW.seen_count + 1U;
      if (VCU10_DW.seen_count + 1U > 65535U) {
        elapsedTicks_m = 65535U;
      }

      VCU10_DW.seen_count = (uint16_T)elapsedTicks_m;
    }
  } else if (VCU10_DW.stale_count < 1000) {
    elapsedTicks_m = VCU10_DW.stale_count + 1U;
    if (VCU10_DW.stale_count + 1U > 65535U) {
      elapsedTicks_m = 65535U;
    }

    VCU10_DW.stale_count = (uint16_T)elapsedTicks_m;
  }

  active = 0U;
  for (i = 0; i < 7; i++) {
    active ^= canb_epssendmsg1[i];
  }

  if ((active == canb_epssendmsg1[7]) && ((canb_epssendmsg1[2] == 0) &&
       (canb_epssendmsg1[6] == 0)) && ((VCU10_DW.seen_count >= 3) &&
       (VCU10_DW.stale_count < 30))) {
    VCU10_DW.bad_count = 0U;
    if (VCU10_DW.good_count < 1000) {
      elapsedTicks_m = VCU10_DW.good_count + 1U;
      if (VCU10_DW.good_count + 1U > 65535U) {
        elapsedTicks_m = 65535U;
      }

      VCU10_DW.good_count = (uint16_T)elapsedTicks_m;
    }

    VCU10_DW.fault = ((VCU10_DW.good_count < 50) && VCU10_DW.fault);
  } else {
    VCU10_DW.good_count = 0U;
    if (VCU10_DW.bad_count < 1000) {
      elapsedTicks_m = VCU10_DW.bad_count + 1U;
      if (VCU10_DW.bad_count + 1U > 65535U) {
        elapsedTicks_m = 65535U;
      }

      VCU10_DW.bad_count = (uint16_T)elapsedTicks_m;
    }

    VCU10_DW.fault = ((VCU10_DW.bad_count >= 3) || (VCU10_DW.stale_count >= 30) ||
                      VCU10_DW.fault);
  }

  /* S-Function (fcgen): '<Root>/10ms11' incorporates:
   *  SubSystem: '<Root>/IPC'
   */
  /* Logic: '<Root>/FSEC_Safety_Fault_OR' incorporates:
   *  DataTypeConversion: '<S167>/Data Type Conversion3'
   *  MATLAB Function: '<Root>/EPS_SCS_Monitor'
   *  UnitDelay: '<Root>/FSEC_Safety_Fault_Delay'
   */
  VCU10_DW.FSEC_Safety_Fault_Delay_DSTATE = (LogicalOperator_o ||
    EBS_Sensor_Fault_Delay || (requested != 0) || VCU10_DW.fault);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */

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

  /* SystemInitialize for MATLAB Function: '<Root>/DBC_Debug_Select' */
  VCU10_DW.ages[0] = 50U;
  VCU10_DW.ages[1] = 50U;
  VCU10_DW.ages[2] = 50U;
  VCU10_DW.ages[3] = 50U;

  /* SystemInitialize for MATLAB Function: '<Root>/EPS_SCS_Monitor' */
  VCU10_DW.fault = true;

  /* Enable for S-Function (fcgen): '<Root>/10ms6' incorporates:
   *  SubSystem: '<Root>/AS_Stateflow'
   */
  /* Enable for Chart: '<S3>/Chart' */
  VCU10_DW.previousTicks_g = VCU10_M->Timing.clockTick0;

  /* End of Enable for S-Function (fcgen): '<Root>/10ms6' */

  /* Enable for S-Function (fcgen): '<Root>/10ms9' incorporates:
   *  SubSystem: '<Root>/EPS'
   */
  /* Enable for Chart: '<S48>/EPS_Stateflow1' */
  VCU10_DW.previousTicks = VCU10_M->Timing.clockTick0;

  /* End of Enable for S-Function (fcgen): '<Root>/10ms9' */

  /* Enable for S-Function (fcgen): '<Root>/10ms1' incorporates:
   *  SubSystem: '<Root>/TS_Activation'
   */
  /* Enable for Chart: '<S18>/Chart2' */
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
  /* Enable for Chart: '<S218>/Shutdown_Button' */
  VCU10_DW.previousTicks_f = VCU10_M->Timing.clockTick0;

  /* Enable for Chart: '<S218>/display' */
  VCU10_DW.previousTicks_ag = VCU10_M->Timing.clockTick0;

  /* Enable for Chart: '<S219>/blue' */
  VCU10_DW.previousTicks_av = VCU10_M->Timing.clockTick0;

  /* Enable for Chart: '<S220>/yellow' */
  VCU10_DW.previousTicks_a = VCU10_M->Timing.clockTick0;

  /* Enable for Chart: '<S13>/TSLED_Inspection' */
  VCU10_DW.previousTicks_o = VCU10_M->Timing.clockTick0;

  /* End of Enable for S-Function (fcgen): '<Root>/10ms2' */
}

/* Model terminate function */
void VCU10_terminate(void)
{
  /* (no terminate code required) */
}
