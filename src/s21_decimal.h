#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXP_MASK 0b00000000111111110000000000000000
#define HIGHT_MASK 0b10000000000000000000000000000000
#define LOW_MASK 0b00000000000000000000000000000001
#define EXPMAX 28
#define MIN_INT -2147483648
#define MIN_FLOAT 0.0000000000000000000000000001f
#define MAX_FLOAT 79228162514264337593543950335.0f

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef union bits_3 {
  int cell;
  struct {
    uint32_t zeros_1 : 16;
    uint32_t pow : 8;
    uint32_t zeros_2 : 7;
    uint32_t sign : 1;
  } sections;
} bits_3;

typedef union {
  int sp_int;
  float sp_float;
} float_dec;

//Сравнение
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);

//Арифметика
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

//Преобразования
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

//Другие
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);

//вспомогательные для преобразования и других
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_is_correct_decimal(s21_decimal decimal);
int s21_get_bit(s21_decimal dst, int index);
int s21_get_pow(s21_decimal decimal);
int s21_get_sign(s21_decimal *decimal);
int s21_from_decimal_to_double(s21_decimal src, long double *dst);
void s21_set_bit(s21_decimal *dst, int index, int bit);
void s21_set_sign(s21_decimal *decimal, int sign);
void s21_set_pow(s21_decimal *decimal, int pow);
int s21_truncate(s21_decimal value, s21_decimal *result);
s21_decimal s21_decimal_int_min(void);
s21_decimal s21_decimal_int_max(void);
s21_decimal s21_fill_zeros(void);

//вспомогательные для арифметики
int s21_EXPOFTEN(s21_decimal value);
void s21_NORMALIZATION(s21_decimal *value_1, s21_decimal *value_2);
int s21_ADDALGORITM(s21_decimal *value_1, s21_decimal *value_2,
                    s21_decimal *result);
void s21_SUBALGORITM(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result);
void s21_SHIFTLEFT(s21_decimal *value, int n);
int s21_NUMBEROFDIGITS(s21_decimal value);
int s21_BITCOMPARISION(s21_decimal value_1, s21_decimal value_2);
int s21_MULTENEXP(s21_decimal *value, int exp);
int s21_DIVTENEXP(s21_decimal *value, int exp);
void s21_BANKROUND(s21_decimal *value, int remain);
void s21_TAKEBIT(s21_decimal *value, int digit);
int s21_CHECKINGFORZERO(s21_decimal value);
void s21_RESETDECIMAL(s21_decimal *value);
void s21_EQUALITYDECIMAL(s21_decimal *result, s21_decimal value);
int s21_MULALGORITM(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result);
void s21_SIGNANDEXPRECORDING(s21_decimal *value, int sign, int exp);
void s21_DIVALGORITM(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result);
int s21_FRACTIONALPART(s21_decimal value_1, s21_decimal value_2);
int s21_MANTISSAOPTIMIZATION(s21_decimal *value, int sign, int exp);

#endif
