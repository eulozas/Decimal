#include "s21_arithmetic_helpers.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result || s21_is_not_valid_decimal(&value_1) ||
      s21_is_not_valid_decimal(&value_2)) {
    return VALID_ERROR;
  } else
    s21_clear_decimal(result);
  int res_add = S21_OK;
  if (s21_is_zero(value_1.bits, UINT_COUNT_DECIMAL) &&
      s21_is_zero(value_2.bits, UINT_COUNT_DECIMAL))
    s21_clear_decimal(result);
  else {
    int sign1 = s21_get_sign(&value_1);
    int sign2 = s21_get_sign(&value_2);
    s21_big_decimal big_value_1 = {{0}, 0}, big_value_2 = {{0}, 0},
                    big_result = {{0}, 0};
    s21_to_big_decimal(&value_1, &big_value_1);
    s21_to_big_decimal(&value_2, &big_value_2);
    s21_set_sign(&value_1, SIGN_OFF);
    s21_set_sign(&value_2, SIGN_OFF);
    s21_normalization_big_scale(&big_value_1, &big_value_2);
    if (sign1 == sign2) {
      s21_set_sign(result, sign1);
      s21_base_add(&big_value_1, &big_value_2, &big_result);
      res_add = s21_big_to_decimal(&big_result, result);
    } else {
      if (s21_is_greater(value_1, value_2)) {
        s21_set_sign(result, sign1);
        s21_base_sub(&big_value_1, &big_value_2, &big_result);
        res_add = s21_big_to_decimal(&big_result, result);
      } else if (s21_is_equal(value_1, value_2)) {
        s21_clear_decimal(result);
      } else {
        s21_set_sign(result, sign2);
        s21_base_sub(&big_value_2, &big_value_1, &big_result);
        res_add = s21_big_to_decimal(&big_result, result);
      }
    }
  }
  return res_add;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result || s21_is_not_valid_decimal(&value_1) ||
      s21_is_not_valid_decimal(&value_2)) {
    return VALID_ERROR;
  } else
    s21_clear_decimal(result);
  int res_sub = S21_OK;
  value_2.bits[UINT_COUNT_DECIMAL] ^= MINUS;
  res_sub = s21_add(value_1, value_2, result);
  return res_sub;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result || s21_is_not_valid_decimal(&value_1) ||
      s21_is_not_valid_decimal(&value_2)) {
    return VALID_ERROR;
  } else
    s21_clear_decimal(result);
  int res_mull = S21_OK;
  if (s21_is_zero(value_1.bits, UINT_COUNT_DECIMAL) ||
      s21_is_zero(value_2.bits, UINT_COUNT_DECIMAL))
    s21_clear_decimal(result);
  else {
    int sign1 = s21_get_sign(&value_1);
    int sign2 = s21_get_sign(&value_2);
    s21_set_sign(result, sign1 ^ sign2);
    s21_big_decimal temp_value_1 = {{0}, 0}, temp_value_2 = {{0}, 0},
                    temp_result = {{0}, 0};
    s21_to_big_decimal(&value_1, &temp_value_1);
    s21_to_big_decimal(&value_2, &temp_value_2);
    s21_to_big_decimal(result, &temp_result);
    s21_base_mull(&temp_value_1, &temp_value_2, &temp_result);
    res_mull = s21_big_to_decimal(&temp_result, result);
  }
  return res_mull;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result || s21_is_not_valid_decimal(&value_1) ||
      s21_is_not_valid_decimal(&value_2)) {
    return VALID_ERROR;
  } else
    s21_clear_decimal(result);
  int res_div = S21_OK;
  if (s21_is_zero(value_2.bits, UINT_COUNT_DECIMAL))
    res_div = S21_DIV_BY_ZERO;
  else if (s21_is_zero(value_1.bits, UINT_COUNT_DECIMAL))
    s21_clear_decimal(result);
  else {
    int sign1 = s21_get_sign(&value_1);
    int sign2 = s21_get_sign(&value_2);
    s21_set_sign(result, sign1 ^ sign2);
    s21_big_decimal remainder = {{0}, 0};
    s21_big_decimal quotient = {{0}, 0};
    s21_big_decimal big_value_1 = {{0}, 0}, big_value_2 = {{0}, 0};
    s21_to_big_decimal(&value_1, &big_value_1);
    s21_to_big_decimal(&value_2, &big_value_2);
    if (big_value_1.scale < big_value_2.scale)
      s21_normalization_big_scale(&big_value_1, &big_value_2);
    quotient.scale = big_value_1.scale - big_value_2.scale;
    s21_base_int_div(&big_value_1, &big_value_2, &remainder, &quotient);
    s21_base_fract_div(&big_value_2, &remainder, &quotient);
    res_div = s21_big_to_decimal(&quotient, result);
  }
  return res_div;
}
