/**
 * @file    command.c
 * @brief   Command Library API
 * @date    2016/08/04  : create
 * @auther  jsaka1259
 */
#include <common.h>

/**
 * @brief   Command Split
 * @param   buf         : Buffer Pointer
 * @param   p_cmd       : Command Pointer
 * @param   p_cmd_args  : Command Arguments Pointer
 * @return  None
 */
void cmd_split(char* buf, char** p_cmd, char** p_cmd_args)
{
    uint8_t idx;
    
    *p_cmd      = buf;
    *p_cmd_args = buf;
    
    for(idx = 0; idx < SHELL_BUF_SIZE; idx++)
    {
        if(0x20 == buf[idx])
        {
            buf[idx]    = 0x00;
            *p_cmd_args = &buf[idx+1];
            break;
        }
    }
}

/**
 * @brief   Command Parser
 * @param   p_cmd       : Command Pointer
 * @param   p_cmd_args  : Command Arguments Pointer
 * @return  Error Code
 * @retval  NO_ERROR    : Valid
 * @retval  NOT_FOUND   : Cound not Find the Commnad
 */
uint8_t cmd_parser(char* p_cmd, char* p_cmd_args)
{
    uint8_t ret = NOT_FOUND;    /* retval : Default NOT FOUND */
    uint8_t idx;                /* Loop Index */
    
    /* Command Parse */
    for(idx = 0; idx < NUM_CMD; idx++)
    {
        /* Compare Command List and Input Command */
        if(0 == strcmp(cmd_list[idx], p_cmd))
        {
            /* Run Commnad */
            ret = cmd_handler[idx](p_cmd, p_cmd_args);
        }
    }
    return ret;
}
