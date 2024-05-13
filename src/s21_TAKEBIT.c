#include "s21_decimal.h"

void s21_TAKEBIT(s21_decimal *value, int digit) {
  int bit = 0;
  int n = digit + 1;
  int k = 0;
  int i = 0;
  while (n < 96 && bit == 0) {
    if (n < 32) {
      k = 0;
      i = n;
    } else if (n >= 32 && n < 64) {
      k = 1;
      i = n - 32;
    } else if (n >= 64 && n < 96) {
      k = 2;
      i = n - 64;
    }
    bit = (value->bits[k] & (LOW_MASK << i)) >> i;
    if (bit == 1) {
      value->bits[k] = value->bits[k] & (~(LOW_MASK << i));
    } else {
      value->bits[k] = value->bits[k] | (LOW_MASK << i);
    }
    n++;
  }
}