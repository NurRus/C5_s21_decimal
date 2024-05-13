#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  s21_decimal tempvalue_1, tempvalue_2;
  s21_EQUALITYDECIMAL(&tempvalue_1, value_1);
  s21_EQUALITYDECIMAL(&tempvalue_2, value_2);
  int sign;
  if ((value_1.bits[3] >> 31) != (value_2.bits[3] >> 31)) {
    sign = 1;
  }
  int digit2 = s21_NUMBEROFDIGITS(value_2);
  int digit1 = s21_NUMBEROFDIGITS(value_1);
  int exp = s21_EXPOFTEN(value_1) - s21_EXPOFTEN(value_2);
  s21_RESETDECIMAL(result);
  if (digit2 == 0) {
    flag = 3;
  } else if (digit1 > 0) {
    while (digit1 < 93) {
      s21_MULTENEXP(&tempvalue_1, 1);
      digit1 = s21_NUMBEROFDIGITS(tempvalue_1);
      exp++;
    }
    while (digit2 >= digit1) {
      s21_DIVTENEXP(&tempvalue_2, 1);
      exp++;
      digit2 = s21_NUMBEROFDIGITS(tempvalue_2);
    }
    s21_DIVALGORITM(tempvalue_1, tempvalue_2, result);
  }
  if (flag == 0 && s21_NUMBEROFDIGITS(*result) > 0) {
    s21_SIGNANDEXPRECORDING(result, sign, exp);
    flag = s21_MANTISSAOPTIMIZATION(result, sign, exp);
  }
  return flag;
}