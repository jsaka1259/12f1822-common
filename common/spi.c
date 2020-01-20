#include "spi.h"

void spi_master_init(void) {
  APFCON &= 0x9f;
  ANSELA &= 0xf8;
  TRISA  |= 0x04;
  TRISA  &= 0xfc;

  SSP1STAT = 0x00;
  SSP1CON1 = 0x30;
}

void spi_slave_init(void) {
  APFCON &= 0x9f;
  ANSELA &= 0xf0;
  TRISA  |= 0x06;
  TRISA  &= 0xfe;

  SSP1STAT = 0x00;
  SSP1CON1 = 0x35;

  PIR1bits.SSP1IF = 0;
  PIE1bits.SSP1IE = 1;
}

uint8_t spi_master_xfer(uint8_t data) {
  SSP1BUF = data;
  while(!SSPSTATbits.BF);
  return SSP1BUF;
}

uint8_t spi_slave_xfer(uint8_t data) {
  uint8_t buf;

  buf = SSPBUF;
  SSPBUF = data;
  return buf;
}
