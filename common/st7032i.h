#ifndef _ST7032I_H_
#define _ST7032I_H_

#include <xc.h>
#include <stdint.h>

#include "i2c.h"
#include "xtal.h"

#define VDD_5V

// ST7032I I2C Address
#define ST7032I_I2C_ADDR 0x3e << 1

#ifdef VDD_5V
// for 5V
#define ST7032I_CONTRAST 0x18
#else
// for 3.3V
#define ST7032I_CONTRAST 0x30
#endif

extern void st7032i_cmd(uint8_t cmd);
extern void st7032i_init(void);
extern void st7032i_clear(void);
extern void st7032i_putc(const char c);
extern void st7032i_puts(const char *buf);

#endif
