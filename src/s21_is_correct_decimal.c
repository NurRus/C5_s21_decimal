#include "s21_decimal.h"

/* проверерка корректности данных, записанных в структуру decimal
Возвращает 1 если выполняется хотя бы одно условие:
bits[3] биты от 0 до 15 не равны нулю.
bits[3] биты с 16 по 23 содержат степень меньше 0 или больше 28
bits[3] биты с 24 по 30 не равны нулю.
0 - ок
1 - данные некорректны
*/
int s21_is_correct_decimal(s21_decimal decimal) {
  int flag = 0;
  // проверяем части, которые должны быть заполнены нулями
  bits_3 template;
  template.cell = decimal.bits[3];
  if (template.sections.zeros_1 != 0 || template.sections.zeros_2 != 0) {
    flag = 1;
    // проверяем степень, должна быть в диапазоне от 0 до 28
  } else {
    int pow = template.sections.pow;
    if (pow < 0 || pow > 28) {
      flag = 1;
    }
  }
  return flag;
}
