#include "s21_decimal.h"

void s21_RESETDECIMAL(s21_decimal *value) {
  for (int i = 0; i < 4; i++) {
    value->bits[i] = 0;
  }
}