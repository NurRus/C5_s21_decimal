#include "s21_decimal.h"

void s21_SHIFTLEFT(s21_decimal *value, int n) {
  int f[3];
  for (int i = 0; i < n; i++) {
    f[0] = 0;
    f[1] = 0;
    f[2] = 0;
    if ((value->bits[2] >> 31) == 1) f[2] = 1;
    if ((value->bits[1] >> 31) == 1) f[1] = 1;
    if ((value->bits[0] >> 31) == 1) f[0] = 1;
    value->bits[0] = value->bits[0] << 1;
    value->bits[1] = value->bits[1] << 1;
    value->bits[2] = value->bits[2] << 1;
    if (f[0] == 1) {
      value->bits[1] = value->bits[1] | LOW_MASK;
    }
    if (f[1] == 1) {
      value->bits[2] = value->bits[2] | LOW_MASK;
    }
    if (f[2] == 1) {
      value->bits[2] = value->bits[2] | HIGHT_MASK;
    }
  }
}