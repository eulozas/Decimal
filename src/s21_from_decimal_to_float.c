#include <stdio.h>

#include "s21_decimal.h"
#include "s21_helpers.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (!dst) return 1;
  int exit_code = 0;
  int sign = get_sign(&src);
  int scale = get_scale(&src);

  int check_bit = check_free_decimal_bit(src);

  if (scale < 0 || scale > MAX_SCALE || check_bit) {
    exit_code = 1;
  }

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