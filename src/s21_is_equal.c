#include "s21_helpers.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int sign_value_1 = s21_get_sign(&value_1);
  int sign_value_2 = s21_get_sign(&value_2);
  int scale_value_1 = s21_get_scale(&value_1);
  int scale_value_2 = s21_get_scale(&value_2);
  int result = 1;
  if (s21_is_zero(value_1.bits, UINT_COUNT_DECIMAL) &&
      s21_is_zero(value_2.bits, UINT_COUNT_DECIMAL)) {
    result = 1;
  } else if (sign_value_1 == sign_value_2) {
    result = 1;
    s21_big_decimal big_value_1 = {0}, big_value_2 = {0};
    s21_to_big_decimal(&value_1, &big_value_1);
    s21_to_big_decimal(&value_2, &big_value_2);
    if (scale_value_1 != scale_value_2) {
      s21_normalization_big_scale(&big_value_1, &big_value_2);
    }
    for (int i = UINT_COUNT_BIG_DECIMAL - 1; i >= 0 && result; i--) {
      if (big_value_1.bits[i] != big_value_2.bits[i]) {
        result = 0;
      }
    }
  } else {
    result = 0;
  }

  return result;
}