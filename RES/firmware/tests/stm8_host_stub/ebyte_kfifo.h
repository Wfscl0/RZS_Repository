#ifndef EBYTE_KFIFO_H
#define EBYTE_KFIFO_H
#include "ebyte_conf.h"
#define EBYTE_FIFO_SIZE 128u
typedef struct { uint8e_t unused; } Ebyte_FIFO_t;
void Ebyte_FIFO_Init(Ebyte_FIFO_t *, uint16e_t);
void Ebyte_FIFO_GetDataLength(Ebyte_FIFO_t *, uint16e_t *);
void Ebyte_FIFO_Read(Ebyte_FIFO_t *, uint8e_t *, uint16e_t);
#endif
