#include "spi.h"

void spi_init(void) {
  APFCON &= 0x9f;
  ANSELA &= 0xf8;
  TRISA  |= 0x04;
  TRISA  &= 0xfc;

  SSP1STAT = 0x00;
  SSP1CON1 = 0x30;
}

uint8_t spi_xfer(uint8_t data) {
  SSP1BUF = data;
  while(!SSP1STATbits.BF);
  return SSP1BUF;
}
