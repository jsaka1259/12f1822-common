#include "adt7410.h"

void adt7410_init(uint8_t mode) {
  uint8_t mval;

  switch (mode) {
    case 0:
      mval = 0x00 | 0x80;
      break;
    case 1:
      mval = 0x40 | 0x80;
      break;
    case 2:
      mval = 0x60;
      break;
    default:
      mval = 0x00 | 0x80;
      break;
  }

  i2c_start(ADT7410_I2C_ADDR);
  i2c_write(0x03);
  i2c_write(mval);
  i2c_stop();
}

int16_t adt7410_read(uint8_t mode) {
  uint16_t val = 0;

  if (mode == 1) {
    i2c_start(ADT7410_I2C_ADDR);
    i2c_write(0x03);
    i2c_write(0x20 | 0x80);
    i2c_stop();
    __delay_ms(240);
  }

  i2c_start(ADT7410_I2C_ADDR);
  i2c_write(0x00);
  i2c_repeat_start(ADT7410_I2C_ADDR | 1);
  val  = (uint16_t)i2c_read(0) << 8;
  val |= (uint16_t)i2c_read(1);
  i2c_stop();

  if (val & 0x8000)
    return (int16_t)((int32_t)val - 65536);
  else
    return val;
}

