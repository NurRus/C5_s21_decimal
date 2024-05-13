#include "s21_decimal.h"

/*
Конвертирует decimal в float
Функция возвращает 0 в случае успешного завершения
1 в случае ошибки.
*/
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int flag = 0;
  if (!dst) {
    flag = 1;  // если указатель является NULL ставим флаг ошибки
  } else if (s21_is_correct_decimal(src) != 0) {
    flag = 1;  // если src не корректный ставим флаг ошибки
  } else {
    double temp = (double)*dst;
    for (int i = 0; i < 96; i++) {
      temp += s21_get_bit(src, i) * pow(2, i);
    }
    temp = temp * pow(10, -s21_get_pow(src));
    if (s21_get_bit(src, 127)) temp = temp * (-1);
    *dst = temp;
  }
  return flag;
}
