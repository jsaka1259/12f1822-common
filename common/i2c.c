#include "i2c.h"

void i2c_master_init(void) {
  ANSELA &= 0xf9;
  PORTA  &= 0xf9;
  TRISA  |= 0x06;

  SSP1CON1 = 0x28;
  SSP1ADD  = 0x13;
}

void i2c_slave_init(uint8_t addr) {
  ANSELA &= 0xf9;
  PORTA  &= 0xf9;
  TRISA  |= 0x06;

  SSP1STAT        = 0x80;
  SSP1CON1        = 0x26;
  SSP1CON2       |= 0x01;
  SSP1ADD         = addr;
  SSP1MSK         = 0xfe;
  PIR1bits.SSP1IF = 0;
  PIE1bits.SSP1IE = 1;
}

uint8_t i2c_start(uint8_t addr) {
  SSP1CON2bits.SEN = 1;
  while(!PIR1bits.SSP1IF);
  PIR1bits.SSP1IF = 0;
  SSPBUF = addr;
  while(SSP1STATbits.BF);
  return SSP1CON2bits.ACKSTAT;
}

uint8_t i2c_repeat_start(uint8_t addr) {
  SSP1CON2bits.RSEN = 1;
  while(!PIR1bits.SSP1IF);
  PIR1bits.SSP1IF = 0;
  SSPBUF = addr;
  while(SSP1STATbits.BF);
  return SSP1CON2bits.ACKSTAT;
}

void i2c_stop(void) {
  SSP1CON2bits.PEN = 1;
}

uint8_t i2c_write(uint8_t data) {
  SSPBUF = data;
  while(SSP1STATbits.BF);
  return SSP1CON2bits.ACKSTAT;
}

uint8_t i2c_read(uint8_t ack) {
  uint8_t data = 0;
  SSP1CON2bits.ACKDT = ack;
  SSP1CON2bits.RCEN = 1;
  while(!SSP1STATbits.BF);
  data = SSPBUF;
  while(!PIR1bits.SSP1IF);
  PIR1bits.SSP1IF = 0;
  return data;
}

void i2c_slave_write(uint8_t data) {
  uint8_t buf;

  if(PIR1bits.SSP1IF) {
    if((SSP1STAT & 0x04) != 0) {
      if((SSP1STAT & 0x01) != 0) {
        buf       = SSP1BUF;
        SSP1BUF   = data;
        SSP1CON1 |= 0x10;
      } else {
        if((SSP1CON2 & 0x40) == 0) {
          SSP1BUF   = 0;
          SSP1CON1 |= 0x10;
        }
      }
    }
    PIR1bits.SSP1IF = 0;
  }
}

uint8_t i2c_slave_read(uint8_t *data) {
  uint8_t ret = 0xff;
  uint8_t buf;

  if(PIR1bits.SSP1IF) {
    if((SSP1STAT & 0x04) == 0) {
      if((SSP1STAT & 0x20) == 0)
        buf = SSP1BUF;
      else {
        ret = 0;
        *data = SSP1BUF;
      }
      SSP1CON1 |= 0x10;
    }
    PIR1bits.SSP1IF = 0;
  }
  return ret;
}
