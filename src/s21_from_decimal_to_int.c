#include "s21_helpers.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (!dst) return 1;
  int exit_code = s21_is_not_valid_decimal(&src);
  int sign = s21_get_sign(&src);
  int scale = s21_get_scale(&src);
  if (!exit_code) {
    while (scale > 0) {
      s21_div_10_decimal(src.bits, 2);
      scale--;
    }

    if (src.bits[2] != 0 || src.bits[1] != 0 ||
        src.bits[0] > (unsigned int)MAX_INT + (sign ? 1 : 0)) {
      exit_code = 1;
    }
    if (!exit_code) {
      int result = (int)src.bits[0];
      if (sign) {
        result = -result;
      }
      *dst = result;
    }
  }

  return exit_code;
}