#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int flag = 0;
  if (!result) {
    flag = 1;
  } else if (s21_is_correct_decimal(value) != 0) {
    // Проверяем, что value является корректными decimal
    flag = 1;
  } else {
    s21_RESETDECIMAL(result);
    float difference = 0;
    // Проверяем, содержит ли исходное число ненулевую степень
    if (s21_get_pow(value)) {
      // Если содержит, то число преобразуем в long double,
      // и производим его усечение с использованием функции trunc()
      long double float_buff = 0.0;
      s21_from_decimal_to_double(value, &float_buff);
      float_buff = trunc(float_buff);
      if (float_buff < 0.0) {
        s21_set_sign(result, 1);
        float_buff *= -1;
      }
      // После этого происходит заполнение битов нового числа
      for (int i = 0; float_buff >= 1 && i < 96; i++) {
        float_buff = floor(float_buff) / 2;
        difference = float_buff - floor(float_buff);
        if (difference > 0.0) {
          s21_set_bit(result, i, 1);
        } else {
          s21_set_bit(result, i, 0);
        }
      }
      // Обнуляем степень
      s21_set_pow(result, 0);
    } else {
      for (int i = 0; i < 4; ++i) {
        result->bits[i] = value.bits[i];
      }
    }
  }
  return flag;
}
