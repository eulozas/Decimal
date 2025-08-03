#include "s21_helpers.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;

  int exit_code = is_not_valid_decimal(&value);

  if (!exit_code) {
    int sign = get_sign(&value);
    *result = value;
    sign ^= 1u;
    set_sign(result, sign);
  }

  return exit_code;
}