#include <common.h>

#define ADT7410_I2C_ADDR   0x90

void adt7410_init(void)
{
    i2c_start();
    i2c_write(ADT7410_I2C_ADDR);
    i2c_write(0x03);
    i2c_write(0x40);
    i2c_stop();
    
}

uint16_t adt7410_read(void)
{
    uint8_t buf[2];
    i2c_start();
    i2c_write(ADT7410_I2C_ADDR);
    i2c_write(0x00);
    i2c_restart();
    i2c_write(ADT7410_I2C_ADDR + 1);
    buf[0] = i2c_read(0x00);
    buf[1] = i2c_read(0x01);
    i2c_stop();
    return ((buf[0] << 8) | buf[1]) >> 3;
}