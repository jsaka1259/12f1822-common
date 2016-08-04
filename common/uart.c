/**
 * @file    uart.c
 * @brief   UART Library API
 * @date    2016/06/30
 * @auther  jsaka1259
 */
#include <common.h>

/**
 * @brief   Initialize UART
 * @param   None
 * @return  None
 */
void uart_init(void)
{
    BAUDCON = BRG16;
    SPBRG   = SPBRG_DATA;
    TXSTA   = (TX9_RX9_DATA | BRGH_DATA | 0x20);
    RCSTA   = (TX9_RX9_DATA | 0x90);
    
    RCIF    = 0;
    RCIE    = 0;
}

/**
 * @brief   Put a Character to UART
 * @param   byte    : Input a Character
 * @return  None
 */
void uart_putc(const char byte)
{
    while(TXIF == 0);
    TXREG = byte;
}

/**
 * @brief   Put String
 * @param   ptr     : String Pointer
 * @return  String Length
 */
uint8_t uart_puts(const char* ptr)
{
    uint8_t len = 0;
    while(ptr[len] != 0x00)
    {
        uart_putc(ptr[len++]);
    }
    return len;
}

/**
 * @brief   Get a Character
 * @param   None
 * @return  A Character from UART
 */
char uart_getc(void)
{
    while(RCIF == 0);
    RCIE = 0;
    return RCREG;
}
