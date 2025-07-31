#include <check.h>
#include "../s21_decimal.h"
#include "s21_arithmetic_helpers.h"
#include "s21_helpers.h"

START_TEST(test_add_1) {
    // 79228162514264337593543950335
    s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
    // 0.49
    s21_decimal value_2 = {{0x31, 0x0, 0x0, 0x20000}};
    s21_decimal result = {{0}};
    // 79228162514264337593543950335
    s21_decimal expected = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
    int s21_code_return = s21_add(value_1, value_2, &result);
    ck_assert_int_eq(s21_code_return, S21_OK);
    ck_assert_int_eq(s21_is_equal(result, expected), 1);
  }
END_TEST

START_TEST(test_add_2) {
  // 79228162514264337593543950335
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  // -0.49
  s21_decimal value_2 = {{0x31, 0x0, 0x0, 0x80020000}};
  s21_decimal result = {{0}};
  // 79228162514264337593543950335
  s21_decimal expected = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  int s21_code_return = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_3) {
  // -79228162514264337593543950335
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  // -0.49
  s21_decimal value_2 = {{0x31, 0x0, 0x0, 0x80020000}};
  s21_decimal result = {{0}};
  // -79228162514264337593543950335
  s21_decimal expected = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  int s21_code_return = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_4) {
  // 39228162514264337593543950335
  s21_decimal value_1 = {{0xbfffffff, 0x076bf67b, 0x7ec0c687, 0x0}};
  // 31228162514264337593543950335
  s21_decimal value_2 = {{0x7fffffff, 0x08e7f494, 0x64e754a2, 0x0}};
  s21_decimal result = {{0}};
  // 70456325028528675187087900670
  s21_decimal expected = {{0x3ffffffe, 0x1053eb10, 0xe3a81b29, 0x0}};
  int s21_code_return = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_5) {
  // -0.5
  s21_decimal value_1 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 79228162514264337593543950335
  s21_decimal value_2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  s21_decimal result = {{0}};
  // 79228162514264337593543950334
  s21_decimal expected = {{0xfffffffe, 0xffffffff, 0xffffffff, 0x0}};
  int s21_code_return = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_6) {
  // 4237574999123243252.047263256
  s21_decimal value_1 = {{0xc239b618, 0x01882ac2, 0x0db13d69, 0x90000}};
  // 4237574999123243252.047263256
  s21_decimal value_2 = {{0xc239b618, 0x01882ac2, 0x0db13d69, 0x80090000}};
  s21_decimal result = {{0}};
  // 0
  s21_decimal expected = {{0x0, 0x0, 0x0, 0x0}};
  int s21_code_return = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_7) {
  // -79228162514264337593543950334
  s21_decimal value_1 = {{0xfffffffe, 0xffffffff, 0xffffffff, 0x80000000}};
  // 0.5000000000000000000000000001
  s21_decimal value_2 = {{0x88000001, 0x1f128130, 0x1027e72f, 0x1c0000}};
  s21_decimal result = {{0}};
  // -79228162514264337593543950333
  s21_decimal expected = {{0xfffffffd, 0xffffffff, 0xffffffff, 0x80000000}};
  int s21_code_return = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_8) {
  // 0.1000000000000000000000000125
  s21_decimal value_1 = {{0xe800007d, 0x9fd0803c, 0x033b2e3c, 0x1c0000}};
  // -0.1000000000000000000000000124
  s21_decimal value_2 = {{0xe800007c, 0x9fd0803c, 0x033b2e3c, 0x801c0000}};
  s21_decimal result = {{0}};
  // -0.0000000000000000000000000001
  s21_decimal expected = {{0x1, 0x0, 0x0, 0x1c0000}};
  int s21_code_return = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_add_uncorrect_1) {
  // 0.7922816251426433759354395033
  s21_decimal value_1 = {{0x99999999, 0x99999999, 0x19999999, 0x1c0000}};
  // 79228162514264337593543950335
  s21_decimal value_2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  s21_decimal result = {{0}};
  int s21_code_return = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OVERFLOW);
}
END_TEST

START_TEST(test_add_uncorrect_2) {
  // 0.5
  s21_decimal value_1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 79228162514264337593543950335
  s21_decimal value_2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  s21_decimal result = {{0}};
  int s21_code_return = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OVERFLOW);
}
END_TEST

START_TEST(test_add_uncorrect_3) {
  // -39614081257132168796771975168
  s21_decimal value_1 = {{0x0, 0x0, 0x80000000, 0x80000000}};
  // -39614081257132168796771975168
  s21_decimal value_2 = {{0x0, 0x0, 0x80000000, 0x80000000}};
  s21_decimal result = {{0}};
  int s21_code_return = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_NEG_OVERFLOW);
}
END_TEST

  Suite *add_suite(void) {
    Suite *s = suite_create("s21_add");
    TCase *tc = tcase_create("Core");
  
    tcase_add_test(tc, test_add_1);
    tcase_add_test(tc, test_add_2);
    tcase_add_test(tc, test_add_3);
    tcase_add_test(tc, test_add_4);
    tcase_add_test(tc, test_add_5);
    tcase_add_test(tc, test_add_6);
    tcase_add_test(tc, test_add_7);
    tcase_add_test(tc, test_add_8);
    tcase_add_test(tc, test_add_uncorrect_1);
    tcase_add_test(tc, test_add_uncorrect_2);
    tcase_add_test(tc, test_add_uncorrect_3);
  
    suite_add_tcase(s, tc);
    return s;
  }