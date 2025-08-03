#include <check.h>

#include "../s21_arithmetic_helpers.h"
#include "../s21_decimal.h"
#include "../s21_helpers.h"

START_TEST(test_div_1) {
  // 79228162514264337593543950335
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  // 4237574999123243252.047263256
  s21_decimal value_2 = {{0xc239b618, 0x01882ac2, 0x0db13d69, 0x90000}};
  s21_decimal result = {{0}};
  // 18696580598.728445112386526146
  s21_decimal expected = {{0xd0431bc2, 0x28da9b43, 0x3c6972f1, 0x120000}};
  int s21_code_return = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_2) {
  // 535873509258928592.89529592859
  s21_decimal value_1 = {{0x78e5ac1b, 0x946e3ff1, 0xad266af2, 0xb0000}};
  // -6534.0000000000000000000000003
  s21_decimal value_2 = {{0xbc000002, 0x8298bb10, 0xd31ffb31, 0x80190000}};
  s21_decimal result = {{0}};
  // -82013086816487.38795459074511
  s21_decimal expected = {{0x19de59cf, 0x7e4ec6f2, 0x1a7ff6aa, 0x800e0000}};
  int s21_code_return = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_3) {
  // -10
  s21_decimal value_1 = {{0xa, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal value_2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  s21_decimal result = {{0}};
  // 0.0000000000000000000000000001
  s21_decimal expected = {{0x1, 0x0, 0x0, 0x801c0000}};
  int s21_code_return = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_4) {
  // 0
  s21_decimal value_1 = {{0x0, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal value_2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  s21_decimal result = {{0}};
  // 0
  s21_decimal expected = {{0x0, 0x0, 0x0, 0x0}};
  int s21_code_return = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_5) {
  // 1
  s21_decimal value_1 = {{0x1, 0x0, 0x0, 0x0}};
  // 2
  s21_decimal value_2 = {{0x2, 0x0, 0x0, 0x0}};
  s21_decimal result = {{0}};
  // 0.5
  s21_decimal expected = {{0x5, 0, 0, 0x010000}};
  int s21_code_return = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OK);
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_div_uncorrect_1) {
  // 0.7922816251426433759354395033
  s21_decimal value_1 = {{0x99999999, 0x99999999, 0x19999999, 0x1c0000}};
  // 29228162514264337593543950335
  s21_decimal value_2 = {{0xafffffff, 0xc946f41a, 0x5e70f828, 0x0}};
  s21_decimal result = {{0}};
  int s21_code_return = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_UNDERFLOW);
}
END_TEST

START_TEST(test_div_uncorrect_2) {
  // 26790900105265827596743072504
  s21_decimal value_1 = {{0x2be1daf8, 0xd93baf9b, 0x5690e9c4, 0x0}};
  // 0.000000000000003
  s21_decimal value_2 = {{0x3, 0x0, 0x0, 0xf0000}};
  s21_decimal result = {{0}};
  int s21_code_return = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_OVERFLOW);
}
END_TEST

START_TEST(test_div_uncorrect_3) {
  // 26790900105265827596743072504
  s21_decimal value_1 = {{0x2be1daf8, 0xd93baf9b, 0x5690e9c4, 0x0}};
  // 0
  s21_decimal value_2 = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result = {{0}};
  int s21_code_return = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_code_return, S21_DIV_BY_ZERO);
}
END_TEST

Suite *div_suite(void) {
  Suite *s = suite_create("s21_div");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_div_1);
  tcase_add_test(tc, test_div_2);
  tcase_add_test(tc, test_div_3);
  tcase_add_test(tc, test_div_4);
  tcase_add_test(tc, test_div_5);
  tcase_add_test(tc, test_div_uncorrect_1);
  tcase_add_test(tc, test_div_uncorrect_2);
  tcase_add_test(tc, test_div_uncorrect_3);

  suite_add_tcase(s, tc);
  return s;
}