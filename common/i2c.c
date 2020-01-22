#include "i2c.h"

static void i2c_wait(void) {
  while((SSP1CON2 & 0x1f) || (SSP1STATbits.R_nW));
}

void i2c_init(uint8_t high_speed) {
  ANSELA &= 0xf9;
  PORTA  &= 0xf9;
  TRISA  |= 0x06;

  SSP1CON1 = 0x28;
  if (high_speed) {
    SSP1STATbits.SMP = 0;
    SSP1ADD          = (_XTAL_FREQ/(4*400000))-1;
  } else {
    SSP1STATbits.SMP = 1;
    SSP1ADD          = (_XTAL_FREQ/(4*100000))-1;
  }
}

void i2c_disable(void) {
  SSP1CON1 = 0x08;
}

uint8_t i2c_start(void) {
  SSP1CON2bits.SEN = 1;
  i2c_wait();
}

uint8_t i2c_repeat_start(void) {
  SSP1CON2bits.RSEN = 1;
  i2c_wait();
}

void i2c_stop(void) {
  SSP1CON2bits.PEN = 1;
  i2c_wait();
}

uint8_t i2c_write(uint8_t data) {
  SSPBUF = data;
  i2c_wait();
  return SSP1CON2bits.ACKSTAT;
}

uint8_t i2c_read(uint8_t ack) {
  uint8_t data = 0;

  SSP1CON2bits.RCEN = 1;
  i2c_wait();
  data = SSPBUF;
  i2c_wait();

  SSP1CON2bits.ACKDT = ack ? 0 : 1;
  SSP1CON2bits.ACKEN = 1;
  i2c_wait();

  return data;
}
