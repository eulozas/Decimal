#include <check.h>

#include "../s21_decimal.h"
#include "s21_arithmetic_helpers.h"
#include "s21_helpers.h"

START_TEST(test_mul_1) {
  // 0.1
  s21_decimal value_1 = {{0x1, 0x0, 0x0, 0x10000}};
  // 79228162514264337593543950335
  s21_decimal value_2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  s21_decimal result = {{0}};
  // 7.9228162514264337593543950335
  s21_decimal expected = {{0xffffffff, 0xffffffff, 0xffffffff, 0x10000}};
  int s21_code_return = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_mul_2) {
  // -19228562514.264337593543950345
  s21_decimal value_1 = {{0x7a000009, 0x964176e5, 0x3e217e7e, 0x80120000}};
  // 2467868965996901046.7496723455
  s21_decimal value_2 = {{0x13d303ff, 0x2bf462f5, 0x4fbdbbcf, 0xa0000}};
  s21_decimal result = {{0}};
  // -47453572689684302651351529048
  s21_decimal expected = {{0x334e7658, 0x1e234cf2, 0x9954ace2, 0x80000000}};
  int s21_code_return = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_mul_3) {
  // -2328562514.264337593543950345
  s21_decimal value_1 = {{0xf6000009, 0xd630ffac, 0x0786244a, 0x80120000}};
  // -589665996901046.7496723455
  s21_decimal value_2 = {{0x163303ff, 0x93d3238a, 0x0004e0aa, 0x800a0000}};
  s21_decimal result = {{0}};
  // 1373074136320088519264082.6932
  s21_decimal expected = {{0x55ea0e34, 0xca7b9f35, 0x2c5dcd94, 0x40000}};
  int s21_code_return = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_mul_4) {
  // 63637540.749672345535439505672
  s21_decimal value_1 = {{0xd4450908, 0x9f1939fc, 0xcd9fbd6c, 0x150000}};
  // -474762955966586.40659969010467
  s21_decimal value_2 = {{0xff44eb23, 0x5f81247b, 0x996778a5, 0x800e0000}};
  s21_decimal result = {{0}};
  // 1373074136320088519264082.6932
  s21_decimal expected = {{0x4fca447e, 0x5d16456e, 0x619f6606, 0x80060000}};
  int s21_code_return = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_mul_5) {
  // 0.7922816251426433759354395033
  s21_decimal value_1 = {{0x99999999, 0x99999999, 0x19999999, 0x1c0000}};
  // 0.0000000000000000000000000001
  s21_decimal value_2 = {{0x1, 0x0, 0x0, 0x1c0000}};
  s21_decimal result = {{0}};
  // 0.0000000000000000000000000001
  s21_decimal expected = {{0x1, 0x0, 0x0, 0x1c0000}};
  int s21_code_return = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_mul_6) {
  // 12125522270318998713428826.191
  s21_decimal value_1 = {{0xc073584f, 0x666a6978, 0x272dff37, 0x30000}};
  // -6534.0000000000000000000000002
  s21_decimal value_2 = {{0xbc000002, 0x8298bb10, 0xd31ffb31, 0x80190000}};
  s21_decimal result = {{0}};
  // 79228162514264337593543950334
  s21_decimal expected = {{0xfffffffe, 0xffffffff, 0xffffffff, 0x80000000}};
  int s21_code_return = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_mul_7) {
  // 535873509258928592.89529592859
  s21_decimal value_1 = {{0x78e5ac1b, 0x946e3ff1, 0xad266af2, 0xb0000}};
  // 0
  s21_decimal value_2 = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result = {{0}};
  // 0
  s21_decimal expected = {{0x0, 0x0, 0x0, 0x0}};
  int s21_code_return = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_mul_8) {
  // 0
  s21_decimal value_1 = {{0x0, 0x0, 0x0, 0x0}};
  // -535873509258928592.89529592859
  s21_decimal value_2 = {{0x78e5ac1b, 0x946e3ff1, 0xad266af2, 0x800b0000}};
  s21_decimal result = {{0}};
  // 0
  s21_decimal expected = {{0x0, 0x0, 0x0, 0x0}};
  int s21_code_return = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_mul_uncorrect_1) {
  // 0.4922816251426433759354395033
  s21_decimal value_1 = {{0xe1999999, 0xba2818e2, 0x0fe80ee3, 0x1c0000}};
  // 0.0000000000000000000000000001
  s21_decimal value_2 = {{0x1, 0x0, 0x0, 0x1c0000}};
  s21_decimal result = {{0}};
  int s21_code_return = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_UNDERFLOW);
}
END_TEST

START_TEST(test_mul_uncorrect_2) {
  // 4922816251426433759354395033
  s21_decimal value_1 = {{0xe1999999, 0xba2818e2, 0x0fe80ee3, 0x0}};
  // 25
  s21_decimal value_2 = {{0x19, 0x0, 0x0, 0x0}};
  s21_decimal result = {{0}};
  int s21_code_return = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OVERFLOW);
}
END_TEST

START_TEST(test_mul_uncorrect_3) {
  // 12125522270318998713428826.191
  s21_decimal value_1 = {{0xc073584f, 0x666a6978, 0x272dff37, 0x30000}};
  // -6534.0000000000000000000000003
  s21_decimal value_2 = {{0xbc000003, 0x8298bb10, 0xd31ffb31, 0x80190000}};
  s21_decimal result = {{0}};
  int s21_code_return = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_NEG_OVERFLOW);
}
END_TEST

START_TEST(test_mul_uncorrect_4) {
  // 12125522270318998713428826.191
  s21_decimal value_1 = {{0xc073584f, 0x666a6978, 0x272dff37, 0x30000}};
  // 6534.0000000000000000000000003
  s21_decimal value_2 = {{0xbc000003, 0x8298bb10, 0xd31ffb31, 0x190000}};
  s21_decimal result = {{0}};
  int s21_code_return = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OVERFLOW);
}
END_TEST

Suite *mul_suite(void) {
  Suite *s = suite_create("s21_mul");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_mul_1);
  tcase_add_test(tc, test_mul_2);
  tcase_add_test(tc, test_mul_3);
  tcase_add_test(tc, test_mul_4);
  tcase_add_test(tc, test_mul_5);
  tcase_add_test(tc, test_mul_6);
  tcase_add_test(tc, test_mul_7);
  tcase_add_test(tc, test_mul_8);
  tcase_add_test(tc, test_mul_uncorrect_1);
  tcase_add_test(tc, test_mul_uncorrect_2);
  tcase_add_test(tc, test_mul_uncorrect_3);
  tcase_add_test(tc, test_mul_uncorrect_4);

  suite_add_tcase(s, tc);
  return s;
}