#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int flag = 0;
  if (!dst) {
    flag = 1;
  } else {
    int sign = 0;
    s21_RESETDECIMAL(dst);
    if (src < 0) {
      sign = 1;
      if (src != MIN_INT) {
        src = -src;
      }
    }
    dst->bits[0] = src;
    s21_SIGNANDEXPRECORDING(dst, sign, 0);
  }
  return flag;
}
