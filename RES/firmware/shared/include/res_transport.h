#ifndef RES_TRANSPORT_H
#define RES_TRANSPORT_H
#include "res_radio_config.h"
#if RES_RADIO_SI4463
#include "res_si4463_transport.h"
#else
#include "res_uart_transport.h"
#endif
#endif
