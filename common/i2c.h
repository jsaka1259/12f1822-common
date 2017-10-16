#ifndef I2C_H
#define	I2C_H

void i2c_master_init(void);
void i2c_slave_init(uint8_t slave_addr);
void i2c_tx_data(uint8_t data);
uint8_t i2c_rx_data(void);
void i2c_master_write(uint8_t addr, uint8_t data);
uint8_t i2c_master_read(uint8_t addr);
void i2c_slave_write(uint8_t data);
uint8_t i2c_slave_read(uint8_t* data);

#endif	/* I2C_H */

