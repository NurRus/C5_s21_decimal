#include "s21_decimal.h"

int s21_MULTENEXP(s21_decimal *value, int exp) {
  int result = 0;
  int i = 0;
  s21_decimal addvalue_1, addvalue_2, tempvalue;
  s21_EQUALITYDECIMAL(&tempvalue, *value);
  while (i < exp && result == 0) {
    s21_EQUALITYDECIMAL(&addvalue_1, *value);
    s21_EQUALITYDECIMAL(&addvalue_2, *value);
    s21_RESETDECIMAL(value);
    s21_SHIFTLEFT(&addvalue_1, 1);
    s21_SHIFTLEFT(&addvalue_2, 3);
    result = s21_ADDALGORITM(&addvalue_1, &addvalue_2, value);
    s21_RESETDECIMAL(&addvalue_1);
    s21_RESETDECIMAL(&addvalue_2);
    i++;
  }
  if (result != 0) {
    s21_EQUALITYDECIMAL(value, tempvalue);
  }
  return result;
}