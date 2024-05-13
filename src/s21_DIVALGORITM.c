#include "s21_decimal.h"

void s21_DIVALGORITM(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  s21_decimal devider, dividend, subvalue;
  s21_RESETDECIMAL(&devider);
  int compar = 0;
  int translation;
  int remainder = 0;
  translation = s21_NUMBEROFDIGITS(value_1) - s21_NUMBEROFDIGITS(value_2);
  s21_EQUALITYDECIMAL(&dividend, value_1);
  while (translation >= 0) {
    s21_SHIFTLEFT(result, 1);
    s21_RESETDECIMAL(&subvalue);
    s21_RESETDECIMAL(&devider);
    s21_EQUALITYDECIMAL(&devider, value_2);
    s21_SHIFTLEFT(&devider, translation);
    compar = s21_BITCOMPARISION(dividend, devider);
    if (compar == 0 || compar == 1) {
      s21_SUBALGORITM(dividend, devider, &subvalue);
      s21_EQUALITYDECIMAL(&dividend, subvalue);
      result->bits[0] = result->bits[0] | LOW_MASK;
    }
    translation--;
  }
  if (s21_NUMBEROFDIGITS(dividend) != 0) {
    remainder = s21_FRACTIONALPART(dividend, value_2);
    s21_BANKROUND(result, remainder);
  }
}