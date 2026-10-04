
#include "ebyte_conf.h"
#include "ebyte_callback.h"

void Ebyte_E10x_IntOrPollTask( void );
void Ebyte_E10x_Init();
void Ebyte_E10x_SetRx( uint32e_t timeout );
void Ebyte_E10x_SendPayload(uint8e_t *payload, uint8e_t size, uint32e_t timeout);