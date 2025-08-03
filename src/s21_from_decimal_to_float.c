#include "s21_helpers.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (!dst) return 1;
  int exit_code = s21_is_not_valid_decimal(&src);
  int sign = s21_get_sign(&src);
  int scale = s21_get_scale(&src);
  if (!exit_code) {
    unsigned int low = src.bits[0];
    unsigned int mid = src.bits[1];
    unsigned int high = src.bits[2];
    double res = (double)low + (double)mid * POW_2_32 + (double)high * POW_2_64;
    if (sign) {
      res = -res;
    }
    res /= pow(10, scale);
    *dst = (float)res;
  }

  return exit_code;
}