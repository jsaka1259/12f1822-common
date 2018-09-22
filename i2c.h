#ifndef I2C_H
#define I2C_H

extern void i2c_master_init(void);
extern void i2c_slave_init(uint8_t slave_addr);
extern void i2c_tx_data(uint8_t data);
extern uint8_t i2c_rx_data(void);
extern void i2c_master_write(uint8_t addr, uint8_t data);
extern uint8_t i2c_master_read(uint8_t addr);
extern void i2c_slave_write(uint8_t data);
extern uint8_t i2c_slave_read(uint8_t* data);

#endif /* I2C_H */

