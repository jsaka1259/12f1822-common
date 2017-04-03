#ifndef _UART_H_
#define	_UART_H_

extern void uart_init(void);
extern void uart_putc(const char);
extern uint8_t uart_puts(const char*);
extern uint8_t uart_getc(void);

#endif	/* _UART_H_ */
