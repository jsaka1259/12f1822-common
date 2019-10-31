#include "common.h"

void uart_init(void) {
  // RX -> RA5
  APFCONbits.RXDTSEL = 1;
  // TX -> RA4
  APFCONbits.TXCKSEL = 1;

  BAUDCON = BRG16;
  SPBRG   = SPBRG_DATA;
  TXSTA   = (TX9_RX9_DATA | BRGH_DATA | 0x20);
  RCSTA   = (TX9_RX9_DATA | 0x90);

  PIR1bits.RCIF = 0;
  PIE1bits.RCIE = 0;
}

void uart_putc(const char data) {
  while(TXIF == 0)
    ;
  TXREG = data;
}

uint8_t uart_puts(const char *buf) {
  uint8_t len = 0;

  while(buf[len] != 0x00)
    uart_putc(buf[len++]);
  return len;
}

uint8_t uart_getc(void) {
  while(PIR1bits.RCIF == 0)
    ;
  RCIE = 0;
  return RCREGbits.RCREG;
}
