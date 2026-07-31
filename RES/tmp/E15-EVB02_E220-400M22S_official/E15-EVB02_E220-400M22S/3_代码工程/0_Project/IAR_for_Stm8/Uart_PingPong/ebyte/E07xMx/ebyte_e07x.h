
#include "ebyte_conf.h"
#include "ebyte_callback.h"


#define RF_FREQUENCY_START                          433000000 // Hz ÆðÊ¼ÆµÂÊ

void Ebyte_E07x_Init( void );
void Ebyte_E07x_IntOrPollTask(void);
void Ebyte_E07x_SendPayload( uint8e_t *payload, uint8e_t size, uint32e_t timeout );
void Ebyte_E07x_SetRx( uint32e_t timeout );