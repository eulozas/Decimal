// #include "s21_decimal.h"
// #include "s21_helpers.h"

// int s21_truncate(s21_decimal value, s21_decimal *result) {
//   if (!result) return 1;

//   int exit_code = 0;

//   int sign = get_sign(&value);
//   int scale = get_scale(&value);
//   int check_bit = check_free_decimal_bit(value);

//   if (scale < 0 || scale > MAX_SCALE || check_bit) {
//     exit_code = 1;
//   }

//   if (!exit_code) {
//     if (scale == 0) {
//       *result = value;
//     } else {
//       unsigned int low = value.bits[0];
//       unsigned int mid = value.bits[1];
//       unsigned int high = value.bits[2];

//       while (scale > 0) {
//         divide_by_10(&high, &mid, &low);
//         scale--;
//       }

//       if (sign) {
//         set_sign(result, sign);
//       }

//       result->bits[0] = low;
//       result->bits[1] = mid;
//       result->bits[2] = high;
//     }
//   }

//   return exit_code;
// }

#include "s21_decimal.h"
#include "s21_helpers.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;

  int exit_code = is_valid_decimal(&value);

  if (!exit_code) {
    int sign = get_sign(&value);
    int scale = get_scale(&value);
    *result = value;
    result->bits[3] = 0u;
    if (scale > 0) {
      while (scale > 0) {
        div_10_decimal(result->bits, 2);
        scale--;
      }
    }
    set_sign(result, sign);
    set_scale(result, scale);
  }
  return exit_code;
}