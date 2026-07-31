/*
 * Auto generated example main program for model: VCU10
 *
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Fri Jul 17 15:45:49 2026
 *
 * Description:
 *   Embedded Coder example single rate main assuming
 *   no operating system.
 *
 * For more information:
 *   o Simulink Coder User's Guide
 *   o Embedded Coder User's Guide
 *   o matlabroot/rtw/c/ert/ert_main.c
 *   o Type 'ecodertutorial' in MATLAB
 *
 * For a real-time operating system deployment example, reconfigure the
 * "Target operating system" option to "VxWorksExample".
 */

#include <stddef.h>
#include <stdio.h>            /* This example main program uses printf/fflush */
#include "VCU10.h"                     /* Model's header file */

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(void);
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(VCU10_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  VCU10_step();

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Initialize model */
  VCU10_initialize();

  /* Attach rt_OneStep to a timer or interrupt service routine with
   * period 0.01 seconds (the model's base sample time) here.  The
   * call syntax for rt_OneStep is
   *
   *  rt_OneStep();
   */
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (rtmGetErrorStatus(VCU10_M) == (NULL)) {
    /*  Perform application tasks here */
  }

  /* Disable rt_OneStep here */
  /* Terminate model */
  VCU10_terminate();
  return 0;
}
