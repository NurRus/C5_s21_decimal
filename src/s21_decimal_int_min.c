#include "s21_decimal.h"

s21_decimal s21_decimal_int_min(void) {
  // -2147483648
  s21_decimal result = s21_fill_zeros();
  result.bits[0] = 0b10000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  return result;
}
