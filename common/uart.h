#ifndef _UART_H_
#define _UART_H_

#include <xc.h>
#include <stdint.h>

// Baudrate
#define BAUDRATE    (9600)
// Data Width
// 0: 8bit, 1: 9bit
#define TX9_RX9_BIT (0)
// Sampling Speed
// 0: Low Speed
// 1: High Speed
#define BRGH_BIT    (1)

#if TX9_RX9_BIT == 1
#define TX9_RX9_DATA (0x40)
#else
#define TX9_RX9_DATA (0x00)
#endif

#if BRGH_BIT == 1
#define BRGH_DATA   (0x04)
#define SPBRG_DATA  ((unsigned char)(((_XTAL_FREQ / 16) / BAUDRATE) - 1))
#else
#define BRGH_DATA   (0x00)
#define SPBRG_DATA  ((unsigned char)(((_XTAL_FREQ / 64) / BAUDRATE) - 1))
#endif

extern void uart_init(void);
extern void uart_putc(const char data);
extern uint8_t uart_puts(const char *buf);
extern uint8_t uart_getc(void);

#endif
