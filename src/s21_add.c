#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  int zero1 = s21_CHECKINGFORZERO(value_1);
  int zero2 = s21_CHECKINGFORZERO(value_2);
  s21_decimal tempvalue_1, tempvalue_2;
  s21_EQUALITYDECIMAL(&tempvalue_1, value_1);
  s21_EQUALITYDECIMAL(&tempvalue_2, value_2);
  s21_NORMALIZATION(&tempvalue_1, &tempvalue_2);
  int sign1 = value_1.bits[3] >> 31;
  int sign2 = value_2.bits[3] >> 31;
  int paramter1 = sign1 - sign2;
  int paramter2 = s21_BITCOMPARISION(tempvalue_1, tempvalue_2);
  switch (paramter1) {
    case 0:
      flag = s21_ADDALGORITM(&tempvalue_1, &tempvalue_2, result);
      break;
    case -1:
    case 1: {
      if (paramter2 == 0) {
        s21_RESETDECIMAL(result);
      } else if (paramter2 == 2) {
        s21_SUBALGORITM(tempvalue_2, tempvalue_1, result);
      } else if (paramter2 == 1) {
        s21_SUBALGORITM(tempvalue_1, tempvalue_2, result);
      }
      break;
    }
  }
  if (zero1 == 1) {
    s21_EQUALITYDECIMAL(result, value_2);
  } else if (zero2 == 1) {
    s21_EQUALITYDECIMAL(result, value_1);
  }
  int sign = result->bits[3] >> 31;
  if (flag == 1 && sign == 1) {
    flag = 2;
  }
  if (flag == 0 && s21_NUMBEROFDIGITS(*result) > 0) {
    int exp = s21_EXPOFTEN(tempvalue_1);
    int sign = result->bits[3] >> 31;
    s21_MANTISSAOPTIMIZATION(result, sign, exp);
  } else {
    s21_RESETDECIMAL(result);
  }
  return flag;
}