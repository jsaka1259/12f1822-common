#include "utils.h"

void itostring(uint8_t digit, uint8_t *buf, uint16_t data) {
  uint8_t i;

  buf += digit;
  for(i = digit; i > 0; i--) {
    buf--;
    *buf = (data % 10) + '0';
    data = data / 10;
  }
}
