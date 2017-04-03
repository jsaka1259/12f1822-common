#include <common.h>

void i2c_master_init(void)
{
    SSP1CON1  = 0x28;
    SSP1ADD   = 0x13;
}

void i2c_slave_init(uint8_t slave_addr)
{
    SSP1STAT        = 0x80;
    SSP1CON1        = 0x26;
    SSP1CON2       |= 0x01;
    SSP1ADD         = (slave_addr << 1) & 0xFE;
    SSP1MSK         = 0xFE;
    PIR1bits.SSP1IF = 0;
    PIE1bits.SSP1IE = 1;
}

 void i2c_tx_data(uint8_t data)
{
    PIR1bits.SSP1IF = 0;
    SSPBUF = data;
    while(!PIR1bits.SSP1IF);
}

uint8_t i2c_rx_data(void)
{
    PIR1bits.SSP1IF = 0;
    SSP1CON2bits.RCEN = 1;
    while(SSP1CON2bits.RCEN);
    return SSPBUF;
}

void i2c_master_write(uint8_t addr, uint8_t data)
{
    SSP1CON2bits.SEN = 1;
    while(SSP1CON2bits.SEN);
    i2c_tx_data((addr << 1) & 0xFE);
    i2c_tx_data(data);
    PIR1bits.SSP1IF  = 0;
    SSP1CON2bits.PEN = 1;
    while(SSP1CON2bits.PEN);
}

uint8_t i2c_master_read(uint8_t addr)
{
    uint8_t data;
    SSP1CON2bits.SEN   = 1;
    while(SSP1CON2bits.SEN);
    i2c_tx_data((addr << 1) | 0x01);
    data = i2c_rx_data();
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
    while(SSP1CON2bits.ACKEN);
    PIR1bits.SSP1IF    = 0;
    SSP1CON2bits.PEN   = 1;
    while(SSP1CON2bits.PEN);
    return data;
}

void i2c_slave_write(uint8_t data)
{
    uint8_t buf;
    if(PIR1bits.SSP1IF)
    {
        if((SSP1STAT & 0x04) != 0)
        {
            if((SSP1STAT & 0x01) != 0)
            {
                buf       = SSP1BUF;
                SSP1BUF   = data;
                SSP1CON1 |= 0x10;
            }
            else
            {
                if((SSP1CON2 & 0x40) == 0)
                {
                    SSP1BUF   = 0;
                    SSP1CON1 |= 0x10;
                }
                else
                {
                }
            }
        }
        PIR1bits.SSP1IF = 0;
   }
} 

uint8_t i2c_slave_read(uint8_t* data)
{
    uint8_t ret = -1;
    uint8_t buf;
    if(PIR1bits.SSP1IF)
    {
        if((SSP1STAT & 0x04) == 0)
        {
            if( (SSP1STAT & 0x20) == 0)
            {
                buf = SSP1BUF;
            }
            else
            {
                ret = 0;
                *data = SSP1BUF;
            }
            SSP1CON1 |= 0x10;
        }
        PIR1bits.SSP1IF = 0;
    }
    return ret;
}
