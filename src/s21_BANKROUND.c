#include "s21_decimal.h"

void s21_BANKROUND(s21_decimal *value, int remain) {
  int j = 0;
  int i = 0;
  int k = 0;
  int bit_v = value->bits[0] & LOW_MASK;
  if (bit_v == 0 && remain > 5) {
    value->bits[k] = value->bits[k] | (LOW_MASK << i);
  }
  if (bit_v == 1 && remain >= 5) {
    while (bit_v == 1) {
      value->bits[k] = value->bits[k] & (~(LOW_MASK << i));
      j++;
      i++;
      if (j == 32 || j == 64) {
        i = 0;
        k++;
      }
      bit_v = (value->bits[k] & (LOW_MASK << i)) >> i;
    }
    value->bits[k] = value->bits[k] | (LOW_MASK << i);
  }
}