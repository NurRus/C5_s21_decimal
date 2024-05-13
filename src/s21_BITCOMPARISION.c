#include "s21_decimal.h"

int s21_BITCOMPARISION(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  int n = 95;
  int k = 0;
  int i = 31;
  while (n > 0 && result == 0) {
    if (n >= 64) {
      k = 2;
    } else if (n < 64 && n >= 32) {
      k = 1;
    } else if (n < 32) {
      k = 0;
    }
    if (n == 63 || n == 31) {
      i = 31;
    }
    if ((value_1.bits[k] & (LOW_MASK << i)) >
        (value_2.bits[k] & (LOW_MASK << i))) {
      result = 1;
    }
    if ((value_1.bits[k] & (LOW_MASK << i)) <
        (value_2.bits[k] & (LOW_MASK << i))) {
      result = 2;
    }
    i--;
    n--;
  }
  return result;
}