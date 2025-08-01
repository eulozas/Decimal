#include <check.h>

#include "../s21_arithmetic_helpers.h"
#include "../s21_decimal.h"
#include "../s21_helpers.h"

START_TEST(test_sub_1) {
  // 39614081257132168796771975167
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0x7fffffff, 0x0}};
  // 0.5
  s21_decimal value_2 = {{0x5, 0x0, 0x0, 0x10000}};
  s21_decimal result = {{0}};
  int s21_code_return = s21_sub(value_1, value_2, &result);
  // 39614081257132168796771975166
  s21_decimal expected = {{0xfffffffe, 0xffffffff, 0x7fffffff, 0x0}};
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_sub_2) {
  // 39614081257132168796771975167
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0x7fffffff, 0x0}};
  // 0.49
  s21_decimal value_2 = {{0x31, 0x0, 0x0, 0x20000}};
  s21_decimal result = {{0}};
  // 39614081257132168796771975167
  s21_decimal expected = {{0xffffffff, 0xffffffff, 0x7fffffff, 0x0}};
  int s21_code_return = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_sub_3) {
  // -39614081257132168796771975167
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0x7fffffff, 0x80000000}};
  // -39614081257132168796771975167
  s21_decimal value_2 = {{0xffffffff, 0xffffffff, 0x7fffffff, 0x80000000}};
  s21_decimal result = {{0}};
  // 0
  s21_decimal expected = {{0x0, 0x0, 0x0, 0x0}};
  int s21_code_return = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_sub_4) {
  // -79228162514264337593543950334
  s21_decimal value_1 = {{0xfffffffe, 0xffffffff, 0xffffffff, 0x80000000}};
  // 1.49
  s21_decimal value_2 = {{0x00000095, 0x00000000, 0x00000000, 0x20000}};
  s21_decimal result = {{0}};
  // -79228162514264337593543950335
  s21_decimal expected = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  int s21_code_return = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_sub_5) {
  // -1922856.251426433759354395034
  s21_decimal value_1 = {{0xf299999a, 0x4239bf16, 0x06368ca6, 0x80150000}};
  // 2467868965996901.0467496723455
  s21_decimal value_2 = {{0x13d303ff, 0x2bf462f5, 0x4fbdbbcf, 0xd0000}};
  s21_decimal result = {{0}};
  // -2467868967919757.2981761061049
  s21_decimal expected = {{0xcff130b9, 0x36cdf6af, 0x4fbdbbd0, 0x800d0000}};
  int s21_code_return = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_sub_uncorrect_1) {
  // 39614081257132168796771975168
  s21_decimal value_1 = {{0x0, 0x0, 0x80000000, 0x0}};
  // -39614081257132168796771975168
  s21_decimal value_2 = {{0x0, 0x0, 0x80000000, 0x80000000}};
  s21_decimal result = {{0}};
  int s21_code_return = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OVERFLOW);
}
END_TEST

START_TEST(test_sub_uncorrect_2) {
  // -39614081257132168796771975168
  s21_decimal value_1 = {{0x0, 0x0, 0x80000000, 0x80000000}};
  // 39614081257132168796771975168
  s21_decimal value_2 = {{0x0, 0x0, 0x80000000, 0x0}};
  s21_decimal result = {{0}};
  int s21_code_return = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_NEG_OVERFLOW);
}
END_TEST

START_TEST(test_sub_uncorrect_3) {
  // -79228162514264337593543950335
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  // 0.5000000000000000000000000001
  s21_decimal value_2 = {{0x88000001, 0x1f128130, 0x1027e72f, 0x1c0000}};
  s21_decimal result = {{0}};
  int s21_code_return = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_NEG_OVERFLOW);
}
END_TEST

START_TEST(test_sub_uncorrect_4) {
  // 79228162514264337593543950335
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal value_2 = {{0x88000001, 0x1f128130, 0x1027e72f, 0x801c0000}};
  s21_decimal result = {{0}};
  int s21_code_return = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OVERFLOW);
}
END_TEST

Suite *sub_suite(void) {
  Suite *s = suite_create("s21_sub");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_sub_1);
  tcase_add_test(tc, test_sub_2);
  tcase_add_test(tc, test_sub_3);
  tcase_add_test(tc, test_sub_4);
  tcase_add_test(tc, test_sub_5);
  tcase_add_test(tc, test_sub_uncorrect_1);
  tcase_add_test(tc, test_sub_uncorrect_2);
  tcase_add_test(tc, test_sub_uncorrect_3);
  tcase_add_test(tc, test_sub_uncorrect_4);
  suite_add_tcase(s, tc);
  return s;
}