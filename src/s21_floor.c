#include "s21_decimal.h"

/*
Округляет указанное Decimal число
до ближайшего целого числа в сторону отрицательной бесконечности.
Функция возвращает 0 в случае успешного завершения
1 в случае ошибки.
*/
int s21_floor(s21_decimal value, s21_decimal *result) {
  int flag = 0;
  if (!result) {
    // Если указатель на decimal является NULL
    flag = 1;
  } else if (s21_is_correct_decimal(value) != 0) {
    // Проверяем, что value является корректными decimal
    flag = 1;
  } else {
    *result = s21_fill_zeros();
    // Получаем целое число
    s21_truncate(value, result);
    // Если исходное число отрицательное и не равно результату усечения
    // вычитаем единицу(уменьшаем в строну -inf)
    if (s21_get_sign(&value) && !s21_is_equal(*result, value)) {
      s21_sub(*result, ((s21_decimal){{1, 0, 0, 0}}), result);
    }
  }
  return flag;
}
