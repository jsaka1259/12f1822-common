#ifndef _I2C_H_
#define _I2C_H_

#include <xc.h>
#include <stdint.h>

extern void i2c_master_init(void);
extern void i2c_slave_init(uint8_t addr);
extern uint8_t i2c_start(uint8_t addr);
extern uint8_t i2c_repeat_start(uint8_t addr);
extern void i2c_stop(void);
extern uint8_t i2c_write(uint8_t data);
extern uint8_t i2c_read(uint8_t ack);
extern void i2c_slave_write(uint8_t data);
extern uint8_t i2c_slave_read(uint8_t* data);

#endif
