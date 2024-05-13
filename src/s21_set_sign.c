#include "s21_decimal.h"

void s21_set_sign(s21_decimal *decimal, int sign) {
  bits_3 temp;
  temp.cell = decimal->bits[3];
  temp.sections.sign = sign;
  decimal->bits[3] = temp.cell;
}
