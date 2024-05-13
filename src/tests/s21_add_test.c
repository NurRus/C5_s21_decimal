#include "s21_decimal_test.h"

START_TEST(s21_add_1) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 2334378;

  decimal_2.bits[0] = 535453;
  decimal_2.bits[3] = 0b00000000000001100000000000000000;

  value.bits[0] = 0b10000011110011011010101000011101;
  value.bits[1] = 0b1000011111;
  value.bits[3] = 0b00000000000001100000000000000000;

  s21_add(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_add_2) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 23344;

  decimal_2.bits[0] = 5354;
  decimal_2.bits[3] = 0b10000000000000100000000000000000;

  value.bits[0] = 2329046;

  value.bits[3] = 0b00000000000000100000000000000000;

  s21_add(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_add_3) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 23344;

  decimal_2.bits[0] = 2334400;
  decimal_2.bits[3] = 0b10000000000000100000000000000000;

  s21_add(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_add_4) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 100;

  decimal_2.bits[0] = 90000;
  decimal_2.bits[3] = 0b10000000000000100000000000000000;

  value.bits[0] = 800;

  value.bits[3] = 0b10000000000000000000000000000000;

  s21_add(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_add_5) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 0;

  decimal_2.bits[0] = 90000;
  decimal_2.bits[3] = 0b10000000000000100000000000000000;

  value.bits[0] = 900;

  value.bits[3] = 0b10000000000000000000000000000000;

  s21_add(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_add_6) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 100;

  decimal_2.bits[0] = 0;

  value.bits[0] = 100;

  s21_add(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_add_7) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[2] = 0b10000000000000000000000000000000;
  decimal_1.bits[3] = 0b10000000000000000000000000000000;

  decimal_2.bits[2] = 0b10000000000000000000000000000000;
  decimal_2.bits[3] = 0b10000000000000000000000000000000;

  ck_assert_int_eq(s21_add(decimal_1, decimal_2, &result), 2);
  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_add_8) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[2] = 0b10000000000000000000000000000000;
  decimal_1.bits[3] = 0b00000000000000010000000000000000;

  decimal_2.bits[2] = 0b10000000000000000000000000000000;
  decimal_2.bits[3] = 0b00000000000000010000000000000000;

  value.bits[2] = 0b00011001100110011001100110011001;
  value.bits[1] = 0b10011001100110011001100110011001;
  value.bits[0] = 0b10011001100110011001100110011010;

  s21_add(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[3], result.bits[3]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_add_9) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 1;
  decimal_1.bits[3] = 0b00000000000000100000000000000000;

  decimal_2.bits[0] = 1;

  value.bits[0] = 101;
  value.bits[3] = 0b00000000000000100000000000000000;

  s21_add(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[3], result.bits[3]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[0], result.bits[0]);
}
END_TEST

Suite *s21_add_suite(void) {
  Suite *s = suite_create("s21_add_suite");
  TCase *tc = tcase_create("s21_add_testcase");

  tcase_add_test(tc, s21_add_1);
  tcase_add_test(tc, s21_add_2);
  tcase_add_test(tc, s21_add_3);
  tcase_add_test(tc, s21_add_4);
  tcase_add_test(tc, s21_add_5);
  tcase_add_test(tc, s21_add_6);
  tcase_add_test(tc, s21_add_7);
  tcase_add_test(tc, s21_add_8);
  tcase_add_test(tc, s21_add_9);

  suite_add_tcase(s, tc);
  return s;
}