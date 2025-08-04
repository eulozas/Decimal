#include "s21_helpers.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;

  int exit_code = s21_is_not_valid_decimal(&value);

  if (!exit_code) {
    int sign = s21_get_sign(&value);
    int scale = s21_get_scale(&value);
    *result = value;
    result->bits[3] = 0u;
    if (scale > 0) {
      int has_fraction = 0;
      while (scale > 0) {
        if (s21_div_10_decimal(result->bits, 2) > 0) {
          has_fraction = 1;
        }
        scale--;
      }
      if (sign && has_fraction) {
        s21_decimal number_1 = {{0x1, 0x0, 0x0, 0x0}};
        s21_add(*result, number_1, result);
      }
    }
    s21_set_sign(result, sign);
    s21_set_scale(result, scale);
  }
  return exit_code;
}