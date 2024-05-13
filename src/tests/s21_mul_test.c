#include "s21_decimal_test.h"

START_TEST(s21_mul_1) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 1;
  decimal_1.bits[3] = 0b10000000000000000000000000000000;

  decimal_2.bits[0] = 1;

  value.bits[0] = 1;
  value.bits[3] = 0b10000000000000000000000000000000;

  s21_mul(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_mul_2) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[2] = 0b1011;
  decimal_1.bits[3] = 0b10000000000000110000000000000000;

  decimal_2.bits[2] = 0b10101001;

  ck_assert_int_eq(s21_mul(decimal_1, decimal_2, &result), 2);
  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_mul_3) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 0b1011;
  decimal_1.bits[3] = 0b00000000000011000000000000000000;

  decimal_2.bits[0] = 0b10101001;
  decimal_2.bits[3] = 0b00000000000111000000000000000000;

  ck_assert_int_eq(s21_mul(decimal_1, decimal_2, &result), 2);
  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_mul_4) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[1] = 0b10;
  decimal_1.bits[3] = 0b00000000000011000000000000000000;

  decimal_2.bits[1] = 0b11;
  decimal_2.bits[3] = 0b00000000000001000000000000000000;

  value.bits[2] = 0b110;
  value.bits[3] = 0b00000000000100000000000000000000;

  s21_mul(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_mul_5) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[2] = 10000000;

  decimal_2.bits[2] = 10000000;

  s21_mul(decimal_1, decimal_2, &result);

  ck_assert_int_eq(s21_mul(decimal_1, decimal_2, &result), 1);
  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

Suite *s21_mul_suite(void) {
  Suite *s = suite_create("s21_mul_suite");
  TCase *tc = tcase_create("s21_mul_testcase");

  tcase_add_test(tc, s21_mul_1);
  tcase_add_test(tc, s21_mul_2);
  tcase_add_test(tc, s21_mul_3);
  tcase_add_test(tc, s21_mul_4);
  tcase_add_test(tc, s21_mul_5);

  suite_add_tcase(s, tc);
  return s;
}