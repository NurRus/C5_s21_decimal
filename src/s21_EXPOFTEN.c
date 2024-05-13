#include "s21_decimal.h"

int s21_EXPOFTEN(s21_decimal value) {
  int result = 0;
  result = (value.bits[3] & EXP_MASK) >> 16;
  return result;
}