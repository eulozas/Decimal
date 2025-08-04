#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_int_to_decimal_simple) {
  s21_decimal decimal;
  int x = 1;
  int res = s21_from_int_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  unsigned int sign_c_sharp = 0;
  unsigned int scale_c_sharp = 0;
  unsigned mantissa0_c_sharp = 1;
  unsigned int mantissa1_c_sharp = 0;
  unsigned int mantissa2_c_sharp = 0;

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, sign_c_sharp);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, scale_c_sharp);
  ck_assert_uint_eq(decimal.bits[0], mantissa0_c_sharp);
  ck_assert_uint_eq(decimal.bits[1], mantissa1_c_sharp);
  ck_assert_uint_eq(decimal.bits[2], mantissa2_c_sharp);
}
END_TEST

START_TEST(test_int_to_decimal_greatest_int) {
  s21_decimal decimal;
  int x = 2147483647;
  int res = s21_from_int_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  unsigned int sign_c_sharp = 0;
  unsigned int scale_c_sharp = 0;
  unsigned mantissa0_c_sharp = 2147483647;
  unsigned int mantissa1_c_sharp = 0;
  unsigned int mantissa2_c_sharp = 0;

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, sign_c_sharp);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, scale_c_sharp);
  ck_assert_uint_eq(decimal.bits[0], mantissa0_c_sharp);
  ck_assert_uint_eq(decimal.bits[1], mantissa1_c_sharp);
  ck_assert_uint_eq(decimal.bits[2], mantissa2_c_sharp);
}
END_TEST

START_TEST(test_int_to_decimal_least_int) {
  s21_decimal decimal;
  int x = -2147483648;
  int res = s21_from_int_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  unsigned int sign_c_sharp = 1;
  unsigned int scale_c_sharp = 0;
  unsigned mantissa0_c_sharp = 2147483648;
  unsigned int mantissa1_c_sharp = 0;
  unsigned int mantissa2_c_sharp = 0;

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, sign_c_sharp);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, scale_c_sharp);
  ck_assert_uint_eq(decimal.bits[0], mantissa0_c_sharp);
  ck_assert_uint_eq(decimal.bits[1], mantissa1_c_sharp);
  ck_assert_uint_eq(decimal.bits[2], mantissa2_c_sharp);
}
END_TEST

START_TEST(test_int_to_decimal_zero) {
  s21_decimal decimal;
  int x = 0;
  int res = s21_from_int_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  unsigned int sign_c_sharp = 0;
  unsigned int scale_c_sharp = 0;
  unsigned mantissa0_c_sharp = 0;
  unsigned int mantissa1_c_sharp = 0;
  unsigned int mantissa2_c_sharp = 0;

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, sign_c_sharp);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, scale_c_sharp);
  ck_assert_uint_eq(decimal.bits[0], mantissa0_c_sharp);
  ck_assert_uint_eq(decimal.bits[1], mantissa1_c_sharp);
  ck_assert_uint_eq(decimal.bits[2], mantissa2_c_sharp);
}
END_TEST

START_TEST(test_int_to_decimal_uncorrect) {
  s21_decimal *decimal = NULL;
  int x = -214748;
  int res = s21_from_int_to_decimal(x, decimal);
  ck_assert_int_eq(1, res);
}
END_TEST

// FLOAT TO DECIMAL

START_TEST(test_float_to_decimal_simple1) {
  s21_decimal decimal;
  float x = 1.000000567;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  unsigned int sign_c_sharp = 0;
  unsigned int scale_c_sharp = 6;
  unsigned int mantissa0_c_sharp = 1000001;
  unsigned int mantissa1_c_sharp = 0;
  unsigned int mantissa2_c_sharp = 0;

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, sign_c_sharp);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, scale_c_sharp);
  ck_assert_uint_eq(decimal.bits[0], mantissa0_c_sharp);
  ck_assert_uint_eq(decimal.bits[1], mantissa1_c_sharp);
  ck_assert_uint_eq(decimal.bits[2], mantissa2_c_sharp);
}
END_TEST

START_TEST(test_float_to_decimal_simple2) {
  s21_decimal decimal;
  float x = 4444443.5;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  unsigned int sign_c_sharp = 0;
  unsigned int scale_c_sharp = 0;
  unsigned int mantissa0_c_sharp = 4444444;
  unsigned int mantissa1_c_sharp = 0;
  unsigned int mantissa2_c_sharp = 0;

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, sign_c_sharp);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, scale_c_sharp);
  ck_assert_uint_eq(decimal.bits[0], mantissa0_c_sharp);
  ck_assert_uint_eq(decimal.bits[1], mantissa1_c_sharp);
  ck_assert_uint_eq(decimal.bits[2], mantissa2_c_sharp);
}
END_TEST

START_TEST(test_float_to_decimal_simple3) {
  s21_decimal decimal;
  float x = 12300.999;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  unsigned int sign_c_sharp = 0;
  unsigned int scale_c_sharp = 0;
  unsigned int mantissa0_c_sharp = 12301;
  unsigned int mantissa1_c_sharp = 0;
  unsigned int mantissa2_c_sharp = 0;

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, sign_c_sharp);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, scale_c_sharp);
  ck_assert_uint_eq(decimal.bits[0], mantissa0_c_sharp);
  ck_assert_uint_eq(decimal.bits[1], mantissa1_c_sharp);
  ck_assert_uint_eq(decimal.bits[2], mantissa2_c_sharp);
}
END_TEST

START_TEST(test_float_to_decimal_int) {
  s21_decimal decimal;
  float x = 123456788.0;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  unsigned int sign_c_sharp = 0;
  unsigned int scale_c_sharp = 0;
  unsigned int mantissa0_c_sharp = 123456800;
  unsigned int mantissa1_c_sharp = 0;
  unsigned int mantissa2_c_sharp = 0;

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, sign_c_sharp);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, scale_c_sharp);
  ck_assert_uint_eq(decimal.bits[0], mantissa0_c_sharp);
  ck_assert_uint_eq(decimal.bits[1], mantissa1_c_sharp);
  ck_assert_uint_eq(decimal.bits[2], mantissa2_c_sharp);
}
END_TEST

START_TEST(test_float_to_decimal_int_div10) {
  s21_decimal decimal;
  float x = 1230000.0;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  unsigned int sign_c_sharp = 0;
  unsigned int scale_c_sharp = 0;
  unsigned int mantissa0_c_sharp = 1230000;
  unsigned int mantissa1_c_sharp = 0;
  unsigned int mantissa2_c_sharp = 0;

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, sign_c_sharp);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, scale_c_sharp);
  ck_assert_uint_eq(decimal.bits[0], mantissa0_c_sharp);
  ck_assert_uint_eq(decimal.bits[1], mantissa1_c_sharp);
  ck_assert_uint_eq(decimal.bits[2], mantissa2_c_sharp);
}
END_TEST

START_TEST(test_float_to_decimal_basic) {
  s21_decimal decimal;
  float x = 0.456745645733;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  unsigned int sign_c_sharp = 0;
  unsigned int scale_c_sharp = 7;
  unsigned int mantissa0_c_sharp = 4567457;
  unsigned int mantissa1_c_sharp = 0;
  unsigned int mantissa2_c_sharp = 0;

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, sign_c_sharp);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, scale_c_sharp);
  ck_assert_uint_eq(decimal.bits[0], mantissa0_c_sharp);
  ck_assert_uint_eq(decimal.bits[1], mantissa1_c_sharp);
  ck_assert_uint_eq(decimal.bits[2], mantissa2_c_sharp);
}
END_TEST

START_TEST(test_float_to_decimal_bank_round) {
  s21_decimal decimal;
  float x = 12345685.0;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  unsigned int sign_c_sharp = 0;
  unsigned int scale_c_sharp = 0;
  unsigned int mantissa0_c_sharp = 12345680;
  unsigned int mantissa1_c_sharp = 0;
  unsigned int mantissa2_c_sharp = 0;

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, sign_c_sharp);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, scale_c_sharp);
  ck_assert_uint_eq(decimal.bits[0], mantissa0_c_sharp);
  ck_assert_uint_eq(decimal.bits[1], mantissa1_c_sharp);
  ck_assert_uint_eq(decimal.bits[2], mantissa2_c_sharp);
}
END_TEST

START_TEST(test_float_to_decimal_two_signif_digits) {
  s21_decimal decimal;
  float x = 0.00021;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  unsigned int sign_c_sharp = 0;
  unsigned int scale_c_sharp = 5;
  unsigned int mantissa0_c_sharp = 21;
  unsigned int mantissa1_c_sharp = 0;
  unsigned int mantissa2_c_sharp = 0;

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, sign_c_sharp);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, scale_c_sharp);
  ck_assert_uint_eq(decimal.bits[0], mantissa0_c_sharp);
  ck_assert_uint_eq(decimal.bits[1], mantissa1_c_sharp);
  ck_assert_uint_eq(decimal.bits[2], mantissa2_c_sharp);
}
END_TEST

START_TEST(test_float_to_decimal_small_num) {
  s21_decimal decimal;
  float x = 0.00000000000021;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  unsigned int sign_c_sharp = 0;
  unsigned int scale_c_sharp = 14;
  unsigned int mantissa0_c_sharp = 21;
  unsigned int mantissa1_c_sharp = 0;
  unsigned int mantissa2_c_sharp = 0;

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, sign_c_sharp);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, scale_c_sharp);
  ck_assert_uint_eq(decimal.bits[0], mantissa0_c_sharp);
  ck_assert_uint_eq(decimal.bits[1], mantissa1_c_sharp);
  ck_assert_uint_eq(decimal.bits[2], mantissa2_c_sharp);
}
END_TEST

START_TEST(test_float_to_decimal_int_and_small_frac) {
  s21_decimal decimal;
  float x = 5000.00000000000021;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  unsigned int sign_c_sharp = 0;
  unsigned int scale_c_sharp = 0;
  unsigned int mantissa0_c_sharp = 5000;
  unsigned int mantissa1_c_sharp = 0;
  unsigned int mantissa2_c_sharp = 0;

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, sign_c_sharp);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, scale_c_sharp);
  ck_assert_uint_eq(decimal.bits[0], mantissa0_c_sharp);
  ck_assert_uint_eq(decimal.bits[1], mantissa1_c_sharp);
  ck_assert_uint_eq(decimal.bits[2], mantissa2_c_sharp);
}
END_TEST

START_TEST(test_float_to_decimal_incorrect_too_big) {
  s21_decimal decimal;
  float x = 7.9228162e28;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(1, res);

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, 0);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, 0);
  ck_assert_uint_eq(decimal.bits[0], 0);
  ck_assert_uint_eq(decimal.bits[1], 0);
  ck_assert_uint_eq(decimal.bits[2], 0);
}
END_TEST

START_TEST(test_float_to_decimal_incorrect_nan) {
  s21_decimal decimal;
  float x = NAN;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(1, res);

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, 0);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, 0);
  ck_assert_uint_eq(decimal.bits[0], 0);
  ck_assert_uint_eq(decimal.bits[1], 0);
  ck_assert_uint_eq(decimal.bits[2], 0);
}
END_TEST

START_TEST(test_float_to_decimal_incorrect_pos_inf) {
  s21_decimal decimal;
  float x = INFINITY;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(1, res);

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, 0);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, 0);
  ck_assert_uint_eq(decimal.bits[0], 0);
  ck_assert_uint_eq(decimal.bits[1], 0);
  ck_assert_uint_eq(decimal.bits[2], 0);
}
END_TEST

START_TEST(test_float_to_decimal_incorrect_neg_inf) {
  s21_decimal decimal;
  float x = -INFINITY;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(1, res);

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, 0);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, 0);
  ck_assert_uint_eq(decimal.bits[0], 0);
  ck_assert_uint_eq(decimal.bits[1], 0);
  ck_assert_uint_eq(decimal.bits[2], 0);
}
END_TEST

START_TEST(test_float_to_decimal_incorrect_less_e_28_neg) {
  s21_decimal decimal;
  float x = -(1e-28 - 1e-29);
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(1, res);

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, 1);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, 0);
  ck_assert_uint_eq(decimal.bits[0], 0);
  ck_assert_uint_eq(decimal.bits[1], 0);
  ck_assert_uint_eq(decimal.bits[2], 0);
}
END_TEST

START_TEST(test_float_to_decimal_incorrect_less_e_28_pos) {
  s21_decimal decimal;
  float x = 1e-28 - 1e-29;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(1, res);

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, 0);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, 0);
  ck_assert_uint_eq(decimal.bits[0], 0);
  ck_assert_uint_eq(decimal.bits[1], 0);
  ck_assert_uint_eq(decimal.bits[2], 0);
}
END_TEST

START_TEST(test_float_to_decimal_incorrect_neg_zero) {
  s21_decimal decimal;
  float x = -0.0;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, 1);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, 0);
  ck_assert_uint_eq(decimal.bits[0], 0);
  ck_assert_uint_eq(decimal.bits[1], 0);
  ck_assert_uint_eq(decimal.bits[2], 0);
}
END_TEST

START_TEST(test_float_to_decimal_incorrect_pos_zero) {
  s21_decimal decimal;
  float x = +0.0000;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, 0);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, 0);
  ck_assert_uint_eq(decimal.bits[0], 0);
  ck_assert_uint_eq(decimal.bits[1], 0);
  ck_assert_uint_eq(decimal.bits[2], 0);
}
END_TEST

START_TEST(test_float_to_decimal_incorrect_decimal) {
  s21_decimal *decimal = NULL;
  float x = 1.0000;
  int res = s21_from_float_to_decimal(x, decimal);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_float_to_decimal_minimum_num) {
  s21_decimal decimal;
  float x = -1e-28;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  unsigned int sign_c_sharp = 1;
  unsigned int scale_c_sharp = 28;
  unsigned int mantissa0_c_sharp = 1;
  unsigned int mantissa1_c_sharp = 0;
  unsigned int mantissa2_c_sharp = 0;

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, sign_c_sharp);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, scale_c_sharp);
  ck_assert_uint_eq(decimal.bits[0], mantissa0_c_sharp);
  ck_assert_uint_eq(decimal.bits[1], mantissa1_c_sharp);
  ck_assert_uint_eq(decimal.bits[2], mantissa2_c_sharp);
}
END_TEST

START_TEST(test_float_to_decimal_max_num) {
  s21_decimal decimal;
  float x = -7.922816e28;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  unsigned int sign_c_sharp = 1;
  unsigned int scale_c_sharp = 0;
  unsigned mantissa0_c_sharp = 536870912;
  unsigned int mantissa1_c_sharp = 3012735514;
  unsigned int mantissa2_c_sharp = 4294967159;

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, sign_c_sharp);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, scale_c_sharp);
  ck_assert_uint_eq(decimal.bits[0], mantissa0_c_sharp);
  ck_assert_uint_eq(decimal.bits[1], mantissa1_c_sharp);
  ck_assert_uint_eq(decimal.bits[2], mantissa2_c_sharp);
}
END_TEST

START_TEST(test_float_to_decimal_max2_num) {
  s21_decimal decimal;
  float x = 12547999962.0;
  int res = s21_from_float_to_decimal(x, &decimal);
  ck_assert_int_eq(0, res);

  unsigned int sign_c_sharp = 0;
  unsigned int scale_c_sharp = 0;
  unsigned int mantissa0_c_sharp = 3958065408;
  unsigned int mantissa1_c_sharp = 2;
  unsigned int mantissa2_c_sharp = 0;

  ck_assert_uint_eq(decimal.bits[3] >> 31 & 1u, sign_c_sharp);
  ck_assert_uint_eq(decimal.bits[3] >> 16 & 0xFF, scale_c_sharp);
  ck_assert_uint_eq(decimal.bits[0], mantissa0_c_sharp);
  ck_assert_uint_eq(decimal.bits[1], mantissa1_c_sharp);
  ck_assert_uint_eq(decimal.bits[2], mantissa2_c_sharp);
}
END_TEST

// DECIMAL TO INT

START_TEST(test_decimal_to_int_null_int) {
  s21_decimal decimal = {{0, 0, 0, 0}};
  int res = s21_from_decimal_to_int(decimal, NULL);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_decimal_to_int_uncorrect_free_bits1) {
  int n;
  s21_decimal decimal = {{0, 0, 0, 0x80000001}};
  int res = s21_from_decimal_to_int(decimal, &n);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_decimal_to_int_uncorrect_free_bits2) {
  int n;
  s21_decimal decimal = {{0, 0, 0, 0x01000000}};
  int res = s21_from_decimal_to_int(decimal, &n);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_decimal_to_int_uncorrect_scale1) {
  int n;
  s21_decimal decimal = {{5, 0, 0, 0x1E0000}};
  int res = s21_from_decimal_to_int(decimal, &n);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_decimal_to_int_uncorrect_scale2) {
  int n;
  s21_decimal decimal = {{1, 0, 0, 0xFF0000}};
  int res = s21_from_decimal_to_int(decimal, &n);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_decimal_to_int_simple1) {
  int n;
  // Decimal value:   6436.4380779142
  s21_decimal decimal = {{0x000D7286, 0x00003A8A, 0x00000000, 0x000A0000}};
  int res = s21_from_decimal_to_int(decimal, &n);
  int int_res = 6436;
  ck_assert_int_eq(0, res);
  ck_assert_int_eq(n, int_res);
}
END_TEST

START_TEST(test_decimal_to_int_negative) {
  int n;
  // Decimal value:   -6436.4380779142
  s21_decimal decimal = {{0x000D7286, 0x00003A8A, 0x00000000, 0x800A0000}};
  int res = s21_from_decimal_to_int(decimal, &n);
  int int_res = -6436;
  ck_assert_int_eq(0, res);
  ck_assert_int_eq(n, int_res);
}
END_TEST

START_TEST(test_decimal_to_int_with_mid) {
  int n;
  // Decimal value:   184467440135.80009457
  s21_decimal decimal = {{0xFFFFFFF1, 0xFFFFFFF1, 0x00000000, 0x00080000}};
  int res = s21_from_decimal_to_int(decimal, &n);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_decimal_to_int_with_high) {
  int n;
  // Decimal value:   792281625142643375935.43950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00080000}};
  int res = s21_from_decimal_to_int(decimal, &n);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_decimal_to_int_with_high_neg) {
  int n;
  // Decimal value:   -792281625142643375935.43950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
  int res = s21_from_decimal_to_int(decimal, &n);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_decimal_to_int_more_max_low) {
  int n;
  // Decimal value:   -2147483649
  s21_decimal decimal = {{0x80000001, 0x0, 0x0, 0x80000000}};
  int res = s21_from_decimal_to_int(decimal, &n);
  ck_assert_int_eq(1, res);
}
END_TEST

// DECIMAL TO FLOAT

START_TEST(test_decimal_to_float_null_float) {
  s21_decimal decimal = {{0, 0, 0, 0}};
  int res = s21_from_decimal_to_float(decimal, NULL);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_decimal_to_float_uncorrect_free_bits1) {
  float n;
  s21_decimal decimal = {{0, 0, 0, 0x80000001}};
  int res = s21_from_decimal_to_float(decimal, &n);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_decimal_to_float_uncorrect_free_bits2) {
  float n;
  s21_decimal decimal = {{0, 0, 0, 0x01000000}};
  int res = s21_from_decimal_to_float(decimal, &n);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_decimal_to_float_uncorrect_scale1) {
  float n;
  s21_decimal decimal = {{5, 0, 0, 0x1E0000}};
  int res = s21_from_decimal_to_float(decimal, &n);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_decimal_to_float_uncorrect_scale2) {
  float n;
  s21_decimal decimal = {{1, 0, 0, 0xFF0000}};
  int res = s21_from_decimal_to_float(decimal, &n);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_decimal_to_float_simple1) {
  float n;
  // Decimal value:   6436.4380779142
  s21_decimal decimal = {{0x000D7286, 0x00003A8A, 0x00000000, 0x000A0000}};
  int res = s21_from_decimal_to_float(decimal, &n);
  float float_res = 6436.438;
  ck_assert_int_eq(0, res);
  ck_assert_float_eq(n, float_res);
}
END_TEST

START_TEST(test_decimal_to_float_negative) {
  float n;
  // Decimal value:   -6436.4380779142
  s21_decimal decimal = {{0x000D7286, 0x00003A8A, 0x00000000, 0x800A0000}};
  int res = s21_from_decimal_to_float(decimal, &n);
  float float_res = -6436.438;
  ck_assert_int_eq(0, res);
  ck_assert_float_eq(n, float_res);
}
END_TEST

START_TEST(test_decimal_to_float_with_mid) {
  float n;
  // Decimal value:   184467440135.80009457
  s21_decimal decimal = {{0xFFFFFFF1, 0xFFFFFFF1, 0x00000000, 0x00080000}};
  int res = s21_from_decimal_to_float(decimal, &n);
  float float_res = 1.8446744E+11;
  ck_assert_int_eq(0, res);
  ck_assert_float_eq(n, float_res);
}
END_TEST

START_TEST(test_decimal_to_float_with_high) {
  float n;
  // Decimal value:   792281625142643375935.43950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00080000}};
  int res = s21_from_decimal_to_float(decimal, &n);
  float float_res = 7.922816E+20;
  ck_assert_int_eq(0, res);
  ck_assert_float_eq(n, float_res);
}
END_TEST

START_TEST(test_decimal_to_float_with_high_neg) {
  float n;
  // Decimal value:   -792281625142643375935.43950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
  int res = s21_from_decimal_to_float(decimal, &n);
  float float_res = -7.922816E+20;
  ck_assert_int_eq(0, res);
  ck_assert_float_eq(n, float_res);
}
END_TEST

START_TEST(test_decimal_to_float_more_max_low) {
  float n;
  // Decimal value:   -2147483649
  s21_decimal decimal = {{0x80000001, 0x0, 0x0, 0x80000000}};
  int res = s21_from_decimal_to_float(decimal, &n);
  float float_res = -2.1474836E+09;
  ck_assert_int_eq(0, res);
  ck_assert_float_eq(n, float_res);
}
END_TEST

Suite *from_int_to_decimal(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("from_int_to_decimal");
  tc = tcase_create("Core");

  tcase_add_test(tc, test_int_to_decimal_simple);
  tcase_add_test(tc, test_int_to_decimal_greatest_int);
  tcase_add_test(tc, test_int_to_decimal_least_int);
  tcase_add_test(tc, test_int_to_decimal_zero);
  tcase_add_test(tc, test_int_to_decimal_uncorrect);

  suite_add_tcase(s, tc);
  return s;
}

Suite *from_float_to_decimal(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("from_float_to_decimal");
  tc = tcase_create("Core");

  tcase_add_test(tc, test_float_to_decimal_simple1);
  tcase_add_test(tc, test_float_to_decimal_simple2);
  tcase_add_test(tc, test_float_to_decimal_simple3);
  tcase_add_test(tc, test_float_to_decimal_int_div10);
  tcase_add_test(tc, test_float_to_decimal_int);
  tcase_add_test(tc, test_float_to_decimal_basic);
  tcase_add_test(tc, test_float_to_decimal_bank_round);
  tcase_add_test(tc, test_float_to_decimal_two_signif_digits);
  tcase_add_test(tc, test_float_to_decimal_small_num);
  tcase_add_test(tc, test_float_to_decimal_int_and_small_frac);
  tcase_add_test(tc, test_float_to_decimal_incorrect_too_big);
  tcase_add_test(tc, test_float_to_decimal_incorrect_nan);
  tcase_add_test(tc, test_float_to_decimal_incorrect_pos_inf);
  tcase_add_test(tc, test_float_to_decimal_incorrect_neg_inf);
  tcase_add_test(tc, test_float_to_decimal_incorrect_less_e_28_neg);
  tcase_add_test(tc, test_float_to_decimal_incorrect_less_e_28_pos);
  tcase_add_test(tc, test_float_to_decimal_incorrect_neg_zero);
  tcase_add_test(tc, test_float_to_decimal_incorrect_pos_zero);
  tcase_add_test(tc, test_float_to_decimal_incorrect_decimal);
  tcase_add_test(tc, test_float_to_decimal_minimum_num);
  tcase_add_test(tc, test_float_to_decimal_max_num);
  tcase_add_test(tc, test_float_to_decimal_max2_num);

  suite_add_tcase(s, tc);
  return s;
}

Suite *from_decimal_to_int(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("from_decimal_to_int");
  tc = tcase_create("Core");

  tcase_add_test(tc, test_decimal_to_int_null_int);
  tcase_add_test(tc, test_decimal_to_int_uncorrect_free_bits1);
  tcase_add_test(tc, test_decimal_to_int_uncorrect_free_bits2);
  tcase_add_test(tc, test_decimal_to_int_uncorrect_scale1);
  tcase_add_test(tc, test_decimal_to_int_uncorrect_scale2);
  tcase_add_test(tc, test_decimal_to_int_simple1);
  tcase_add_test(tc, test_decimal_to_int_negative);
  tcase_add_test(tc, test_decimal_to_int_with_mid);
  tcase_add_test(tc, test_decimal_to_int_with_high);
  tcase_add_test(tc, test_decimal_to_int_with_high_neg);
  tcase_add_test(tc, test_decimal_to_int_more_max_low);

  suite_add_tcase(s, tc);
  return s;
}

Suite *from_decimal_to_float(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("from_decimal_to_float");
  tc = tcase_create("Core");

  tcase_add_test(tc, test_decimal_to_float_null_float);
  tcase_add_test(tc, test_decimal_to_float_uncorrect_free_bits1);
  tcase_add_test(tc, test_decimal_to_float_uncorrect_free_bits2);
  tcase_add_test(tc, test_decimal_to_float_uncorrect_scale1);
  tcase_add_test(tc, test_decimal_to_float_uncorrect_scale2);
  tcase_add_test(tc, test_decimal_to_float_simple1);
  tcase_add_test(tc, test_decimal_to_float_negative);
  tcase_add_test(tc, test_decimal_to_float_with_mid);
  tcase_add_test(tc, test_decimal_to_float_with_high);
  tcase_add_test(tc, test_decimal_to_float_with_high_neg);
  tcase_add_test(tc, test_decimal_to_float_more_max_low);

  suite_add_tcase(s, tc);
  return s;
}
