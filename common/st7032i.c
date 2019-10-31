#include "common.h"

void st7032i_i2c_master_write(uint8_t addr, uint8_t cont, uint8_t data) {
  SEN = 1;
  while(SEN)
    ;
  i2c_tx_data(addr);
  i2c_tx_data(cont);
  i2c_tx_data(data);
  SSP1IF = 0;
  PEN = 1;
  while(PEN);
}

void st7032i_cmd(uint8_t cmd) {
  st7032i_i2c_master_write(ST7032I_I2C_ADDR, 0x00, cmd);

  /* Clear or Home */
  if(cmd & 0xFC)
    __delay_us(50);
  else
    __delay_ms(2);
}

void st7032i_init(void) {
  __delay_ms(100);
  // 8bit 2line Noraml mode
  st7032i_cmd(0x38);
  // 8bit 2line Extend mode
  st7032i_cmd(0x39);
  // OSC 183Hz BIAS 1/5
  st7032i_cmd(0x14);
  // CONTRAST
  st7032i_cmd(0x70 + (CONTRAST & 0x0F));
  st7032i_cmd(0x50 + (CONTRAST >> 4));
#ifdef VDD_5V
  // Follower for 5V
  st7032i_cmd(0x6A);
#else
  // Follower for 3.3V
  st7032i_cmd(0x6B);
#endif
  __delay_ms(100);
  // Set Normal mode
  st7032i_cmd(0x38);
  // Display On
  st7032i_cmd(0x0C);
  // Clear Display
  st7032i_cmd(0x01);
}

void st7032i_clear(void) {
  // Clear Display
  st7032i_cmd(0x01);
}

void st7032i_putc(const uint8_t data) {
  st7032i_i2c_master_write(ST7032I_I2C_ADDR, 0x40, data);
  __delay_us(50);
}

void st7032i_puts(const uint8_t* buf) {
  while(*buf)
    st7032i_putc(*buf++);
}
