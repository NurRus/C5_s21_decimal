#include "s21_decimal.h"

/*
Функция преобразует десятичное число в число с плавающей точкой long double
*/
int s21_from_decimal_to_double(s21_decimal src, long double *dst) {
  long double temp = (double)*dst;
  for (int i = 0; i < 96; i++) {
    temp += s21_get_bit(src, i) * pow(2, i);
  }
  temp = temp * pow(10, -s21_get_pow(src));
  if (s21_get_sign(&src)) temp = temp * (-1);
  *dst = temp;
  return 0;
}
