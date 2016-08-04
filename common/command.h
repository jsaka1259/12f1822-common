/**
 * @file    command.h
 * @brief   Command Library API
 * @date    2016/08/04  : create
 * @auther  jsaka1259
 */
#ifndef _COMMAND_H_
#define	_COMMAND_H_

extern void cmd_split(char*, char**, char**);
extern uint8_t cmd_parser(char*, char*);

#endif	/* _COMMAND_H_ */
