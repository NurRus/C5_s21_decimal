#include "s21_decimal.h"

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;
  s21_decimal tempvalue_1, tempvalue_2;
  s21_EQUALITYDECIMAL(&tempvalue_1, value_1);
  s21_EQUALITYDECIMAL(&tempvalue_2, value_2);
  if ((value_1.bits[3] >> 31) == (value_2.bits[3] >> 31)) {
    s21_NORMALIZATION(&tempvalue_1, &tempvalue_2);
    if (s21_BITCOMPARISION(tempvalue_1, tempvalue_2) == 0) {
      result = 0;
    }
  }
  return result;
}