#include "uart.h"

void uart_init(void) {
  ANSELA &= 0x0f;
  PORTA  &= 0x0f;
  TRISA  |= 0x20;
  TRISA  &= 0x2f;

  APFCONbits.RXDTSEL = 1;
  APFCONbits.TXCKSEL = 1;

  BAUDCONbits.BRG16 = BRG16_BIT;
#if BRG16_BIT
  SPBRGH = (uint8_t)(SPBRG_DATA << 8);
#else
  SPBRGH = 0;
#endif
  SPBRGL = (uint8_t)(SPBRG_DATA & 0x00ff);

  TXSTAbits.TXEN = 1;
  TXSTAbits.SYNC = SYNC_BIT;
  TXSTAbits.BRGH = BRGH_BIT;
  RCSTAbits.CREN = 1;
  RCSTAbits.SPEN = 1;
}

void uart_disable(void) {
  TXSTAbits.TXEN = 0;
  RCSTAbits.CREN = 0;
  RCSTAbits.SPEN = 0;
}

void uart_putc(const char data) {
  while(!PIR1bits.TXIF);
  TXREG = data;
}

uint8_t uart_puts(const char *buf) {
  uint8_t len = 0;

  while(buf[len])
    uart_putc(buf[len++]);
  return len;
}

uint8_t uart_getc(void) {
  while(!PIR1bits.RCIF);
  return RCREGbits.RCREG;
}
