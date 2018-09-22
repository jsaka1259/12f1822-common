#include <common.h>

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

void uart_init(void)
{
    APFCONbits.RXDTSEL = 1;     // RX -> RA5
    APFCONbits.TXCKSEL = 1;     // TX -> RA4
    
    BAUDCON = BRG16;
    SPBRG   = SPBRG_DATA;
    TXSTA   = (TX9_RX9_DATA | BRGH_DATA | 0x20);
    RCSTA   = (TX9_RX9_DATA | 0x90);
    
    PIR1bits.RCIF = 0;
    PIE1bits.RCIE = 0;
}

void uart_putc(const char byte)
{
    while(TXIF == 0);
    TXREG = byte;
}

uint8_t uart_puts(const char* ptr)
{
    uint8_t len = 0;
    while(ptr[len] != 0x00)
    {
        uart_putc(ptr[len++]);
    }
    return len;
}

uint8_t uart_getc(void)
{
    while(PIR1bits.RCIF == 0);
    RCIE = 0;
    return RCREGbits.RCREG;
}
