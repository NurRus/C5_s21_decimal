#include "s21_decimal.h"

void s21_EQUALITYDECIMAL(s21_decimal *result, s21_decimal value) {
  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }
}