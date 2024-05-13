#include "s21_decimal.h"

void s21_NORMALIZATION(s21_decimal *value_1, s21_decimal *value_2) {
  int exp1 = s21_EXPOFTEN(*value_1);
  int exp2 = s21_EXPOFTEN(*value_2);
  if (exp1 > exp2) {
    int deltaexp = exp1 - exp2;
    while ((s21_NUMBEROFDIGITS(*value_2) + 4) <= 96 && deltaexp > 0) {
      s21_MULTENEXP(value_2, 1);
      deltaexp--;
      value_2->bits[3] = value_2->bits[3] + (1 << 16);
    }
    if (deltaexp > 0) {
      s21_DIVTENEXP(value_1, deltaexp);
      value_1->bits[3] = value_1->bits[3] - (deltaexp << 16);
    }
  }
  if (exp2 > exp1) {
    int deltaexp = exp2 - exp1;
    while ((s21_NUMBEROFDIGITS(*value_1) + 4) <= 96 && deltaexp > 0) {
      s21_MULTENEXP(value_1, 1);
      deltaexp--;
      value_1->bits[3] = value_1->bits[3] + (1 << 16);
    }
    if (deltaexp > 0) {
      s21_DIVTENEXP(value_2, deltaexp);
      value_2->bits[3] = value_2->bits[3] - (deltaexp << 16);
    }
  }
}