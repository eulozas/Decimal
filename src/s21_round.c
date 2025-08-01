#include "s21_decimal.h"
#include "s21_helpers.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;

  int exit_code = 0;

  int sign = get_sign(&value);
  int scale = get_scale(&value);
  int check_bit = check_free_decimal_bit(value);

  if (scale < 0 || scale > MAX_SCALE || check_bit) {
    exit_code = 1;
  }

  if (!exit_code) {
    if (scale == 0) {
      *result = value;
    } else {
      s21_decimal number_0_5 = {{0x5, 0x0, 0x0, 0x10000}};
      s21_decimal number_1 = {{0x1, 0x0, 0x0, 0x0}};
      s21_decimal integer_part = {0};
      s21_decimal fractional_part = {0};
      if (sign) {
        set_sign(&value, 0);
      }
      s21_truncate(value, &integer_part);
      s21_sub(value, integer_part, &fractional_part);
      if (s21_is_greater_or_equal(fractional_part, number_0_5)) {
        s21_add(integer_part, number_1, result);
      } else {
        *result = integer_part;
      }

      if (sign) {
        set_sign(result, 1);
      }
    }
  }

  return exit_code;
}
