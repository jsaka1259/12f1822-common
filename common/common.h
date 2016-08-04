/**
 * @file    common.h
 * @brief   Initialize PIC12F1822 Common Library API
 * @date    2016/06/29  : create
 * @auther  jsaka1259
 */
#ifndef _COMMON_H_
#define	_COMMON_H_

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

#include "shell.h"
#include "uart.h"
#include "command.h"

/**
 * Common Config
 */
/* System Clock */
#ifndef _XTAL_FREQ
#define _XTAL_FREQ  (32000000)
#endif

/**
 * Shell Config
 */
/* Shell Buffer Size */
#define SHELL_BUF_SIZE (0x0F)

/**
 * UART Config
 */
#define BAUDRATE    (9600)  /* 9.6kbps */
#define TX9_RX9_BIT (0)     /* 0: 8bit, 1: 9bit */
#define BRGH_BIT    (1)     /* 0: Set Low Speed Sampling */
                            /* 1: High Speed Sampling */
 
#if TX9_RX9_BIT == 1
#define TX9_RX9_DATA (0x40)
#else
#define TX9_RX9_DATA (0x00)
#endif

#if BRGH_BIT == 1
#define BRGH_DATA   (0x04)
#define SPBRG_DATA  ((unsigned char)(((_XTAL_FREQ / 16) / BAUDRATE) - 1))
#else
#define BRGH_DATA   (0x00)
#define SPBRG_DATA  ((unsigned char)(((_XTAL_FREQ / 64) / BAUDRATE) - 1))
#endif

/**
 * Commnad Config
 */
#define NUM_CMD     (1)     /* Number of Command */
#define CMD_LEN     (16)    /* Command Length */

/* Error Code */
#define NO_ERROR    (0)     /* No Eroor */
#define NOT_FOUND   (-1)    /* Cound not Find the Command */

/* Command List */
char cmd_list[NUM_CMD][CMD_LEN] = {
    "help"
};

/* Command Prototyep Declaration */
extern uint8_t help(char*);

/* Command Pointer */
uint8_t (*cmd_handler[NUM_CMD])(char*) = {
    help,
};


/* Extern Declaration */
extern void common_init(void);

#endif	/* _COMMON_H_ */
