#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  *dst = s21_fill_zeros();
  int flag = 0;
  // Проверяем на наличие бесконечности или NaN
  if (isinf(src) || isnan(src)) {
    flag = 1;
  } else {
    if (src != 0) {
      // Получаем знак числа src
      int sign = *(int *)&src >> 31;
      // Получаем экспоненту числа src
      // *(int *)&src - это приведение указателя src к типу int, чтобы получить
      // доступ к битам числа. ~0x80000000 - это инвертирование бита знака,
      // чтобы оставить только биты экспоненты.
      // >> 23 - это сдвиг вправо на 23 бита, чтобы извлечь экспоненту.
      // - 127 - это коррекция смещения экспоненты в формате с плавающей
      // запятой.
      int exp = ((*(int *)&src & ~0x80000000) >> 23) - 127;
      double temp = (double)fabs(src);
      int right_zeros = 0;
      // Находим отступ (right_zeros) до 7 значащих знаков
      for (; right_zeros < 28 && (int)temp / (int)pow(2, 21) == 0;
           right_zeros++) {
        temp *= 10;
      }
      // Округляем temp
      temp = round(temp);
      // Проверяем на допустимость значений exp и right_zeros
      if (right_zeros <= 28 && (exp > -94 && exp < 96)) {
        // Структура для работы с битами мантиссы
        float_dec mantissa = {0};
        // Преобразуем temp во float и сохраняем
        temp = (float)temp;
        // цикл используется для удаления нулей справа в мантиссе числа src.
        // fmod(temp, 10) == 0 проверяет, является ли последняя цифра нулем.
        // right_zeros > 0 проверяет, что количество нулей (отступ) больше 0.
        for (; fmod(temp, 10) == 0 && right_zeros > 0; right_zeros--) {
          temp /= 10;
        }
        // Сохраняем мантиссу в структуру float_dec
        mantissa.sp_float = temp;
        // Вычисляем новую экспоненту из мантиссы
        exp = ((*(int *)&mantissa.sp_float & ~0x80000000) >> 23) - 127;
        // Устанавливаем биты мантиссы в s21_decimal
        dst->bits[exp / 32] |= 1 << exp % 32;
        for (int i = exp - 1, j = 22; j >= 0; i--, j--)
          if ((mantissa.sp_int & (1 << j)) != 0)
            dst->bits[i / 32] |= 1 << i % 32;
        // Устанавливаем знак и отступ в s21_decimal
        dst->bits[3] = (sign << 31) | (right_zeros << 16);
      }
    }
  }
  return flag;
}
