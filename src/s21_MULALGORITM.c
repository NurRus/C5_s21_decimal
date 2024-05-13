#include "s21_decimal.h"

int s21_MULALGORITM(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  int flag = 0;
  s21_RESETDECIMAL(result);
  int digit1 = s21_NUMBEROFDIGITS(value_1);
  int digit2 = s21_NUMBEROFDIGITS(value_2);
  s21_decimal tempvalue_1, tempvalue_2, tempvalue_3, tempresult;
  if (digit1 >= digit2) {
    s21_EQUALITYDECIMAL(&tempvalue_1, value_1);
    s21_EQUALITYDECIMAL(&tempvalue_2, value_2);
  } else {
    s21_EQUALITYDECIMAL(&tempvalue_2, value_1);
    s21_EQUALITYDECIMAL(&tempvalue_1, value_2);
    digit2 = digit1;
    digit1 = s21_NUMBEROFDIGITS(value_2);
  }
  int j = 0;
  int k = 0;
  int i = 0;
  int bit_v;
  for (; j < digit2; j++) {
    if (j == 32 || j == 64) {
      k++;
      i = 0;
    }
    bit_v = (tempvalue_2.bits[k] & (LOW_MASK << i)) >> i;
    if (bit_v == 1) {
      s21_EQUALITYDECIMAL(&tempvalue_3, tempvalue_1);
      s21_EQUALITYDECIMAL(&tempresult, *result);
      s21_SHIFTLEFT(&tempvalue_3, j);
      s21_RESETDECIMAL(result);
      flag = s21_ADDALGORITM(&tempresult, &tempvalue_3, result);
    }
    i++;
  }
  return flag;
}