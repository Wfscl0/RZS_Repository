/*
 * VCU10_private.h
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

#ifndef RTW_HEADER_VCU10_private_h_
#define RTW_HEADER_VCU10_private_h_
#include "rtwtypes.h"
#include "VCU10.h"
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

extern real_T look1_iu16td_linlcapw(uint16_T u0, const uint16_T bp0[], const
  real_T table[], uint32_T maxIndex);
extern void VCU10_BitShift(uint8_T rtu_u, uint8_T *rty_y);
extern void VCU10_BitShift1(uint8_T rtu_u, uint8_T *rty_y);
extern void VCU10_BitShift2(uint8_T rtu_u, uint8_T *rty_y);
extern void VCU10_BitShift_a(uint8_T rtu_u, uint8_T *rty_y);
extern void VCU10_BitShift_p(uint16_T rtu_u, uint16_T *rty_y);
extern void VCU10_BitShift1_j(uint16_T rtu_u, uint16_T *rty_y);
extern void VCU10_BitShift2_b(uint16_T rtu_u, uint16_T *rty_y);
extern void VCU10_BitShift3(uint16_T rtu_u, uint16_T *rty_y);
extern void VCU10_BitShift4(uint16_T rtu_u, uint16_T *rty_y);
extern void VCU10_BitShift8(real_T rtu_u, real_T *rty_y);
extern void VCU10_BitShift1_i(uint8_T rtu_u, uint8_T *rty_y);
extern void VCU10_BitShift2_e(uint8_T rtu_u, uint8_T *rty_y);
extern void VCU10_BitShift3_m(uint8_T rtu_u, uint8_T *rty_y);
extern void VCU10_BitShift5(uint16_T rtu_u, uint16_T *rty_y);
extern void VCU10_BitShift6(uint16_T rtu_u, uint16_T *rty_y);
extern void VCU10_BitShift7(uint16_T rtu_u, uint16_T *rty_y);
extern void VCU10_NEGATIVEEdge(real_T rtu_Enable, boolean_T rtu_IN, boolean_T
  rtu_INprevious, boolean_T *rty_OUT);
extern void VCU10_POSITIVEEdge(real_T rtu_Enable, boolean_T rtu_IN, boolean_T
  rtu_INprevious, boolean_T *rty_OUT);
extern void VCU10_BitShift10(uint8_T rtu_u, uint8_T *rty_y);
extern void VCU10_BitShift4_h(uint8_T rtu_u, uint8_T *rty_y);

#endif                                 /* RTW_HEADER_VCU10_private_h_ */
