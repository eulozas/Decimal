#include "s21_arithmetic_helpers.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res_add = S21_OK;
  if (is_zero(&value_1) && is_zero(&value_2))
    to_zero(result);
  else {
    int sign1 = get_sign(&value_1);
    int sign2 = get_sign(&value_2);
    big_decimal big_value_1 = {{0}, 0}, big_value_2 = {{0}, 0},
                big_result = {{0}, 0};
    to_big_decimal(&value_1, &big_value_1);
    to_big_decimal(&value_2, &big_value_2);
    set_bit(&value_1, 127, 0);
    set_bit(&value_2, 127, 0);
    s21_normalization_big_scale(&big_value_1, &big_value_2);
    if (sign1 == sign2) {
      set_bit(result, 127, sign1);
      base_add(&big_value_1, &big_value_2, &big_result);
      res_add = big_to_decimal(&big_result, result);
    } else {
      if (s21_is_greater(value_1, value_2)) {
        set_bit(result, 127, sign1);
        base_sub(&big_value_1, &big_value_2, &big_result);
        res_add = big_to_decimal(&big_result, result);
      } else if (s21_is_equal(value_1, value_2)) {
        to_zero(result);
      } else {
        set_bit(result, 127, sign2);
        base_sub(&big_value_2, &big_value_1, &big_result);
        res_add = big_to_decimal(&big_result, result);
      }
    }
  }
  return res_add;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res_sub = S21_OK;
  value_2.bits[3] ^= MINUS;
  res_sub = s21_add(value_1, value_2, result);
  return res_sub;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res_mull = S21_OK;
  if (is_zero(&value_1) || is_zero(&value_2))
    to_zero(result);
  else {
    int sign1 = get_sign(&value_1);
    int sign2 = get_sign(&value_2);
    set_bit(result, 127, sign1 ^ sign2);
    big_decimal temp_value_1 = {{0}, 0}, temp_value_2 = {{0}, 0},
                temp_result = {{0}, 0};
    to_big_decimal(&value_1, &temp_value_1);
    to_big_decimal(&value_2, &temp_value_2);
    to_big_decimal(result, &temp_result);
    base_mull(&temp_value_1, &temp_value_2, &temp_result);
    res_mull = big_to_decimal(&temp_result, result);
  }
  return res_mull;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res_div = S21_OK;
  if (is_zero(&value_2))
    res_div = S21_DIV_BY_ZERO;
  else if (is_zero(&value_1))
    to_zero(result);
  else {
    int sign1 = get_sign(&value_1);
    int sign2 = get_sign(&value_2);
    set_bit(result, 127, sign1 ^ sign2);
    big_decimal remainder = {{0}, 0};
    big_decimal quotient = {{0}, 0};
    big_decimal big_value_1 = {{0}, 0}, big_value_2 = {{0}, 0};
    to_big_decimal(&value_1, &big_value_1);
    to_big_decimal(&value_2, &big_value_2);
    if (big_value_1.scale < big_value_2.scale)
      s21_normalization_big_scale(&big_value_1, &big_value_2);
    quotient.scale = big_value_1.scale - big_value_2.scale;
    base_int_div(&big_value_1, &big_value_2, &remainder, &quotient);
    base_fract_div(&big_value_2, &remainder, &quotient);
    res_div = big_to_decimal(&quotient, result);
  }
  return res_div;
}
