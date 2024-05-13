#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal tempvalue_1, tempvalue_2;
  s21_EQUALITYDECIMAL(&tempvalue_1, value_1);
  s21_EQUALITYDECIMAL(&tempvalue_2, value_2);
  int flag = 0;
  int digit1 = s21_NUMBEROFDIGITS(value_1);
  int digit2 = s21_NUMBEROFDIGITS(value_2);
  int exp = s21_EXPOFTEN(value_1) + s21_EXPOFTEN(value_2);
  int digit = digit1 + digit2;
  int sign = 0;
  if ((value_1.bits[3] >> 31) != (value_2.bits[3] >> 31)) {
    sign = 1;
  }
  while (digit > 96) {
    if (digit1 >= digit2) {
      s21_DIVTENEXP(&tempvalue_1, 1);
      exp--;
      digit1 = s21_NUMBEROFDIGITS(tempvalue_1);
    } else {
      s21_DIVTENEXP(&tempvalue_2, 1);
      exp--;
      digit2 = s21_NUMBEROFDIGITS(tempvalue_2);
    }
    digit = digit1 + digit2;
  }
  flag = s21_MULALGORITM(tempvalue_1, tempvalue_2, result);
  if (flag == 0) {
    flag = s21_MANTISSAOPTIMIZATION(result, sign, exp);
  }
  if (flag != 0) {
    s21_RESETDECIMAL(result);
  }
  return flag;
}