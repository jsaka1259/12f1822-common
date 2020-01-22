#include "st7032i.h"

static void st7032i_i2c_write(uint8_t addr, uint8_t cont, uint8_t data) {
  i2c_start();
  i2c_write(addr);
  i2c_write(cont);
  i2c_write(data);
  i2c_stop();
}

void st7032i_cmd(uint8_t cmd) {
  st7032i_i2c_write(ST7032I_I2C_ADDR, 0x00, cmd);

  /* Clear or Home */
  if((cmd == 0x01) || (cmd == 0x02))
    __delay_ms(2);
  else
    __delay_us(30);
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
  st7032i_cmd(0x70 + (ST7032I_CONTRAST & 0x0f));
  st7032i_cmd(0x5c + (ST7032I_CONTRAST >> 4));
#ifdef VDD_5V
  // Follower for 5V
  st7032i_cmd(0x6a);
#else
  // Follower for 3.3V
  st7032i_cmd(0x6c);
#endif
  __delay_ms(300);
  // Set Normal mode
  st7032i_cmd(0x38);
  // Display On
  st7032i_cmd(0x0c);
  // Clear Display
  st7032i_cmd(0x01);
}

void st7032i_clear(void) {
  // Clear Display
  st7032i_cmd(0x01);
}

void st7032i_putc(const char c) {
  st7032i_i2c_write(ST7032I_I2C_ADDR, 0x40, c);
  __delay_us(30);
}

void st7032i_puts(const char *buf) {
  while(*buf)
    st7032i_putc(*buf++);
}
