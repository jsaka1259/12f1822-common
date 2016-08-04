/**
 * @file    shell.c
 * @brief   Shell Library API
 * @date    2016/07/16  : create
 * @auther  jsaka1259
 */
#include <common.h>

static char shell_buf[SHELL_BUF_SIZE];  /* Shell Buffer */
static char* cmd;                       /* Commnad Pointer */
static char* cmd_args;                  /* Command Arguments Pointer */

/**
 * @brief   Shell Function
 * @param   None
 * @return  None
 */
void shell(void)
{
    char ch;
    uint8_t idx = 0;
    while(1)
    {
        idx = 0;
        uart_puts("> ");
        while(1)
        {
            ch = uart_getc();
            if(0x0D == ch || (SHELL_BUF_SIZE-1) <= idx)
            {
                shell_buf[idx] = 0x00;
                uart_putc('\n');
                
                /* Command Split */
                cmd_split(shell_buf, &cmd, &cmd_args);
                
                /* Run Commnad */
                switch(cmd_parser(cmd, cmd_args))
                {
                    case NOT_FOUND:
                        uart_puts("Cound not find the Command: ");
                        uart_puts(cmd);
                        uart_puts("\n");
                        break;
                    default:
                        break;
                }
                break;
            }
            else if(0x08 == ch && 0 < idx)
            {
                idx--;
                uart_puts("\b \b");
            }
            else if(0x20 <= ch && 0x7F > ch)
            {
                shell_buf[idx++] = ch;
                uart_putc(ch);
            }
            else
            {
                continue;
            }
        }
    }
}
