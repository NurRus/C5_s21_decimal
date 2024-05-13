#include "s21_decimal.h"

int s21_NUMBEROFDIGITS(s21_decimal value) {
  int count = 0;
  int i = 0;
  while (i < 32 && (value.bits[2] & (HIGHT_MASK >> i)) == 0) {
    count++;
    i++;
  }
  if (count == 32) {
    i = 0;
    while (i < 32 && (value.bits[1] & (HIGHT_MASK >> i)) == 0) {
      count++;
      i++;
    }
  }
  if (count == 64) {
    i = 0;
    while (i < 32 && (value.bits[0] & (HIGHT_MASK >> i)) == 0) {
      count++;
      i++;
    }
  }
  return 96 - count;
}