#include "s21_decimal_test.h"

START_TEST(s21_sub_1) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[2] = 0b1010;

  decimal_2.bits[0] = 0b1010;

  value.bits[2] = 0b1001;
  value.bits[1] = 0b11111111111111111111111111111111;
  value.bits[0] = 0b11111111111111111111111111110110;

  s21_sub(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_2) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 2334378;

  decimal_2.bits[0] = 53545342;

  value.bits[0] = 51210964;
  value.bits[3] = 0b10000000000000000000000000000000;

  s21_sub(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_3) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 53545342;

  decimal_2.bits[0] = 53545342;

  s21_sub(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_4) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 3242342;

  decimal_2.bits[0] = 23433;
  decimal_2.bits[3] = 0b10000000000000000000000000000000;

  value.bits[0] = 3265775;

  s21_sub(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_5) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_2.bits[0] = 23433;
  decimal_2.bits[3] = 0b10000000000000000000000000000000;

  value.bits[0] = 23433;

  s21_sub(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_6) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 3242342;

  value.bits[0] = 3242342;

  s21_sub(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_7) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[2] = 0b11111111000000000000000000000000;
  decimal_1.bits[3] = 0b10000000000000000000000000000000;

  decimal_2.bits[2] = 0b01100111000000000000000000000000;

  ck_assert_int_eq(s21_sub(decimal_1, decimal_2, &result), 2);
}
END_TEST

START_TEST(s21_sub_8) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 0b00000000000000000000000000000001;
  decimal_1.bits[3] = 0b00000000000111000000000000000000;

  decimal_2.bits[2] = 0b10000000000000000000000000000000;

  value.bits[2] = 0b10000000000000000000000000000000;
  value.bits[3] = 0b10000000000000000000000000000000;

  s21_sub(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_9) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 21;
  decimal_1.bits[3] = 0b10000000000000000000000000000000;

  decimal_2.bits[0] = 1;
  decimal_2.bits[3] = 0b00000000000000000000000000000000;

  value.bits[0] = 22;
  value.bits[3] = 0b10000000000000000000000000000000;

  s21_sub(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_10) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[2] = 0b10000000000000000000000000000000;

  decimal_2.bits[0] = 100;
  decimal_2.bits[3] = 0b00000000000000100000000000000000;

  value.bits[2] = 0b01111111111111111111111111111111;
  value.bits[1] = 0b11111111111111111111111111111111;
  value.bits[0] = 0b11111111111111111111111111111111;
  value.bits[3] = 0b00000000000000000000000000000000;

  s21_sub(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_11) {
  s21_decimal decimal_1, decimal_2, result, value;

  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);
  s21_RESETDECIMAL(&result);
  s21_RESETDECIMAL(&value);

  decimal_1.bits[0] = 29;

  decimal_2.bits[0] = 1;

  value.bits[0] = 28;

  s21_sub(decimal_1, decimal_2, &result);

  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

Suite *s21_sub_suite(void) {
  Suite *s = suite_create("s21_sub_suite");
  TCase *tc = tcase_create("s21_sub_testcase");

  tcase_add_test(tc, s21_sub_1);
  tcase_add_test(tc, s21_sub_2);
  tcase_add_test(tc, s21_sub_3);
  tcase_add_test(tc, s21_sub_4);
  tcase_add_test(tc, s21_sub_5);
  tcase_add_test(tc, s21_sub_6);
  tcase_add_test(tc, s21_sub_7);
  tcase_add_test(tc, s21_sub_8);
  tcase_add_test(tc, s21_sub_9);
  tcase_add_test(tc, s21_sub_10);
  tcase_add_test(tc, s21_sub_11);

  suite_add_tcase(s, tc);
  return s;
}