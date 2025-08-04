#include "s21_helpers.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;

  int exit_code = s21_is_not_valid_decimal(&value);

  if (!exit_code) {
    int sign = s21_get_sign(&value);
    int scale = s21_get_scale(&value);
    *result = value;
    result->bits[3] = 0u;
    if (scale > 0) {
      while (scale > 0) {
        s21_div_10_decimal(result->bits, 2);
        scale--;
      }
    }
    s21_set_sign(result, sign);
    s21_set_scale(result, scale);
  }
  return exit_code;
}