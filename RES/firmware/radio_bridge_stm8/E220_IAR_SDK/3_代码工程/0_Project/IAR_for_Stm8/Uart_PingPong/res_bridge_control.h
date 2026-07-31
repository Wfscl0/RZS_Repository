#ifndef RES_BRIDGE_CONTROL_H
#define RES_BRIDGE_CONTROL_H

#include "ebyte_conf.h"

/* Called by Ebyte's polling callback; functions only post an event to main. */
void RES_Bridge_OnReceivedFrame(const uint8e_t *buffer, uint8e_t length);
void RES_Bridge_OnReceiveTimeout(void);

#endif
