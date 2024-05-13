#include "s21_decimal.h"

void s21_SUBALGORITM(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  s21_decimal tempvalue_1, tempvalue_2;
  for (int i = 0; i < 3; i++) {
    tempvalue_1.bits[i] = value_1.bits[i];
    tempvalue_2.bits[i] = value_2.bits[i];
  }
  int max_digit = s21_NUMBEROFDIGITS(value_1);
  int i = 0;
  int k = 0;
  int bit_v1 = 0;
  int bit_v2 = 0;
  for (int j = 0; j < max_digit; j++) {
    if (j == 32 || j == 64) {
      i = 0;
      k++;
    }
    bit_v1 = (tempvalue_1.bits[k] & (LOW_MASK << i)) >> i;
    bit_v2 = (tempvalue_2.bits[k] & (LOW_MASK << i)) >> i;
    if (bit_v1 == 1 && bit_v2 == 0) {
      result->bits[k] = result->bits[k] | (LOW_MASK << i);
    }
    if (bit_v1 == 0 && bit_v2 == 1) {
      result->bits[k] = result->bits[k] | (LOW_MASK << i);
      s21_TAKEBIT(&tempvalue_1, j);
    }
    i++;
  }
  result->bits[3] = value_1.bits[3];
}