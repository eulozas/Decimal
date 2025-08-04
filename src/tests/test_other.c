#include <check.h>

#include "../s21_decimal.h"

START_TEST(test_floor_1) {
  // Decimal value:   -227725055642965785980985
  s21_decimal decimal = {{12345, 12345, 12345, 0x80000000}};
  s21_decimal decimal_res = {0};
  s21_decimal decimal_check = {{12345, 12345, 12345, 0x80000000}};

  int res = s21_floor(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_floor_2) {
  // Decimal value:   227725055642965785980985
  s21_decimal decimal = {{12345, 12345, 12345, 0}};
  s21_decimal decimal_res = {0};
  s21_decimal decimal_check = {{12345, 12345, 12345, 0}};

  int res = s21_floor(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_floor_3) {
  // Decimal value:   -2277250556429657.85980985
  s21_decimal decimal = {{12345, 12345, 12345, 0x80080000}};
  s21_decimal decimal_res = {0};
  // Decimal value:   -2277250556429658
  s21_decimal decimal_check = {{3061515610, 530213, 0, 0x80000000}};

  int res = s21_floor(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_floor_4) {
  // Decimal value:   -2277250555900088.40320071
  s21_decimal decimal = {{1111111, 15, 12345, 0x80080000}};
  s21_decimal decimal_res = {0};
  // Decimal value:   -2277250555900088
  s21_decimal decimal_check = {{3060986041, 530213, 0, 0x80000000}};

  int res = s21_floor(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_floor_5) {
  // Decimal value:   -1230.0
  s21_decimal decimal = {{12300, 0, 0, 0x80010000}};
  s21_decimal decimal_res = {0};
  // Decimal value:   -1230
  s21_decimal decimal_check = {{1230, 0, 0, 0x80000000}};

  int res = s21_floor(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_floor_6) {
  // Decimal value:   1230.0
  s21_decimal decimal = {{12300, 0, 0, 0x00010000}};
  s21_decimal decimal_res = {0};
  // Decimal value:   1230
  s21_decimal decimal_check = {{1230, 0, 0, 0x00000000}};

  int res = s21_floor(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_floor_7) {
  // Decimal value:   -1844674407370955161.5
  s21_decimal decimal = {{4294967295, 4294967295, 0, 0x80010000}};
  s21_decimal decimal_res = {0};
  // Decimal value:   -1844674407370955162
  s21_decimal decimal_check = {{2576980378, 429496729, 0, 0x80000000}};

  int res = s21_floor(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_floor_8) {
  // Decimal value:   -4294967295.1
  s21_decimal decimal = {{0xFFFFFFF7, 0x00000009, 0, 0x80010000}};
  s21_decimal decimal_res = {0};
  // Decimal value:   -4294967296
  s21_decimal decimal_check = {{0, 1, 0, 0x80000000}};

  int res = s21_floor(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_floor_9) {
  // Decimal value:   -18446744073709551616.1
  s21_decimal decimal = {{0x00000001, 0x00000000, 0x0000000A, 0x80010000}};
  s21_decimal decimal_res = {0};
  // Decimal value:   -18446744073709551617
  s21_decimal decimal_check = {{1, 0, 1, 0x80000000}};

  int res = s21_floor(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_floor_10) {
  // Decimal value:   -18446744073709551615.1
  s21_decimal decimal = {{0xFFFFFFF7, 0xFFFFFFFF, 0x00000009, 0x80010000}};
  s21_decimal decimal_res = {0};
  // Decimal value:   -18446744073709551616
  s21_decimal decimal_check = {{0, 0, 1, 0x80000000}};

  int res = s21_floor(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_floor_null) {
  s21_decimal decimal = {{0, 0, 0, 0}};
  s21_decimal *decimal_res = NULL;
  int res = s21_floor(decimal, decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_floor_uncorrect_free_bits1) {
  s21_decimal decimal = {{0, 0, 0, 0x80000001}};
  s21_decimal decimal_res = {0};
  int res = s21_floor(decimal, &decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_floor_uncorrect_free_bits2) {
  s21_decimal decimal = {{0, 0, 0, 0x01000000}};
  s21_decimal decimal_res = {0};
  int res = s21_floor(decimal, &decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_floor_uncorrect_scale1) {
  s21_decimal decimal = {{5, 0, 0, 0x1E0000}};
  s21_decimal decimal_res = {0};
  int res = s21_floor(decimal, &decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_floor_uncorrect_scale2) {
  s21_decimal decimal = {{1, 0, 0, 0xFF0000}};
  s21_decimal decimal_res = {0};
  int res = s21_floor(decimal, &decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_round_0) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal decimal_res = {0};

  int res = s21_round(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_round_1) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395034
  s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  s21_decimal decimal_res = {0};

  int res = s21_round(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_round_2) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -7922816251426433759354395034
  s21_decimal decimal_check = {
      {0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  s21_decimal decimal_res = {0};

  int res = s21_round(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_round_4) {
  // -792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
  // -792281625142643375935439503
  s21_decimal decimal_check = {{0x28F5C28F, 0xF5C28F5C, 0x28F5C28, 0x80000000}};
  s21_decimal decimal_res = {0};

  int res = s21_round(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_round_5) {
  // 79228162514264337593.543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
  // 79228162514264337594
  s21_decimal decimal_check = {{0xB5A52CBA, 0x4B82FA09, 0x4, 0x0}};
  s21_decimal decimal_res = {0};

  int res = s21_round(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_round_null) {
  s21_decimal decimal = {{0, 0, 0, 0}};
  s21_decimal *decimal_res = NULL;
  int res = s21_round(decimal, decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_round_uncorrect_free_bits1) {
  s21_decimal decimal = {{0, 0, 0, 0x80000001}};
  s21_decimal decimal_res = {0};
  int res = s21_round(decimal, &decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_round_uncorrect_free_bits2) {
  s21_decimal decimal = {{0, 0, 0, 0x01000000}};
  s21_decimal decimal_res = {0};
  int res = s21_round(decimal, &decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_round_uncorrect_scale1) {
  s21_decimal decimal = {{5, 0, 0, 0x1E0000}};
  s21_decimal decimal_res = {0};
  int res = s21_round(decimal, &decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_round_uncorrect_scale2) {
  s21_decimal decimal = {{1, 0, 0, 0xFF0000}};
  s21_decimal decimal_res = {0};
  int res = s21_round(decimal, &decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_truncate_0) {
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 52818775009509558392832655360
  s21_decimal decimal_check = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  s21_decimal decimal_res = {0};

  int res = s21_truncate(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_truncate_1) {
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
  // 5281877500950955839283265536
  s21_decimal decimal_check = {{0x0, 0x11111111, 0x11111111, 0x0}};
  s21_decimal decimal_res = {0};

  int res = s21_truncate(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_truncate_2) {
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x800D0000}};
  // -5281877500950955
  s21_decimal decimal_check = {{0xF030F9AB, 0x12C3D6, 0x0, 0x80000000}};
  s21_decimal decimal_res = {0};

  int res = s21_truncate(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_truncate_null) {
  s21_decimal decimal = {{0, 0, 0, 0}};
  s21_decimal *decimal_res = NULL;
  int res = s21_truncate(decimal, decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_truncate_uncorrect_free_bits1) {
  s21_decimal decimal = {{0, 0, 0, 0x80000001}};
  s21_decimal decimal_res = {0};
  int res = s21_truncate(decimal, &decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_truncate_uncorrect_free_bits2) {
  s21_decimal decimal = {{0, 0, 0, 0x01000000}};
  s21_decimal decimal_res = {0};
  int res = s21_truncate(decimal, &decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_truncate_uncorrect_scale1) {
  s21_decimal decimal = {{5, 0, 0, 0x1E0000}};
  s21_decimal decimal_res = {0};
  int res = s21_truncate(decimal, &decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_truncate_uncorrect_scale2) {
  s21_decimal decimal = {{1, 0, 0, 0xFF0000}};
  s21_decimal decimal_res = {0};
  int res = s21_truncate(decimal, &decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_negate_0) {
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x0}};
  s21_decimal decimal_res = {0};
  // Decimal value:   1230
  s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x80000000}};

  int res = s21_negate(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_negate_1) {
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80000000}};
  s21_decimal decimal_res = {0};
  // Decimal value:   1230
  s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x0}};

  int res = s21_negate(decimal, &decimal_res);
  ck_assert_int_eq(0, res);

  ck_assert_uint_eq(decimal_res.bits[3] >> 31 & 1u,
                    decimal_check.bits[3] >> 31 & 1u);
  ck_assert_uint_eq(decimal_res.bits[3] >> 16 & 0xFF,
                    decimal_check.bits[3] >> 16 & 0xFF);
  ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
  ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
  ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_negate_null) {
  s21_decimal decimal = {{0, 0, 0, 0}};
  s21_decimal *decimal_res = NULL;
  int res = s21_negate(decimal, decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_negate_uncorrect_free_bits1) {
  s21_decimal decimal = {{0, 0, 0, 0x80000001}};
  s21_decimal decimal_res = {0};
  int res = s21_negate(decimal, &decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_negate_uncorrect_free_bits2) {
  s21_decimal decimal = {{0, 0, 0, 0x01000000}};
  s21_decimal decimal_res = {0};
  int res = s21_negate(decimal, &decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_negate_uncorrect_scale1) {
  s21_decimal decimal = {{5, 0, 0, 0x1E0000}};
  s21_decimal decimal_res = {0};
  int res = s21_negate(decimal, &decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_negate_uncorrect_scale2) {
  s21_decimal decimal = {{1, 0, 0, 0xFF0000}};
  s21_decimal decimal_res = {0};
  int res = s21_negate(decimal, &decimal_res);
  ck_assert_int_eq(1, res);
}
END_TEST

Suite *floor_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("floor_suite");
  tc = tcase_create("Core");

  tcase_add_test(tc, test_floor_1);
  tcase_add_test(tc, test_floor_2);
  tcase_add_test(tc, test_floor_3);
  tcase_add_test(tc, test_floor_4);
  tcase_add_test(tc, test_floor_5);
  tcase_add_test(tc, test_floor_6);
  tcase_add_test(tc, test_floor_7);
  tcase_add_test(tc, test_floor_8);
  tcase_add_test(tc, test_floor_9);
  tcase_add_test(tc, test_floor_10);
  tcase_add_test(tc, test_floor_null);
  tcase_add_test(tc, test_floor_uncorrect_free_bits1);
  tcase_add_test(tc, test_floor_uncorrect_free_bits2);
  tcase_add_test(tc, test_floor_uncorrect_scale1);
  tcase_add_test(tc, test_floor_uncorrect_scale2);

  suite_add_tcase(s, tc);
  return s;
}

Suite *round_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("round_suite");
  tc = tcase_create("Core");

  tcase_add_test(tc, test_round_0);
  tcase_add_test(tc, test_round_1);
  tcase_add_test(tc, test_round_2);
  tcase_add_test(tc, test_round_4);
  tcase_add_test(tc, test_round_5);
  tcase_add_test(tc, test_round_null);
  tcase_add_test(tc, test_round_uncorrect_free_bits1);
  tcase_add_test(tc, test_round_uncorrect_free_bits2);
  tcase_add_test(tc, test_round_uncorrect_scale1);
  tcase_add_test(tc, test_round_uncorrect_scale2);

  suite_add_tcase(s, tc);
  return s;
}

Suite *truncate_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("truncate_suite");
  tc = tcase_create("Core");

  tcase_add_test(tc, test_truncate_0);
  tcase_add_test(tc, test_truncate_1);
  tcase_add_test(tc, test_truncate_2);
  tcase_add_test(tc, test_truncate_null);
  tcase_add_test(tc, test_truncate_uncorrect_free_bits1);
  tcase_add_test(tc, test_truncate_uncorrect_free_bits2);
  tcase_add_test(tc, test_truncate_uncorrect_scale1);
  tcase_add_test(tc, test_truncate_uncorrect_scale2);

  suite_add_tcase(s, tc);
  return s;
}

Suite *negate_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("negate_suite");
  tc = tcase_create("Core");
  tcase_add_test(tc, test_negate_0);
  tcase_add_test(tc, test_negate_1);
  tcase_add_test(tc, test_negate_null);
  tcase_add_test(tc, test_negate_uncorrect_free_bits1);
  tcase_add_test(tc, test_negate_uncorrect_free_bits2);
  tcase_add_test(tc, test_negate_uncorrect_scale1);
  tcase_add_test(tc, test_negate_uncorrect_scale2);

  suite_add_tcase(s, tc);
  return s;
}
