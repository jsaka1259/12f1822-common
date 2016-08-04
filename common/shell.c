/**
 * @file    shell.c
 * @brief   Shell API
 * @date    2016/07/16
 * @auther  jsaka1259
 */
#include <common.h>

#define SHELL_BUF_SIZE (0x28)
static char shell_buf[SHELL_BUF_SIZE];

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
            if(0x0D == ch || SHELL_BUF_SIZE <= idx)
            {
                shell_buf[idx] = 0x00;
                uart_putc('\n');
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
