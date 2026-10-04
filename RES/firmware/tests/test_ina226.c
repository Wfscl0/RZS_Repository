#include "ina226.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
typedef struct { uint16_t regs[256]; bool io_fail; bool corrupt_write; } fixture_t;
static bool rd(void *ctx,uint8_t reg,uint16_t *value)
{
    fixture_t *f=ctx;
    if(f->io_fail) return false;
    *value=f->regs[reg];
    if(reg==6u) f->regs[reg] &= (uint16_t)~8u;
    return true;
}
static bool wr(void *ctx,uint8_t reg,uint16_t value)
{
    fixture_t *f=ctx;
    if(f->io_fail) return false;
    f->regs[reg]=f->corrupt_write?0u:value;
    return true;
}
static void setup(fixture_t *f,ina226_t *d)
{
    memset(f,0,sizeof(*f)); memset(d,0,sizeof(*d));
    f->regs[0xFE]=0x5449u; f->regs[0xFF]=0x2260u;
    d->context=f; d->read_register=rd; d->write_register=wr;
}
int main(void)
{
    fixture_t f; ina226_t d; uint16_t v; int16_t i; uint32_t p;
    setup(&f,&d); assert(ina226_init(&d));
    assert(f.regs[0]==0x4527u && f.regs[5]==1024u);
    f.regs[6]=8u; f.regs[2]=9600u; f.regs[4]=200u; f.regs[3]=96u;
    assert(ina226_read(&d,&v,&i,&p)); assert(v==12000u && i==100 && p==1200u);
    assert(!ina226_read(&d,&v,&i,&p));
    assert(d.last_error==INA226_NOT_READY && v==0u && i==0 && p==0u);
    f.regs[6]=8u; f.regs[2]=0u;
    assert(ina226_read(&d,&v,&i,&p) && v==0u); /* critical, not fabricated */
    f.regs[0]=0x4127u; assert(!ina226_read(&d,&v,&i,&p));
    assert(d.last_error==INA226_CONFIG_MISMATCH && !d.initialized);
    setup(&f,&d); f.regs[0xFF]=0x2261u; assert(ina226_init(&d));
    setup(&f,&d); f.regs[0xFE]=0u; assert(!ina226_init(&d));
    assert(d.last_error==INA226_ID_MISMATCH);
    setup(&f,&d); f.corrupt_write=true; assert(!ina226_init(&d));
    assert(d.last_error==INA226_CONFIG_MISMATCH);
    setup(&f,&d); f.io_fail=true; assert(!ina226_init(&d));
    assert(d.last_error==INA226_IO_ERROR);
    setup(&f,&d); assert(ina226_init(&d)); f.io_fail=true;
    assert(!ina226_read(&d,&v,&i,&p) && !d.initialized);
    setup(&f,&d); assert(ina226_init(&d)); f.regs[6]=12u;
    assert(!ina226_read(&d,&v,&i,&p) && d.last_error==INA226_MATH_OVERFLOW);
    setup(&f,&d); assert(ina226_init(&d)); f.regs[6]=8u; f.regs[2]=65535u;
    assert(!ina226_read(&d,&v,&i,&p) && d.last_error==INA226_RANGE_ERROR);
    puts("test_ina226: PASS"); return 0;
}
