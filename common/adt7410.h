#ifndef _ADT7410_H_
#define _ADT7410_H_

#include <xc.h>
#include <stdint.h>

#include "i2c.h"
#include "xtal.h"

#define ADT7410_I2C_ADDR 0x48 << 1

extern void adt7410_init(uint8_t mode);
extern int16_t adt7410_read(uint8_t mode);

#endif

