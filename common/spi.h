#ifndef _SPI_H_
#define _SPI_H_

#include <xc.h>
#include <stdint.h>

extern void spi_init(void);
extern uint8_t spi_xfer(uint8_t data);

#endif
