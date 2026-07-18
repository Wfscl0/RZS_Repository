/*
 * VCU10_data.c
 *
 * Code generation for model "VCU10".
 *
 * Model version              : 1.30
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Fri Jul 17 15:02:18 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "VCU10.h"
#include "VCU10_private.h"

/* Invariant block signals (default storage) */
const ConstB_VCU10_T VCU10_ConstB = {
  { 0.0, 1.0 },                        /* '<S44>/Multiport Switch' */

  { 1.0, 0.0 },                        /* '<S47>/Multiport Switch' */
  83.333333333333329,                  /* '<S238>/Gain' */
  0.0,                                 /* '<S238>/Gain1' */
  0.81,                                /* '<S279>/Product' */
  500U,                                /* '<S238>/Data Type Conversion8' */
  15500U,                              /* '<S238>/Add2' */
  83U,                                 /* '<S238>/Data Type Conversion9' */
  0U,                                  /* '<S238>/Bitwise AND7' */
  0U,                                  /* '<S238>/Data Type Conversion10' */
  0U,                                  /* '<S238>/Bitwise AND8' */
  0U,                                  /* '<S238>/Bitwise AND9' */
  15360U,                              /* '<S238>/Bitwise AND13' */
  140U,                                /* '<S238>/Bitwise AND12' */
  83U,                                 /* '<S238>/Bitwise AND6' */
  93U,                                 /* '<S239>/Data Type Conversion5' */
  0U,                                  /* '<S239>/Bitwise AND1' */
  9U,                                  /* '<S239>/Data Type Conversion1' */
  0U,                                  /* '<S239>/Bitwise AND3' */
  93U,                                 /* '<S239>/Bitwise AND' */
  9U,                                  /* '<S239>/Bitwise AND2' */
  0U,                                  /* '<S146>/Bitwise AND8' */
  0U,                                  /* '<S238>/Data Type Conversion1' */
  0U,                                  /* '<S238>/Bitwise AND1' */
  2U,                                  /* '<S238>/Data Type Conversion3' */
  2U,                                  /* '<S238>/Bitwise AND2' */
  1U,                                  /* '<S238>/Data Type Conversion4' */
  1U,                                  /* '<S238>/Bitwise AND3' */
  0U,                                  /* '<S238>/Data Type Conversion5' */
  0U,                                  /* '<S238>/Bitwise AND4' */
  0U,                                  /* '<S238>/Data Type Conversion6' */
  0U,                                  /* '<S238>/Bitwise AND5' */
  83U,                                 /* '<S238>/Data Type Conversion11' */
  140U,                                /* '<S238>/Data Type Conversion16' */
  93U,                                 /* '<S239>/Data Type Conversion2' */
  9U                                   /* '<S239>/Data Type Conversion4' */
};

/* Constant parameters (default storage) */
const ConstP_VCU10_T VCU10_ConstP = {
  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S14>/1-D Lookup Table'
   *   '<S14>/1-D Lookup Table9'
   *   '<S44>/neg. edge'
   *   '<S47>/neg. edge'
   */
  { 0.0, 1.0 },

  /* Pooled Parameter (Expression: [252 2000])
   * Referenced by:
   *   '<S14>/1-D Lookup Table'
   *   '<S14>/1-D Lookup Table9'
   */
  { 252U, 2000U }
};
