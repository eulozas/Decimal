#include <check.h>
#include <stdio.h>

#include "../s21_decimal.h"

START_TEST(test_equal_basic) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{100, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_equal_different_scale_but_same_value) {
  s21_decimal a = {{1000, 0, 0, 1 << 16}};  // 100.0
  s21_decimal b = {{10000, 0, 0, 2 << 16}}; // 100.00
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_equal_negative_zero) {
  s21_decimal a = {{0, 0, 0, 1u << 31}}; // -0
  s21_decimal b = {{0, 0, 0, 0}};        // +0
  ck_assert_int_eq(s21_is_equal(a, b), 1); // они равны
}
END_TEST

START_TEST(test_equal_negative_zero2) {
  s21_decimal a = {{10, 0, 0, 3 << 16}}; 
  s21_decimal b = {{11, 0, 0, 0}};       
  ck_assert_int_eq(s21_is_equal(a, b), 0); // они равны
}
END_TEST

START_TEST(test_not_equal_different_value) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{456, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_not_equal_same_value_different_sign) {
  s21_decimal a = {{500, 0, 0, 0}};
  s21_decimal b = {{500, 0, 0, 1u << 31}}; // -500
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_less_basic) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{200, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_less_negative_vs_positive) {
  s21_decimal a = {{100, 0, 0, 1u << 31}}; // -100
  s21_decimal b = {{100, 0, 0, 0}};        // +100
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_less_negative_vs_positive2) {
  s21_decimal a = {{100, 0, 0, 0}}; // -100
  s21_decimal b = {{100, 0, 0, 0}};        // +100
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_less_with_scale) {
  s21_decimal a = {{1000, 0, 0, 2 << 16}}; // 10.00
  s21_decimal b = {{1100, 0, 0, 2 << 16}}; // 11.00
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_less_or_equal_equal_case) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{123, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_less_or_equal_true_case) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{200, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_less_or_equal_false_case) {
  s21_decimal a = {{300, 0, 0, 0}};
  s21_decimal b = {{200, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
}
END_TEST

START_TEST(test_greater_basic) {
  s21_decimal a = {{500, 0, 0, 0}};
  s21_decimal b = {{100, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_greater_negative_less_than_positive) {
  s21_decimal a = {{500, 0, 0, 1u << 31}}; // -500
  s21_decimal b = {{500, 0, 0, 0}};        // +500
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_greater_or_equal_equal_case) {
  s21_decimal a = {{222, 0, 0, 0}};
  s21_decimal b = {{222, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_greater_or_equal_true_case) {
  s21_decimal a = {{400, 0, 0, 0}};
  s21_decimal b = {{100, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_greater_or_equal_false_case) {
  s21_decimal a = {{99, 0, 0, 0}};
  s21_decimal b = {{100, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
}
END_TEST


Suite *comparison_suite(void) {
  Suite *s = suite_create("s21_comparison");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_equal_basic);
  tcase_add_test(tc, test_equal_different_scale_but_same_value);
  tcase_add_test(tc, test_equal_negative_zero);
  tcase_add_test(tc, test_equal_negative_zero2);

  tcase_add_test(tc, test_not_equal_different_value);
  tcase_add_test(tc, test_not_equal_same_value_different_sign);

  tcase_add_test(tc, test_less_basic);
  tcase_add_test(tc, test_less_negative_vs_positive);
  tcase_add_test(tc, test_less_negative_vs_positive2);
  tcase_add_test(tc, test_less_with_scale);

  tcase_add_test(tc, test_less_or_equal_equal_case);
  tcase_add_test(tc, test_less_or_equal_true_case);
  tcase_add_test(tc, test_less_or_equal_false_case);

  tcase_add_test(tc, test_greater_basic);
  tcase_add_test(tc, test_greater_negative_less_than_positive);

  tcase_add_test(tc, test_greater_or_equal_equal_case);
  tcase_add_test(tc, test_greater_or_equal_true_case);
  tcase_add_test(tc, test_greater_or_equal_false_case);

  suite_add_tcase(s, tc);
  return s;
}