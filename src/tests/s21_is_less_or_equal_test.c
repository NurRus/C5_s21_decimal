#include "s21_decimal_test.h"

START_TEST(s21_is_less_or_equal_1) {
  s21_decimal decimal_1, decimal_2;
  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);

  decimal_1.bits[0] = 462;
  decimal_1.bits[3] = 0b00000000000000110000000000000000;

  decimal_2.bits[0] = 462;
  decimal_2.bits[3] = 0b00000000000000110000000000000000;

  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_2) {
  s21_decimal decimal_1, decimal_2;
  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);

  decimal_1.bits[0] = 462;
  decimal_1.bits[3] = 0b00000000000000110000000000000000;

  decimal_2.bits[0] = 462;
  decimal_2.bits[3] = 0b00000000000000010000000000000000;

  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_3) {
  s21_decimal decimal_1, decimal_2;
  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);

  decimal_1.bits[0] = 462;
  decimal_1.bits[3] = 0b00000000000000110000000000000000;

  decimal_2.bits[0] = 462;
  decimal_2.bits[3] = 0b10000000000000010000000000000000;

  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 0);
}
END_TEST

START_TEST(s21_is_less_or_equal_4) {
  s21_decimal decimal_1, decimal_2;
  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);

  decimal_1.bits[0] = 462;
  decimal_1.bits[3] = 0b00000000000000010000000000000000;

  decimal_2.bits[0] = 462;
  decimal_2.bits[3] = 0b00000000000000110000000000000000;

  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 0);
}
END_TEST

START_TEST(s21_is_less_or_equal_5) {
  s21_decimal decimal_1, decimal_2;
  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);

  decimal_1.bits[0] = 462;
  decimal_1.bits[3] = 0b10000000000000010000000000000000;

  decimal_2.bits[0] = 462;
  decimal_2.bits[3] = 0b0000000000000011000000000000000;

  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_6) {
  s21_decimal decimal_1, decimal_2;
  s21_RESETDECIMAL(&decimal_1);
  s21_RESETDECIMAL(&decimal_2);

  decimal_1.bits[0] = 462;
  decimal_1.bits[3] = 0b10000000000000010000000000000000;

  decimal_2.bits[0] = 462;
  decimal_2.bits[3] = 0b10000000000000110000000000000000;

  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 1);
}
END_TEST

Suite *s21_is_less_or_equal_suite(void) {
  Suite *s = suite_create("s21_is_less_or_equal_suite");
  TCase *t = tcase_create("s21_is_less_or_equal_testcase");

  tcase_add_test(t, s21_is_less_or_equal_1);
  tcase_add_test(t, s21_is_less_or_equal_2);
  tcase_add_test(t, s21_is_less_or_equal_3);
  tcase_add_test(t, s21_is_less_or_equal_4);
  tcase_add_test(t, s21_is_less_or_equal_5);
  tcase_add_test(t, s21_is_less_or_equal_6);

  suite_add_tcase(s, t);
  return s;
}
