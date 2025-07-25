#include <check.h>
#include "../s21_decimal.h"


//INT TO DECIMAL

START_TEST(test_floor_1) {
    //Decimal value:   -227725055642965785980985
    s21_decimal decimal = {{12345, 12345, 12345, 0x80000000}};
    s21_decimal decimal_res = {0};
    s21_decimal decimal_check = {{12345, 12345, 12345, 0x80000000}};
   
    int res = s21_floor(decimal, &decimal_res);
    ck_assert_int_eq(0, res);
    
    ck_assert_uint_eq(decimal_res.bits[3]>>31 & 1u, decimal_check.bits[3]>>31 & 1u);
    ck_assert_uint_eq(decimal_res.bits[3]>>16 & 0xFF, decimal_check.bits[3]>>16 & 0xFF);
    ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
    ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
    ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_floor_2) {
    //Decimal value:   227725055642965785980985
    s21_decimal decimal = {{12345, 12345, 12345, 0}};
    s21_decimal decimal_res = {0};
    s21_decimal decimal_check = {{12345, 12345, 12345, 0}};
   
    int res = s21_floor(decimal, &decimal_res);
    ck_assert_int_eq(0, res);
    
    ck_assert_uint_eq(decimal_res.bits[3]>>31 & 1u, decimal_check.bits[3]>>31 & 1u);
    ck_assert_uint_eq(decimal_res.bits[3]>>16 & 0xFF, decimal_check.bits[3]>>16 & 0xFF);
    ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
    ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
    ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_floor_3) {
    //Decimal value:   -2277250556429657.85980985
    s21_decimal decimal = {{12345, 12345, 12345, 0x80080000}};
    s21_decimal decimal_res = {0};
    //Decimal value:   -2277250556429658
    s21_decimal decimal_check = {{3061515610, 530213, 0, 0x80000000}};
   
    int res = s21_floor(decimal, &decimal_res);
    ck_assert_int_eq(0, res);
    
    ck_assert_uint_eq(decimal_res.bits[3]>>31 & 1u, decimal_check.bits[3]>>31 & 1u);
    ck_assert_uint_eq(decimal_res.bits[3]>>16 & 0xFF, decimal_check.bits[3]>>16 & 0xFF);
    ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
    ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
    ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_floor_4) {
    //Decimal value:   -2277250555900088.40320071
    s21_decimal decimal = {{1111111, 15, 12345, 0x80080000}};
    s21_decimal decimal_res = {0};
    //Decimal value:   -2277250555900088
    s21_decimal decimal_check = {{3060986041, 530213, 0, 0x80000000}};
   
    int res = s21_floor(decimal, &decimal_res);
    ck_assert_int_eq(0, res);
    
    ck_assert_uint_eq(decimal_res.bits[3]>>31 & 1u, decimal_check.bits[3]>>31 & 1u);
    ck_assert_uint_eq(decimal_res.bits[3]>>16 & 0xFF, decimal_check.bits[3]>>16 & 0xFF);
    ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
    ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
    ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_floor_5) {
    //Decimal value:   -1230.0
    s21_decimal decimal = {{12300, 0, 0, 0x80010000}};
    s21_decimal decimal_res = {0};
    //Decimal value:   -1230
    s21_decimal decimal_check = {{1230, 0, 0, 0x80000000}};
   
    int res = s21_floor(decimal, &decimal_res);
    ck_assert_int_eq(0, res);
    
    ck_assert_uint_eq(decimal_res.bits[3]>>31 & 1u, decimal_check.bits[3]>>31 & 1u);
    ck_assert_uint_eq(decimal_res.bits[3]>>16 & 0xFF, decimal_check.bits[3]>>16 & 0xFF);
    ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
    ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
    ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_floor_6) {
    //Decimal value:   1230.0
    s21_decimal decimal = {{12300, 0, 0, 0x00010000}};
    s21_decimal decimal_res = {0};
    //Decimal value:   1230
    s21_decimal decimal_check = {{1230, 0, 0, 0x00000000}};
   
    int res = s21_floor(decimal, &decimal_res);
    ck_assert_int_eq(0, res);
    
    ck_assert_uint_eq(decimal_res.bits[3]>>31 & 1u, decimal_check.bits[3]>>31 & 1u);
    ck_assert_uint_eq(decimal_res.bits[3]>>16 & 0xFF, decimal_check.bits[3]>>16 & 0xFF);
    ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
    ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
    ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_floor_7) {
    //Decimal value:   -1844674407370955161.5
    s21_decimal decimal = {{4294967295, 4294967295, 0, 0x80010000}};
    s21_decimal decimal_res = {0};
    //Decimal value:   -1844674407370955162
    s21_decimal decimal_check = {{2576980378, 429496729, 0, 0x80000000}};
   
    int res = s21_floor(decimal, &decimal_res);
    ck_assert_int_eq(0, res);
    
    ck_assert_uint_eq(decimal_res.bits[3]>>31 & 1u, decimal_check.bits[3]>>31 & 1u);
    ck_assert_uint_eq(decimal_res.bits[3]>>16 & 0xFF, decimal_check.bits[3]>>16 & 0xFF);
    ck_assert_uint_eq(decimal_res.bits[0], decimal_check.bits[0]);
    ck_assert_uint_eq(decimal_res.bits[1], decimal_check.bits[1]);
    ck_assert_uint_eq(decimal_res.bits[2], decimal_check.bits[2]);
}
END_TEST

START_TEST(test_floor_null) {
    s21_decimal decimal = {{0, 0, 0, 0}};
    s21_decimal * decimal_res = NULL;
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
    tcase_add_test(tc, test_floor_null);
    tcase_add_test(tc, test_floor_uncorrect_free_bits1);
    tcase_add_test(tc, test_floor_uncorrect_free_bits2);
    tcase_add_test(tc, test_floor_uncorrect_scale1);
    tcase_add_test(tc, test_floor_uncorrect_scale2);
  

    suite_add_tcase(s, tc);
    return s;
}
