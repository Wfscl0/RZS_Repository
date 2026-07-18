/*
 * File: rtmodel.c
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

#include "rtmodel.h"

/* Use this function only if you need to maintain compatibility with an existing static main program. */
void rzs10thnew2021b_step(int_T tid)
{
  switch (tid) {
   case 0 :
    rzs10thnew2021b_step0();
    break;

   case 1 :
    rzs10thnew2021b_step1();
    break;

   default :
    /* do nothing */
    break;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
