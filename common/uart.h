#ifndef _UART_H_
#define _UART_H_

#include <xc.h>
#include <stdint.h>

#include "xtal.h"

// baudrate
#define BAUDRATE 9600

// synchronous bit
// 0: asynchronous, 1: synchronous
#define SYNC_BIT 0

// 16 bit baudrate generater
// 0: 8 bit, 1: 16bit
#define BRG16_BIT 1

// sampling speed
// 0: low speed, 1: high speed
#define BRGH_BIT 1

#if SYNC_BIT == 0 && BRG16_BIT == 0 && BRGH_BIT == 0
#define SPBRG_DATA (uint16_t)(((_XTAL_FREQ / BAUDRATE) / 64) - 1)
#elif SYNC_BIT == 0 && (BRG16_BIT == 1 ^ BRGH_BIT == 1)
#define SPBRG_DATA (uint16_t)(((_XTAL_FREQ / BAUDRATE) / 16) - 1)
#elif SYNC_BIT == 1 || (BRG16_BIT == 1 && BRGH_BIT == 1)
#define SPBRG_DATA (uint16_t)(((_XTAL_FREQ / BAUDRATE) / 4) - 1)
#endif

extern void uart_init(void);
extern void uart_putc(const char data);
extern uint8_t uart_puts(const char *buf);
extern uint8_t uart_getc(void);

#endif
