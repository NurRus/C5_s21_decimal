#include "s21_decimal.h"

s21_decimal s21_decimal_int_max(void) {
  // 2147483647
  s21_decimal result = s21_fill_zeros();
  result.bits[0] = 0b01111111111111111111111111111111;
  return result;
}
