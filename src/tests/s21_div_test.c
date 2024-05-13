#include "s21_decimal_test.h"

START_TEST(s21_div_1) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 2334378;

  decimal_2.bits[0] = 0;

  ck_assert_int_eq(s21_div(decimal_1, decimal_2, &result), 3);
  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_div_2) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 2334378;

  decimal_2.bits[0] = 23343780;
  decimal_2.bits[3] = 0b00000000000000010000000000000000;

  value.bits[0] = 1;

  s21_div(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_div_3) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[2] = 0b00100000000000000000000000000000;
  decimal_1.bits[3] = 0b00000000000111000000000000000000;

  decimal_2.bits[2] = 0b01000000000000000000000000000000;
  decimal_2.bits[3] = 0b00000000000000000000000000000000;

  ck_assert_int_eq(s21_div(decimal_1, decimal_2, &result), 2);
  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_div_4) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 1561;
  decimal_1.bits[3] = 0b10000000000000000000000000000000;

  decimal_2.bits[0] = 1561000;

  value.bits[0] = 1;
  value.bits[3] = 0b10000000000000110000000000000000;

  s21_div(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_div_5) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 2600000000;

  decimal_2.bits[0] = 300000000;

  value.bits[2] = 4;
  value.bits[1] = 2998786599;
  value.bits[0] = 1440393899;
  value.bits[3] = 0b00000000000100110000000000000000;
  // 1001011001010111101110110100010011101010101110110101010101010101011
  // 86666666666666666667E-19

  s21_div(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

Suite *s21_div_suite(void) {
  Suite *s = suite_create("s21_add_suite");
  TCase *tc = tcase_create("s21_add_testcase");

  tcase_add_test(tc, s21_div_1);
  tcase_add_test(tc, s21_div_2);
  tcase_add_test(tc, s21_div_3);
  tcase_add_test(tc, s21_div_4);
  tcase_add_test(tc, s21_div_5);

  suite_add_tcase(s, tc);
  return s;
}