#include "s21_decimal.h"

/*
Округляет Decimal до ближайшего целого числа.
Функция возвращает 0 в случае успешного завершения
1 в случае ошибки.
*/
int s21_round(s21_decimal value, s21_decimal *result) {
  int flag = 0;
  if (!result) {
    // Если указатель на decimal является NULL
    flag = 1;
  } else if (s21_is_correct_decimal(value) != 0) {
    // Проверяем, что value является корректными decimal
    flag = 1;
  } else {
    *result = s21_fill_zeros();
    long double float_buff = 0.0;
    long double difference = 0;
    // Число преобразуется в long double и производится его округление
    s21_from_decimal_to_double(value, &float_buff);
    float_buff = round(float_buff);
    if (float_buff < 0.0) {
      s21_set_sign(result, 1);
      float_buff *= -1;
    }
    // Заполняем битами новое число в соответствии с округленным значением.
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
    // s21_set_pow(result, 0);
  }
  return flag;
}
