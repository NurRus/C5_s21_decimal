#include "s21_decimal.h"

int s21_DIVTENEXP(s21_decimal *value, int exp) {
  int result = 0;
  s21_decimal devider, dividend, subvalue;
  s21_RESETDECIMAL(&devider);
  int compar = 0;
  int translation;
  for (int i = 0; i < exp; i++) {
    translation = s21_NUMBEROFDIGITS(*value) - 4;
    for (int i = 0; i < 3; i++) {
      dividend.bits[i] = value->bits[i];
      value->bits[i] = 0;
    }
    while (translation >= 0) {
      s21_SHIFTLEFT(value, 1);
      s21_RESETDECIMAL(&subvalue);
      s21_RESETDECIMAL(&devider);
      devider.bits[0] = 10;
      s21_SHIFTLEFT(&devider, translation);
      compar = s21_BITCOMPARISION(dividend, devider);
      if (compar == 0 || compar == 1) {
        s21_SUBALGORITM(dividend, devider, &subvalue);
        dividend.bits[2] = subvalue.bits[2];
        dividend.bits[1] = subvalue.bits[1];
        dividend.bits[0] = subvalue.bits[0];
        value->bits[0] = value->bits[0] | LOW_MASK;
      }
      translation--;
    }
    int remainder = 0;
    remainder = dividend.bits[0];
    if (remainder > 0) {
      result = 1;
      s21_BANKROUND(value, remainder);
    }
  }
  return result;
}