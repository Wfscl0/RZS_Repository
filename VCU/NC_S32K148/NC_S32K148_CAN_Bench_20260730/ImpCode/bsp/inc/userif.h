#ifndef _USERIF_H_
#define _USERIF_H_

#include "VCU10.h"



#define MODEL_INIT          VCU10_initialize
#define MODEL_STEP          VCU10_step
#define MODEL_TERMINATE     VCU10_terminate

/*
 * CoreApp and the generated model both use a 10 ms base period. Execute one
 * model step per CoreApp period.
 */
#define MODEL_BASE_PERIOD_MS            (10U)
#define CORE_APP_PERIOD_MS              (10U)
#define MODEL_STEPS_PER_CORE_PERIOD     (CORE_APP_PERIOD_MS / MODEL_BASE_PERIOD_MS)

#if ((CORE_APP_PERIOD_MS % MODEL_BASE_PERIOD_MS) != 0U)
#error "CoreApp period must be an integer multiple of the model base period"
#endif





#endif
