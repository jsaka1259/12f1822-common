#ifndef _COMMON_H_
#define	_COMMON_H_

/* System Clock */
#ifndef _XTAL_FREQ
#define _XTAL_FREQ  (8000000)
#endif

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

#include "i2c.h"
#include "spi.h"
#include "st7032i.h"
#include "adt7410.h"
#include "uart.h"
#include "utils.h"

#endif	/* _COMMON_H_ */
