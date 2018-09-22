#ifndef SPI_H
#define SPI_H

extern void spi_master_init(void);
extern void spi_slave_init(void);
extern uint8_t spi_master_xfer(uint8_t data);
extern uint8_t spi_slave_xfer(uint8_t data);

#endif /* SPI_H */

