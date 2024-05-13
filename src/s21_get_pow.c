#include "s21_decimal.h"

/*
Возвращает степень числа из bits[3]
*/
int s21_get_pow(s21_decimal decimal) {
  bits_3 template;
  template.cell = decimal.bits[3];
  return template.sections.pow;
}
