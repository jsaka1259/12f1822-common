#ifndef SPI_H
#define	SPI_H

void spi_master_init(void);
void spi_slave_init(void);
uint8_t spi_master_xfer(uint8_t data);
uint8_t spi_slave_xfer(uint8_t data);

#endif	/* SPI_H */

