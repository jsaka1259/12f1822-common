#include <common.h>

#define LCD_I2C_ADDR    0x7C    // LCD I2C Address
#define CONTRAST        0x18    // CONTRAST

void lcd_i2c_master_write(uint8_t addr, uint8_t cont, uint8_t data)
{
    SEN = 1;
    while(SEN);
    i2c_tx_data(addr);
    i2c_tx_data(cont);
    i2c_tx_data(data);
    SSP1IF = 0;
    PEN = 1;
    while(PEN);
}

void lcd_cmd(uint8_t cmd)
{
    lcd_i2c_master_write(LCD_I2C_ADDR, 0x00, cmd);
    
    /* Clear or Home */
    if(cmd & 0xFC)
    {
        __delay_us(50);
    }
    else
    {
        __delay_ms(2);
    }
}

void lcd_init(void)
{
    __delay_ms(100);
    lcd_cmd(0x38);                      // 8bit 2line Noraml mode
    lcd_cmd(0x39);                      // 8bit 2line Extend mode
    lcd_cmd(0x14);                      // OSC 183Hz BIAS 1/5
    lcd_cmd(0x70 + (CONTRAST & 0x0F));  // CONTRAST
    lcd_cmd(0x50 + (CONTRAST >> 4));    // CONTRAST
    lcd_cmd(0x6A);                      // Follower for 5V
    //lcd_cmd(0x6B);                     // Follower for 3.3V
    __delay_ms(100);
    __delay_ms(100);
    lcd_cmd(0x38);                      // Set Normal mode
    lcd_cmd(0x0C);                      // Display On
    lcd_cmd(0x01);                      // Clear Display
}

void lcd_clear(void)
{
    lcd_cmd(0x01);                      // Clear Display
}

void lcd_putc(uint8_t data)
{    
    lcd_i2c_master_write(LCD_I2C_ADDR, 0x40, data);
    __delay_us(50);
}

void lcd_puts(const uint8_t* buf)
{
    while(*buf)
    {
        lcd_putc(*buf++);
    }
}
