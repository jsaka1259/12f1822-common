#ifndef _UART_H_
#define	_UART_H_

void uart_init(void);
void uart_putc(const char);
uint8_t uart_puts(const char*);
uint8_t uart_getc(void);

#endif	/* _UART_H_ */
