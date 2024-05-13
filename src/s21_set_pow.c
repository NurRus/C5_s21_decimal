#include "s21_decimal.h"

void s21_set_pow(s21_decimal *decimal, int pow) {
  bits_3 temp;
  temp.cell = decimal->bits[3];
  temp.sections.pow = pow;
  decimal->bits[3] = temp.cell;
}
