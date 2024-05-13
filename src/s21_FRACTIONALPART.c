#include "s21_decimal.h"

int s21_FRACTIONALPART(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  s21_decimal tempvalue_1, tempvalue_2;
  s21_RESETDECIMAL(&tempvalue_1);
  s21_RESETDECIMAL(&tempvalue_2);
  s21_ADDALGORITM(&value_1, &value_1, &tempvalue_1);
  int compare = s21_BITCOMPARISION(tempvalue_1, value_2);
  if (compare == 1) {
    s21_SUBALGORITM(tempvalue_1, value_2, &tempvalue_2);
    s21_MULTENEXP(&tempvalue_2, 1);
    compare = s21_BITCOMPARISION(tempvalue_2, value_2);
    if (compare == 1 || compare == 0) {
      result = 7;
    }
  } else if (compare == 0) {
    result = 5;
  } else {
    result = 3;
  }
  return result;
}