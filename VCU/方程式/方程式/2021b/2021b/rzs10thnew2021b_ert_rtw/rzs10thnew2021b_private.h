/*
 * File: rzs10thnew2021b_private.h
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

#ifndef RTW_HEADER_rzs10thnew2021b_private_h_
#define RTW_HEADER_rzs10thnew2021b_private_h_
#include "rtwtypes.h"
#include "rzs10thnew2021b.h"
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

extern uint16_T look1_iu16lu16n16_linlcase(uint16_T u0, const uint16_T bp0[],
  const uint16_T table[], uint32_T maxIndex);
extern void rzs10thnew2021b_BitShift(uint8_T rtu_u, uint8_T *rty_y);
extern void rzs10thnew2021b_BitShift1(uint8_T rtu_u, uint8_T *rty_y);
extern void rzs10thnew2021b_BitShift2(uint8_T rtu_u, uint8_T *rty_y);
extern void rzs10thnew2021b_BitShift_a(uint16_T rtu_u, uint16_T *rty_y);
extern void rzs10thnew2021b_BitShift1_f(uint16_T rtu_u, uint16_T *rty_y);
extern void rzs10thnew2021b_BitShift2_i(uint16_T rtu_u, uint16_T *rty_y);
extern void rzs10thnew2021b_BitShift3(uint16_T rtu_u, uint16_T *rty_y);
extern void rzs10thnew2021b_BitShift4(uint16_T rtu_u, uint16_T *rty_y);
extern void rzs10thnew2021b_BitShift8(real_T rtu_u, real_T *rty_y);
extern void rzs10thnew2021b_BitShift1_k(uint8_T rtu_u, uint8_T *rty_y);
extern void rzs10thnew2021b_BitShift2_g(uint8_T rtu_u, uint8_T *rty_y);
extern void rzs10thnew2021b_BitShift_c(uint8_T rtu_u, uint8_T *rty_y);
extern void rzs10thnew2021_BitShift1_kp(uint8_T rtu_u, uint8_T *rty_y);
extern void rzs10thnew2021b_BitShift2_o(uint8_T rtu_u, uint8_T *rty_y);
extern void rzs10thnew2021b_BitShift3_p(uint8_T rtu_u, uint8_T *rty_y);
extern void rzs10thnew2021b_BitShift4_j(uint8_T rtu_u, uint8_T *rty_y);
extern void rzs10thnew2021b_BitShift5(uint16_T rtu_u, uint16_T *rty_y);
extern void rzs10thnew2021b_BitShift6(uint16_T rtu_u, uint16_T *rty_y);
extern void rzs10thnew2021b_BitShift7(uint16_T rtu_u, uint16_T *rty_y);
extern void rzs10thnew2021_NEGATIVEEdge(real_T rtu_Enable, boolean_T rtu_IN,
  boolean_T rtu_INprevious, boolean_T *rty_OUT);
extern void rzs10thnew2021_POSITIVEEdge(real_T rtu_Enable, boolean_T rtu_IN,
  boolean_T rtu_INprevious, boolean_T *rty_OUT);
extern void rzs10thnew2021b_BitShift10(uint8_T rtu_u, uint8_T *rty_y);
extern void rzs10thnew2021b_BitShift4_p(uint8_T rtu_u, uint8_T *rty_y);

#endif                               /* RTW_HEADER_rzs10thnew2021b_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
