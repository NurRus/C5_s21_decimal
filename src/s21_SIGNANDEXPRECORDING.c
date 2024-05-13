#include "s21_decimal.h"

void s21_SIGNANDEXPRECORDING(s21_decimal *value, int sign, int exp) {
  value->bits[3] = 0;
  value->bits[3] = exp << 16;
  if (sign == 1) {
    value->bits[3] = value->bits[3] | HIGHT_MASK;
  }
}