// #include "s21_decimal.h"
// #include "s21_helpers.h"

// int s21_floor(s21_decimal value, s21_decimal *result) {
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

//       int has_fraction = 0;
//       while (scale > 0) {
//         if (divide_by_10(&high, &mid, &low)) {
//           has_fraction = 1;
//         }
//         scale--;
//       }
//       if (sign) {
//         if (has_fraction) {
//           increment_decimal_bits(&low, &mid, &high);
//         }
//         set_sign(result, sign);
//       }

//       result->bits[0] = low;
//       result->bits[1] = mid;
//       result->bits[2] = high;
//     }
//   }

//   return exit_code;
// }

#include "s21_arithmetic_helpers.h"
#include "s21_decimal.h"
#include "s21_helpers.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;

  int exit_code = is_valid_decimal(&value);

  if (!exit_code) {
    int sign = get_sign(&value);
    int scale = get_scale(&value);
    *result = value;
    result->bits[3] = 0u;
    if (scale > 0) {
      int has_fraction = 0;
      while (scale > 0) {
        if (div_10_decimal(result->bits, 2) > 0) {
          has_fraction = 1;
        }
        scale--;
      }
      if (sign && has_fraction) {
        s21_decimal number_1 = {{0x1, 0x0, 0x0, 0x0}};
        s21_add(*result, number_1, result);
      }
    }
    set_sign(result, sign);
    set_scale(result, scale);
  }
  return exit_code;
}