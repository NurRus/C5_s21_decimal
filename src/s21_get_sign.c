#include "s21_decimal.h"

int s21_get_sign(s21_decimal *decimal) {
  bits_3 temp;
  int sign = 0;
  temp.cell = decimal->bits[3];
  sign = temp.sections.sign;
  return sign;
}
