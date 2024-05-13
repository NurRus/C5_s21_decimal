#include "s21_decimal.h"

int s21_MANTISSAOPTIMIZATION(s21_decimal *value, int sign, int exp) {
  int result = 0;
  s21_decimal tempvalue;
  s21_EQUALITYDECIMAL(&tempvalue, *value);
  int flag = 0;
  int overflow = 0;
  int digit = s21_NUMBEROFDIGITS(tempvalue);
  while (exp > 0 && flag == 0 && digit > 0) {
    flag = s21_DIVTENEXP(&tempvalue, 1);
    exp--;
    if (flag == 1) {
      exp++;
    } else {
      s21_EQUALITYDECIMAL(value, tempvalue);
    }
  }
  while (exp < 0 && overflow == 0) {
    overflow = s21_MULTENEXP(&tempvalue, 1);
    exp++;
    if (overflow == 1) {
      exp--;
    } else {
      s21_EQUALITYDECIMAL(value, tempvalue);
    }
  }
  while (exp > EXPMAX && digit > 0) {
    s21_DIVTENEXP(value, 1);
    exp--;
    digit = s21_NUMBEROFDIGITS(*value);
    if (digit == 0) {
      result = 2;
    }
  }
  s21_SIGNANDEXPRECORDING(value, sign, exp);
  if (exp < 0 && sign == 0) {
    result = 1;
  } else if (exp < 0 && sign == 1) {
    result = 2;
  }
  if (result != 0) {
    s21_RESETDECIMAL(value);
  }
  return result;
}