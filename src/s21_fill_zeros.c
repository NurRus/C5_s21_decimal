#include "s21_decimal.h"

/*
Заполняет структуру нулями
*/
s21_decimal s21_fill_zeros(void) {
  s21_decimal result;
  result.bits[0] = 0;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 0;
  return result;
}
