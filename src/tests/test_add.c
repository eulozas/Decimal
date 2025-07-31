#include <check.h>
#include "../s21_decimal.h"
#include "s21_arithmetic_helpers.h"
#include "s21_helpers.h"

START_TEST(test_add_1) {
    s21_decimal value_1 = {{100, 0, 0, 0}};
    s21_decimal value_2 = {{100, 0, 0, 0}};
    s21_decimal result = {{0}};
    s21_decimal expected = {};
    int s21_code_return = s21_add(value_1, value_2, &result);
    ck_assert_int_eq(s21_is_equal(value_1, value_2), 1);
  }
  END_TEST

  Suite *add_suite(void) {
    Suite *s = suite_create("s21_add");
    TCase *tc = tcase_create("Core");
  
    tcase_add_test(tc, test_add_1);
  
    suite_add_tcase(s, tc);
    return s;
  }