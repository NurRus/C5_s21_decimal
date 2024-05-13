#include "s21_decimal.h"

int s21_ADDALGORITM(s21_decimal *value_1, s21_decimal *value_2,
                    s21_decimal *result) {
  s21_RESETDECIMAL(result);
  result->bits[3] = value_1->bits[3];
  int stec = 0;
  int n = 0;
  int j = 0;
  int i = 0;
  int bit_v1 = 0;
  int bit_v2 = 0;
  int max_digit = s21_NUMBEROFDIGITS(*value_1);
  int digit2 = s21_NUMBEROFDIGITS(*value_2);
  if (digit2 > max_digit) {
    max_digit = digit2;
  }
  while (i <= max_digit && i < 96) {
    if (i == 32 || i == 64) {
      j = 0;
      n++;
    }
    bit_v1 = ((value_1->bits[n] & (LOW_MASK << j))) >> j;
    bit_v2 = ((value_2->bits[n] & (LOW_MASK << j))) >> j;
    if ((bit_v1 + bit_v2 + stec) == 2) {
      stec = 1;
    } else if ((bit_v1 + bit_v2 + stec) == 3) {
      stec = 1;
      result->bits[n] = result->bits[n] | (LOW_MASK << j);
    } else if ((bit_v1 + bit_v2 + stec) == 1) {
      stec = 0;
      result->bits[n] = result->bits[n] | (LOW_MASK << j);
    } else if ((bit_v1 + bit_v2 + stec) == 0) {
      stec = 0;
    }
    j++;
    i++;
  }
  if (stec == 1 && s21_EXPOFTEN(*value_1) > 0) {
    s21_DIVTENEXP(value_1, 1);
    s21_DIVTENEXP(value_2, 1);
    value_1->bits[3] = value_1->bits[3] - (1 << 16);
    value_2->bits[3] = value_2->bits[3] - (1 << 16);
    stec = s21_ADDALGORITM(value_1, value_2, result);
  }
  return stec;
}