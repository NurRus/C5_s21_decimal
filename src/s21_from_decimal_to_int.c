#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int flag = 0;
  if (!dst) {
    flag = 1;  // если указатель является NULL ставим флаг ошибки
  } else if (s21_is_correct_decimal(src) != 0) {
    flag = 1;  // если src не корректный ставим флаг ошибки
  } else {
    *dst = 0;
    s21_decimal trim_to_dot;
    s21_RESETDECIMAL(&trim_to_dot);
    s21_truncate(src, &trim_to_dot);  // обрезаем и отбрасываем дробную часть
    if (s21_is_less(trim_to_dot, s21_decimal_int_min()) == 1) {
      flag = 1;  // если число меньше -2147483648 ставим флаг ошибки
    } else if (s21_is_greater(trim_to_dot, s21_decimal_int_max()) == 1) {
      flag = 1;  // если число больше 2147483647 ставим флаг ошибки
    } else {
      *dst = trim_to_dot.bits[0];  // присваиваем инту значение
      if (s21_get_sign(&src) == 1 && *dst != MIN_INT) {
        *dst = -*dst;  // меняем знак если число отрицательное, кроме MIN_INT
      }
    }
  }
  return flag;
}
