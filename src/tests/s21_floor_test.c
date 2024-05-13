#include "s21_decimal_test.h"

START_TEST(test_s21_floor_1) {
  s21_decimal src1, origin, result = {{0, 0, 0, 0}};
  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_s21_floor_2) {
  s21_decimal num1;
  num1.bits[0] = 0b00000000000000000000000001111011;  // 12.3
  num1.bits[1] = 0b00000000000000000000000000000000;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal *res1 = NULL;
  int value = s21_floor(num1, res1);
  ck_assert_int_eq(value, 1);
}
END_TEST

START_TEST(test_s21_floor_3) {
  s21_decimal dec1;
  dec1.bits[0] = 0b00000000000000000000000011011001;  // 21.7
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000010101;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  ck_assert_int_eq(res1.bits[0], result.bits[0]);
  ck_assert_int_eq(res1.bits[1], result.bits[1]);
  ck_assert_int_eq(res1.bits[2], result.bits[2]);
  ck_assert_int_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_s21_floor_4) {
  s21_decimal dec1;
  dec1.bits[0] = 0b00000000000000000000000011011001;  // -21.7
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000000010000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000010110;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  ck_assert_int_eq(res1.bits[0], result.bits[0]);
  ck_assert_int_eq(res1.bits[1], result.bits[1]);
  ck_assert_int_eq(res1.bits[2], result.bits[2]);
  ck_assert_int_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_s21_floor_5) {
  s21_decimal a = {{3, 2, 1, 0}};
  s21_decimal b;
  s21_set_sign(&a, 1);
  ck_assert_int_eq(s21_floor(a, &b), 0);
}
END_TEST

START_TEST(test_s21_floor_6) {
  s21_decimal num1;
  num1.bits[0] = 0b00000000000000000000000001111011;
  num1.bits[1] = 0b00000000000000000000000000000000;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b10000000000111110000000000000000;
  s21_decimal *res1 = NULL;
  int value = s21_floor(num1, res1);
  ck_assert_int_eq(value, 1);
}
END_TEST

START_TEST(test_s21_floor_7) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_pow(&value_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result;
  int return_value = s21_floor(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(test_s21_floor_8) {
  s21_decimal num1;
  num1.bits[0] = 0b00000000000000000000000001111011;  // 12.3
  num1.bits[1] = 0b00000000000000000000000000000000;
  num1.bits[2] = 0b00000000000000000000000000000000;
  num1.bits[3] = 0b00000000001111110000000000000000;
  s21_decimal res1 = {{0, 0, 0, 0}};
  int value = s21_floor(num1, &res1);
  ck_assert_int_eq(value, 1);
}
END_TEST

Suite *s21_floor_suite(void) {
  Suite *s = suite_create("\033[42m-=s21_floor_suite=-\033[0m");
  TCase *tc = tcase_create("s21_floor_testcase");

  tcase_add_test(tc, test_s21_floor_1);
  tcase_add_test(tc, test_s21_floor_2);
  tcase_add_test(tc, test_s21_floor_3);
  tcase_add_test(tc, test_s21_floor_4);
  tcase_add_test(tc, test_s21_floor_5);
  tcase_add_test(tc, test_s21_floor_6);
  tcase_add_test(tc, test_s21_floor_7);
  tcase_add_test(tc, test_s21_floor_8);

  suite_add_tcase(s, tc);
  return s;
}
