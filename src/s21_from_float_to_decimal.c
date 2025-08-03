#include "s21_helpers.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (!dst) return 1;
  s21_clear_decimal(dst);
  int exit_code = 0;
  if (isnan(src) || isinf(src) || fabs((double)src) >= MAX_DECIMAL_VALUE_NEXT)
    exit_code = 1;
  if (!exit_code && src != 0.0f && fabsf(src) < 1e-28f) {
    if (signbit(src)) s21_set_sign(dst, 1);
    exit_code = 1;
  }

  if (!exit_code) {
    double value = fabs((double)src);
    int scale = 0;
    unsigned long long mantissa;
    int digits = 0;
    if (src == 0.0f) {
      exit_code = 0;
    } else if (value > 1e6) {
      int point = s21_find_point_index(value);
      scale = point - (SIGNIF_DIGITS - 1);
      double rounded_value = s21_bank_round(value / pow(10.0, scale));
      mantissa = (unsigned long long)(rounded_value);
      s21_write_mantissa_to_decimal(mantissa, dst);
      while (scale) {
        s21_mul_10_decimal(dst->bits, UINT_COUNT_DECIMAL);
        // mul_decimal_by_10_and_carry_bits(dst);
        scale--;
      }
    } else {
      while (scale < MAX_SCALE && digits < SIGNIF_DIGITS - 1) {
        mantissa = (unsigned long long)value;
        digits = s21_count_digits_before_point(mantissa);
        value *= 10.0;
        scale++;
      }
      value = s21_bank_round(value);
      mantissa = (unsigned long long)value;
      s21_normalize_mantissa(&mantissa, &scale);
      s21_write_mantissa_to_decimal(mantissa, dst);
    }
    if (scale > 0) s21_set_scale(dst, scale);
    if (signbit(src)) s21_set_sign(dst, 1);
  }
  return exit_code;
}
