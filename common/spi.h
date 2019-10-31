#ifndef _SPI_H_
#define _SPI_H_

#include <xc.h>
#include <stdint.h>

extern void spi_master_init(void);
extern void spi_slave_init(void);
extern uint8_t spi_master_xfer(uint8_t data);
extern uint8_t spi_slave_xfer(uint8_t data);

#endif
