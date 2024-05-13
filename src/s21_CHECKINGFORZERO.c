#include "s21_decimal.h"

int s21_CHECKINGFORZERO(s21_decimal value) {
  int result = 1;
  for (int i = 0; i < 3; i++) {
    if (value.bits[i] != 0) {
      result = 0;
    }
  }
  return result;
}