#ifndef EBYTE_CORE_H
#define EBYTE_CORE_H
#include "ebyte_conf.h"
typedef struct {
    void (*Init)(void);
    void (*Send)(uint8e_t *, uint8e_t, uint32e_t);
    void (*EnterSleepMode)(uint8e_t);
    void (*EnterReceiveMode)(uint32e_t);
    void (*StartPollTask)(void);
} Ebyte_RF_t;
extern const Ebyte_RF_t Ebyte_RF;
void Ebyte_BSP_Init(void);
void Ebyte_BSP_GlobalIntEnable(void);
#endif
