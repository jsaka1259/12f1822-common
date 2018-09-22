#include <common.h>

void itostring(uint8_t digit, uint16_t data, uint8_t* buf)
{
    uint8_t lc;
    
    buf += digit;
    for(lc = digit; lc > 0; lc--)
    {
        buf--;
        *buf = (data % 10) + '0';
        data = data / 10;
    }
}
