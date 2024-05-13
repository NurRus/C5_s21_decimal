#include "s21_decimal_test.h"

int main(void) {
  run_tests();
  return 0;
}

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;
  if (counter_testcase > 1) counter_testcase++;
  SRunner *sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  srunner_free(sr);
}

void run_tests(void) {
  Suite *list_cases[] = {s21_add_suite(),
                         s21_sub_suite(),
                         s21_mul_suite(),
                         s21_div_suite(),
                         s21_is_equal_suite(),
                         s21_is_not_equal_suite(),
                         s21_is_greater_suite(),
                         s21_is_greater_or_equal_suite(),
                         s21_is_less_suite(),
                         s21_is_less_or_equal_suite(),
                         s21_from_int_to_decimal_suite(),
                         s21_from_decimal_to_int_suite(),
                         s21_from_float_to_decimal_suite(),
                         s21_from_decimal_to_float_suite(),
                         s21_floor_suite(),
                         s21_round_suite(),
                         NULL}; /*

                          s21_truncate_suite(),
                          s21_negate_suite(),
                          s21_round_suite(),*/

  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}