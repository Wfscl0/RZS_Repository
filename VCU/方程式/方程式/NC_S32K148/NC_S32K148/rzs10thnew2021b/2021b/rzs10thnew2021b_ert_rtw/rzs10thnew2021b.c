/*
 * File: rzs10thnew2021b.c
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

#include "rzs10thnew2021b.h"
#include "rzs10thnew2021b_private.h"

/* Named constants for Chart: '<S14>/Chart' */
#define rzs10thnew2021b_IN_Check       ((uint8_T)1U)
#define rzs10thnew2021b_IN_Checkoff    ((uint8_T)1U)
#define rzs10thnew2021b_IN_begin       ((uint8_T)3U)
#define rzs10thnew202_IN_DI8_Check_Flag ((uint8_T)2U)
#define rzs10thnew202_IN_Flameout_Check ((uint8_T)1U)
#define rzs10thnew202_IN_Ignition_Check ((uint8_T)2U)
#define rzs10thnew20_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define rzs10thnew_IN_DI8_Offcheck_Flag ((uint8_T)2U)

/* Named constants for Chart: '<S14>/Chart1' */
#define rzs10thnew202_IN_Run_Check_Flag ((uint8_T)2U)
#define rzs10thnew_IN_Run_Offcheck_Flag ((uint8_T)2U)

/* Named constants for Chart: '<S14>/Chart2' */
#define rzs10thnew2021b_IN_begin_b     ((uint8_T)1U)

/* Named constants for Chart: '<S248>/heaartbeat_chart' */
#define rzs10thnew2021b_IN_compare     ((uint8_T)2U)
#define rzs10thnew2021b_IN_judge       ((uint8_T)3U)
#define rzs10thnew2021b_IN_same        ((uint8_T)4U)

/* Named constants for Chart: '<S248>/xor_Check' */
#define rzs10thnew2021b_IN_Init        ((uint8_T)1U)
#define rzs10thnew2021b_IN_different   ((uint8_T)3U)
#define rzs10thnew2021b_IN_judge_e     ((uint8_T)4U)

/* Named constants for Chart: '<S5>/Chart' */
#define rzs10thnew2021b_IN_Default     ((uint8_T)1U)
#define rzs10thnew2021b_IN_Emergency   ((uint8_T)2U)

/* Named constants for Chart: '<S17>/Chart' */
#define rzs10thnew2021b_IN_as_driving  ((uint8_T)1U)
#define rzs10thnew2021b_IN_as_emergency ((uint8_T)2U)
#define rzs10thnew2021b_IN_as_finished ((uint8_T)3U)
#define rzs10thnew2021b_IN_as_off      ((uint8_T)4U)
#define rzs10thnew2021b_IN_as_ready    ((uint8_T)5U)
#define rzs10thnew2021b_IN_begin_n     ((uint8_T)6U)
#define rzs10thnew2021b_IN_r2d         ((uint8_T)8U)
#define rzs10thnew202_IN_munual_driving ((uint8_T)7U)

/* Named constants for Chart: '<S196>/BMS_LED' */
#define rzs10thnew2021_IN_EBS_LED_Check ((uint8_T)1U)
#define rzs10thnew2021b_IN_EBS_LED_ON  ((uint8_T)2U)
#define rzs10thnew2021b_IN_delay       ((uint8_T)3U)

/* Named constants for Chart: '<S197>/Shutdown_Button' */
#define rzs10thnew2021b_IN_same1       ((uint8_T)4U)

/* Named constants for Chart: '<S197>/display' */
#define rzs10thnew2021b_IN_end         ((uint8_T)2U)

/* Named constants for Chart: '<S198>/blue' */
#define rzs10thnew2021b_IN_Blink       ((uint8_T)1U)
#define rzs10thnew2021b_IN_Close       ((uint8_T)2U)
#define rzs10thnew2021b_IN_Delay       ((uint8_T)3U)
#define rzs10thnew2021b_IN_Node        ((uint8_T)4U)

/* Named constants for Chart: '<S199>/yellow' */
#define rzs10thnew2021b_IN_On          ((uint8_T)3U)
#define rzs10thnew2021b_IN_delay_g     ((uint8_T)4U)
#define rzs10thnew2021b_IN_node        ((uint8_T)5U)

/* Named constants for Chart: '<S11>/Motor_Torque_Stateflow' */
#define rzs10thnew2021b_IN_AS_Driving  ((uint8_T)1U)
#define rzs10thnew2021b_IN_Default_n   ((uint8_T)2U)
#define rzs10thnew202_IN_Manual_Driving ((uint8_T)3U)

/* Named constants for Chart: '<S3>/Chart' */
#define rzs10thnew2021_IN_manualdriving ((uint8_T)7U)
#define rzs10thnew2021b_IN_Acceleration ((uint8_T)1U)
#define rzs10thnew2021b_IN_EBS_Test    ((uint8_T)2U)
#define rzs10thnew2021b_IN_Init_k      ((uint8_T)3U)
#define rzs10thnew2021b_IN_Skidpad     ((uint8_T)4U)
#define rzs10thnew2021b_IN_Trackdriver ((uint8_T)5U)
#define rzs10thnew2021b_IN_inspection  ((uint8_T)6U)

/* Named constants for Chart: '<S4>/Chart' */
#define rzs10thnew2021b_IN_AS_Emergency ((uint8_T)2U)
#define rzs10thnew2021b_IN_AS_Finished ((uint8_T)3U)
#define rzs10thnew2021b_IN_AS_Off      ((uint8_T)4U)
#define rzs10thnew2021b_IN_AS_Ready    ((uint8_T)5U)
#define rzs10thnew2021b_IN_R2D         ((uint8_T)1U)
#define rzs10thnew2021b_IN_go          ((uint8_T)2U)
#define rzs10thnew2_IN_Manual_Driving_j ((uint8_T)6U)

/* Named constants for Chart: '<S151>/ESP_Chart1' */
#define rzs10thnew2021b_IN_ESC_Able    ((uint8_T)1U)
#define rzs10thnew2021b_IN_ESC_Engage  ((uint8_T)2U)
#define rzs10thnew2021b_IN_ESC_Unable  ((uint8_T)3U)

/* Named constants for Chart: '<S56>/EPS_Stateflow1' */
#define rzs10thnew2021b_IN_EPS_Enable  ((uint8_T)1U)
#define rzs10thnew2021b_IN_EPS_Return  ((uint8_T)2U)
#define rzs10thnew2021b_IN_EPS_Unable  ((uint8_T)3U)

/* Exported block signals */
boolean_T bms_error;                   /* '<Root>/bms_error' */
boolean_T imd_error;                   /* '<Root>/imd_error' */
uint8_T ESP_T_01[8];                   /* '<Root>/ESP_T_01' */
uint8_T ESP_T_03[8];                   /* '<Root>/ESP_T_03' */
uint8_T ESP_T_06[8];                   /* '<Root>/ESP_T_06' */
uint8_T ESP_T_07[8];                   /* '<Root>/ESP_T_07' */
uint8_T canb_epssendmsg1[8];           /* '<Root>/canb_epssendmsg1' */
uint8_T canb_epssendmsg2[8];           /* '<Root>/canb_epssendmsg2' */
uint8_T res_msg[8];                    /* '<Root>/res_msg' */
uint8_T canb_ipctsmsg1[8];             /* '<Root>/canb_ipctsmsg1' */
uint8_T canb_ipctsmsg2[8];             /* '<Root>/canb_ipctsmsg2' */
uint8_T AMI_Tx[8];                     /* '<Root>/AMI_Tx' */
VCU_IN_PAR digital_input;              /* '<Root>/Input' */
VCU_OUT_PAR digital_output;            /* '<S15>/Bus Creator' */
uint8_T ESP_R_00[8];                   /* '<Root>/Delay' */
uint8_T cana_motor_cmd[8];             /* '<Root>/Delay1' */
uint8_T cana_motor_cmd3[8];            /* '<Root>/Delay2' */
uint8_T canb_epsmsg[8];                /* '<S7>/EPS_TransmitMsg' */
uint8_T AMI_Rx[8];                     /* '<S17>/Signal Conversion' */
uint8_T canb_ipcrxmsg[8];              /* '<S9>/IPC_ReceiveMsg' */
boolean_T ebs_trig;                    /* '<S6>/Logical Operator' */
boolean_T ebs_watchdog;                /* '<S6>/Data Type Conversion5' */
boolean_T led_brake;                   /* '<S10>/brake_on' */
boolean_T led_ebs_error;               /* '<S197>/Logical Operator' */
boolean_T led_assi_blue;               /* '<S198>/Data Type Conversion' */
boolean_T led_assi_yellow;             /* '<S199>/Data Type Conversion' */
boolean_T led_imd_error;               /* '<S196>/IMD_LED' */
boolean_T led_bms_error;               /* '<S196>/BMS_LED' */
boolean_T r2d_buzzer;                  /* '<S5>/r2d_warning' */
boolean_T ebs_buzzer;                  /* '<S5>/Switch' */
boolean_T ts_buzzer;                   /* '<S5>/ts_warning' */
boolean_T res_error;                   /*  */
boolean_T run;                         /* '<S14>/Chart1' */
boolean_T di8;                         /* '<S14>/Chart' */

/* Block signals (default storage) */
B_rzs10thnew2021b_T rzs10thnew2021b_B;

/* Block states (default storage) */
DW_rzs10thnew2021b_T rzs10thnew2021b_DW;

/* Real-time model */
static RT_MODEL_rzs10thnew2021b_T rzs10thnew2021b_M_;
RT_MODEL_rzs10thnew2021b_T *const rzs10thnew2021b_M = &rzs10thnew2021b_M_;

/* Forward declaration for local functions */
static void rzs10thnew2_enter_atomic_AS_Off(void);
static void rzs10_enter_atomic_AS_Emergency(void);
static void rzs10thnew2021b_AS_Driving(const boolean_T *LogicalOperator);
uint16_T look1_iu16lu16n16_linlcase(uint16_T u0, const uint16_T bp0[], const
  uint16_T table[], uint32_T maxIndex)
{
  uint32_T bpIdx;
  uint16_T frac;
  uint16_T y;
  uint16_T yL_0d0;
  uint16_T yR_0d0;

  /* Column-major Lookup 1-D
     Search method: 'linear'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
     Rounding mode: 'simplest'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'linear'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
     Rounding mode: 'simplest'
   */
  if (u0 <= bp0[0U]) {
    bpIdx = 0U;
    frac = 0U;
  } else if (u0 < bp0[maxIndex]) {
    /* Linear Search */
    for (bpIdx = maxIndex >> 1U; u0 < bp0[bpIdx]; bpIdx--) {
    }

    while (u0 >= bp0[bpIdx + 1U]) {
      bpIdx++;
    }

    frac = bp0[bpIdx];
    frac = (uint16_T)(((uint32_T)(uint16_T)((uint32_T)u0 - frac) << 16) /
                      (uint16_T)((uint32_T)bp0[bpIdx + 1U] - frac));
  } else {
    bpIdx = maxIndex;
    frac = 0U;
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'on'
     Rounding mode: 'simplest'
     Overflow mode: 'wrapping'
   */
  if (bpIdx == maxIndex) {
    y = table[bpIdx];
  } else {
    yR_0d0 = table[bpIdx + 1U];
    yL_0d0 = table[bpIdx];
    if (yR_0d0 >= yL_0d0) {
      y = (uint16_T)((uint32_T)(uint16_T)(((uint32_T)(uint16_T)((uint32_T)yR_0d0
        - yL_0d0) * frac) >> 16) + yL_0d0);
    } else {
      y = (uint16_T)((uint32_T)yL_0d0 - (uint16_T)(((uint32_T)(uint16_T)
        ((uint32_T)yL_0d0 - yR_0d0) * frac) >> 16));
    }
  }

  return y;
}

/*
 * Output and update for atomic system:
 *    '<S244>/Bit Shift'
 *    '<S69>/Bit Shift15'
 *    '<S69>/Bit Shift8'
 */
void rzs10thnew2021b_BitShift(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S245>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 1);
}

/*
 * Output and update for atomic system:
 *    '<S244>/Bit Shift1'
 *    '<S69>/Bit Shift1'
 *    '<S69>/Bit Shift9'
 */
void rzs10thnew2021b_BitShift1(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S246>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 2);
}

/*
 * Output and update for atomic system:
 *    '<S244>/Bit Shift2'
 *    '<S16>/Bit Shift'
 *    '<S69>/Bit Shift11'
 *    '<S69>/Bit Shift5'
 *    '<S69>/Bit Shift7'
 *    '<S15>/Bit Shift12'
 */
void rzs10thnew2021b_BitShift2(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S247>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 4);
}

/*
 * Output and update for atomic system:
 *    '<S172>/Bit Shift'
 *    '<S70>/Bit Shift2'
 *    '<S70>/Bit Shift5'
 *    '<S72>/Bit Shift2'
 *    '<S72>/Bit Shift5'
 *    '<S58>/Bit Shift1'
 */
void rzs10thnew2021b_BitShift_a(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S174>/bit_shift' */
  *rty_y = (uint16_T)(rtu_u << 8);
}

/*
 * Output and update for atomic system:
 *    '<S172>/Bit Shift1'
 *    '<S71>/Bit Shift3'
 */
void rzs10thnew2021b_BitShift1_f(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S175>/bit_shift' */
  *rty_y = (uint16_T)((uint32_T)rtu_u >> 2);
}

/*
 * Output and update for atomic system:
 *    '<S172>/Bit Shift2'
 *    '<S71>/Bit Shift2'
 */
void rzs10thnew2021b_BitShift2_i(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S176>/bit_shift' */
  *rty_y = (uint16_T)(rtu_u << 6);
}

/*
 * Output and update for atomic system:
 *    '<S172>/Bit Shift3'
 *    '<S70>/Bit Shift1'
 *    '<S70>/Bit Shift4'
 *    '<S71>/Bit Shift8'
 *    '<S72>/Bit Shift1'
 *    '<S72>/Bit Shift4'
 */
void rzs10thnew2021b_BitShift3(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S177>/bit_shift' */
  *rty_y = (uint16_T)((uint32_T)rtu_u >> 4);
}

/*
 * Output and update for atomic system:
 *    '<S172>/Bit Shift4'
 *    '<S70>/Bit Shift'
 *    '<S70>/Bit Shift3'
 *    '<S71>/Bit Shift7'
 *    '<S72>/Bit Shift'
 *    '<S72>/Bit Shift3'
 */
void rzs10thnew2021b_BitShift4(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S178>/bit_shift' */
  *rty_y = (uint16_T)(rtu_u << 4);
}

/*
 * Output and update for atomic system:
 *    '<S172>/Bit Shift8'
 *    '<S173>/Bit Shift'
 */
void rzs10thnew2021b_BitShift8(real_T rtu_u, real_T *rty_y)
{
  /* MATLAB Function: '<S181>/bit_shift' */
  *rty_y = ldexp(rtu_u, 8);
}

/*
 * Output and update for atomic system:
 *    '<S173>/Bit Shift1'
 *    '<S69>/Bit Shift14'
 *    '<S69>/Bit Shift16'
 */
void rzs10thnew2021b_BitShift1_k(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S191>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 7);
}

/*
 * Output and update for atomic system:
 *    '<S173>/Bit Shift2'
 *    '<S69>/Bit Shift13'
 */
void rzs10thnew2021b_BitShift2_g(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S192>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 6);
}

/*
 * Output and update for atomic system:
 *    '<S17>/Bit Shift'
 *    '<S215>/Bit Shift'
 *    '<S15>/Bit Shift13'
 *    '<S15>/Bit Shift9'
 */
void rzs10thnew2021b_BitShift_g(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S20>/bit_shift' */
  *rty_y = (uint8_T)(rtu_u << 1);
}

/*
 * Output and update for atomic system:
 *    '<S215>/Bit Shift1'
 *    '<S15>/Bit Shift14'
 */
void rzs10thnew2021_BitShift1_kp(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S220>/bit_shift' */
  *rty_y = (uint8_T)(rtu_u << 2);
}

/*
 * Output and update for atomic system:
 *    '<S215>/Bit Shift2'
 *    '<S15>/Bit Shift16'
 */
void rzs10thnew2021b_BitShift2_o(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S221>/bit_shift' */
  *rty_y = (uint8_T)(rtu_u << 4);
}

/*
 * Output and update for atomic system:
 *    '<S215>/Bit Shift3'
 *    '<S151>/Bit Shift6'
 *    '<S15>/Bit Shift18'
 */
void rzs10thnew2021b_BitShift3_p(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S222>/bit_shift' */
  *rty_y = (uint8_T)(rtu_u << 6);
}

/*
 * Output and update for atomic system:
 *    '<S215>/Bit Shift4'
 *    '<S15>/Bit Shift19'
 */
void rzs10thnew2021b_BitShift4_j(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S223>/bit_shift' */
  *rty_y = (uint8_T)(rtu_u << 7);
}

/*
 * Output and update for atomic system:
 *    '<S215>/Bit Shift5'
 *    '<S215>/Bit Shift8'
 *    '<S215>/Bit Shift9'
 *    '<S216>/Bit Shift'
 *    '<S216>/Bit Shift1'
 *    '<S151>/Bit Shift2'
 *    '<S151>/Bit Shift5'
 *    '<S56>/Bit Shift'
 */
void rzs10thnew2021b_BitShift5(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S224>/bit_shift' */
  *rty_y = (uint16_T)((uint32_T)rtu_u >> 8);
}

/*
 * Output and update for atomic system:
 *    '<S215>/Bit Shift6'
 *    '<S151>/Bit Shift1'
 *    '<S151>/Bit Shift4'
 */
void rzs10thnew2021b_BitShift6(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S225>/bit_shift' */
  *rty_y = (uint16_T)(rtu_u << 4);
}

/*
 * Output and update for atomic system:
 *    '<S215>/Bit Shift7'
 *    '<S151>/Bit Shift'
 *    '<S151>/Bit Shift3'
 *    '<S15>/Bit Shift4'
 */
void rzs10thnew2021b_BitShift7(uint16_T rtu_u, uint16_T *rty_y)
{
  /* MATLAB Function: '<S226>/bit_shift' */
  *rty_y = (uint16_T)((uint32_T)rtu_u >> 4);
}

/*
 * Output and update for enable system:
 *    '<S46>/NEGATIVE Edge'
 *    '<S49>/NEGATIVE Edge'
 *    '<S52>/NEGATIVE Edge'
 */
void rzs10thnew2021_NEGATIVEEdge(real_T rtu_Enable, boolean_T rtu_IN, boolean_T
  rtu_INprevious, boolean_T *rty_OUT)
{
  /* Outputs for Enabled SubSystem: '<S46>/NEGATIVE Edge' incorporates:
   *  EnablePort: '<S47>/Enable'
   */
  if (rtu_Enable > 0.0) {
    /* RelationalOperator: '<S47>/Relational Operator1' */
    *rty_OUT = ((int32_T)rtu_INprevious > (int32_T)rtu_IN);
  }

  /* End of Outputs for SubSystem: '<S46>/NEGATIVE Edge' */
}

/*
 * Output and update for enable system:
 *    '<S46>/POSITIVE Edge'
 *    '<S49>/POSITIVE Edge'
 *    '<S52>/POSITIVE Edge'
 */
void rzs10thnew2021_POSITIVEEdge(real_T rtu_Enable, boolean_T rtu_IN, boolean_T
  rtu_INprevious, boolean_T *rty_OUT)
{
  /* Outputs for Enabled SubSystem: '<S46>/POSITIVE Edge' incorporates:
   *  EnablePort: '<S48>/Enable'
   */
  if (rtu_Enable > 0.0) {
    /* RelationalOperator: '<S48>/Relational Operator1' */
    *rty_OUT = ((int32_T)rtu_IN > (int32_T)rtu_INprevious);
  }

  /* End of Outputs for SubSystem: '<S46>/POSITIVE Edge' */
}

/*
 * Output and update for atomic system:
 *    '<S69>/Bit Shift10'
 *    '<S69>/Bit Shift3'
 *    '<S15>/Bit Shift11'
 */
void rzs10thnew2021b_BitShift10(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S76>/bit_shift' */
  *rty_y = (uint8_T)((uint32_T)rtu_u >> 3);
}

/*
 * Output and update for atomic system:
 *    '<S69>/Bit Shift4'
 *    '<S69>/Bit Shift6'
 */
void rzs10thnew2021b_BitShift4_p(uint8_T rtu_u, uint8_T *rty_y)
{
  /* MATLAB Function: '<S85>/bit_shift' */
  *rty_y = (uint8_T)(rtu_u << 4);
}

/* Function for Chart: '<S4>/Chart' */
static void rzs10thnew2_enter_atomic_AS_Off(void)
{
  rzs10thnew2021b_B.r2d_flag_l = 0.0;
  rzs10thnew2021b_B.steering_flag_i = 0.0;
  rzs10thnew2021b_B.brake_flag_b = 0.0;
  rzs10thnew2021b_B.as_led_yellow = 0.0;
  rzs10thnew2021b_B.as_led_blue = 0.0;
  rzs10thnew2021b_B.as_off_flag_d = 1.0;
  rzs10thnew2021b_B.as_ready_flag_p = 0.0;
  rzs10thnew2021b_B.as_driving_flag_b = 0.0;
  rzs10thnew2021b_B.as_finished_flag_g = 0.0;
  rzs10thnew2021b_B.as_emergency_flag_e = 0.0;
  rzs10thnew2021b_B.manual_driving_flag_k = 0.0;
}

/* Function for Chart: '<S4>/Chart' */
static void rzs10_enter_atomic_AS_Emergency(void)
{
  rzs10thnew2021b_B.r2d_flag_l = 0.0;
  rzs10thnew2021b_B.steering_flag_i = 0.0;
  rzs10thnew2021b_B.brake_flag_b = 0.0;
  rzs10thnew2021b_B.as_led_yellow = 0.0;
  rzs10thnew2021b_B.as_led_blue = 2.0;
  rzs10thnew2021b_B.as_off_flag_d = 0.0;
  rzs10thnew2021b_B.as_ready_flag_p = 0.0;
  rzs10thnew2021b_B.as_driving_flag_b = 0.0;
  rzs10thnew2021b_B.as_finished_flag_g = 0.0;
  rzs10thnew2021b_B.as_emergency_flag_e = 1.0;
  rzs10thnew2021b_B.manual_driving_flag_k = 0.0;
}

/* Function for Chart: '<S4>/Chart' */
static void rzs10thnew2021b_AS_Driving(const boolean_T *LogicalOperator)
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
  if (rzs10thnew2021b_DW.ebs_working) {
    guard2 = true;
  } else if ((*LogicalOperator) && rzs10thnew2021b_DW.task_finish) {
    rzs10thnew2021b_B.as_ebs_trig = 1.0;
    guard3 = true;
  } else if (rzs10thnew2021b_B.ami_inspection_signal == 1.0) {
    if (rzs10thnew2021b_DW.ebs_working) {
      guard2 = true;
    } else if (rzs10thnew2021b_DW.temporalCounter_i1 >= 2700U) {
      rzs10thnew2021b_B.as_ebs_trig = 1.0;
      guard3 = true;
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard3) {
    rzs10thnew2021b_DW.is_AS_Driving = rzs10thnew20_IN_NO_ACTIVE_CHILD;
    rzs10thnew2021b_DW.is_c1_rzs10thnew2021b = rzs10thnew2021b_IN_AS_Finished;
    rzs10thnew2021b_B.r2d_flag_l = 0.0;
    rzs10thnew2021b_B.steering_flag_i = 0.0;
    rzs10thnew2021b_B.brake_flag_b = 0.0;
    rzs10thnew2021b_B.as_led_yellow = 0.0;
    rzs10thnew2021b_B.as_led_blue = 1.0;
    rzs10thnew2021b_B.as_off_flag_d = 0.0;
    rzs10thnew2021b_B.as_ready_flag_p = 0.0;
    rzs10thnew2021b_B.as_driving_flag_b = 0.0;
    rzs10thnew2021b_B.as_finished_flag_g = 1.0;
    rzs10thnew2021b_B.as_emergency_flag_e = 0.0;
    rzs10thnew2021b_B.manual_driving_flag_k = 0.0;
  }

  if (guard2) {
    rzs10thnew2021b_DW.is_AS_Driving = rzs10thnew20_IN_NO_ACTIVE_CHILD;
    rzs10thnew2021b_DW.is_c1_rzs10thnew2021b = rzs10thnew2021b_IN_AS_Emergency;
    rzs10_enter_atomic_AS_Emergency();
  }

  if (guard1) {
    if (rzs10thnew2021b_DW.is_AS_Driving == rzs10thnew2021b_IN_R2D) {
      if (rzs10thnew2021b_DW.steer_zero) {
        rzs10thnew2021b_B.steer_return = F;
        rzs10thnew2021b_B.r2d_warning = F;
        rzs10thnew2021b_DW.is_AS_Driving = rzs10thnew2021b_IN_go;
        rzs10thnew2021b_B.r2d_flag_l = 0.0;
        rzs10thnew2021b_B.steering_flag_i = 1.0;
        rzs10thnew2021b_B.brake_flag_b = 1.0;
        rzs10thnew2021b_B.as_led_yellow = 2.0;
        rzs10thnew2021b_B.as_led_blue = 0.0;
        rzs10thnew2021b_B.as_off_flag_d = 0.0;
        rzs10thnew2021b_B.as_ready_flag_p = 0.0;
        rzs10thnew2021b_B.as_driving_flag_b = 1.0;
        rzs10thnew2021b_B.as_finished_flag_g = 0.0;
        rzs10thnew2021b_B.as_emergency_flag_e = 0.0;
        rzs10thnew2021b_B.manual_driving_flag_k = 0.0;
      }
    } else {
      /* case IN_go: */
      rzs10thnew2021b_B.r2d_flag_l = 0.0;
      rzs10thnew2021b_B.steering_flag_i = 1.0;
      rzs10thnew2021b_B.brake_flag_b = 1.0;
      rzs10thnew2021b_B.as_led_yellow = 2.0;
      rzs10thnew2021b_B.as_led_blue = 0.0;
      rzs10thnew2021b_B.as_off_flag_d = 0.0;
      rzs10thnew2021b_B.as_ready_flag_p = 0.0;
      rzs10thnew2021b_B.as_driving_flag_b = 1.0;
      rzs10thnew2021b_B.as_finished_flag_g = 0.0;
      rzs10thnew2021b_B.as_emergency_flag_e = 0.0;
      rzs10thnew2021b_B.manual_driving_flag_k = 0.0;
    }
  }

  /* End of DataStoreRead: '<Root>/Data Store Read7' */
}

/* Model step function for TID0 */
void rzs10thnew2021b_step0(void)       /* Sample time: [0.001s, 0.0s] */
{
  /* (no output/update code required) */
}

/* Model step function for TID1 */
void rzs10thnew2021b_step1(void)       /* Sample time: [0.01s, 0.0s] */
{
  int32_T airprs_sensor1;
  int32_T apps1;
  int32_T apps2;
  int32_T rtb_mode;
  uint32_T elapsedTicks_h;
  uint16_T rtb_Add1_p;
  uint16_T rtb_Add2_i;
  uint16_T rtb_ebs_drivercheck;
  uint16_T rtb_y_ap;
  uint16_T rtb_y_cg;
  uint16_T rtb_y_ci;
  uint16_T rtb_y_gs;
  uint16_T rtb_y_ir;
  uint16_T rtb_y_jo;
  uint16_T rtb_y_ju;
  uint16_T rtb_y_k0;
  uint16_T rtb_y_l;
  uint16_T rtb_y_my;
  uint8_T res_heartbeat_prev;
  uint8_T rtb_BitwiseAND_cd;
  uint8_T rtb_MCU1_Rx_Command3byte3;
  uint8_T rtb_y_ao;
  uint8_T rtb_y_ar;
  uint8_T rtb_y_dn;
  uint8_T rtb_y_hwh;
  uint8_T rtb_y_ip;
  uint8_T rtb_y_nr;
  boolean_T LogicalOperator;
  boolean_T Switch_e;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T rtb_xor_consequence;

  /* S-Function (sfix_bitop): '<S15>/Bitwise AND' incorporates:
   *  Inport: '<Root>/Input'
   */
  rtb_ebs_drivercheck = (uint16_T)(digital_input.io_in & 1);

  /* S-Function (fcgen): '<Root>/10ms' incorporates:
   *  SubSystem: '<Root>/Sensor_Signal'
   */
  /* DataTypeConversion: '<S13>/Data Type Conversion12' incorporates:
   *  Inport: '<Root>/Input'
   *  Lookup_n-D: '<S13>/1-D Lookup Table6'
   */
  airprs_sensor1 = look1_iu16lu16n16_linlcase(digital_input.adc_in[3],
    rzs10thnew2021b_ConstP.pooled33, rzs10thnew2021b_ConstP.pooled32, 1U);

  /* Product: '<S254>/Product1' incorporates:
   *  Constant: '<S254>/Constant'
   *  DataTypeConversion: '<S13>/Data Type Conversion6'
   *  Gain: '<S254>/Gain'
   *  Gain: '<S254>/Gain1'
   *  Inport: '<Root>/Input'
   *  Product: '<S254>/Divide'
   */
  rzs10thnew2021b_B.Product1 = 36.0 * (real_T)digital_input.adc_in[5] * 3.1415 /
    180.0 * rzs10thnew2021b_ConstB.Product;

  /* Product: '<S254>/Product2' incorporates:
   *  Constant: '<S254>/Constant3'
   *  DataTypeConversion: '<S13>/Data Type Conversion7'
   *  Gain: '<S254>/Gain2'
   *  Gain: '<S254>/Gain3'
   *  Inport: '<Root>/Input'
   *  Product: '<S254>/Divide1'
   */
  rzs10thnew2021b_B.Product2 = 36.0 * (real_T)digital_input.adc_in[6] * 3.1415 /
    180.0 * rzs10thnew2021b_ConstB.Product;

  /* DataTypeConversion: '<S13>/Data Type Conversion' incorporates:
   *  Inport: '<Root>/Input'
   *  Lookup_n-D: '<S13>/1-D Lookup Table'
   */
  rzs10thnew2021b_B.DataTypeConversion1 = look1_iu16lu16n16_linlcase
    (digital_input.adc_in[0], rzs10thnew2021b_ConstP.pooled33,
     rzs10thnew2021b_ConstP.pooled32, 1U);

  /* Saturate: '<S13>/Saturation' */
  if (rzs10thnew2021b_B.DataTypeConversion1 > 1.0) {
    /* Saturate: '<S13>/Saturation' */
    apps1 = 1;
  } else {
    /* Saturate: '<S13>/Saturation' */
    apps1 = (int32_T)rzs10thnew2021b_B.DataTypeConversion1;
  }

  /* End of Saturate: '<S13>/Saturation' */

  /* DataTypeConversion: '<S13>/Data Type Conversion2' incorporates:
   *  Inport: '<Root>/Input'
   *  Lookup_n-D: '<S13>/1-D Lookup Table9'
   */
  rzs10thnew2021b_B.DataTypeConversion1 = look1_iu16lu16n16_linlcase
    (digital_input.adc_in[1], rzs10thnew2021b_ConstP.pooled33,
     rzs10thnew2021b_ConstP.pooled32, 1U);

  /* Saturate: '<S13>/Saturation1' */
  if (rzs10thnew2021b_B.DataTypeConversion1 > 1.0) {
    /* Saturate: '<S13>/Saturation1' */
    apps2 = 1;
  } else {
    /* Saturate: '<S13>/Saturation1' */
    apps2 = (int32_T)rzs10thnew2021b_B.DataTypeConversion1;
  }

  /* End of Saturate: '<S13>/Saturation1' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */

  /* S-Function (fcgen): '<Root>/10ms10' incorporates:
   *  SubSystem: '<Root>/Res'
   */
  /* S-Function (sfix_bitop): '<S244>/Bitwise AND' incorporates:
   *  Inport: '<Root>/res_msg'
   */
  rtb_BitwiseAND_cd = (uint8_T)(res_msg[0] & 1);

  /* SignalConversion generated from: '<S12>/res_error' incorporates:
   *  DataTypeConversion: '<S244>/Data Type Conversion7'
   */
  res_error = (rtb_BitwiseAND_cd != 0);

  /* Outputs for Atomic SubSystem: '<S244>/Bit Shift' */
  /* S-Function (sfix_bitop): '<S244>/Bitwise AND1' incorporates:
   *  Inport: '<Root>/res_msg'
   */
  rzs10thnew2021b_BitShift((uint8_T)(res_msg[0] & 2), &rtb_y_ao);

  /* End of Outputs for SubSystem: '<S244>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S244>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S244>/Bitwise AND2' incorporates:
   *  Inport: '<Root>/res_msg'
   */
  rzs10thnew2021b_BitShift1((uint8_T)(res_msg[0] & 4), &rtb_y_ao);

  /* End of Outputs for SubSystem: '<S244>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S244>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S244>/Bitwise AND3' incorporates:
   *  Inport: '<Root>/res_msg'
   */
  rzs10thnew2021b_BitShift2((uint8_T)(res_msg[0] & 16), &rtb_y_hwh);

  /* End of Outputs for SubSystem: '<S244>/Bit Shift2' */

  /* Logic: '<S244>/Logical Operator' incorporates:
   *  Inport: '<Root>/res_msg'
   */
  rtb_xor_consequence = (res_msg[0] != 0) ^ (res_msg[1] != 0);

  /* Chart: '<S248>/heaartbeat_chart' incorporates:
   *  Inport: '<Root>/res_msg'
   *  S-Function (sfix_bitop): '<S244>/Bitwise AND4'
   */
  res_heartbeat_prev = rzs10thnew2021b_DW.res_heartbeat_start;
  rzs10thnew2021b_DW.res_heartbeat_start = res_msg[1];
  if (rzs10thnew2021b_DW.is_active_c10_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c10_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c10_rzs10thnew2021b = rzs10thnew2021b_IN_begin_b;
  } else {
    switch (rzs10thnew2021b_DW.is_c10_rzs10thnew2021b) {
     case rzs10thnew2021b_IN_begin_b:
      if (res_heartbeat_prev != rzs10thnew2021b_DW.res_heartbeat_start) {
        rzs10thnew2021b_DW.is_c10_rzs10thnew2021b = rzs10thnew2021b_IN_compare;
        rzs10thnew2021b_B.res_hbcheck = 1.0;
      }
      break;

     case rzs10thnew2021b_IN_compare:
      if (res_heartbeat_prev == rzs10thnew2021b_DW.res_heartbeat_start) {
        rzs10thnew2021b_DW.is_c10_rzs10thnew2021b = rzs10thnew2021b_IN_same;
        rzs10thnew2021b_DW.hbcnt++;
      } else {
        rzs10thnew2021b_B.res_hbcheck = 1.0;
      }
      break;

     case rzs10thnew2021b_IN_judge:
      if (res_heartbeat_prev != rzs10thnew2021b_DW.res_heartbeat_start) {
        rzs10thnew2021b_DW.is_c10_rzs10thnew2021b = rzs10thnew2021b_IN_compare;
        rzs10thnew2021b_B.res_hbcheck = 1.0;
      } else {
        rzs10thnew2021b_B.res_hbcheck = 0.0;
      }
      break;

     default:
      /* case IN_same: */
      if (rzs10thnew2021b_DW.hbcnt > 10.0) {
        rzs10thnew2021b_DW.is_c10_rzs10thnew2021b = rzs10thnew2021b_IN_judge;
        rzs10thnew2021b_B.res_hbcheck = 0.0;
      } else if (res_heartbeat_prev != rzs10thnew2021b_DW.res_heartbeat_start) {
        rzs10thnew2021b_DW.hbcnt = 0.0;
        rzs10thnew2021b_DW.is_c10_rzs10thnew2021b = rzs10thnew2021b_IN_compare;
        rzs10thnew2021b_B.res_hbcheck = 1.0;
      } else {
        rzs10thnew2021b_DW.hbcnt++;
      }
      break;
    }
  }

  /* End of Chart: '<S248>/heaartbeat_chart' */

  /* Chart: '<S248>/xor_Check' incorporates:
   *  Inport: '<Root>/res_msg'
   *  S-Function (sfix_bitop): '<S244>/Bitwise AND5'
   */
  if (rzs10thnew2021b_DW.is_active_c19_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c19_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c19_rzs10thnew2021b = rzs10thnew2021b_IN_Init;
    rzs10thnew2021b_DW.err_cnt = 0.0;
  } else {
    switch (rzs10thnew2021b_DW.is_c19_rzs10thnew2021b) {
     case rzs10thnew2021b_IN_Init:
      if (res_msg[2] == rtb_xor_consequence) {
        rzs10thnew2021b_DW.is_c19_rzs10thnew2021b = rzs10thnew2021b_IN_compare;
        rzs10thnew2021b_B.xorcheck = 1.0;
      }
      break;

     case rzs10thnew2021b_IN_compare:
      rzs10thnew2021b_B.xorcheck = 1.0;
      if (res_msg[2] != rtb_xor_consequence) {
        rzs10thnew2021b_DW.is_c19_rzs10thnew2021b = rzs10thnew2021b_IN_different;
        rzs10thnew2021b_DW.err_cnt++;
      }
      break;

     case rzs10thnew2021b_IN_different:
      if (rzs10thnew2021b_DW.err_cnt >= 10.0) {
        rzs10thnew2021b_DW.is_c19_rzs10thnew2021b = rzs10thnew2021b_IN_judge_e;
        rzs10thnew2021b_B.xorcheck = 0.0;
      } else if (res_msg[2] == rtb_xor_consequence) {
        rzs10thnew2021b_DW.err_cnt = 0.0;
        rzs10thnew2021b_DW.is_c19_rzs10thnew2021b = rzs10thnew2021b_IN_compare;
        rzs10thnew2021b_B.xorcheck = 1.0;
      }
      break;

     default:
      /* case IN_judge: */
      rzs10thnew2021b_B.xorcheck = 0.0;
      if (res_msg[2] == rtb_xor_consequence) {
        rzs10thnew2021b_DW.err_cnt = 0.0;
        rzs10thnew2021b_DW.is_c19_rzs10thnew2021b = rzs10thnew2021b_IN_compare;
        rzs10thnew2021b_B.xorcheck = 1.0;
      }
      break;
    }
  }

  /* End of Chart: '<S248>/xor_Check' */

  /* Logic: '<S248>/Logical Operator' incorporates:
   *  DataTypeConversion: '<S244>/Data Type Conversion2'
   */
  rtb_xor_consequence = ((rtb_y_ao != 0) && (rzs10thnew2021b_B.res_hbcheck !=
    0.0) && (rzs10thnew2021b_B.xorcheck != 0.0));

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms10' */

  /* S-Function (fcgen): '<Root>/10ms11' incorporates:
   *  SubSystem: '<Root>/IPC'
   */
  /* Outputs for Atomic SubSystem: '<S172>/Bit Shift' */
  /* S-Function (sfix_bitop): '<S172>/Bitwise AND' incorporates:
   *  DataTypeConversion: '<S172>/Data Type Conversion1'
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  rzs10thnew2021b_BitShift_a((uint16_T)(canb_ipctsmsg1[1] & 3), &rtb_y_jo);

  /* End of Outputs for SubSystem: '<S172>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S172>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S172>/Bitwise AND1' incorporates:
   *  DataTypeConversion: '<S172>/Data Type Conversion1'
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  rzs10thnew2021b_BitShift1_f((uint16_T)(canb_ipctsmsg1[1] & 252), &rtb_y_ju);

  /* End of Outputs for SubSystem: '<S172>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S172>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S172>/Bitwise AND2' incorporates:
   *  DataTypeConversion: '<S172>/Data Type Conversion2'
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  rzs10thnew2021b_BitShift2_i((uint16_T)(canb_ipctsmsg1[2] & 15), &rtb_y_l);

  /* End of Outputs for SubSystem: '<S172>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S172>/Bit Shift3' */
  /* S-Function (sfix_bitop): '<S172>/Bitwise AND3' incorporates:
   *  DataTypeConversion: '<S172>/Data Type Conversion2'
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  rzs10thnew2021b_BitShift3((uint16_T)(canb_ipctsmsg1[2] & 240), &rtb_y_k0);

  /* End of Outputs for SubSystem: '<S172>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S172>/Bit Shift4' */
  /* S-Function (sfix_bitop): '<S172>/Bitwise AND4' incorporates:
   *  DataTypeConversion: '<S172>/Data Type Conversion3'
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  rzs10thnew2021b_BitShift4((uint16_T)(canb_ipctsmsg1[3] & 63), &rtb_y_ir);

  /* End of Outputs for SubSystem: '<S172>/Bit Shift4' */

  /* Outputs for Atomic SubSystem: '<S172>/Bit Shift8' */
  /* DataTypeConversion: '<S172>/Data Type Conversion7' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg1'
   */
  rzs10thnew2021b_BitShift8((real_T)canb_ipctsmsg1[7],
    &rzs10thnew2021b_B.DataTypeConversion1);

  /* End of Outputs for SubSystem: '<S172>/Bit Shift8' */

  /* DataTypeConversion: '<S172>/Data Type Conversion8' incorporates:
   *  DataTypeConversion: '<S172>/Data Type Conversion4'
   *  Inport: '<Root>/canb_ipctsmsg1'
   *  Sum: '<S172>/Add'
   */
  rzs10thnew2021b_B.y = (uint16_T)((uint32_T)canb_ipctsmsg1[0] + rtb_y_jo);

  /* Gain: '<S172>/Gain' */
  rzs10thnew2021b_B.ipc_esp_flprs = rzs10thnew2021b_B.y * 0.01;

  /* Gain: '<S172>/Gain1' incorporates:
   *  DataTypeConversion: '<S172>/Data Type Conversion9'
   *  Sum: '<S172>/Add1'
   */
  rzs10thnew2021b_B.ipc_eps_frprs = (real_T)(uint16_T)((uint32_T)rtb_y_ju +
    rtb_y_l) * 0.01;

  /* Gain: '<S172>/Gain2' incorporates:
   *  DataTypeConversion: '<S172>/Data Type Conversion10'
   *  Sum: '<S172>/Add2'
   */
  rzs10thnew2021b_B.ipc_esp_rlprs = (real_T)(uint16_T)((uint32_T)rtb_y_k0 +
    rtb_y_ir) * 0.01;

  /* Outputs for Atomic SubSystem: '<S172>/Bit Shift5' */
  /* Outputs for Atomic SubSystem: '<S172>/Bit Shift6' */
  /* Gain: '<S172>/Gain3' incorporates:
   *  DataTypeConversion: '<S172>/Data Type Conversion11'
   *  DataTypeConversion: '<S172>/Data Type Conversion3'
   *  DataTypeConversion: '<S172>/Data Type Conversion5'
   *  Inport: '<Root>/canb_ipctsmsg1'
   *  MATLAB Function: '<S179>/bit_shift'
   *  MATLAB Function: '<S180>/bit_shift'
   *  S-Function (sfix_bitop): '<S172>/Bitwise AND5'
   *  Sum: '<S172>/Add3'
   */
  rzs10thnew2021b_B.ipc_esp_rrprs = (real_T)((int32_T)((uint32_T)
    (canb_ipctsmsg1[3] & 192) >> 6) + (canb_ipctsmsg1[4] << 2)) * 0.01;

  /* End of Outputs for SubSystem: '<S172>/Bit Shift6' */
  /* End of Outputs for SubSystem: '<S172>/Bit Shift5' */

  /* Outputs for Atomic SubSystem: '<S173>/Bit Shift' */
  /* DataTypeConversion: '<S173>/Data Type Conversion2' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S9>/canb_ipctsmsg2'
   */
  rzs10thnew2021b_BitShift8((real_T)canb_ipctsmsg2[0], &rzs10thnew2021b_B.y);

  /* End of Outputs for SubSystem: '<S173>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S173>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S173>/Bitwise AND' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S9>/canb_ipctsmsg2'
   */
  rzs10thnew2021b_BitShift1_k((uint8_T)(canb_ipctsmsg2[3] & 128), &rtb_y_ao);

  /* End of Outputs for SubSystem: '<S173>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S173>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S173>/Bitwise AND1' incorporates:
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S9>/canb_ipctsmsg2'
   */
  rzs10thnew2021b_BitShift2_g((uint8_T)(canb_ipctsmsg2[3] & 64),
    &res_heartbeat_prev);

  /* End of Outputs for SubSystem: '<S173>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S169>/Bit Shift' */
  /* S-Function (fcgen): '<Root>/10ms10' incorporates:
   *  SubSystem: '<Root>/Res'
   */
  /* SignalConversion generated from: '<S9>/canb_ipcrxmsg' incorporates:
   *  DataTypeConversion: '<S244>/Data Type Conversion3'
   *  DataTypeConversion: '<S244>/Data Type Conversion7'
   *  MATLAB Function: '<S170>/bit_shift'
   *  Sum: '<S169>/Add'
   */
  canb_ipcrxmsg[0] = (uint8_T)((uint32_T)((rtb_BitwiseAND_cd != 0) << 1) +
    (rtb_y_hwh != 0));

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms10' */
  /* End of Outputs for SubSystem: '<S169>/Bit Shift' */

  /* DataTypeConversion: '<S169>/Data Type Conversion3' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read17'
   */
  rzs10thnew2021b_B.d = floor(rzs10thnew2021b_DW.ipc_astask);
  if (rtIsNaN(rzs10thnew2021b_B.d) || rtIsInf(rzs10thnew2021b_B.d)) {
    rzs10thnew2021b_B.d = 0.0;
  } else {
    rzs10thnew2021b_B.d = fmod(rzs10thnew2021b_B.d, 256.0);
  }

  /* SignalConversion generated from: '<S9>/canb_ipcrxmsg' incorporates:
   *  DataTypeConversion: '<S169>/Data Type Conversion3'
   */
  canb_ipcrxmsg[1] = (uint8_T)(rzs10thnew2021b_B.d < 0.0 ? (int32_T)(uint8_T)
    -(int8_T)(uint8_T)-rzs10thnew2021b_B.d : (int32_T)(uint8_T)
    rzs10thnew2021b_B.d);
  canb_ipcrxmsg[2] = ((uint8_T)0U);
  canb_ipcrxmsg[3] = ((uint8_T)0U);
  canb_ipcrxmsg[4] = ((uint8_T)0U);
  canb_ipcrxmsg[5] = ((uint8_T)0U);
  canb_ipcrxmsg[6] = ((uint8_T)0U);
  canb_ipcrxmsg[7] = ((uint8_T)0U);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */

  /* S-Function (fcgen): '<Root>/10ms5' incorporates:
   *  SubSystem: '<Root>/AS_AMI'
   */
  /* Chart: '<S3>/Chart' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read14'
   *  DataStoreRead: '<Root>/Data Store Read16'
   */
  if (rzs10thnew2021b_DW.is_active_c7_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c7_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c7_rzs10thnew2021b = rzs10thnew2021b_IN_Init_k;
    rzs10thnew2021b_B.ipc_astask = 0.0;
  } else {
    switch (rzs10thnew2021b_DW.is_c7_rzs10thnew2021b) {
     case rzs10thnew2021b_IN_Acceleration:
      rzs10thnew2021b_B.ipc_astask = 1.0;
      if (rzs10thnew2021b_DW.task_finish) {
        rzs10thnew2021b_DW.is_c7_rzs10thnew2021b = rzs10thnew2021b_IN_Init_k;
        rzs10thnew2021b_B.ipc_astask = 0.0;
      }
      break;

     case rzs10thnew2021b_IN_EBS_Test:
      rzs10thnew2021b_B.ipc_astask = 4.0;
      if (rzs10thnew2021b_DW.task_finish) {
        rzs10thnew2021b_DW.is_c7_rzs10thnew2021b = rzs10thnew2021b_IN_Init_k;
        rzs10thnew2021b_B.ipc_astask = 0.0;
      }
      break;

     case rzs10thnew2021b_IN_Init_k:
      rzs10thnew2021b_B.ipc_astask = 0.0;
      switch (rzs10thnew2021b_DW.ami_astask) {
       case 0:
        rzs10thnew2021b_DW.is_c7_rzs10thnew2021b =
          rzs10thnew2021b_IN_Acceleration;
        rzs10thnew2021b_B.ipc_astask = 1.0;
        break;

       case 2:
        rzs10thnew2021b_DW.is_c7_rzs10thnew2021b =
          rzs10thnew2021b_IN_Trackdriver;
        rzs10thnew2021b_B.ipc_astask = 2.0;
        break;

       case 1:
        rzs10thnew2021b_DW.is_c7_rzs10thnew2021b = rzs10thnew2021b_IN_Skidpad;
        rzs10thnew2021b_B.ipc_astask = 3.0;
        break;

       case 3:
        rzs10thnew2021b_DW.is_c7_rzs10thnew2021b = rzs10thnew2021b_IN_EBS_Test;
        rzs10thnew2021b_B.ipc_astask = 4.0;
        break;

       case 4:
        rzs10thnew2021b_DW.is_c7_rzs10thnew2021b = rzs10thnew2021b_IN_inspection;
        rzs10thnew2021b_B.ami_inspection_signal = 1.0;
        break;

       case 5:
        rzs10thnew2021b_DW.is_c7_rzs10thnew2021b =
          rzs10thnew2021_IN_manualdriving;
        rzs10thnew2021b_B.ipc_astask = 5.0;
        break;
      }
      break;

     case rzs10thnew2021b_IN_Skidpad:
      rzs10thnew2021b_B.ipc_astask = 3.0;
      if (rzs10thnew2021b_DW.task_finish) {
        rzs10thnew2021b_DW.is_c7_rzs10thnew2021b = rzs10thnew2021b_IN_Init_k;
        rzs10thnew2021b_B.ipc_astask = 0.0;
      }
      break;

     case rzs10thnew2021b_IN_Trackdriver:
      rzs10thnew2021b_B.ipc_astask = 2.0;
      if (rzs10thnew2021b_DW.task_finish) {
        rzs10thnew2021b_DW.is_c7_rzs10thnew2021b = rzs10thnew2021b_IN_Init_k;
        rzs10thnew2021b_B.ipc_astask = 0.0;
      }
      break;

     case rzs10thnew2021b_IN_inspection:
      rzs10thnew2021b_B.ami_inspection_signal = 1.0;
      if (rzs10thnew2021b_DW.task_finish) {
        rzs10thnew2021b_DW.is_c7_rzs10thnew2021b = rzs10thnew2021b_IN_Init_k;
        rzs10thnew2021b_B.ipc_astask = 0.0;
      }
      break;

     default:
      /* case IN_manualdriving: */
      rzs10thnew2021b_B.ipc_astask = 5.0;
      if (rzs10thnew2021b_DW.task_finish) {
        rzs10thnew2021b_DW.is_c7_rzs10thnew2021b = rzs10thnew2021b_IN_Init_k;
        rzs10thnew2021b_B.ipc_astask = 0.0;
      }
      break;
    }
  }

  /* End of Chart: '<S3>/Chart' */

  /* Switch: '<S3>/Switch' */
  Switch_e = (rzs10thnew2021b_B.ipc_astask > 0.0);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms5' */

  /* S-Function (fcgen): '<Root>/10ms6' incorporates:
   *  SubSystem: '<Root>/AS_Stateflow'
   */
  /* S-Function (fcgen): '<Root>/10ms' incorporates:
   *  SubSystem: '<Root>/Sensor_Signal'
   */
  /* DeadZone: '<S38>/Dead Zone' incorporates:
   *  DataTypeConversion: '<S13>/Data Type Conversion8'
   */
  if (rzs10thnew2021b_B.Product1 > 0.5) {
    rzs10thnew2021b_B.Product1 -= 0.5;
  } else if (rzs10thnew2021b_B.Product1 >= -0.5) {
    rzs10thnew2021b_B.Product1 = 0.0;
  } else {
    rzs10thnew2021b_B.Product1 -= -0.5;
  }

  /* End of DeadZone: '<S38>/Dead Zone' */

  /* DeadZone: '<S38>/Dead Zone1' incorporates:
   *  DataTypeConversion: '<S13>/Data Type Conversion9'
   */
  if (rzs10thnew2021b_B.Product2 > 0.5) {
    rzs10thnew2021b_B.Product2 -= 0.5;
  } else if (rzs10thnew2021b_B.Product2 >= -0.5) {
    rzs10thnew2021b_B.Product2 = 0.0;
  } else {
    rzs10thnew2021b_B.Product2 -= -0.5;
  }

  /* End of DeadZone: '<S38>/Dead Zone1' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */

  /* Logic: '<S38>/Logical Operator' incorporates:
   *  Constant: '<S40>/Constant'
   *  Constant: '<S41>/Constant'
   *  RelationalOperator: '<S40>/Compare'
   *  RelationalOperator: '<S41>/Compare'
   */
  LogicalOperator = ((rzs10thnew2021b_B.Product1 == 0.0) &&
                     (rzs10thnew2021b_B.Product2 == 0.0));

  /* Chart: '<S4>/Chart' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read4'
   *  DataStoreRead: '<Root>/Data Store Read6'
   *  DataStoreRead: '<Root>/Data Store Read8'
   *  DataTypeConversion: '<S244>/Data Type Conversion7'
   *  Switch: '<S3>/Switch1'
   */
  elapsedTicks_h = rzs10thnew2021b_M->Timing.clockTick1 -
    rzs10thnew2021b_DW.previousTicks_i;
  rzs10thnew2021b_DW.previousTicks_i = rzs10thnew2021b_M->Timing.clockTick1;
  if (rzs10thnew2021b_DW.temporalCounter_i1 + elapsedTicks_h <= 4095U) {
    rzs10thnew2021b_DW.temporalCounter_i1 = (uint16_T)
      (rzs10thnew2021b_DW.temporalCounter_i1 + elapsedTicks_h);
  } else {
    rzs10thnew2021b_DW.temporalCounter_i1 = 4095U;
  }

  if (rzs10thnew2021b_DW.is_active_c1_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c1_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c1_rzs10thnew2021b = rzs10thnew2021b_IN_AS_Off;
    rzs10thnew2_enter_atomic_AS_Off();
  } else {
    guard1 = false;
    guard2 = false;
    switch (rzs10thnew2021b_DW.is_c1_rzs10thnew2021b) {
     case rzs10thnew2021b_IN_AS_Driving:
      rzs10thnew2021b_AS_Driving(&LogicalOperator);
      break;

     case rzs10thnew2021b_IN_AS_Emergency:
      if ((!rzs10thnew2021b_DW.ebs_warning) && (!rzs10thnew2021b_DW.brake_on)) {
        rzs10thnew2021b_DW.is_c1_rzs10thnew2021b = rzs10thnew2021b_IN_AS_Off;
        rzs10thnew2_enter_atomic_AS_Off();
      } else {
        rzs10thnew2021b_B.r2d_flag_l = 0.0;
        rzs10thnew2021b_B.steering_flag_i = 0.0;
        rzs10thnew2021b_B.brake_flag_b = 0.0;
        rzs10thnew2021b_B.as_led_yellow = 0.0;
        rzs10thnew2021b_B.as_led_blue = 2.0;
        rzs10thnew2021b_B.as_off_flag_d = 0.0;
        rzs10thnew2021b_B.as_ready_flag_p = 0.0;
        rzs10thnew2021b_B.as_driving_flag_b = 0.0;
        rzs10thnew2021b_B.as_finished_flag_g = 0.0;
        rzs10thnew2021b_B.as_emergency_flag_e = 1.0;
        rzs10thnew2021b_B.manual_driving_flag_k = 0.0;
      }
      break;

     case rzs10thnew2021b_IN_AS_Finished:
      /* S-Function (fcgen): '<Root>/10ms10' incorporates:
       *  SubSystem: '<Root>/Res'
       */
      if (rtb_BitwiseAND_cd != 0) {
        rzs10thnew2021b_DW.is_c1_rzs10thnew2021b =
          rzs10thnew2021b_IN_AS_Emergency;
        rzs10_enter_atomic_AS_Emergency();
      } else if (!rzs10thnew2021b_DW.brake_on) {
        rzs10thnew2021b_DW.is_c1_rzs10thnew2021b = rzs10thnew2021b_IN_AS_Off;
        rzs10thnew2_enter_atomic_AS_Off();
      } else {
        rzs10thnew2021b_B.r2d_flag_l = 0.0;
        rzs10thnew2021b_B.steering_flag_i = 0.0;
        rzs10thnew2021b_B.brake_flag_b = 0.0;
        rzs10thnew2021b_B.as_led_yellow = 0.0;
        rzs10thnew2021b_B.as_led_blue = 1.0;
        rzs10thnew2021b_B.as_off_flag_d = 0.0;
        rzs10thnew2021b_B.as_ready_flag_p = 0.0;
        rzs10thnew2021b_B.as_driving_flag_b = 0.0;
        rzs10thnew2021b_B.as_finished_flag_g = 1.0;
        rzs10thnew2021b_B.as_emergency_flag_e = 0.0;
        rzs10thnew2021b_B.manual_driving_flag_k = 0.0;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms10' */
      break;

     case rzs10thnew2021b_IN_AS_Off:
      /* S-Function (fcgen): '<Root>/10ms5' incorporates:
       *  SubSystem: '<Root>/AS_AMI'
       */
      if ((rzs10thnew2021b_B.ipc_astask >= 5.0) &&
          (!rzs10thnew2021b_DW.ebs_check) && (rzs10thnew2021b_DW.ts == 1.0)) {
        rzs10thnew2021b_DW.is_c1_rzs10thnew2021b =
          rzs10thnew2_IN_Manual_Driving_j;
        rzs10thnew2021b_B.r2d_flag_l = 0.0;
        rzs10thnew2021b_B.steering_flag_i = 0.0;
        rzs10thnew2021b_B.brake_flag_b = 0.0;
        rzs10thnew2021b_B.as_led_yellow = 0.0;
        rzs10thnew2021b_B.as_led_blue = 0.0;
        rzs10thnew2021b_B.as_off_flag_d = 0.0;
        rzs10thnew2021b_B.as_ready_flag_p = 0.0;
        rzs10thnew2021b_B.as_driving_flag_b = 0.0;
        rzs10thnew2021b_B.as_finished_flag_g = 0.0;
        rzs10thnew2021b_B.as_emergency_flag_e = 0.0;
        rzs10thnew2021b_B.manual_driving_flag_k = 1.0;
      } else {
        rzs10thnew2021b_B.r2d_flag_l = 0.0;
        rzs10thnew2021b_B.steering_flag_i = 0.0;
        rzs10thnew2021b_B.brake_flag_b = 0.0;
        rzs10thnew2021b_B.as_led_yellow = 0.0;
        rzs10thnew2021b_B.as_led_blue = 0.0;
        rzs10thnew2021b_B.as_off_flag_d = 1.0;
        rzs10thnew2021b_B.as_ready_flag_p = 0.0;
        rzs10thnew2021b_B.as_driving_flag_b = 0.0;
        rzs10thnew2021b_B.as_finished_flag_g = 0.0;
        rzs10thnew2021b_B.as_emergency_flag_e = 0.0;
        rzs10thnew2021b_B.manual_driving_flag_k = 0.0;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms5' */
      break;

     case rzs10thnew2021b_IN_AS_Ready:
      if (rzs10thnew2021b_DW.ebs_working) {
        guard2 = true;
      } else if (rzs10thnew2021b_DW.temporalCounter_i1 >= 500U) {
        if (rzs10thnew2021b_DW.ebs_working) {
          guard2 = true;
        } else if (rtb_y_hwh != 0) {
          rzs10thnew2021b_B.r2d_warning = T;
          rzs10thnew2021b_B.steer_return = T;
          rzs10thnew2021b_DW.is_c1_rzs10thnew2021b =
            rzs10thnew2021b_IN_AS_Driving;
          rzs10thnew2021b_DW.temporalCounter_i1 = 0U;
          rzs10thnew2021b_DW.is_AS_Driving = rzs10thnew2021b_IN_R2D;
          rzs10thnew2021b_B.r2d_flag_l = 1.0;
          rzs10thnew2021b_B.as_ready_flag_p = 0.0;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
      break;

     default:
      /* case IN_Manual_Driving: */
      if (rzs10thnew2021b_DW.ts == 0.0) {
        rzs10thnew2021b_DW.is_c1_rzs10thnew2021b = rzs10thnew2021b_IN_AS_Off;
        rzs10thnew2_enter_atomic_AS_Off();
      } else {
        rzs10thnew2021b_B.r2d_flag_l = 0.0;
        rzs10thnew2021b_B.steering_flag_i = 0.0;
        rzs10thnew2021b_B.brake_flag_b = 0.0;
        rzs10thnew2021b_B.as_led_yellow = 0.0;
        rzs10thnew2021b_B.as_led_blue = 0.0;
        rzs10thnew2021b_B.as_off_flag_d = 0.0;
        rzs10thnew2021b_B.as_ready_flag_p = 0.0;
        rzs10thnew2021b_B.as_driving_flag_b = 0.0;
        rzs10thnew2021b_B.as_finished_flag_g = 0.0;
        rzs10thnew2021b_B.as_emergency_flag_e = 0.0;
        rzs10thnew2021b_B.manual_driving_flag_k = 1.0;
      }
      break;
    }

    if (guard2) {
      rzs10thnew2021b_DW.is_c1_rzs10thnew2021b = rzs10thnew2021b_IN_AS_Emergency;
      rzs10_enter_atomic_AS_Emergency();
    }

    if (guard1) {
      rzs10thnew2021b_B.r2d_flag_l = 0.0;
      rzs10thnew2021b_B.steering_flag_i = 1.0;
      rzs10thnew2021b_B.brake_flag_b = 2.0;
      rzs10thnew2021b_B.as_led_yellow = 1.0;
      rzs10thnew2021b_B.as_led_blue = 0.0;
      rzs10thnew2021b_B.as_off_flag_d = 0.0;
      rzs10thnew2021b_B.as_ready_flag_p = 1.0;
      rzs10thnew2021b_B.as_driving_flag_b = 0.0;
      rzs10thnew2021b_B.as_finished_flag_g = 0.0;
      rzs10thnew2021b_B.as_emergency_flag_e = 0.0;
      rzs10thnew2021b_B.manual_driving_flag_k = 0.0;
    }
  }

  /* End of Chart: '<S4>/Chart' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */

  /* S-Function (fcgen): '<Root>/10ms8' incorporates:
   *  SubSystem: '<Root>/ESP'
   */
  /* Chart: '<S151>/ESP_Chart1' incorporates:
   *  DataStoreWrite: '<S4>/Data Store Write1'
   */
  if (rzs10thnew2021b_DW.is_active_c16_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c16_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c16_rzs10thnew2021b = rzs10thnew2021b_IN_ESC_Unable;
    rtb_mode = 0;
  } else {
    switch (rzs10thnew2021b_DW.is_c16_rzs10thnew2021b) {
     case rzs10thnew2021b_IN_ESC_Able:
      rtb_mode = 1;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (rzs10thnew2021b_B.brake_flag_b == 0.0) {
        rzs10thnew2021b_DW.is_c16_rzs10thnew2021b =
          rzs10thnew2021b_IN_ESC_Unable;
        rtb_mode = 0;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case rzs10thnew2021b_IN_ESC_Engage:
      rtb_mode = 1;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (rzs10thnew2021b_B.brake_flag_b == 1.0) {
        rzs10thnew2021b_DW.is_c16_rzs10thnew2021b = rzs10thnew2021b_IN_ESC_Able;
        rzs10thnew2021b_B.tarPrsReqFL = rzs10thnew2021b_B.ipc_esp_flprs;
        rzs10thnew2021b_B.tarPrsReqFR = rzs10thnew2021b_B.ipc_eps_frprs;
        rzs10thnew2021b_B.tarPrsReqRL = rzs10thnew2021b_B.ipc_esp_rlprs;
        rzs10thnew2021b_B.tarPrsReqRR = rzs10thnew2021b_B.ipc_esp_rrprs;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     default:
      /* case IN_ESC_Unable: */
      rtb_mode = 0;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (rzs10thnew2021b_B.brake_flag_b == 2.0) {
        rzs10thnew2021b_DW.is_c16_rzs10thnew2021b =
          rzs10thnew2021b_IN_ESC_Engage;
        rtb_mode = 1;
        rzs10thnew2021b_B.tarPrsReqFL = rzs10thnew2021b_B.ipc_esp_flprs;
        rzs10thnew2021b_B.tarPrsReqFR = rzs10thnew2021b_B.ipc_eps_frprs;
        rzs10thnew2021b_B.tarPrsReqRL = rzs10thnew2021b_B.ipc_esp_rlprs;
        rzs10thnew2021b_B.tarPrsReqRR = rzs10thnew2021b_B.ipc_esp_rrprs;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;
    }
  }

  /* End of Chart: '<S151>/ESP_Chart1' */

  /* DataTypeConversion: '<S151>/Data Type Conversion5' incorporates:
   *  Gain: '<S151>/Gain'
   */
  rzs10thnew2021b_B.d = floor(100.0 * rzs10thnew2021b_B.tarPrsReqFL);
  if (rtIsNaN(rzs10thnew2021b_B.d) || rtIsInf(rzs10thnew2021b_B.d)) {
    rzs10thnew2021b_B.d = 0.0;
  } else {
    rzs10thnew2021b_B.d = fmod(rzs10thnew2021b_B.d, 65536.0);
  }

  rtb_y_jo = (uint16_T)(rzs10thnew2021b_B.d < 0.0 ? (int32_T)(uint16_T)-(int16_T)
                        (uint16_T)-rzs10thnew2021b_B.d : (int32_T)(uint16_T)
                        rzs10thnew2021b_B.d);

  /* End of DataTypeConversion: '<S151>/Data Type Conversion5' */

  /* Outputs for Atomic SubSystem: '<S151>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S151>/Bitwise AND1' */
  rzs10thnew2021b_BitShift6((uint16_T)(rtb_y_jo & 15), &rtb_y_ju);

  /* End of Outputs for SubSystem: '<S151>/Bit Shift1' */

  /* DataTypeConversion: '<S151>/Data Type Conversion8' incorporates:
   *  Gain: '<S151>/Gain1'
   */
  rzs10thnew2021b_B.d = floor(100.0 * rzs10thnew2021b_B.tarPrsReqFR);
  if (rtIsNaN(rzs10thnew2021b_B.d) || rtIsInf(rzs10thnew2021b_B.d)) {
    rzs10thnew2021b_B.d = 0.0;
  } else {
    rzs10thnew2021b_B.d = fmod(rzs10thnew2021b_B.d, 65536.0);
  }

  rtb_y_l = (uint16_T)(rzs10thnew2021b_B.d < 0.0 ? (int32_T)(uint16_T)-(int16_T)
                       (uint16_T)-rzs10thnew2021b_B.d : (int32_T)(uint16_T)
                       rzs10thnew2021b_B.d);

  /* End of DataTypeConversion: '<S151>/Data Type Conversion8' */

  /* Outputs for Atomic SubSystem: '<S151>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S151>/Bitwise AND2' */
  rzs10thnew2021b_BitShift5((uint16_T)(rtb_y_l & 3840), &rtb_y_k0);

  /* End of Outputs for SubSystem: '<S151>/Bit Shift2' */

  /* Sum: '<S151>/Add' */
  rtb_y_ir = (uint16_T)((uint32_T)rtb_y_ju + rtb_y_k0);

  /* DataTypeConversion: '<S151>/Data Type Conversion9' incorporates:
   *  Gain: '<S151>/Gain2'
   */
  rzs10thnew2021b_B.d = floor(100.0 * rzs10thnew2021b_B.tarPrsReqRL);
  if (rtIsNaN(rzs10thnew2021b_B.d) || rtIsInf(rzs10thnew2021b_B.d)) {
    rzs10thnew2021b_B.d = 0.0;
  } else {
    rzs10thnew2021b_B.d = fmod(rzs10thnew2021b_B.d, 65536.0);
  }

  rtb_Add2_i = (uint16_T)(rzs10thnew2021b_B.d < 0.0 ? (int32_T)(uint16_T)
    -(int16_T)(uint16_T)-rzs10thnew2021b_B.d : (int32_T)(uint16_T)
    rzs10thnew2021b_B.d);

  /* End of DataTypeConversion: '<S151>/Data Type Conversion9' */

  /* Outputs for Atomic SubSystem: '<S151>/Bit Shift4' */
  /* S-Function (sfix_bitop): '<S151>/Bitwise AND5' */
  rzs10thnew2021b_BitShift6((uint16_T)(rtb_Add2_i & 15), &rtb_y_k0);

  /* End of Outputs for SubSystem: '<S151>/Bit Shift4' */

  /* DataTypeConversion: '<S151>/Data Type Conversion10' incorporates:
   *  Gain: '<S151>/Gain3'
   */
  rzs10thnew2021b_B.d = floor(100.0 * rzs10thnew2021b_B.tarPrsReqRR);
  if (rtIsNaN(rzs10thnew2021b_B.d) || rtIsInf(rzs10thnew2021b_B.d)) {
    rzs10thnew2021b_B.d = 0.0;
  } else {
    rzs10thnew2021b_B.d = fmod(rzs10thnew2021b_B.d, 65536.0);
  }

  rtb_Add1_p = (uint16_T)(rzs10thnew2021b_B.d < 0.0 ? (int32_T)(uint16_T)
    -(int16_T)(uint16_T)-rzs10thnew2021b_B.d : (int32_T)(uint16_T)
    rzs10thnew2021b_B.d);

  /* End of DataTypeConversion: '<S151>/Data Type Conversion10' */

  /* Outputs for Atomic SubSystem: '<S151>/Bit Shift5' */
  /* S-Function (sfix_bitop): '<S151>/Bitwise AND6' */
  rzs10thnew2021b_BitShift5((uint16_T)(rtb_Add1_p & 3840), &rtb_y_ju);

  /* End of Outputs for SubSystem: '<S151>/Bit Shift5' */

  /* Sum: '<S151>/Add1' */
  rtb_y_ju = (uint16_T)((uint32_T)rtb_y_k0 + rtb_y_ju);

  /* DataTypeConversion: '<S151>/Data Type Conversion11' */
  rtb_BitwiseAND_cd = (uint8_T)rtb_mode;

  /* Outputs for Atomic SubSystem: '<S151>/Bit Shift6' */
  rzs10thnew2021b_BitShift3_p((uint8_T)rtb_mode, &rtb_BitwiseAND_cd);

  /* End of Outputs for SubSystem: '<S151>/Bit Shift6' */

  /* Outputs for Atomic SubSystem: '<S151>/Bit Shift' */
  /* S-Function (sfix_bitop): '<S151>/Bitwise AND' */
  rzs10thnew2021b_BitShift7((uint16_T)(rtb_y_jo & 4080), &rtb_y_jo);

  /* End of Outputs for SubSystem: '<S151>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S151>/Bit Shift3' */
  /* S-Function (sfix_bitop): '<S151>/Bitwise AND4' */
  rzs10thnew2021b_BitShift7((uint16_T)(rtb_Add2_i & 4080), &rtb_y_k0);

  /* End of Outputs for SubSystem: '<S151>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S69>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S69>/Bitwise AND12' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  rzs10thnew2021b_BitShift1((uint8_T)(ESP_T_01[3] & 252), &rtb_y_hwh);

  /* End of Outputs for SubSystem: '<S69>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S69>/Bit Shift10' */
  /* S-Function (sfix_bitop): '<S69>/Bitwise AND3' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  rzs10thnew2021b_BitShift10((uint8_T)(ESP_T_01[0] & 4), &rtb_y_hwh);

  /* End of Outputs for SubSystem: '<S69>/Bit Shift10' */

  /* Outputs for Atomic SubSystem: '<S69>/Bit Shift11' */
  /* S-Function (sfix_bitop): '<S69>/Bitwise AND4' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  rzs10thnew2021b_BitShift2((uint8_T)(ESP_T_01[0] & 5), &rtb_y_hwh);

  /* End of Outputs for SubSystem: '<S69>/Bit Shift11' */

  /* Outputs for Atomic SubSystem: '<S69>/Bit Shift13' */
  /* S-Function (sfix_bitop): '<S69>/Bitwise AND6' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  rzs10thnew2021b_BitShift2_g((uint8_T)(ESP_T_01[0] & 7), &rtb_y_hwh);

  /* End of Outputs for SubSystem: '<S69>/Bit Shift13' */

  /* Outputs for Atomic SubSystem: '<S69>/Bit Shift14' */
  /* S-Function (sfix_bitop): '<S69>/Bitwise AND7' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  rzs10thnew2021b_BitShift1_k((uint8_T)(ESP_T_01[0] & 8), &rtb_y_hwh);

  /* End of Outputs for SubSystem: '<S69>/Bit Shift14' */

  /* Outputs for Atomic SubSystem: '<S69>/Bit Shift15' */
  /* S-Function (sfix_bitop): '<S69>/Bitwise AND10' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  rzs10thnew2021b_BitShift((uint8_T)(ESP_T_01[2] & 254), &rtb_y_hwh);

  /* End of Outputs for SubSystem: '<S69>/Bit Shift15' */

  /* Outputs for Atomic SubSystem: '<S69>/Bit Shift16' */
  /* S-Function (sfix_bitop): '<S69>/Bitwise AND9' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  rzs10thnew2021b_BitShift1_k((uint8_T)(ESP_T_01[1] & 128), &rtb_y_hwh);

  /* End of Outputs for SubSystem: '<S69>/Bit Shift16' */

  /* Outputs for Atomic SubSystem: '<S69>/Bit Shift3' */
  /* S-Function (sfix_bitop): '<S69>/Bitwise AND14' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  rzs10thnew2021b_BitShift10((uint8_T)(ESP_T_01[4] & 248), &rtb_y_hwh);

  /* End of Outputs for SubSystem: '<S69>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S69>/Bit Shift4' */
  /* S-Function (sfix_bitop): '<S69>/Bitwise AND15' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  rzs10thnew2021b_BitShift4_p((uint8_T)(ESP_T_01[4] & 7), &rtb_y_hwh);

  /* End of Outputs for SubSystem: '<S69>/Bit Shift4' */

  /* Outputs for Atomic SubSystem: '<S69>/Bit Shift5' */
  /* S-Function (sfix_bitop): '<S69>/Bitwise AND16' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  rzs10thnew2021b_BitShift2((uint8_T)(ESP_T_01[5] & 240), &rtb_y_hwh);

  /* End of Outputs for SubSystem: '<S69>/Bit Shift5' */

  /* Outputs for Atomic SubSystem: '<S69>/Bit Shift6' */
  /* S-Function (sfix_bitop): '<S69>/Bitwise AND17' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  rzs10thnew2021b_BitShift4_p((uint8_T)(ESP_T_01[5] & 15), &rtb_y_hwh);

  /* End of Outputs for SubSystem: '<S69>/Bit Shift6' */

  /* Outputs for Atomic SubSystem: '<S69>/Bit Shift7' */
  /* S-Function (sfix_bitop): '<S69>/Bitwise AND18' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  rzs10thnew2021b_BitShift2((uint8_T)(ESP_T_01[6] & 240), &rtb_y_hwh);

  /* End of Outputs for SubSystem: '<S69>/Bit Shift7' */

  /* Outputs for Atomic SubSystem: '<S69>/Bit Shift8' */
  /* S-Function (sfix_bitop): '<S69>/Bitwise AND1' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  rzs10thnew2021b_BitShift((uint8_T)(ESP_T_01[0] & 2), &rtb_y_hwh);

  /* End of Outputs for SubSystem: '<S69>/Bit Shift8' */

  /* Outputs for Atomic SubSystem: '<S69>/Bit Shift9' */
  /* S-Function (sfix_bitop): '<S69>/Bitwise AND2' incorporates:
   *  Inport: '<Root>/ESP_T_01'
   */
  rzs10thnew2021b_BitShift1((uint8_T)(ESP_T_01[0] & 3), &rtb_y_hwh);

  /* End of Outputs for SubSystem: '<S69>/Bit Shift9' */

  /* Outputs for Atomic SubSystem: '<S70>/Bit Shift' */
  /* DataTypeConversion: '<S70>/Data Type Conversion1' incorporates:
   *  Inport: '<Root>/ESP_T_03'
   */
  rzs10thnew2021b_BitShift4((uint16_T)ESP_T_03[0], &rtb_Add2_i);

  /* End of Outputs for SubSystem: '<S70>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S70>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S70>/Bitwise AND1' incorporates:
   *  DataTypeConversion: '<S70>/Data Type Conversion3'
   *  Inport: '<Root>/ESP_T_03'
   */
  rzs10thnew2021b_BitShift3((uint16_T)(ESP_T_03[1] & 240), &rtb_y_ap);

  /* End of Outputs for SubSystem: '<S70>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S70>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S70>/Bitwise AND2' incorporates:
   *  DataTypeConversion: '<S70>/Data Type Conversion4'
   *  Inport: '<Root>/ESP_T_03'
   */
  rzs10thnew2021b_BitShift_a((uint16_T)(ESP_T_03[1] & 15), &rtb_y_ci);

  /* End of Outputs for SubSystem: '<S70>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S70>/Bit Shift3' */
  /* DataTypeConversion: '<S70>/Data Type Conversion6' incorporates:
   *  Inport: '<Root>/ESP_T_03'
   */
  rzs10thnew2021b_BitShift4((uint16_T)ESP_T_03[3], &rtb_y_my);

  /* End of Outputs for SubSystem: '<S70>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S70>/Bit Shift4' */
  /* S-Function (sfix_bitop): '<S70>/Bitwise AND5' incorporates:
   *  DataTypeConversion: '<S70>/Data Type Conversion7'
   *  Inport: '<Root>/ESP_T_03'
   */
  rzs10thnew2021b_BitShift3((uint16_T)(ESP_T_03[4] & 240), &rtb_y_gs);

  /* End of Outputs for SubSystem: '<S70>/Bit Shift4' */

  /* Outputs for Atomic SubSystem: '<S70>/Bit Shift5' */
  /* S-Function (sfix_bitop): '<S70>/Bitwise AND6' incorporates:
   *  DataTypeConversion: '<S70>/Data Type Conversion8'
   *  Inport: '<Root>/ESP_T_03'
   */
  rzs10thnew2021b_BitShift_a((uint16_T)(ESP_T_03[4] & 15), &rtb_y_cg);

  /* End of Outputs for SubSystem: '<S70>/Bit Shift5' */

  /* Gain: '<S70>/Gain' incorporates:
   *  DataTypeConversion: '<S70>/Data Type Conversion2'
   *  Sum: '<S70>/Add'
   */
  rzs10thnew2021b_B.Product1 = (real_T)(uint16_T)((uint32_T)rtb_Add2_i +
    rtb_y_ap) * 0.01;

  /* Gain: '<S70>/Gain1' incorporates:
   *  DataTypeConversion: '<S70>/Data Type Conversion12'
   *  DataTypeConversion: '<S70>/Data Type Conversion9'
   *  Inport: '<Root>/ESP_T_03'
   *  Sum: '<S70>/Add3'
   */
  rzs10thnew2021b_B.Product2 = (real_T)(uint16_T)((uint32_T)rtb_y_cg + ESP_T_03
    [5]) * 0.01;

  /* Gain: '<S70>/Gain2' incorporates:
   *  DataTypeConversion: '<S70>/Data Type Conversion10'
   *  DataTypeConversion: '<S70>/Data Type Conversion5'
   *  Inport: '<Root>/ESP_T_03'
   *  Sum: '<S70>/Add1'
   */
  rzs10thnew2021b_B.ipc_esp_flprs = (real_T)(uint16_T)((uint32_T)rtb_y_ci +
    ESP_T_03[2]) * 0.01;

  /* Gain: '<S70>/Gain3' incorporates:
   *  DataTypeConversion: '<S70>/Data Type Conversion11'
   *  Sum: '<S70>/Add2'
   */
  rzs10thnew2021b_B.ipc_eps_frprs = (real_T)(uint16_T)((uint32_T)rtb_y_my +
    rtb_y_gs) * 0.01;

  /* Chart: '<S73>/brkmotor_check_system' incorporates:
   *  Inport: '<Root>/ESP_T_03'
   */
  rtb_y_hwh = rzs10thnew2021b_DW.lifesig_start;
  rzs10thnew2021b_DW.lifesig_start = ESP_T_03[6];
  if (rzs10thnew2021b_DW.is_active_c18_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c18_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c18_rzs10thnew2021b = rzs10thnew2021b_IN_begin_b;
  } else {
    switch (rzs10thnew2021b_DW.is_c18_rzs10thnew2021b) {
     case rzs10thnew2021b_IN_begin_b:
      if (rtb_y_hwh != rzs10thnew2021b_DW.lifesig_start) {
        rzs10thnew2021b_DW.is_c18_rzs10thnew2021b = rzs10thnew2021b_IN_compare;
        rzs10thnew2021b_B.brkmotor_check = T;
      }
      break;

     case rzs10thnew2021b_IN_compare:
      if (rtb_y_hwh == rzs10thnew2021b_DW.lifesig_start) {
        rzs10thnew2021b_DW.is_c18_rzs10thnew2021b = rzs10thnew2021b_IN_same;
        rzs10thnew2021b_DW.lscnt++;
      } else {
        rzs10thnew2021b_B.brkmotor_check = T;
      }
      break;

     case rzs10thnew2021b_IN_judge:
      if (rtb_y_hwh != rzs10thnew2021b_DW.lifesig_start) {
        rzs10thnew2021b_DW.is_c18_rzs10thnew2021b = rzs10thnew2021b_IN_compare;
        rzs10thnew2021b_B.brkmotor_check = T;
      } else {
        rzs10thnew2021b_B.brkmotor_check = F;
      }
      break;

     default:
      /* case IN_same: */
      if (rzs10thnew2021b_DW.lscnt > 10.0) {
        rzs10thnew2021b_DW.is_c18_rzs10thnew2021b = rzs10thnew2021b_IN_judge;
        rzs10thnew2021b_B.brkmotor_check = F;
      } else if (rtb_y_hwh != rzs10thnew2021b_DW.lifesig_start) {
        rzs10thnew2021b_DW.lscnt = 0.0;
        rzs10thnew2021b_DW.is_c18_rzs10thnew2021b = rzs10thnew2021b_IN_compare;
        rzs10thnew2021b_B.brkmotor_check = T;
      } else {
        rzs10thnew2021b_DW.lscnt++;
      }
      break;
    }
  }

  /* End of Chart: '<S73>/brkmotor_check_system' */

  /* Outputs for Atomic SubSystem: '<S71>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S71>/Bitwise AND2' incorporates:
   *  DataTypeConversion: '<S71>/Data Type Conversion3'
   *  Inport: '<Root>/ESP_T_06'
   */
  rzs10thnew2021b_BitShift2_i((uint16_T)(ESP_T_06[1] & 31), &rtb_Add2_i);

  /* End of Outputs for SubSystem: '<S71>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S71>/Bit Shift3' */
  /* S-Function (sfix_bitop): '<S71>/Bitwise AND3' incorporates:
   *  DataTypeConversion: '<S71>/Data Type Conversion4'
   *  Inport: '<Root>/ESP_T_06'
   */
  rzs10thnew2021b_BitShift1_f((uint16_T)(ESP_T_06[2] & 252), &rtb_Add2_i);

  /* End of Outputs for SubSystem: '<S71>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S71>/Bit Shift7' */
  /* S-Function (sfix_bitop): '<S71>/Bitwise AND7' incorporates:
   *  DataTypeConversion: '<S71>/Data Type Conversion8'
   *  Inport: '<Root>/ESP_T_06'
   */
  rzs10thnew2021b_BitShift4((uint16_T)(ESP_T_06[4] & 127), &rtb_Add2_i);

  /* End of Outputs for SubSystem: '<S71>/Bit Shift7' */

  /* Outputs for Atomic SubSystem: '<S71>/Bit Shift8' */
  /* S-Function (sfix_bitop): '<S71>/Bitwise AND8' incorporates:
   *  DataTypeConversion: '<S71>/Data Type Conversion9'
   *  Inport: '<Root>/ESP_T_06'
   */
  rzs10thnew2021b_BitShift3((uint16_T)(ESP_T_06[5] & 240), &rtb_Add2_i);

  /* End of Outputs for SubSystem: '<S71>/Bit Shift8' */

  /* Outputs for Atomic SubSystem: '<S72>/Bit Shift' */
  /* DataTypeConversion: '<S72>/Data Type Conversion2' incorporates:
   *  Inport: '<Root>/ESP_T_07'
   */
  rzs10thnew2021b_BitShift4((uint16_T)ESP_T_07[0], &rtb_Add2_i);

  /* End of Outputs for SubSystem: '<S72>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S72>/Bit Shift1' */
  /* S-Function (sfix_bitop): '<S72>/Bitwise AND1' incorporates:
   *  DataTypeConversion: '<S72>/Data Type Conversion1'
   *  Inport: '<Root>/ESP_T_07'
   */
  rzs10thnew2021b_BitShift3((uint16_T)(ESP_T_07[1] & 240), &rtb_Add2_i);

  /* End of Outputs for SubSystem: '<S72>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S72>/Bit Shift2' */
  /* S-Function (sfix_bitop): '<S72>/Bitwise AND2' incorporates:
   *  DataTypeConversion: '<S72>/Data Type Conversion3'
   *  Inport: '<Root>/ESP_T_07'
   */
  rzs10thnew2021b_BitShift_a((uint16_T)(ESP_T_07[1] & 15), &rtb_Add2_i);

  /* End of Outputs for SubSystem: '<S72>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S72>/Bit Shift3' */
  /* DataTypeConversion: '<S72>/Data Type Conversion5' incorporates:
   *  Inport: '<Root>/ESP_T_07'
   */
  rzs10thnew2021b_BitShift4((uint16_T)ESP_T_07[3], &rtb_Add2_i);

  /* End of Outputs for SubSystem: '<S72>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S72>/Bit Shift4' */
  /* S-Function (sfix_bitop): '<S72>/Bitwise AND5' incorporates:
   *  DataTypeConversion: '<S72>/Data Type Conversion6'
   *  Inport: '<Root>/ESP_T_07'
   */
  rzs10thnew2021b_BitShift3((uint16_T)(ESP_T_07[4] & 240), &rtb_Add2_i);

  /* End of Outputs for SubSystem: '<S72>/Bit Shift4' */

  /* Outputs for Atomic SubSystem: '<S72>/Bit Shift5' */
  /* S-Function (sfix_bitop): '<S72>/Bitwise AND6' incorporates:
   *  DataTypeConversion: '<S72>/Data Type Conversion7'
   *  Inport: '<Root>/ESP_T_07'
   */
  rzs10thnew2021b_BitShift_a((uint16_T)(ESP_T_07[4] & 15), &rtb_Add2_i);

  /* End of Outputs for SubSystem: '<S72>/Bit Shift5' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms8' */

  /* S-Function (fcgen): '<Root>/10ms2' incorporates:
   *  SubSystem: '<Root>/LED_Control'
   */
  /* S-Function (fcgen): '<Root>/10ms' incorporates:
   *  SubSystem: '<Root>/Sensor_Signal'
   */
  /* DataTypeConversion: '<S13>/Data Type Conversion15' incorporates:
   *  Inport: '<Root>/Input'
   *  Lookup_n-D: '<S13>/1-D Lookup Table7'
   *  RelationalOperator: '<S203>/Compare'
   */
  rzs10thnew2021b_B.ipc_esp_rlprs = look1_iu16lu16n16_linlcase
    (digital_input.adc_in[4], rzs10thnew2021b_ConstP.pooled33,
     rzs10thnew2021b_ConstP.pooled32, 1U);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms2' */

  /* S-Function (fcgen): '<Root>/10ms3' incorporates:
   *  SubSystem: '<Root>/ASB_Selfcheck'
   */
  /* RelationalOperator: '<S36>/Compare' incorporates:
   *  Constant: '<S36>/Constant'
   *  DataTypeConversion: '<S13>/Data Type Conversion15'
   */
  rzs10thnew2021b_DW.ebs_working = (rzs10thnew2021b_B.ipc_esp_rlprs >= 0.9);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */

  /* DataStoreWrite: '<Root>/Data Store Write' incorporates:
   *  Constant: '<S27>/Constant'
   *  Constant: '<S28>/Constant'
   *  Constant: '<S29>/Constant'
   *  Constant: '<S30>/Constant'
   *  Constant: '<S31>/Constant'
   *  DataStoreRead: '<Root>/Data Store Read'
   *  Logic: '<S23>/Logical Operator'
   *  Logic: '<S2>/Logical Operator'
   *  RelationalOperator: '<S27>/Compare'
   *  RelationalOperator: '<S28>/Compare'
   *  RelationalOperator: '<S29>/Compare'
   *  RelationalOperator: '<S30>/Compare'
   *  RelationalOperator: '<S31>/Compare'
   */
  rzs10thnew2021b_DW.asb_check = ((rtb_ebs_drivercheck != 0) && ((airprs_sensor1
    >= 0.74) && (rzs10thnew2021b_B.Product1 >= 0.848) &&
    (rzs10thnew2021b_B.ipc_esp_flprs >= 0.848) &&
    (rzs10thnew2021b_B.ipc_eps_frprs >= 0.742) && (rzs10thnew2021b_B.Product2 >=
    0.742)) && rtb_xor_consequence && rzs10thnew2021b_DW.brkmotor_check);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms3' */

  /* DataStoreWrite: '<Root>/Data Store Write10' */
  rzs10thnew2021b_DW.ipc_astask = rzs10thnew2021b_B.ipc_astask;

  /* S-Function (fcgen): '<Root>/10ms11' incorporates:
   *  SubSystem: '<Root>/IPC'
   */
  /* DataStoreWrite: '<Root>/Data Store Write11' incorporates:
   *  DataTypeConversion: '<S173>/Data Type Conversion4'
   */
  rzs10thnew2021b_DW.task_finish = (res_heartbeat_prev != 0);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */

  /* S-Function (fcgen): '<Root>/10ms13' incorporates:
   *  SubSystem: '<Root>/AMI_CAN'
   */
  /* Chart: '<S17>/Chart' incorporates:
   *  DataStoreWrite: '<S4>/Data Store Write10'
   *  DataStoreWrite: '<S4>/Data Store Write2'
   *  DataStoreWrite: '<S4>/Data Store Write3'
   *  DataStoreWrite: '<S4>/Data Store Write6'
   *  DataStoreWrite: '<S4>/Data Store Write7'
   *  DataStoreWrite: '<S4>/Data Store Write8'
   *  DataStoreWrite: '<S4>/Data Store Write9'
   */
  if (rzs10thnew2021b_DW.is_active_c20_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c20_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c20_rzs10thnew2021b = rzs10thnew2021b_IN_begin_n;
  } else {
    switch (rzs10thnew2021b_DW.is_c20_rzs10thnew2021b) {
     case rzs10thnew2021b_IN_as_driving:
      rzs10thnew2021b_B.ami_process = 16U;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (rzs10thnew2021b_B.as_driving_flag_b != 1.0) {
        rzs10thnew2021b_DW.is_c20_rzs10thnew2021b = rzs10thnew2021b_IN_begin_n;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case rzs10thnew2021b_IN_as_emergency:
      rzs10thnew2021b_B.ami_process = 64U;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (rzs10thnew2021b_B.as_emergency_flag_e != 1.0) {
        rzs10thnew2021b_DW.is_c20_rzs10thnew2021b = rzs10thnew2021b_IN_begin_n;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case rzs10thnew2021b_IN_as_finished:
      rzs10thnew2021b_B.ami_process = 32U;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (rzs10thnew2021b_B.as_finished_flag_g != 1.0) {
        rzs10thnew2021b_DW.is_c20_rzs10thnew2021b = rzs10thnew2021b_IN_begin_n;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case rzs10thnew2021b_IN_as_off:
      rzs10thnew2021b_B.ami_process = 1U;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (rzs10thnew2021b_B.as_off_flag_d != 1.0) {
        rzs10thnew2021b_DW.is_c20_rzs10thnew2021b = rzs10thnew2021b_IN_begin_n;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case rzs10thnew2021b_IN_as_ready:
      rzs10thnew2021b_B.ami_process = 4U;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (rzs10thnew2021b_B.as_ready_flag_p != 1.0) {
        rzs10thnew2021b_DW.is_c20_rzs10thnew2021b = rzs10thnew2021b_IN_begin_n;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case rzs10thnew2021b_IN_begin_n:
      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (rzs10thnew2021b_B.as_off_flag_d == 1.0) {
        rzs10thnew2021b_DW.is_c20_rzs10thnew2021b = rzs10thnew2021b_IN_as_off;
        rzs10thnew2021b_B.ami_process = 1U;
      } else if (rzs10thnew2021b_B.manual_driving_flag_k == 1.0) {
        rzs10thnew2021b_DW.is_c20_rzs10thnew2021b =
          rzs10thnew202_IN_munual_driving;
        rzs10thnew2021b_B.ami_process = 2U;
      } else if (rzs10thnew2021b_B.as_ready_flag_p == 1.0) {
        rzs10thnew2021b_DW.is_c20_rzs10thnew2021b = rzs10thnew2021b_IN_as_ready;
        rzs10thnew2021b_B.ami_process = 4U;
      } else if (rzs10thnew2021b_B.r2d_flag_l == 1.0) {
        rzs10thnew2021b_DW.is_c20_rzs10thnew2021b = rzs10thnew2021b_IN_r2d;
        rzs10thnew2021b_B.ami_process = 8U;
      } else if (rzs10thnew2021b_B.as_driving_flag_b == 1.0) {
        rzs10thnew2021b_DW.is_c20_rzs10thnew2021b =
          rzs10thnew2021b_IN_as_driving;
        rzs10thnew2021b_B.ami_process = 16U;
      } else if (rzs10thnew2021b_B.as_finished_flag_g == 1.0) {
        rzs10thnew2021b_DW.is_c20_rzs10thnew2021b =
          rzs10thnew2021b_IN_as_finished;
        rzs10thnew2021b_B.ami_process = 32U;
      } else if (rzs10thnew2021b_B.as_emergency_flag_e == 1.0) {
        rzs10thnew2021b_DW.is_c20_rzs10thnew2021b =
          rzs10thnew2021b_IN_as_emergency;
        rzs10thnew2021b_B.ami_process = 64U;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case rzs10thnew202_IN_munual_driving:
      rzs10thnew2021b_B.ami_process = 2U;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (rzs10thnew2021b_B.manual_driving_flag_k != 1.0) {
        rzs10thnew2021b_DW.is_c20_rzs10thnew2021b = rzs10thnew2021b_IN_begin_n;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     default:
      /* case IN_r2d: */
      rzs10thnew2021b_B.ami_process = 8U;

      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (rzs10thnew2021b_B.r2d_flag_l != 1.0) {
        rzs10thnew2021b_DW.is_c20_rzs10thnew2021b = rzs10thnew2021b_IN_begin_n;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;
    }
  }

  /* End of Chart: '<S17>/Chart' */

  /* Outputs for Atomic SubSystem: '<S17>/Bit Shift' */
  /* S-Function (sfix_bitop): '<S17>/Bitwise AND' */
  rzs10thnew2021b_BitShift_g((uint8_T)(rzs10thnew2021b_B.ami_process & 127),
    &res_heartbeat_prev);

  /* End of Outputs for SubSystem: '<S17>/Bit Shift' */

  /* SignalConversion: '<S17>/Signal Conversion' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read12'
   *  Sum: '<S17>/Add1'
   */
  AMI_Rx[0] = (uint8_T)((uint32_T)res_heartbeat_prev +
                        rzs10thnew2021b_DW.task_finish);
  AMI_Rx[1] = ((uint8_T)0U);
  AMI_Rx[2] = ((uint8_T)0U);
  AMI_Rx[3] = ((uint8_T)0U);
  AMI_Rx[4] = ((uint8_T)0U);
  AMI_Rx[5] = ((uint8_T)0U);
  AMI_Rx[6] = ((uint8_T)0U);
  AMI_Rx[7] = ((uint8_T)0U);

  /* Outputs for Atomic SubSystem: '<S16>/Bit Shift' */
  /* DataStoreWrite: '<Root>/Data Store Write12' incorporates:
   *  Inport: '<Root>/AMI_Tx'
   *  S-Function (sfix_bitop): '<S16>/Bitwise AND'
   */
  rzs10thnew2021b_BitShift2((uint8_T)(AMI_Tx[0] & 240),
    &rzs10thnew2021b_DW.ami_astask);

  /* End of Outputs for SubSystem: '<S16>/Bit Shift' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms13' */

  /* S-Function (fcgen): '<Root>/10ms3' incorporates:
   *  SubSystem: '<Root>/ASB_Selfcheck'
   */
  /* DataStoreWrite: '<Root>/Data Store Write2' incorporates:
   *  Constant: '<S32>/Constant'
   *  Constant: '<S33>/Constant'
   *  Constant: '<S34>/Constant'
   *  Constant: '<S35>/Constant'
   *  Logic: '<S23>/Logical Operator1'
   *  RelationalOperator: '<S32>/Compare'
   *  RelationalOperator: '<S33>/Compare'
   *  RelationalOperator: '<S34>/Compare'
   *  RelationalOperator: '<S35>/Compare'
   */
  rzs10thnew2021b_DW.brake_on = ((rzs10thnew2021b_B.Product1 >= 0.848) &&
    (rzs10thnew2021b_B.ipc_esp_flprs >= 0.848) &&
    (rzs10thnew2021b_B.ipc_eps_frprs >= 0.742) && (rzs10thnew2021b_B.Product2 >=
    0.742));

  /* S-Function (fcgen): '<Root>/10ms' incorporates:
   *  SubSystem: '<Root>/Sensor_Signal'
   */
  /* DataStoreWrite: '<Root>/Data Store Write3' incorporates:
   *  Constant: '<S25>/Constant'
   *  DataTypeConversion: '<S13>/Data Type Conversion12'
   *  Inport: '<Root>/Input'
   *  Logic: '<S2>/Logical Operator1'
   *  Lookup_n-D: '<S13>/1-D Lookup Table6'
   *  RelationalOperator: '<S24>/Compare'
   *  RelationalOperator: '<S25>/Compare'
   */
  rzs10thnew2021b_DW.ebs_check = ((!rzs10thnew2021b_DW.ebs_working) &&
    (rtb_ebs_drivercheck != 0) && (look1_iu16lu16n16_linlcase
    (digital_input.adc_in[3], rzs10thnew2021b_ConstP.pooled33,
     rzs10thnew2021b_ConstP.pooled32, 1U) >= 0.74));

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms3' */

  /* DataStoreWrite: '<Root>/Data Store Write4' */
  rzs10thnew2021b_DW.brkmotor_check = rzs10thnew2021b_B.brkmotor_check;

  /* S-Function (fcgen): '<Root>/10ms9' incorporates:
   *  SubSystem: '<Root>/EPS'
   */
  /* Sum: '<S57>/Add' incorporates:
   *  Constant: '<S57>/Constant1'
   *  DataTypeConversion: '<S57>/Data Type Conversion1'
   *  DataTypeConversion: '<S57>/Data Type Conversion2'
   *  Gain: '<S57>/Gain1'
   *  Inport: '<Root>/canb_epssendmsg1'
   */
  rtb_mode = ((canb_epssendmsg1[3] << 8) + canb_epssendmsg1[4]) - 1024;

  /* Outputs for Atomic SubSystem: '<S58>/Bit Shift1' */
  /* DataTypeConversion: '<S58>/Data Type Conversion3' incorporates:
   *  Inport: '<Root>/canb_epssendmsg2'
   */
  rzs10thnew2021b_BitShift_a((uint16_T)canb_epssendmsg2[1], &rtb_ebs_drivercheck);

  /* End of Outputs for SubSystem: '<S58>/Bit Shift1' */

  /* S-Function (fcgen): '<Root>/10ms11' incorporates:
   *  SubSystem: '<Root>/IPC'
   */
  /* DataTypeConversion: '<S65>/Data Type Conversion5' incorporates:
   *  Constant: '<S173>/Constant'
   *  Constant: '<S65>/Constant1'
   *  DataTypeConversion: '<S173>/Data Type Conversion1'
   *  Gain: '<S65>/Gain1'
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S9>/canb_ipctsmsg2'
   *  Sum: '<S173>/Add'
   *  Sum: '<S65>/Add1'
   */
  rzs10thnew2021b_B.d = floor(((rzs10thnew2021b_B.y + (real_T)canb_ipctsmsg2[1])
    - 1024.0) * 5.0 + 1024.0);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */
  if (rtIsNaN(rzs10thnew2021b_B.d) || rtIsInf(rzs10thnew2021b_B.d)) {
    rzs10thnew2021b_B.d = 0.0;
  } else {
    rzs10thnew2021b_B.d = fmod(rzs10thnew2021b_B.d, 65536.0);
  }

  rtb_ebs_drivercheck = (uint16_T)(rzs10thnew2021b_B.d < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-rzs10thnew2021b_B.d : (int32_T)(uint16_T)
    rzs10thnew2021b_B.d);

  /* End of DataTypeConversion: '<S65>/Data Type Conversion5' */

  /* Logic: '<S56>/Logical Operator3' incorporates:
   *  Constant: '<S62>/Constant'
   *  Constant: '<S63>/Constant'
   *  RelationalOperator: '<S62>/Compare'
   *  RelationalOperator: '<S63>/Compare'
   */
  rzs10thnew2021b_DW.steer_zero = ((rtb_mode >= -2) && (rtb_mode <= 2));

  /* Chart: '<S56>/EPS_Stateflow1' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read2'
   *  DataStoreWrite: '<S4>/Data Store Write4'
   *  Inport: '<Root>/canb_ipctsmsg2'
   *  Inport: '<S9>/canb_ipctsmsg2'
   */
  elapsedTicks_h = rzs10thnew2021b_M->Timing.clockTick1 -
    rzs10thnew2021b_DW.previousTicks;
  rzs10thnew2021b_DW.previousTicks = rzs10thnew2021b_M->Timing.clockTick1;
  if (rzs10thnew2021b_DW.temporalCounter_i1_a + elapsedTicks_h <= 1U) {
    rzs10thnew2021b_DW.temporalCounter_i1_a = (uint8_T)
      (rzs10thnew2021b_DW.temporalCounter_i1_a + elapsedTicks_h);
  } else {
    rzs10thnew2021b_DW.temporalCounter_i1_a = 1U;
  }

  if (rzs10thnew2021b_DW.is_active_c15_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c15_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c15_rzs10thnew2021b = rzs10thnew2021b_IN_EPS_Unable;
    rzs10thnew2021b_B.eps_cmdworkmode = 0U;
    rzs10thnew2021b_B.eps_cmdmiddle = 0U;
  } else {
    switch (rzs10thnew2021b_DW.is_c15_rzs10thnew2021b) {
     case rzs10thnew2021b_IN_EPS_Enable:
      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (rzs10thnew2021b_B.steering_flag_i == 0.0) {
        rzs10thnew2021b_DW.is_c15_rzs10thnew2021b =
          rzs10thnew2021b_IN_EPS_Unable;
        rzs10thnew2021b_B.eps_cmdworkmode = 0U;
        rzs10thnew2021b_B.eps_cmdmiddle = 0U;
      } else if ((rzs10thnew2021b_DW.temporalCounter_i1_a >= 1U) &&
                 rzs10thnew2021b_DW.steer_return) {
        rzs10thnew2021b_DW.is_c15_rzs10thnew2021b =
          rzs10thnew2021b_IN_EPS_Return;
        rzs10thnew2021b_B.eps_cmdworkmode = 32U;
        rzs10thnew2021b_B.eps_cmdangle = 4U;
        rzs10thnew2021b_B.eps_cmdmiddle = 85U;
        rzs10thnew2021b_B.eps_cmdvelocity = 20U;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     case rzs10thnew2021b_IN_EPS_Return:
      if (rzs10thnew2021b_DW.steer_zero) {
        rzs10thnew2021b_DW.is_c15_rzs10thnew2021b =
          rzs10thnew2021b_IN_EPS_Enable;
        rzs10thnew2021b_DW.temporalCounter_i1_a = 0U;
        rzs10thnew2021b_B.eps_cmdworkmode = 32U;
        rzs10thnew2021b_B.eps_cmdangle = rtb_ebs_drivercheck;
        rzs10thnew2021b_B.eps_cmdmiddle = 0U;

        /* S-Function (fcgen): '<Root>/10ms11' incorporates:
         *  SubSystem: '<Root>/IPC'
         */
        rzs10thnew2021b_B.eps_cmdvelocity = canb_ipctsmsg2[2];

        /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */
      } else {
        rzs10thnew2021b_B.eps_cmdworkmode = 32U;
        rzs10thnew2021b_B.eps_cmdangle = 4U;
        rzs10thnew2021b_B.eps_cmdmiddle = 85U;
        rzs10thnew2021b_B.eps_cmdvelocity = 20U;
      }
      break;

     default:
      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      /* case IN_EPS_Unable: */
      if (rzs10thnew2021b_B.steering_flag_i == 1.0) {
        rzs10thnew2021b_DW.is_c15_rzs10thnew2021b =
          rzs10thnew2021b_IN_EPS_Enable;
        rzs10thnew2021b_DW.temporalCounter_i1_a = 0U;
        rzs10thnew2021b_B.eps_cmdworkmode = 32U;
        rzs10thnew2021b_B.eps_cmdangle = rtb_ebs_drivercheck;
        rzs10thnew2021b_B.eps_cmdmiddle = 0U;

        /* S-Function (fcgen): '<Root>/10ms11' incorporates:
         *  SubSystem: '<Root>/IPC'
         */
        rzs10thnew2021b_B.eps_cmdvelocity = canb_ipctsmsg2[2];

        /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;
    }
  }

  /* End of Chart: '<S56>/EPS_Stateflow1' */

  /* Switch: '<S56>/Switch' incorporates:
   *  Rounding: '<S56>/Rounding Function'
   *  Sin: '<S56>/Sine Wave1'
   */
  if (rzs10thnew2021b_B.ami_inspection_signal > 0.0) {
    rzs10thnew2021b_B.y = floor(sin(((rzs10thnew2021b_M->Timing.clockTick1) *
      0.01)) * 90.0);
  } else {
    rzs10thnew2021b_B.y = rzs10thnew2021b_B.eps_cmdangle;
  }

  /* End of Switch: '<S56>/Switch' */

  /* DataTypeConversion: '<S56>/Data Type Conversion1' incorporates:
   *  Constant: '<S56>/Constant2'
   *  Sum: '<S56>/Add'
   */
  if (rtIsNaN(rzs10thnew2021b_B.y + 1024.0)) {
    rzs10thnew2021b_B.d = 0.0;
  } else {
    rzs10thnew2021b_B.d = fmod(rzs10thnew2021b_B.y + 1024.0, 65536.0);
  }

  /* Outputs for Atomic SubSystem: '<S56>/Bit Shift' */
  /* S-Function (sfix_bitop): '<S56>/Bitwise AND' incorporates:
   *  DataTypeConversion: '<S56>/Data Type Conversion1'
   */
  rzs10thnew2021b_BitShift5((uint16_T)((uint16_T)rzs10thnew2021b_B.d & 65280),
    &rtb_ebs_drivercheck);

  /* End of Outputs for SubSystem: '<S56>/Bit Shift' */

  /* DataTypeConversion: '<S56>/Data Type Conversion5' incorporates:
   *  DataTypeConversion: '<S56>/Data Type Conversion1'
   *  S-Function (sfix_bitop): '<S56>/Bitwise AND1'
   */
  res_heartbeat_prev = (uint8_T)((uint16_T)rzs10thnew2021b_B.d & 255);

  /* SignalConversion generated from: '<S7>/canb_epsmsg' incorporates:
   *  Constant: '<S56>/Constant'
   *  Constant: '<S56>/Constant1'
   *  DataTypeConversion: '<S56>/Data Type Conversion4'
   *  DataTypeConversion: '<S56>/Data Type Conversion6'
   *  Logic: '<S56>/Logical Operator2'
   *  S-Function (sfix_bitop): '<S56>/Bitwise AND2'
   *  S-Function (sfix_bitop): '<S56>/Bitwise AND3'
   */
  canb_epsmsg[0] = rzs10thnew2021b_B.eps_cmdworkmode;
  canb_epsmsg[1] = 0U;
  canb_epsmsg[2] = 0U;
  canb_epsmsg[3] = (uint8_T)rtb_ebs_drivercheck;
  canb_epsmsg[4] = res_heartbeat_prev;
  canb_epsmsg[5] = rzs10thnew2021b_B.eps_cmdmiddle;
  canb_epsmsg[6] = rzs10thnew2021b_B.eps_cmdvelocity;
  canb_epsmsg[7] = (uint8_T)((int8_T)((int8_T)((int8_T)((int8_T)
    (rzs10thnew2021b_B.eps_cmdworkmode != 0) ^ (int8_T)((uint8_T)
    rtb_ebs_drivercheck != 0)) ^ (int8_T)(res_heartbeat_prev != 0)) ^ (int8_T)
    (rzs10thnew2021b_B.eps_cmdmiddle != 0)) ^ (int8_T)
    (rzs10thnew2021b_B.eps_cmdvelocity != 0));

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms9' */

  /* Outputs for Atomic SubSystem: '<S15>/Bit Shift4' */
  /* S-Function (sfix_bitop): '<S15>/Bitwise AND4' incorporates:
   *  Inport: '<Root>/Input'
   */
  rzs10thnew2021b_BitShift7((uint16_T)(digital_input.io_in & 5),
    &rtb_ebs_drivercheck);

  /* End of Outputs for SubSystem: '<S15>/Bit Shift4' */

  /* S-Function (fcgen): '<Root>/10ms1' incorporates:
   *  SubSystem: '<Root>/TS_Activation'
   */
  /* Switch: '<S14>/Switch' incorporates:
   *  Logic: '<S14>/Logical Operator'
   *  Logic: '<S14>/Logical Operator2'
   */
  if (rzs10thnew2021b_B.ami_inspection_signal > 0.0) {
    LogicalOperator = true;
  } else {
    LogicalOperator = (rtb_ebs_drivercheck == 0);
  }

  /* End of Switch: '<S14>/Switch' */

  /* Chart: '<S14>/Chart' */
  if (rzs10thnew2021b_DW.is_active_c3_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c3_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c3_rzs10thnew2021b = rzs10thnew202_IN_Ignition_Check;
    rzs10thnew2021b_DW.is_Ignition_Check_c = rzs10thnew2021b_IN_begin;
    rzs10thnew2021b_DW.di8_flag = F;
  } else if (rzs10thnew2021b_DW.is_c3_rzs10thnew2021b == 1) {
    if (rzs10thnew2021b_DW.di8_flag == F) {
      rzs10thnew2021b_DW.is_Flameout_Check_j = rzs10thnew20_IN_NO_ACTIVE_CHILD;
      rzs10thnew2021b_DW.is_c3_rzs10thnew2021b = rzs10thnew202_IN_Ignition_Check;
      rzs10thnew2021b_DW.is_Ignition_Check_c = rzs10thnew2021b_IN_begin;
      rzs10thnew2021b_DW.di8_flag = F;
    } else {
      switch (rzs10thnew2021b_DW.is_Flameout_Check_j) {
       case rzs10thnew2021b_IN_Checkoff:
        break;

       default:
        /* case IN_DI8_Offcheck_Flag: */
        if (rzs10thnew2021b_DW.di8_offcheck_flag == 0.0) {
          rzs10thnew2021b_DW.is_Flameout_Check_j =
            rzs10thnew_IN_DI8_Offcheck_Flag;
          if (!LogicalOperator) {
            rzs10thnew2021b_DW.di8_offcheck_flag = 1.0;
          }
        } else {
          rzs10thnew2021b_DW.is_Flameout_Check_j = rzs10thnew2021b_IN_Checkoff;
          if (LogicalOperator) {
            rzs10thnew2021b_DW.di8_flag = F;
            di8 = F;
          }
        }
        break;
      }
    }

    /* case IN_Ignition_Check: */
  } else if (rzs10thnew2021b_DW.di8_flag == T) {
    rzs10thnew2021b_DW.is_Ignition_Check_c = rzs10thnew20_IN_NO_ACTIVE_CHILD;
    rzs10thnew2021b_DW.is_c3_rzs10thnew2021b = rzs10thnew202_IN_Flameout_Check;
    rzs10thnew2021b_DW.is_Flameout_Check_j = rzs10thnew_IN_DI8_Offcheck_Flag;
    if (!LogicalOperator) {
      rzs10thnew2021b_DW.di8_offcheck_flag = 1.0;
    }
  } else {
    switch (rzs10thnew2021b_DW.is_Ignition_Check_c) {
     case rzs10thnew2021b_IN_Check:
      if (rzs10thnew2021b_DW.di8_check_flag == 0.0) {
        rzs10thnew2021b_DW.is_Ignition_Check_c = rzs10thnew202_IN_DI8_Check_Flag;
        rzs10thnew2021b_DW.di8_check_flag = !LogicalOperator;
      } else if (rzs10thnew2021b_DW.di8_check_flag == 1.0) {
        rzs10thnew2021b_DW.is_Ignition_Check_c = rzs10thnew2021b_IN_Check;
        if (LogicalOperator) {
          rzs10thnew2021b_DW.di8_flag = T;
          di8 = T;
        }
      }
      break;

     case rzs10thnew202_IN_DI8_Check_Flag:
      if (rzs10thnew2021b_DW.di8_check_flag == 0.0) {
        rzs10thnew2021b_DW.is_Ignition_Check_c = rzs10thnew202_IN_DI8_Check_Flag;
        rzs10thnew2021b_DW.di8_check_flag = !LogicalOperator;
      } else if (rzs10thnew2021b_DW.di8_check_flag == 1.0) {
        rzs10thnew2021b_DW.is_Ignition_Check_c = rzs10thnew2021b_IN_Check;
        if (LogicalOperator) {
          rzs10thnew2021b_DW.di8_flag = T;
          di8 = T;
        }
      }
      break;

     default:
      /* case IN_begin: */
      rzs10thnew2021b_DW.is_Ignition_Check_c = rzs10thnew202_IN_DI8_Check_Flag;
      rzs10thnew2021b_DW.di8_check_flag = !LogicalOperator;
      break;
    }
  }

  /* End of Chart: '<S14>/Chart' */

  /* Chart: '<S14>/Chart1' */
  if (rzs10thnew2021b_DW.is_active_c8_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c8_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c8_rzs10thnew2021b = rzs10thnew202_IN_Ignition_Check;
    rzs10thnew2021b_DW.is_Ignition_Check = rzs10thnew2021b_IN_begin;
    rzs10thnew2021b_DW.run_flag = 0.0;
  } else if (rzs10thnew2021b_DW.is_c8_rzs10thnew2021b == 1) {
    if (rzs10thnew2021b_DW.run_flag == 0.0) {
      rzs10thnew2021b_DW.is_Flameout_Check = rzs10thnew20_IN_NO_ACTIVE_CHILD;
      rzs10thnew2021b_DW.is_c8_rzs10thnew2021b = rzs10thnew202_IN_Ignition_Check;
      rzs10thnew2021b_DW.is_Ignition_Check = rzs10thnew2021b_IN_begin;
      rzs10thnew2021b_DW.run_flag = 0.0;
    } else {
      switch (rzs10thnew2021b_DW.is_Flameout_Check) {
       case rzs10thnew2021b_IN_Checkoff:
        break;

       default:
        /* case IN_Run_Offcheck_Flag: */
        if (rzs10thnew2021b_DW.run_offcheck_flag == 0.0) {
          rzs10thnew2021b_DW.is_Flameout_Check = rzs10thnew_IN_Run_Offcheck_Flag;
        } else {
          rzs10thnew2021b_DW.is_Flameout_Check = rzs10thnew2021b_IN_Checkoff;
          rzs10thnew2021b_DW.run_flag = 0.0;
          run = F;
        }
        break;
      }
    }

    /* case IN_Ignition_Check: */
  } else if (rzs10thnew2021b_DW.run_flag == 1.0) {
    rzs10thnew2021b_DW.is_Ignition_Check = rzs10thnew20_IN_NO_ACTIVE_CHILD;
    rzs10thnew2021b_DW.is_c8_rzs10thnew2021b = rzs10thnew202_IN_Flameout_Check;
    rzs10thnew2021b_DW.is_Flameout_Check = rzs10thnew_IN_Run_Offcheck_Flag;
  } else {
    switch (rzs10thnew2021b_DW.is_Ignition_Check) {
     case rzs10thnew2021b_IN_Check:
      if (rzs10thnew2021b_DW.run_check_flag == 0.0) {
        rzs10thnew2021b_DW.is_Ignition_Check = rzs10thnew202_IN_Run_Check_Flag;
        rzs10thnew2021b_DW.run_check_flag = 0.0;
      } else if (rzs10thnew2021b_DW.run_check_flag == 1.0) {
        rzs10thnew2021b_DW.is_Ignition_Check = rzs10thnew2021b_IN_Check;
        rzs10thnew2021b_DW.run_flag = 1.0;
        run = T;
      }
      break;

     case rzs10thnew202_IN_Run_Check_Flag:
      if (rzs10thnew2021b_DW.run_check_flag == 0.0) {
        rzs10thnew2021b_DW.is_Ignition_Check = rzs10thnew202_IN_Run_Check_Flag;
        rzs10thnew2021b_DW.run_check_flag = 0.0;
      } else if (rzs10thnew2021b_DW.run_check_flag == 1.0) {
        rzs10thnew2021b_DW.is_Ignition_Check = rzs10thnew2021b_IN_Check;
        rzs10thnew2021b_DW.run_flag = 1.0;
        run = T;
      }
      break;

     default:
      /* case IN_begin: */
      rzs10thnew2021b_DW.is_Ignition_Check = rzs10thnew202_IN_Run_Check_Flag;
      rzs10thnew2021b_DW.run_check_flag = 0.0;
      break;
    }
  }

  /* End of Chart: '<S14>/Chart1' */

  /* Chart: '<S14>/Chart2' */
  elapsedTicks_h = rzs10thnew2021b_M->Timing.clockTick1 -
    rzs10thnew2021b_DW.previousTicks_l;
  rzs10thnew2021b_DW.previousTicks_l = rzs10thnew2021b_M->Timing.clockTick1;
  if (rzs10thnew2021b_DW.temporalCounter_i1_i + elapsedTicks_h <= 255U) {
    rzs10thnew2021b_DW.temporalCounter_i1_i = (uint8_T)
      (rzs10thnew2021b_DW.temporalCounter_i1_i + elapsedTicks_h);
  } else {
    rzs10thnew2021b_DW.temporalCounter_i1_i = MAX_uint8_T;
  }

  if (rzs10thnew2021b_DW.is_active_c9_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c9_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c9_rzs10thnew2021b = rzs10thnew2021b_IN_begin_b;
  } else if (rzs10thnew2021b_DW.is_c9_rzs10thnew2021b == 1) {
    rzs10thnew2021b_B.ts = 0.0;

    /* case IN_delay: */
  } else if (rzs10thnew2021b_DW.temporalCounter_i1_i >= 200U) {
    rzs10thnew2021b_B.ts_warning = F;
    rzs10thnew2021b_B.ts = 0.0;
  }

  /* End of Chart: '<S14>/Chart2' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms1' */

  /* DataStoreWrite: '<Root>/Data Store Write6' */
  rzs10thnew2021b_DW.ts = rzs10thnew2021b_B.ts;

  /* S-Function (fcgen): '<Root>/10ms12' incorporates:
   *  SubSystem: '<Root>/Buzzer'
   */
  /* Inport: '<S5>/r2d_warning' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read3'
   */
  r2d_buzzer = rzs10thnew2021b_DW.r2d_warning;

  /* Chart: '<S5>/Chart' incorporates:
   *  DataStoreWrite: '<S4>/Data Store Write3'
   */
  elapsedTicks_h = rzs10thnew2021b_M->Timing.clockTick1 -
    rzs10thnew2021b_DW.previousTicks_dy;
  rzs10thnew2021b_DW.previousTicks_dy = rzs10thnew2021b_M->Timing.clockTick1;
  if (rzs10thnew2021b_DW.temporalCounter_i1_j + elapsedTicks_h <= 1023U) {
    rzs10thnew2021b_DW.temporalCounter_i1_j = (uint16_T)
      (rzs10thnew2021b_DW.temporalCounter_i1_j + elapsedTicks_h);
  } else {
    rzs10thnew2021b_DW.temporalCounter_i1_j = 1023U;
  }

  if (rzs10thnew2021b_DW.is_active_c11_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c11_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c11_rzs10thnew2021b = rzs10thnew2021b_IN_Default;
    LogicalOperator = F;
  } else if (rzs10thnew2021b_DW.is_c11_rzs10thnew2021b == 1) {
    LogicalOperator = F;

    /* S-Function (fcgen): '<Root>/10ms6' incorporates:
     *  SubSystem: '<Root>/AS_Stateflow'
     */
    if (rzs10thnew2021b_B.as_emergency_flag_e == 1.0) {
      rzs10thnew2021b_DW.is_c11_rzs10thnew2021b = rzs10thnew2021b_IN_Emergency;
      rzs10thnew2021b_DW.temporalCounter_i1_j = 0U;
      LogicalOperator = T;
    }

    /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
  } else {
    /* case IN_Emergency: */
    LogicalOperator = T;
    if (rzs10thnew2021b_DW.temporalCounter_i1_j >= 900U) {
      rzs10thnew2021b_DW.is_c11_rzs10thnew2021b = rzs10thnew2021b_IN_Default;
      LogicalOperator = F;
    }
  }

  /* End of Chart: '<S5>/Chart' */

  /* DiscretePulseGenerator: '<S5>/Pulse Generator' */
  rtb_mode = ((rzs10thnew2021b_DW.clockTickCounter_l < 50) &&
              (rzs10thnew2021b_DW.clockTickCounter_l >= 0));
  if (rzs10thnew2021b_DW.clockTickCounter_l >= 99) {
    rzs10thnew2021b_DW.clockTickCounter_l = 0;
  } else {
    rzs10thnew2021b_DW.clockTickCounter_l++;
  }

  /* End of DiscretePulseGenerator: '<S5>/Pulse Generator' */

  /* Switch: '<S5>/Switch' */
  if (LogicalOperator) {
    /* Switch: '<S5>/Switch' incorporates:
     *  DataTypeConversion: '<S5>/Data Type Conversion6'
     */
    ebs_buzzer = (rtb_mode != 0);
  } else {
    /* Switch: '<S5>/Switch' incorporates:
     *  Constant: '<S5>/Constant'
     */
    ebs_buzzer = false;
  }

  /* End of Switch: '<S5>/Switch' */

  /* Inport: '<S5>/ts_warning' */
  ts_buzzer = rzs10thnew2021b_B.ts_warning;

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms12' */

  /* DataStoreWrite: '<Root>/Data Store Write7' */
  rzs10thnew2021b_DW.ebs_warning = ebs_buzzer;

  /* DataStoreWrite: '<Root>/Data Store Write8' */
  rzs10thnew2021b_DW.r2d_warning = rzs10thnew2021b_B.r2d_warning;

  /* DataStoreWrite: '<Root>/Data Store Write9' */
  rzs10thnew2021b_DW.steer_return = rzs10thnew2021b_B.steer_return;
  for (rtb_mode = 0; rtb_mode < 8; rtb_mode++) {
    /* Delay: '<Root>/Delay' */
    ESP_R_00[rtb_mode] = rzs10thnew2021b_DW.Delay_DSTATE[rtb_mode];
  }

  /* S-Function (fcgen): '<Root>/10ms7' incorporates:
   *  SubSystem: '<Root>/EBS'
   */
  /* Outputs for Enabled SubSystem: '<S46>/POSITIVE Edge' */
  /* DataStoreRead: '<Root>/Data Store Read1' incorporates:
   *  UnitDelay: '<S46>/Unit Delay'
   */
  rzs10thnew2021_POSITIVEEdge(rzs10thnew2021b_ConstB.MultiportSwitch[0],
    rzs10thnew2021b_DW.asb_check, rzs10thnew2021b_DW.UnitDelay_DSTATE,
    &rzs10thnew2021b_B.RelationalOperator1_h);

  /* End of Outputs for SubSystem: '<S46>/POSITIVE Edge' */

  /* Outputs for Enabled SubSystem: '<S46>/NEGATIVE Edge' */
  rzs10thnew2021_NEGATIVEEdge(rzs10thnew2021b_ConstB.MultiportSwitch[1],
    rzs10thnew2021b_DW.asb_check, rzs10thnew2021b_DW.UnitDelay_DSTATE,
    &rzs10thnew2021b_B.RelationalOperator1_n);

  /* End of Outputs for SubSystem: '<S46>/NEGATIVE Edge' */

  /* Outputs for Enabled SubSystem: '<S49>/POSITIVE Edge' */
  /* UnitDelay: '<S49>/Unit Delay' */
  rzs10thnew2021_POSITIVEEdge(rzs10thnew2021b_ConstB.MultiportSwitch_n[0],
    rtb_xor_consequence, rzs10thnew2021b_DW.UnitDelay_DSTATE_h,
    &rzs10thnew2021b_B.RelationalOperator1_i);

  /* End of Outputs for SubSystem: '<S49>/POSITIVE Edge' */

  /* Outputs for Enabled SubSystem: '<S49>/NEGATIVE Edge' */
  rzs10thnew2021_NEGATIVEEdge(rzs10thnew2021b_ConstB.MultiportSwitch_n[1],
    rtb_xor_consequence, rzs10thnew2021b_DW.UnitDelay_DSTATE_h,
    &rzs10thnew2021b_B.RelationalOperator1_c);

  /* End of Outputs for SubSystem: '<S49>/NEGATIVE Edge' */

  /* Outputs for Enabled SubSystem: '<S52>/POSITIVE Edge' */
  /* S-Function (fcgen): '<Root>/10ms11' incorporates:
   *  SubSystem: '<Root>/IPC'
   */
  /* DataTypeConversion: '<S173>/Data Type Conversion3' incorporates:
   *  UnitDelay: '<S52>/Unit Delay'
   */
  rzs10thnew2021_POSITIVEEdge(rzs10thnew2021b_ConstB.MultiportSwitch_p[0],
    rtb_y_ao != 0, rzs10thnew2021b_DW.UnitDelay_DSTATE_f,
    &rzs10thnew2021b_B.RelationalOperator1);

  /* End of Outputs for SubSystem: '<S52>/POSITIVE Edge' */

  /* Outputs for Enabled SubSystem: '<S52>/NEGATIVE Edge' */
  rzs10thnew2021_NEGATIVEEdge(rzs10thnew2021b_ConstB.MultiportSwitch_p[1],
    rtb_y_ao != 0, rzs10thnew2021b_DW.UnitDelay_DSTATE_f,
    &rzs10thnew2021b_B.RelationalOperator1_k);

  /* End of Outputs for SubSystem: '<S52>/NEGATIVE Edge' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */

  /* Logic: '<S6>/Logical Operator' incorporates:
   *  Logic: '<S46>/Logical Operator1'
   *  Logic: '<S49>/Logical Operator1'
   *  Logic: '<S52>/Logical Operator1'
   */
  ebs_trig = (rzs10thnew2021b_B.RelationalOperator1_h ||
              rzs10thnew2021b_B.RelationalOperator1_n ||
              (rzs10thnew2021b_B.RelationalOperator1_i ||
               rzs10thnew2021b_B.RelationalOperator1_c) ||
              (rzs10thnew2021b_B.RelationalOperator1 ||
               rzs10thnew2021b_B.RelationalOperator1_k) ||
              (rzs10thnew2021b_B.as_ebs_trig != 0.0));

  /* DiscretePulseGenerator: '<S6>/Pulse Generator' */
  rtb_mode = ((rzs10thnew2021b_DW.clockTickCounter < 5) &&
              (rzs10thnew2021b_DW.clockTickCounter >= 0));
  if (rzs10thnew2021b_DW.clockTickCounter >= 9) {
    rzs10thnew2021b_DW.clockTickCounter = 0;
  } else {
    rzs10thnew2021b_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<S6>/Pulse Generator' */

  /* DataTypeConversion: '<S6>/Data Type Conversion5' */
  ebs_watchdog = (rtb_mode != 0);

  /* Update for UnitDelay: '<S46>/Unit Delay' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read1'
   */
  rzs10thnew2021b_DW.UnitDelay_DSTATE = rzs10thnew2021b_DW.asb_check;

  /* Update for UnitDelay: '<S49>/Unit Delay' */
  rzs10thnew2021b_DW.UnitDelay_DSTATE_h = rtb_xor_consequence;

  /* S-Function (fcgen): '<Root>/10ms11' incorporates:
   *  SubSystem: '<Root>/IPC'
   */
  /* Update for UnitDelay: '<S52>/Unit Delay' incorporates:
   *  DataTypeConversion: '<S173>/Data Type Conversion3'
   */
  rzs10thnew2021b_DW.UnitDelay_DSTATE_f = (rtb_y_ao != 0);

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms7' */

  /* S-Function (fcgen): '<Root>/10ms4' incorporates:
   *  SubSystem: '<Root>/Motor_Control'
   */
  /* Outputs for Enabled SubSystem: '<S11>/AS_Torque_Calculation' incorporates:
   *  EnablePort: '<S214>/Enable'
   */
  if (Switch_e) {
    /* S-Function (fcgen): '<Root>/10ms11' incorporates:
     *  SubSystem: '<Root>/IPC'
     */
    /* Sum: '<S172>/Add4' incorporates:
     *  Constant: '<S172>/Constant'
     *  DataTypeConversion: '<S172>/Data Type Conversion6'
     *  Inport: '<Root>/canb_ipctsmsg1'
     */
    rzs10thnew2021b_B.DataTypeConversion = ((real_T)canb_ipctsmsg1[6] +
      rzs10thnew2021b_B.DataTypeConversion1) - 5000.0;

    /* End of Outputs for S-Function (fcgen): '<Root>/10ms11' */

    /* Saturate: '<S214>/Saturation' */
    if (rzs10thnew2021b_B.DataTypeConversion > 55.0) {
      /* Sum: '<S172>/Add4' incorporates:
       *  DataTypeConversion: '<S214>/Data Type Conversion'
       */
      rzs10thnew2021b_B.DataTypeConversion = 55.0;
    } else if (rzs10thnew2021b_B.DataTypeConversion < 0.0) {
      /* Sum: '<S172>/Add4' incorporates:
       *  DataTypeConversion: '<S214>/Data Type Conversion'
       */
      rzs10thnew2021b_B.DataTypeConversion = 0.0;
    }

    /* End of Saturate: '<S214>/Saturation' */
  }

  /* End of Outputs for SubSystem: '<S11>/AS_Torque_Calculation' */

  /* DataTypeConversion: '<S215>/Data Type Conversion2' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read15'
   */
  rzs10thnew2021b_B.d = floor(rzs10thnew2021b_DW.ts);
  if (rtIsNaN(rzs10thnew2021b_B.d) || rtIsInf(rzs10thnew2021b_B.d)) {
    rzs10thnew2021b_B.d = 0.0;
  } else {
    rzs10thnew2021b_B.d = fmod(rzs10thnew2021b_B.d, 256.0);
  }

  rtb_y_ao = (uint8_T)(rzs10thnew2021b_B.d < 0.0 ? (int32_T)(uint8_T)-(int8_T)
                       (uint8_T)-rzs10thnew2021b_B.d : (int32_T)(uint8_T)
                       rzs10thnew2021b_B.d);

  /* End of DataTypeConversion: '<S215>/Data Type Conversion2' */

  /* S-Function (sfix_bitop): '<S215>/Bitwise AND' */
  res_heartbeat_prev = (uint8_T)(rtb_y_ao & 1);

  /* Outputs for Atomic SubSystem: '<S215>/Bit Shift' */
  rzs10thnew2021b_BitShift_g(rzs10thnew2021b_ConstB.BitwiseAND1_o, &rtb_y_hwh);

  /* End of Outputs for SubSystem: '<S215>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S215>/Bit Shift1' */
  rzs10thnew2021_BitShift1_kp(rzs10thnew2021b_ConstB.BitwiseAND2_l, &rtb_y_dn);

  /* End of Outputs for SubSystem: '<S215>/Bit Shift1' */

  /* Outputs for Atomic SubSystem: '<S215>/Bit Shift2' */
  rzs10thnew2021b_BitShift2_o(rzs10thnew2021b_ConstB.BitwiseAND3_i, &rtb_y_ip);

  /* End of Outputs for SubSystem: '<S215>/Bit Shift2' */

  /* Outputs for Atomic SubSystem: '<S215>/Bit Shift3' */
  rzs10thnew2021b_BitShift3_p(rzs10thnew2021b_ConstB.BitwiseAND4, &rtb_y_ao);

  /* End of Outputs for SubSystem: '<S215>/Bit Shift3' */

  /* Outputs for Atomic SubSystem: '<S215>/Bit Shift4' */
  rzs10thnew2021b_BitShift4_j(rzs10thnew2021b_ConstB.BitwiseAND5,
    &rtb_MCU1_Rx_Command3byte3);

  /* End of Outputs for SubSystem: '<S215>/Bit Shift4' */

  /* Outputs for Enabled SubSystem: '<S11>/Manual_Torque_Calculation' incorporates:
   *  EnablePort: '<S217>/Enable'
   */
  /* S-Function (fcgen): '<Root>/10ms6' incorporates:
   *  SubSystem: '<Root>/AS_Stateflow'
   */
  /* DataStoreWrite: '<S4>/Data Store Write2' */
  if (rzs10thnew2021b_B.manual_driving_flag_k > 0.0) {
    /* Chart: '<S217>/Pedal_Fault_Check' */
    if (apps1 - apps2 >= 0.1) {
      rzs10thnew2021b_DW.fault_count++;
      if (rzs10thnew2021b_DW.fault_count >= 3.0) {
        rzs10thnew2021b_B.pedal_error = 1.0;
      }
    } else {
      rzs10thnew2021b_DW.fault_count = 0.0;
      rzs10thnew2021b_B.pedal_error = 0.0;
    }

    /* End of Chart: '<S217>/Pedal_Fault_Check' */

    /* Switch: '<S217>/Switch' incorporates:
     *  Logic: '<S217>/Logical Operator'
     */
    if (!(rzs10thnew2021b_B.pedal_error != 0.0)) {
      /* Switch: '<S217>/Switch' incorporates:
       *  Constant: '<S217>/Constant'
       *  Constant: '<S217>/max_torque'
       *  Product: '<S217>/Divide'
       *  Product: '<S217>/Product'
       *  Sum: '<S217>/Add'
       */
      rzs10thnew2021b_B.Switch = (real_T)(apps1 + apps2) / 2.0 * 50.0;
    } else {
      /* Switch: '<S217>/Switch' incorporates:
       *  Constant: '<S217>/Constant1'
       */
      rzs10thnew2021b_B.Switch = 0.0;
    }

    /* End of Switch: '<S217>/Switch' */
  }

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
  /* End of Outputs for SubSystem: '<S11>/Manual_Torque_Calculation' */

  /* Chart: '<S11>/Motor_Torque_Stateflow' incorporates:
   *  DataStoreWrite: '<S4>/Data Store Write2'
   */
  if (rzs10thnew2021b_DW.is_active_c4_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c4_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c4_rzs10thnew2021b = rzs10thnew2021b_IN_Default_n;
    rzs10thnew2021b_B.motor_torque = 0.0;
  } else {
    switch (rzs10thnew2021b_DW.is_c4_rzs10thnew2021b) {
     case rzs10thnew2021b_IN_AS_Driving:
      if (!Switch_e) {
        rzs10thnew2021b_DW.is_c4_rzs10thnew2021b = rzs10thnew2021b_IN_Default_n;
        rzs10thnew2021b_B.motor_torque = 0.0;
      }
      break;

     case rzs10thnew2021b_IN_Default_n:
      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      if (rzs10thnew2021b_B.manual_driving_flag_k == 1.0) {
        rzs10thnew2021b_DW.is_c4_rzs10thnew2021b =
          rzs10thnew202_IN_Manual_Driving;
        rzs10thnew2021b_B.motor_torque = rzs10thnew2021b_B.Switch;
      } else if (Switch_e) {
        rzs10thnew2021b_DW.is_c4_rzs10thnew2021b = rzs10thnew2021b_IN_AS_Driving;
        rzs10thnew2021b_B.motor_torque = rzs10thnew2021b_B.DataTypeConversion;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;

     default:
      /* S-Function (fcgen): '<Root>/10ms6' incorporates:
       *  SubSystem: '<Root>/AS_Stateflow'
       */
      /* case IN_Manual_Driving: */
      if (rzs10thnew2021b_B.manual_driving_flag_k == 0.0) {
        rzs10thnew2021b_DW.is_c4_rzs10thnew2021b = rzs10thnew2021b_IN_Default_n;
        rzs10thnew2021b_B.motor_torque = 0.0;
      }

      /* End of Outputs for S-Function (fcgen): '<Root>/10ms6' */
      break;
    }
  }

  /* End of Chart: '<S11>/Motor_Torque_Stateflow' */

  /* DataTypeConversion: '<S215>/Data Type Conversion7' */
  rzs10thnew2021b_B.d = floor(rzs10thnew2021b_B.motor_torque);
  if (rtIsNaN(rzs10thnew2021b_B.d) || rtIsInf(rzs10thnew2021b_B.d)) {
    rzs10thnew2021b_B.d = 0.0;
  } else {
    rzs10thnew2021b_B.d = fmod(rzs10thnew2021b_B.d, 65536.0);
  }

  /* Sum: '<S215>/Add1' incorporates:
   *  Constant: '<S215>/constant'
   *  DataTypeConversion: '<S215>/Data Type Conversion7'
   */
  rtb_y_my = (uint16_T)((rzs10thnew2021b_B.d < 0.0 ? (int32_T)(uint16_T)
    -(int16_T)(uint16_T)-rzs10thnew2021b_B.d : (int32_T)(uint16_T)
    rzs10thnew2021b_B.d) + 5000U);

  /* Outputs for Atomic SubSystem: '<S215>/Bit Shift5' */
  rzs10thnew2021b_BitShift5(rzs10thnew2021b_ConstB.BitwiseAND7, &rtb_Add2_i);

  /* End of Outputs for SubSystem: '<S215>/Bit Shift5' */

  /* Outputs for Atomic SubSystem: '<S215>/Bit Shift6' */
  rzs10thnew2021b_BitShift6(rzs10thnew2021b_ConstB.BitwiseAND8, &rtb_y_ap);

  /* End of Outputs for SubSystem: '<S215>/Bit Shift6' */

  /* Sum: '<S215>/Add3' */
  rtb_y_ci = (uint16_T)((uint32_T)rtb_Add2_i + rtb_y_ap);

  /* Outputs for Atomic SubSystem: '<S215>/Bit Shift7' */
  rzs10thnew2021b_BitShift7(rzs10thnew2021b_ConstB.BitwiseAND9, &rtb_y_ap);

  /* End of Outputs for SubSystem: '<S215>/Bit Shift7' */

  /* Outputs for Atomic SubSystem: '<S215>/Bit Shift8' */
  /* S-Function (sfix_bitop): '<S215>/Bitwise AND11' */
  rzs10thnew2021b_BitShift5((uint16_T)(rtb_y_my & 65280), &rtb_Add2_i);

  /* End of Outputs for SubSystem: '<S215>/Bit Shift8' */

  /* Outputs for Atomic SubSystem: '<S215>/Bit Shift9' */
  rzs10thnew2021b_BitShift5(rzs10thnew2021b_ConstB.BitwiseAND13,
    &rtb_ebs_drivercheck);

  /* End of Outputs for SubSystem: '<S215>/Bit Shift9' */

  /* S-Function (sfix_bitop): '<S215>/Bitwise AND10' */
  rtb_y_my = (uint16_T)(rtb_y_my & 255);

  /* SignalConversion generated from: '<Root>/Delay1' incorporates:
   *  DataTypeConversion: '<S215>/Data Type Conversion12'
   *  DataTypeConversion: '<S215>/Data Type Conversion14'
   */
  rzs10thnew2021b_B.TmpSignalConversionAtDelay1[2] = (uint8_T)rtb_y_ci;
  rzs10thnew2021b_B.TmpSignalConversionAtDelay1[4] = (uint8_T)rtb_y_my;

  /* Outputs for Atomic SubSystem: '<S216>/Bit Shift' */
  rzs10thnew2021b_BitShift5(rzs10thnew2021b_ConstB.BitwiseAND1, &rtb_y_ci);

  /* End of Outputs for SubSystem: '<S216>/Bit Shift' */

  /* Outputs for Atomic SubSystem: '<S216>/Bit Shift1' */
  rzs10thnew2021b_BitShift5(rzs10thnew2021b_ConstB.BitwiseAND3, &rtb_y_my);

  /* End of Outputs for SubSystem: '<S216>/Bit Shift1' */

  /* SignalConversion generated from: '<S11>/cana_motor_cmd3' incorporates:
   *  Constant: '<S216>/constant'
   *  DataTypeConversion: '<S216>/Data Type Conversion3'
   *  DataTypeConversion: '<S216>/Data Type Conversion6'
   */
  rzs10thnew2021b_B.OutportBufferForcana_motor_cmd3[0] =
    rzs10thnew2021b_ConstB.MCU1_Rx_Command3byte0;
  rzs10thnew2021b_B.OutportBufferForcana_motor_cmd3[1] = (uint8_T)rtb_y_ci;
  rzs10thnew2021b_B.OutportBufferForcana_motor_cmd3[2] =
    rzs10thnew2021b_ConstB.MCU1_Rx_Command3byte2;
  rzs10thnew2021b_B.OutportBufferForcana_motor_cmd3[3] = (uint8_T)rtb_y_my;
  rzs10thnew2021b_B.OutportBufferForcana_motor_cmd3[4] = 0U;
  rzs10thnew2021b_B.OutportBufferForcana_motor_cmd3[5] = 0U;
  rzs10thnew2021b_B.OutportBufferForcana_motor_cmd3[6] = 0U;
  rzs10thnew2021b_B.OutportBufferForcana_motor_cmd3[7] = 0U;

  /* SignalConversion generated from: '<Root>/Delay1' incorporates:
   *  DataTypeConversion: '<S215>/Data Type Conversion11'
   *  DataTypeConversion: '<S215>/Data Type Conversion13'
   *  DataTypeConversion: '<S215>/Data Type Conversion15'
   *  DataTypeConversion: '<S215>/Data Type Conversion16'
   *  DataTypeConversion: '<S215>/Data Type Conversion17'
   *  Sum: '<S215>/Add'
   */
  rzs10thnew2021b_B.TmpSignalConversionAtDelay1[0] = (uint8_T)((uint32_T)
    (uint8_T)((uint32_T)(uint8_T)((uint32_T)(uint8_T)((uint32_T)(uint8_T)
    ((uint32_T)res_heartbeat_prev + rtb_y_hwh) + rtb_y_dn) + rtb_y_ip) +
              rtb_y_ao) + rtb_MCU1_Rx_Command3byte3);
  rzs10thnew2021b_B.TmpSignalConversionAtDelay1[1] = (uint8_T)
    rzs10thnew2021b_ConstB.BitwiseAND6;
  rzs10thnew2021b_B.TmpSignalConversionAtDelay1[3] = (uint8_T)rtb_y_ap;
  rzs10thnew2021b_B.TmpSignalConversionAtDelay1[5] = (uint8_T)rtb_Add2_i;
  rzs10thnew2021b_B.TmpSignalConversionAtDelay1[6] = (uint8_T)
    rzs10thnew2021b_ConstB.BitwiseAND12;
  rzs10thnew2021b_B.TmpSignalConversionAtDelay1[7] = (uint8_T)
    rtb_ebs_drivercheck;

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms4' */

  /* Delay: '<Root>/Delay1' */
  cana_motor_cmd[0] = rzs10thnew2021b_DW.Delay1_DSTATE;

  /* Delay: '<Root>/Delay2' */
  cana_motor_cmd3[0] = rzs10thnew2021b_DW.Delay2_DSTATE;
  for (rtb_mode = 0; rtb_mode < 7; rtb_mode++) {
    /* Delay: '<Root>/Delay1' */
    cana_motor_cmd[rtb_mode + 1] =
      rzs10thnew2021b_B.TmpSignalConversionAtDelay1[rtb_mode];

    /* Delay: '<Root>/Delay2' */
    cana_motor_cmd3[rtb_mode + 1] =
      rzs10thnew2021b_B.OutportBufferForcana_motor_cmd3[rtb_mode];
  }

  /* Outputs for Atomic SubSystem: '<S15>/Bit Shift2' */
  /* MATLAB Function: '<S269>/bit_shift' incorporates:
   *  Inport: '<Root>/Input'
   *  S-Function (sfix_bitop): '<S15>/Bitwise AND1'
   */
  rtb_Add2_i = (uint16_T)((uint32_T)(digital_input.io_in & 2) >> 1);

  /* End of Outputs for SubSystem: '<S15>/Bit Shift2' */

  /* S-Function (fcgen): '<Root>/10ms2' incorporates:
   *  SubSystem: '<Root>/LED_Control'
   */
  /* Inport: '<S10>/brake_on' incorporates:
   *  DataStoreRead: '<Root>/Data Store Read13'
   */
  led_brake = rzs10thnew2021b_DW.brake_on;

  /* Chart: '<S197>/Shutdown_Button' */
  elapsedTicks_h = rzs10thnew2021b_M->Timing.clockTick1 -
    rzs10thnew2021b_DW.previousTicks_c;
  rzs10thnew2021b_DW.previousTicks_c = rzs10thnew2021b_M->Timing.clockTick1;
  if (rzs10thnew2021b_DW.temporalCounter_i1_e + elapsedTicks_h <= 127U) {
    rzs10thnew2021b_DW.temporalCounter_i1_e = (uint8_T)
      (rzs10thnew2021b_DW.temporalCounter_i1_e + elapsedTicks_h);
  } else {
    rzs10thnew2021b_DW.temporalCounter_i1_e = 127U;
  }

  if (rzs10thnew2021b_DW.is_active_c17_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c17_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c17_rzs10thnew2021b = rzs10thnew2021b_IN_begin_b;
    rzs10thnew2021b_DW.temporalCounter_i1_e = 0U;
  } else {
    switch (rzs10thnew2021b_DW.is_c17_rzs10thnew2021b) {
     case rzs10thnew2021b_IN_begin_b:
      if ((rzs10thnew2021b_DW.temporalCounter_i1_e >= 100U) && (rtb_Add2_i == 0))
      {
        rzs10thnew2021b_DW.is_c17_rzs10thnew2021b = rzs10thnew2021b_IN_same1;
        rzs10thnew2021b_B.shutdown_flag = T;
      }
      break;

     case rzs10thnew2021b_IN_compare:
      if (rzs10thnew2021b_DW.shutdown_count > 10.0) {
        rzs10thnew2021b_DW.is_c17_rzs10thnew2021b = rzs10thnew2021b_IN_judge;
        rzs10thnew2021b_B.shutdown_flag = F;
      } else if (rtb_Add2_i == 0) {
        rzs10thnew2021b_DW.shutdown_count = 0.0;
        rzs10thnew2021b_DW.is_c17_rzs10thnew2021b = rzs10thnew2021b_IN_same1;
        rzs10thnew2021b_B.shutdown_flag = T;
      } else {
        rzs10thnew2021b_DW.shutdown_count++;
      }
      break;

     case rzs10thnew2021b_IN_judge:
      if (rtb_Add2_i == 0) {
        rzs10thnew2021b_DW.is_c17_rzs10thnew2021b = rzs10thnew2021b_IN_same1;
        rzs10thnew2021b_B.shutdown_flag = T;
      } else {
        rzs10thnew2021b_B.shutdown_flag = F;
      }
      break;

     default:
      /* case IN_same1: */
      if (rtb_Add2_i != 0) {
        rzs10thnew2021b_DW.is_c17_rzs10thnew2021b = rzs10thnew2021b_IN_compare;
        rzs10thnew2021b_DW.shutdown_count++;
      } else {
        rzs10thnew2021b_B.shutdown_flag = T;
      }
      break;
    }
  }

  /* End of Chart: '<S197>/Shutdown_Button' */

  /* Chart: '<S197>/display' */
  elapsedTicks_h = rzs10thnew2021b_M->Timing.clockTick1 -
    rzs10thnew2021b_DW.previousTicks_b;
  rzs10thnew2021b_DW.previousTicks_b = rzs10thnew2021b_M->Timing.clockTick1;
  if (rzs10thnew2021b_DW.temporalCounter_i1_g + elapsedTicks_h <= 255U) {
    rzs10thnew2021b_DW.temporalCounter_i1_g = (uint8_T)
      (rzs10thnew2021b_DW.temporalCounter_i1_g + elapsedTicks_h);
  } else {
    rzs10thnew2021b_DW.temporalCounter_i1_g = MAX_uint8_T;
  }

  if (rzs10thnew2021b_DW.is_active_c6_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c6_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c6_rzs10thnew2021b = rzs10thnew2021b_IN_begin_b;
    rzs10thnew2021b_DW.temporalCounter_i1_g = 0U;
    rtb_xor_consequence = T;
  } else if (rzs10thnew2021b_DW.is_c6_rzs10thnew2021b == 1) {
    if (rzs10thnew2021b_DW.temporalCounter_i1_g >= 200U) {
      rzs10thnew2021b_DW.is_c6_rzs10thnew2021b = rzs10thnew2021b_IN_end;
      rtb_xor_consequence = F;
    } else {
      rtb_xor_consequence = T;
    }
  } else {
    /* case IN_end: */
    rtb_xor_consequence = F;
  }

  /* End of Chart: '<S197>/display' */

  /* Logic: '<S197>/Logical Operator' incorporates:
   *  Constant: '<S202>/Constant'
   *  Constant: '<S203>/Constant'
   *  Constant: '<S205>/Constant'
   *  Constant: '<S206>/Constant'
   *  Constant: '<S207>/Constant'
   *  Constant: '<S208>/Constant'
   *  Logic: '<S197>/Logical Operator3'
   *  RelationalOperator: '<S202>/Compare'
   *  RelationalOperator: '<S203>/Compare'
   *  RelationalOperator: '<S205>/Compare'
   *  RelationalOperator: '<S206>/Compare'
   *  RelationalOperator: '<S207>/Compare'
   *  RelationalOperator: '<S208>/Compare'
   */
  led_ebs_error = ((airprs_sensor1 <= 0.11) || (rzs10thnew2021b_B.ipc_esp_rlprs <=
    0.5) || rzs10thnew2021b_B.In1 || ((rzs10thnew2021b_B.Product1 <= 0.11) ||
    (rzs10thnew2021b_B.ipc_esp_flprs <= 0.11) ||
    (rzs10thnew2021b_B.ipc_eps_frprs <= 0.11) || (rzs10thnew2021b_B.Product2 <=
    0.11)) || rtb_xor_consequence);

  /* Chart: '<S198>/blue' */
  elapsedTicks_h = rzs10thnew2021b_M->Timing.clockTick1 -
    rzs10thnew2021b_DW.previousTicks_g;
  rzs10thnew2021b_DW.previousTicks_g = rzs10thnew2021b_M->Timing.clockTick1;
  if (rzs10thnew2021b_DW.temporalCounter_i1_m + elapsedTicks_h <= 255U) {
    rzs10thnew2021b_DW.temporalCounter_i1_m = (uint8_T)
      (rzs10thnew2021b_DW.temporalCounter_i1_m + elapsedTicks_h);
  } else {
    rzs10thnew2021b_DW.temporalCounter_i1_m = MAX_uint8_T;
  }

  if (rzs10thnew2021b_DW.is_active_c13_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c13_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c13_rzs10thnew2021b = rzs10thnew2021b_IN_Delay;
    rzs10thnew2021b_DW.temporalCounter_i1_m = 0U;
    rtb_Add2_i = 60000U;
  } else {
    switch (rzs10thnew2021b_DW.is_c13_rzs10thnew2021b) {
     case rzs10thnew2021b_IN_Blink:
      rzs10thnew2021b_DW.is_c13_rzs10thnew2021b = rzs10thnew2021b_IN_Close;
      rtb_Add2_i = 0U;
      break;

     case rzs10thnew2021b_IN_Close:
      rtb_Add2_i = 0U;
      break;

     case rzs10thnew2021b_IN_Delay:
      rtb_Add2_i = 60000U;
      if (rzs10thnew2021b_DW.temporalCounter_i1_m >= 200U) {
        rzs10thnew2021b_DW.is_c13_rzs10thnew2021b = rzs10thnew2021b_IN_Node;
        rtb_Add2_i = 0U;
      }
      break;

     case rzs10thnew2021b_IN_Node:
      rtb_Add2_i = 0U;
      rzs10thnew2021b_DW.is_c13_rzs10thnew2021b = rzs10thnew2021b_IN_Close;
      break;

     default:
      /* case IN_On: */
      rzs10thnew2021b_DW.is_c13_rzs10thnew2021b = rzs10thnew2021b_IN_Close;
      rtb_Add2_i = 0U;
      break;
    }
  }

  /* End of Chart: '<S198>/blue' */

  /* DiscretePulseGenerator: '<S198>/Pulse Generator' */
  airprs_sensor1 = ((rzs10thnew2021b_DW.clockTickCounter_i < 50) &&
                    (rzs10thnew2021b_DW.clockTickCounter_i >= 0));
  if (rzs10thnew2021b_DW.clockTickCounter_i >= 99) {
    rzs10thnew2021b_DW.clockTickCounter_i = 0;
  } else {
    rzs10thnew2021b_DW.clockTickCounter_i++;
  }

  /* End of DiscretePulseGenerator: '<S198>/Pulse Generator' */

  /* Switch: '<S198>/Switch' incorporates:
   *  Constant: '<S198>/Constant'
   */
  if (rtb_Add2_i > 10) {
    apps1 = rtb_Add2_i;
  } else {
    apps1 = 0;
  }

  /* End of Switch: '<S198>/Switch' */

  /* Switch: '<S198>/Switch2' incorporates:
   *  Constant: '<S198>/Constant1'
   *  Constant: '<S198>/Constant2'
   *  Switch: '<S198>/Switch1'
   */
  if (apps1 > 40000) {
    airprs_sensor1 = 1;
  } else if (rtb_Add2_i <= 10) {
    airprs_sensor1 = 0;
  }

  /* End of Switch: '<S198>/Switch2' */

  /* DataTypeConversion: '<S198>/Data Type Conversion' */
  led_assi_blue = (airprs_sensor1 != 0);

  /* Chart: '<S199>/yellow' */
  elapsedTicks_h = rzs10thnew2021b_M->Timing.clockTick1 -
    rzs10thnew2021b_DW.previousTicks_n;
  rzs10thnew2021b_DW.previousTicks_n = rzs10thnew2021b_M->Timing.clockTick1;
  if (rzs10thnew2021b_DW.temporalCounter_i1_h + elapsedTicks_h <= 255U) {
    rzs10thnew2021b_DW.temporalCounter_i1_h = (uint8_T)
      (rzs10thnew2021b_DW.temporalCounter_i1_h + elapsedTicks_h);
  } else {
    rzs10thnew2021b_DW.temporalCounter_i1_h = MAX_uint8_T;
  }

  if (rzs10thnew2021b_DW.is_active_c14_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c14_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c14_rzs10thnew2021b = rzs10thnew2021b_IN_delay_g;
    rzs10thnew2021b_DW.temporalCounter_i1_h = 0U;
    rtb_Add2_i = 60000U;
  } else {
    switch (rzs10thnew2021b_DW.is_c14_rzs10thnew2021b) {
     case rzs10thnew2021b_IN_Blink:
      rzs10thnew2021b_DW.is_c14_rzs10thnew2021b = rzs10thnew2021b_IN_Close;
      rtb_Add2_i = 0U;
      break;

     case rzs10thnew2021b_IN_Close:
      rtb_Add2_i = 0U;
      break;

     case rzs10thnew2021b_IN_On:
      rzs10thnew2021b_DW.is_c14_rzs10thnew2021b = rzs10thnew2021b_IN_Close;
      rtb_Add2_i = 0U;
      break;

     case rzs10thnew2021b_IN_delay_g:
      rtb_Add2_i = 60000U;
      if (rzs10thnew2021b_DW.temporalCounter_i1_h >= 200U) {
        rzs10thnew2021b_DW.is_c14_rzs10thnew2021b = rzs10thnew2021b_IN_node;
        rtb_Add2_i = 0U;
      }
      break;

     default:
      /* case IN_node: */
      rtb_Add2_i = 0U;
      rzs10thnew2021b_DW.is_c14_rzs10thnew2021b = rzs10thnew2021b_IN_Close;
      break;
    }
  }

  /* End of Chart: '<S199>/yellow' */

  /* DiscretePulseGenerator: '<S199>/Pulse Generator' */
  airprs_sensor1 = ((rzs10thnew2021b_DW.clockTickCounter_o < 50) &&
                    (rzs10thnew2021b_DW.clockTickCounter_o >= 0));
  if (rzs10thnew2021b_DW.clockTickCounter_o >= 99) {
    rzs10thnew2021b_DW.clockTickCounter_o = 0;
  } else {
    rzs10thnew2021b_DW.clockTickCounter_o++;
  }

  /* End of DiscretePulseGenerator: '<S199>/Pulse Generator' */

  /* Switch: '<S199>/Switch' incorporates:
   *  Constant: '<S199>/Constant'
   */
  if (rtb_Add2_i > 10) {
    apps1 = rtb_Add2_i;
  } else {
    apps1 = 0;
  }

  /* End of Switch: '<S199>/Switch' */

  /* Switch: '<S199>/Switch2' incorporates:
   *  Constant: '<S199>/Constant1'
   *  Constant: '<S199>/Constant3'
   *  Switch: '<S199>/Switch1'
   */
  if (apps1 > 40000) {
    airprs_sensor1 = 1;
  } else if (rtb_Add2_i <= 10) {
    airprs_sensor1 = 0;
  }

  /* End of Switch: '<S199>/Switch2' */

  /* DataTypeConversion: '<S199>/Data Type Conversion' */
  led_assi_yellow = (airprs_sensor1 != 0);

  /* Chart: '<S196>/BMS_LED' incorporates:
   *  Inport: '<Root>/bms_error'
   */
  elapsedTicks_h = rzs10thnew2021b_M->Timing.clockTick1 -
    rzs10thnew2021b_DW.previousTicks_d;
  rzs10thnew2021b_DW.previousTicks_d = rzs10thnew2021b_M->Timing.clockTick1;
  if (rzs10thnew2021b_DW.temporalCounter_i1_d + elapsedTicks_h <= 255U) {
    rzs10thnew2021b_DW.temporalCounter_i1_d = (uint8_T)
      (rzs10thnew2021b_DW.temporalCounter_i1_d + elapsedTicks_h);
  } else {
    rzs10thnew2021b_DW.temporalCounter_i1_d = MAX_uint8_T;
  }

  if (rzs10thnew2021b_DW.is_active_c5_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c5_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c5_rzs10thnew2021b = rzs10thnew2021b_IN_delay;
    rzs10thnew2021b_DW.temporalCounter_i1_d = 0U;
    led_bms_error = T;
  } else {
    switch (rzs10thnew2021b_DW.is_c5_rzs10thnew2021b) {
     case rzs10thnew2021_IN_EBS_LED_Check:
      led_bms_error = F;
      if (bms_error) {
        rzs10thnew2021b_DW.is_c5_rzs10thnew2021b = rzs10thnew2021b_IN_EBS_LED_ON;
      }
      break;

     case rzs10thnew2021b_IN_EBS_LED_ON:
      led_bms_error = F;
      if (!bms_error) {
        rzs10thnew2021b_DW.is_c5_rzs10thnew2021b =
          rzs10thnew2021_IN_EBS_LED_Check;
      }
      break;

     default:
      /* case IN_delay: */
      led_bms_error = T;
      if (rzs10thnew2021b_DW.temporalCounter_i1_d >= 200U) {
        rzs10thnew2021b_DW.is_c5_rzs10thnew2021b =
          rzs10thnew2021_IN_EBS_LED_Check;
        led_bms_error = F;
      }
      break;
    }
  }

  /* End of Chart: '<S196>/BMS_LED' */

  /* Chart: '<S196>/IMD_LED' incorporates:
   *  Inport: '<Root>/imd_error'
   */
  elapsedTicks_h = rzs10thnew2021b_M->Timing.clockTick1 -
    rzs10thnew2021b_DW.previousTicks_a;
  rzs10thnew2021b_DW.previousTicks_a = rzs10thnew2021b_M->Timing.clockTick1;
  if (rzs10thnew2021b_DW.temporalCounter_i1_h1 + elapsedTicks_h <= 255U) {
    rzs10thnew2021b_DW.temporalCounter_i1_h1 = (uint8_T)
      (rzs10thnew2021b_DW.temporalCounter_i1_h1 + elapsedTicks_h);
  } else {
    rzs10thnew2021b_DW.temporalCounter_i1_h1 = MAX_uint8_T;
  }

  if (rzs10thnew2021b_DW.is_active_c12_rzs10thnew2021b == 0U) {
    rzs10thnew2021b_DW.is_active_c12_rzs10thnew2021b = 1U;
    rzs10thnew2021b_DW.is_c12_rzs10thnew2021b = rzs10thnew2021b_IN_delay;
    rzs10thnew2021b_DW.temporalCounter_i1_h1 = 0U;
    led_imd_error = T;
  } else {
    switch (rzs10thnew2021b_DW.is_c12_rzs10thnew2021b) {
     case rzs10thnew2021_IN_EBS_LED_Check:
      led_imd_error = F;
      if (imd_error) {
        rzs10thnew2021b_DW.is_c12_rzs10thnew2021b =
          rzs10thnew2021b_IN_EBS_LED_ON;
      }
      break;

     case rzs10thnew2021b_IN_EBS_LED_ON:
      led_imd_error = F;
      if (!imd_error) {
        rzs10thnew2021b_DW.is_c12_rzs10thnew2021b =
          rzs10thnew2021_IN_EBS_LED_Check;
      }
      break;

     default:
      /* case IN_delay: */
      led_imd_error = T;
      if (rzs10thnew2021b_DW.temporalCounter_i1_h1 >= 200U) {
        rzs10thnew2021b_DW.is_c12_rzs10thnew2021b =
          rzs10thnew2021_IN_EBS_LED_Check;
        led_imd_error = F;
      }
      break;
    }
  }

  /* End of Chart: '<S196>/IMD_LED' */
  /* End of Outputs for S-Function (fcgen): '<Root>/10ms2' */

  /* Outputs for Atomic SubSystem: '<S15>/Bit Shift9' */
  /* DataTypeConversion: '<S15>/Data Type Conversion8' */
  rzs10thnew2021b_BitShift_g((uint8_T)led_assi_blue, &rtb_y_ao);

  /* End of Outputs for SubSystem: '<S15>/Bit Shift9' */

  /* Outputs for Atomic SubSystem: '<S15>/Bit Shift11' */
  /* DataTypeConversion: '<S15>/Data Type Conversion2' */
  rzs10thnew2021b_BitShift10((uint8_T)led_ebs_error, &res_heartbeat_prev);

  /* End of Outputs for SubSystem: '<S15>/Bit Shift11' */

  /* Outputs for Atomic SubSystem: '<S15>/Bit Shift12' */
  /* DataTypeConversion: '<S15>/Data Type Conversion3' */
  rzs10thnew2021b_BitShift2((uint8_T)res_error, &rtb_y_hwh);

  /* End of Outputs for SubSystem: '<S15>/Bit Shift12' */

  /* Outputs for Atomic SubSystem: '<S15>/Bit Shift13' */
  /* DataTypeConversion: '<S15>/Data Type Conversion10' */
  rzs10thnew2021b_BitShift_g((uint8_T)led_bms_error, &rtb_y_dn);

  /* End of Outputs for SubSystem: '<S15>/Bit Shift13' */

  /* Outputs for Atomic SubSystem: '<S15>/Bit Shift14' */
  /* DataTypeConversion: '<S15>/Data Type Conversion11' */
  rzs10thnew2021_BitShift1_kp((uint8_T)led_imd_error, &rtb_y_ip);

  /* End of Outputs for SubSystem: '<S15>/Bit Shift14' */

  /* Outputs for Atomic SubSystem: '<S15>/Bit Shift16' */
  /* DataTypeConversion: '<S15>/Data Type Conversion13' */
  rzs10thnew2021b_BitShift2_o((uint8_T)run, &rtb_MCU1_Rx_Command3byte3);

  /* End of Outputs for SubSystem: '<S15>/Bit Shift16' */

  /* Outputs for Atomic SubSystem: '<S15>/Bit Shift18' */
  /* DataTypeConversion: '<S15>/Data Type Conversion15' */
  rzs10thnew2021b_BitShift3_p((uint8_T)ts_buzzer, &rtb_y_nr);

  /* End of Outputs for SubSystem: '<S15>/Bit Shift18' */

  /* Outputs for Atomic SubSystem: '<S15>/Bit Shift19' */
  /* DataTypeConversion: '<S15>/Data Type Conversion16' */
  rzs10thnew2021b_BitShift4_j((uint8_T)ebs_buzzer, &rtb_y_ar);

  /* End of Outputs for SubSystem: '<S15>/Bit Shift19' */

  /* Outputs for Atomic SubSystem: '<S15>/Bit Shift15' */
  /* Outputs for Atomic SubSystem: '<S15>/Bit Shift17' */
  /* Sum: '<S15>/Add1' incorporates:
   *  DataTypeConversion: '<S15>/Data Type Conversion12'
   *  DataTypeConversion: '<S15>/Data Type Conversion14'
   *  DataTypeConversion: '<S15>/Data Type Conversion9'
   *  MATLAB Function: '<S264>/bit_shift'
   *  MATLAB Function: '<S266>/bit_shift'
   */
  digital_output.HOUT = (uint8_T)((uint32_T)(uint8_T)((uint32_T)(uint8_T)
    ((uint32_T)(uint8_T)((uint32_T)(uint8_T)((uint32_T)(uint8_T)((uint32_T)
    (uint8_T)((uint32_T)ebs_trig + rtb_y_dn) + rtb_y_ip) + (di8 << 3)) +
    rtb_MCU1_Rx_Command3byte3) + (r2d_buzzer << 5)) + rtb_y_nr) + rtb_y_ar);

  /* End of Outputs for SubSystem: '<S15>/Bit Shift17' */
  /* End of Outputs for SubSystem: '<S15>/Bit Shift15' */

  /* BusCreator: '<S15>/Bus Creator' incorporates:
   *  DataTypeConversion: '<S15>/Data Type Conversion4'
   *  Sum: '<S15>/Add'
   */
  digital_output.OUT = (uint8_T)((uint32_T)(uint8_T)((uint32_T)(uint8_T)
    ((uint32_T)led_brake + rtb_y_ao) + res_heartbeat_prev) + rtb_y_hwh);

  /* S-Function (fcgen): '<Root>/10ms8' incorporates:
   *  SubSystem: '<Root>/ESP'
   */
  /* SignalConversion generated from: '<Root>/Delay' incorporates:
   *  DataTypeConversion: '<S151>/Data Type Conversion1'
   *  DataTypeConversion: '<S151>/Data Type Conversion13'
   *  DataTypeConversion: '<S151>/Data Type Conversion2'
   *  DataTypeConversion: '<S151>/Data Type Conversion4'
   *  DataTypeConversion: '<S151>/Data Type Conversion6'
   *  Delay: '<Root>/Delay'
   *  S-Function (sfix_bitop): '<S151>/Bitwise AND3'
   *  S-Function (sfix_bitop): '<S151>/Bitwise AND7'
   *  Sum: '<S151>/Add2'
   */
  rzs10thnew2021b_DW.Delay_DSTATE[0] = (uint8_T)rtb_y_jo;
  rzs10thnew2021b_DW.Delay_DSTATE[1] = (uint8_T)rtb_y_ir;
  rzs10thnew2021b_DW.Delay_DSTATE[2] = (uint8_T)(rtb_y_l & 255);
  rzs10thnew2021b_DW.Delay_DSTATE[3] = (uint8_T)rtb_y_k0;
  rzs10thnew2021b_DW.Delay_DSTATE[4] = (uint8_T)rtb_y_ju;
  rzs10thnew2021b_DW.Delay_DSTATE[5] = (uint8_T)(rtb_Add1_p & 255);
  rzs10thnew2021b_DW.Delay_DSTATE[6] = (uint8_T)((uint32_T)rtb_BitwiseAND_cd +
    rzs10thnew2021b_ConstB.BitwiseAND8_j);
  rzs10thnew2021b_DW.Delay_DSTATE[7] = 0U;

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms8' */

  /* S-Function (fcgen): '<Root>/10ms4' incorporates:
   *  SubSystem: '<Root>/Motor_Control'
   */
  /* Update for Delay: '<Root>/Delay1' incorporates:
   *  DataTypeConversion: '<S215>/Data Type Conversion17'
   */
  rzs10thnew2021b_DW.Delay1_DSTATE = (uint8_T)rtb_ebs_drivercheck;

  /* End of Outputs for S-Function (fcgen): '<Root>/10ms4' */

  /* Update for Delay: '<Root>/Delay2' */
  rzs10thnew2021b_DW.Delay2_DSTATE = 0U;

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.01, which is the step size
   * of the task. Size of "clockTick1" ensures timer will not overflow during the
   * application lifespan selected.
   */
  rzs10thnew2021b_M->Timing.clockTick1++;
}

/* Model initialize function */
void rzs10thnew2021b_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
  (rzs10thnew2021b_M)->Timing.TaskCounters.cLimit[0] = 1;
  (rzs10thnew2021b_M)->Timing.TaskCounters.cLimit[1] = 10;

  /* Enable for S-Function (fcgen): '<Root>/10ms6' incorporates:
   *  SubSystem: '<Root>/AS_Stateflow'
   */
  /* Enable for Chart: '<S4>/Chart' */
  rzs10thnew2021b_DW.previousTicks_i = rzs10thnew2021b_M->Timing.clockTick1;

  /* End of Enable for S-Function (fcgen): '<Root>/10ms6' */

  /* Enable for S-Function (fcgen): '<Root>/10ms9' incorporates:
   *  SubSystem: '<Root>/EPS'
   */
  /* Enable for Chart: '<S56>/EPS_Stateflow1' */
  rzs10thnew2021b_DW.previousTicks = rzs10thnew2021b_M->Timing.clockTick1;

  /* End of Enable for S-Function (fcgen): '<Root>/10ms9' */

  /* Enable for S-Function (fcgen): '<Root>/10ms1' incorporates:
   *  SubSystem: '<Root>/TS_Activation'
   */
  /* Enable for Chart: '<S14>/Chart2' */
  rzs10thnew2021b_DW.previousTicks_l = rzs10thnew2021b_M->Timing.clockTick1;

  /* End of Enable for S-Function (fcgen): '<Root>/10ms1' */

  /* Enable for S-Function (fcgen): '<Root>/10ms12' incorporates:
   *  SubSystem: '<Root>/Buzzer'
   */
  /* Enable for Chart: '<S5>/Chart' */
  rzs10thnew2021b_DW.previousTicks_dy = rzs10thnew2021b_M->Timing.clockTick1;

  /* End of Enable for S-Function (fcgen): '<Root>/10ms12' */

  /* Enable for S-Function (fcgen): '<Root>/10ms2' incorporates:
   *  SubSystem: '<Root>/LED_Control'
   */
  /* Enable for Chart: '<S197>/Shutdown_Button' */
  rzs10thnew2021b_DW.previousTicks_c = rzs10thnew2021b_M->Timing.clockTick1;

  /* Enable for Chart: '<S197>/display' */
  rzs10thnew2021b_DW.previousTicks_b = rzs10thnew2021b_M->Timing.clockTick1;

  /* Enable for Chart: '<S198>/blue' */
  rzs10thnew2021b_DW.previousTicks_g = rzs10thnew2021b_M->Timing.clockTick1;

  /* Enable for Chart: '<S199>/yellow' */
  rzs10thnew2021b_DW.previousTicks_n = rzs10thnew2021b_M->Timing.clockTick1;

  /* Enable for Chart: '<S196>/BMS_LED' */
  rzs10thnew2021b_DW.previousTicks_d = rzs10thnew2021b_M->Timing.clockTick1;

  /* Enable for Chart: '<S196>/IMD_LED' */
  rzs10thnew2021b_DW.previousTicks_a = rzs10thnew2021b_M->Timing.clockTick1;

  /* End of Enable for S-Function (fcgen): '<Root>/10ms2' */
}

/* Model terminate function */
void rzs10thnew2021b_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
