/**
 * @file    common.c
 * @brief   Initialize PIC12F1822 Common Library API
 * @date    2016/06/29  : create
 * @auther  jsaka1259
 */
#include <common.h>

// CONFIG1
#pragma config FOSC     = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE     = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE    = ON        // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE    = OFF       // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP       = OFF       // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD      = OFF       // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN    = ON        // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF       // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO     = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN    = OFF       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT      = OFF       // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN    = ON        // PLL Enable (4x PLL enabled)
#pragma config STVREN   = ON        // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV     = HI        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), high trip point selected.)
#pragma config LVP      = OFF       // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

/**
 * @brief   Initialize PIC12F1822
 * @param   None
 * @return  None
 */
void common_init(void)
{
    OSCCON = 0xF0;               // OSC 32MHz(with Internal Oscillator)
    PORTA  = 0x04;               // RA Pin default Low
    ANSELA = 0x00;               // All Digital Pin
    TRISA  = 0x0A;               // RA1, 3 Input Mode
    WPUA   = 0x08;               // Assign RA3 WPU
    nWPUEN = 0;                  // Enable WPU
    
    APFCONbits.TXCKSEL = 0;      // TX/CK function is on RA0
    APFCONbits.RXDTSEL = 0;      // RX/DT function is on RA1
    
    uart_init();
}
