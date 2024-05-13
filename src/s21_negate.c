#include "s21_decimal.h"

/**
 Операция отрицания для десятичного числа.

 Функция принимает десятичное число dec и указатель на структуру result, в
 которую будет сохранен результат.

 Возвращает 0, если операция отрицания выполнена успешно.
 1 в случае ошибки.
 */
int s21_negate(s21_decimal dec, s21_decimal *result) {
  int flag = 1;  // Инициализация флага ошибки
  if (result) {  // Проверяем, что result не равен NULL
    *result = s21_fill_zeros();     // Заполняем result нулями
    int sign = s21_get_sign(&dec);  // Получаем знак числа dec
    *result = dec;
    // Изменяем знак числа в result
    if (sign == 1) {
      s21_set_sign(result, 0);  // Если исходное число отрицательное,
                                // устанавливаем положительный знак
    } else {
      s21_set_sign(result, 1);  // Устанавливаем отрицательный знак
    }
    if (s21_is_correct_decimal(dec) == 0) {
      flag = 0;  // Операция выполнена успешно, сбрасываем флаг ошибки
    }
  }
  return flag;  // Возвращаем флаг ошибки
}
