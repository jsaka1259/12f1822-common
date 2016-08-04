/**
 * @file    help.c
 * @brief   Help Command
 * @date    2016/08/04  : create
 * @auther  jsaka1259
 */
#include <common.h>

/**
 * @brief   help
 * @param   p_cmd_args  : Commnad Arguments Poiter
 * @return  Error Code
 * @retval  NO_ERROR    : Valid
 */
uint8_t help(char* p_cmd_args)
{
    uint8_t idx;
    for(idx = 0; idx < NUM_CMD; idx++)
    {
        uart_puts(cmd_list[idx]);
        uart_puts("\n");
    }
    return NO_ERROR;
}
