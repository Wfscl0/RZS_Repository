/*
 * File: rzs10thnew2021b_types.h
 *
 * Code generated for Simulink model 'rzs10thnew2021b'.
 *
 * Model version                  : 1.19
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Wed Apr 29 16:29:38 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_rzs10thnew2021b_types_h_
#define RTW_HEADER_rzs10thnew2021b_types_h_
#include "rtwtypes.h"

/* Model Code Variants */
#ifndef DEFINED_TYPEDEF_FOR_VCU_IN_PAR_
#define DEFINED_TYPEDEF_FOR_VCU_IN_PAR_

typedef struct {
  uint16_T adc_in[7];
  uint16_T io_in;
} VCU_IN_PAR;

#endif

#ifndef DEFINED_TYPEDEF_FOR_VCU_OUT_PAR_
#define DEFINED_TYPEDEF_FOR_VCU_OUT_PAR_

typedef struct {
  uint8_T OUT;
  uint8_T HOUT;
} VCU_OUT_PAR;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_Q4zT2QxgVMN4E6PagXjoBE_
#define DEFINED_TYPEDEF_FOR_struct_Q4zT2QxgVMN4E6PagXjoBE_

typedef struct {
  real_T steering_flag;
  real_T brake_flag;
  real_T manual_driving_flag;
  real_T as_emergency_flag;
  real_T ebs_system_flag;
  real_T as_off_flag;
  real_T as_ready_flag;
  real_T as_driving_flag;
  real_T as_finished_flag;
  real_T r2d_flag;
  real_T ts_flag;
} struct_Q4zT2QxgVMN4E6PagXjoBE;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_0t74Q1hpMIPrZ9wpfvA4OC_
#define DEFINED_TYPEDEF_FOR_struct_0t74Q1hpMIPrZ9wpfvA4OC_

typedef struct {
  boolean_T ctlSts_pivRR;
  boolean_T ctlSts_pivRL;
  boolean_T ctlSts_pivFL;
  boolean_T ctlSts_pivFR;
  boolean_T ctlSts_psvFRRL;
  boolean_T ctlSts_psvFLRR;
  boolean_T ctlSts_plvFRRL;
  boolean_T ctlSts_plvFLRR;
  uint8_T ctlSts_pump;
  boolean_T ctlSts_pumpEn;
  uint8_T ctlSts_prvFL;
  uint8_T ctlSts_prvFR;
  uint8_T ctlSts_prvRL;
  uint8_T ctlSts_prvRR;
  real_T VBAT;
  uint8_T lifeSig;
  uint8_T checkSum;
} struct_0t74Q1hpMIPrZ9wpfvA4OC;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_CAt0xpD2G8kS71ft53IcV_
#define DEFINED_TYPEDEF_FOR_struct_CAt0xpD2G8kS71ft53IcV_

typedef struct {
  real_T oilprs_flsensor;
  real_T oilprs_frsensor;
  real_T oilprs_rlsensor;
  real_T oilprs_rrsensor;
  uint8_T lifeSig;
  uint8_T checkSum;
} struct_CAt0xpD2G8kS71ft53IcV;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_5htIk3TlJvG4EZzXbVyfKH_
#define DEFINED_TYPEDEF_FOR_struct_5htIk3TlJvG4EZzXbVyfKH_

typedef struct {
  uint16_T WheelSpdPulseFL;
  uint16_T WheelSpdPulseFR;
  uint16_T WheelSpdPulseRL;
  uint16_T WheelSpdPulseRR;
  uint8_T lifeSig;
  uint8_T checkSum;
} struct_5htIk3TlJvG4EZzXbVyfKH;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_fAtogmvZgob3IzKnAdvDpG_
#define DEFINED_TYPEDEF_FOR_struct_fAtogmvZgob3IzKnAdvDpG_

typedef struct {
  real_T SlipRatFL;
  real_T SlipRatFR;
  real_T SlipRatRL;
  real_T SlipRatRR;
  uint8_T lifeSig;
  uint8_T checkSum;
} struct_fAtogmvZgob3IzKnAdvDpG;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_eVMkgPVkLll19nmjvj829C_
#define DEFINED_TYPEDEF_FOR_struct_eVMkgPVkLll19nmjvj829C_

typedef struct {
  real_T ipc_esp_flprs;
  real_T ipc_eps_frprs;
  real_T ipc_esp_rlprs;
  real_T ipc_esp_rrprs;
} struct_eVMkgPVkLll19nmjvj829C;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_TKlx0BKB4fF6CsXv4OAeiB_
#define DEFINED_TYPEDEF_FOR_struct_TKlx0BKB4fF6CsXv4OAeiB_

typedef struct {
  boolean_T res_stop;
  boolean_T res_gobutton;
  boolean_T res_communication;
  boolean_T res_go;
  boolean_T res_check;
} struct_TKlx0BKB4fF6CsXv4OAeiB;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_KvAaWugW3m2Hh7STnBeb2C_
#define DEFINED_TYPEDEF_FOR_struct_KvAaWugW3m2Hh7STnBeb2C_

typedef struct {
  real_T apps1;
  real_T signal2;
  real_T apps2;
  real_T signal4;
  real_T brkps;
  real_T signal6;
  real_T wlspd_fsensor;
  real_T wlspd_hsensor;
  real_T airprs_sensor1;
  real_T airprs_sensor2;
} struct_KvAaWugW3m2Hh7STnBeb2C;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_rzs10thnew2021b_T RT_MODEL_rzs10thnew2021b_T;

#endif                                 /* RTW_HEADER_rzs10thnew2021b_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
