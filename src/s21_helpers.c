#include "s21_helpers.h"

#include <stdint.h>
#include <stdio.h>

void clear_decimal(s21_decimal *decimal) {
  if (!decimal) return;
  for (int i = 0; i < 4; ++i) {
    decimal->bits[i] = 0;
  }
}

int get_bit(const unsigned *decimal, int index) {
  int bit_index = index % BITS_IN_UINT;
  int bit_number = index / BITS_IN_UINT;

  return (decimal[bit_number] >> bit_index) & 1u;
}

void set_bit(unsigned *bits, int index, int val) {
  int bit_index = index % BITS_IN_UINT;
  int bit_number = index / BITS_IN_UINT;
  unsigned mask = 1u << bit_index;

  if (val) {
    bits[bit_number] |= mask;
  } else {
    bits[bit_number] &= ~mask;
  }
}

void set_sign(s21_decimal *decimal, int val) {
  int ind_sign = 127;
  set_bit(decimal->bits, ind_sign, val);
}

int get_sign(const s21_decimal *decimal) {
  return (decimal->bits[UINT_COUNT_DECIMAL] >> (BITS_IN_UINT - 1)) & 1u;
}

int get_scale(const s21_decimal *decimal) {
  return (decimal->bits[UINT_COUNT_DECIMAL] >> 16) & 0xFF;
}

void set_scale(s21_decimal *decimal, int scale) {
  decimal->bits[UINT_COUNT_DECIMAL] |= (scale << 16);
}

void s21_normalization_big_scale(big_decimal *value_1, big_decimal *value_2) {
  while (value_1->scale > value_2->scale) {
    mul_10_decimal(value_2->bits, UINT_COUNT_BIG_DECIMAL);
    value_2->scale++;
    // mull_10_big_decimal(value_2);
  }
  while (value_2->scale > value_1->scale) {
    mul_10_decimal(value_1->bits, UINT_COUNT_BIG_DECIMAL);
    value_1->scale++;
    // mull_10_big_decimal(value_1);
  }
}

// void mull_10_big_decimal(big_decimal *b_decimal) {
//   big_decimal tmp1 = *b_decimal;
//   big_decimal tmp2 = *b_decimal;
//   shift_left(&tmp1, 3);
//   shift_left(&tmp2, 1);
//   base_add(&tmp1, &tmp2, b_decimal);
//   b_decimal->scale++;
// }

// int is_zero(const s21_decimal *decimal) {
//   return decimal->bits[0] == 0 && decimal->bits[1] == 0 &&
//          decimal->bits[2] == 0;
// }

int is_zero(const unsigned *bits, int index_high_bits) {
  int ret = 1;
  for (int i = 0; i < index_high_bits && ret; i++) {
    if (bits[i] != 0u) ret = 0;
  }
  return ret;
}

void to_zero(s21_decimal *decimal) {
  for (int i = 0; i <= UINT_COUNT_DECIMAL; i++) {
    decimal->bits[i] = 0;
  }
}

int count_digits_before_point(unsigned long long n) {
  int count = 0;
  do {
    count++;
    n /= 10;
  } while (n > 0);
  return count;
}

double bank_round(double x) {
  // до нижнего
  double floor_x = floor(x);
  double diff = x - floor_x;

  if (diff > 0.5) {
    // до верхнего
    return ceil(x);
  } else if (diff < 0.5) {
    return floor_x;
  } else {
    if (fmod(floor_x, 2.0) == 0.0) {
      // чётное — вниз
      return floor_x;
    } else {
      // нечётное — вверх
      return ceil(x);
    }
  }
}

int find_point_index(double x) {
  x = fabs(x);
  int index = 0;

  while (x >= 10.0) {
    x /= 10.0;
    index++;
  }
  return index;
}

void normalize_mantissa(unsigned long long *mantissa, int *scale) {
  while (*scale > 0 && (*mantissa % 10 == 0)) {
    *mantissa /= 10;
    (*scale)--;
  }
}

void mul_10_decimal(unsigned *bits, int index_high_bits) {
  int overflow = 0;
  for (int i = 0; i < index_high_bits; i++) {
    unsigned long long buffer = (unsigned long long)bits[i] * 10 + overflow;
    bits[i] = (unsigned long long)buffer & 0xFFFFFFFF;
    overflow = buffer >> 32;
  }
}

// void mul_decimal_by_10_and_carry_bits(s21_decimal *decimal) {
//   unsigned long long a = (unsigned long long)decimal->bits[0] * 10;
//   unsigned long long b = (unsigned long long)decimal->bits[1] * 10 + (a >>
//   32); unsigned long long c = (unsigned long long)decimal->bits[2] * 10 + (b
//   >> 32);

//   decimal->bits[0] = (unsigned int)(a & 0xFFFFFFFF);
//   decimal->bits[1] = (unsigned int)(b & 0xFFFFFFFF);
//   decimal->bits[2] = (unsigned int)(c & 0xFFFFFFFF);
// }

void write_mantissa_to_decimal(unsigned long long mantissa,
                               s21_decimal *decimal) {
  decimal->bits[0] = (unsigned int)(mantissa & 0xFFFFFFFF);
  decimal->bits[1] = (unsigned int)((mantissa >> BITS_IN_UINT) & 0xFFFFFFFF);
  decimal->bits[2] = 0;
}

// int divide_by_10(unsigned int *high, unsigned int *mid, unsigned int *low) {
//   int has_fraction = 0;
//   unsigned long long rest = 0;

//   unsigned long long value = ((unsigned long long)(*high));
//   *high = (unsigned int)(value / 10);
//   rest = value % 10;

//   value = ((unsigned long long)(*mid)) + (rest << 32);
//   *mid = (unsigned int)(value / 10);
//   rest = value % 10;

//   value = ((unsigned long long)(*low)) + (rest << 32);
//   *low = (unsigned int)(value / 10);
//   if (value % 10 != 0) has_fraction = 1;  // дробное, остаток был

//   return has_fraction;
// }

int check_free_decimal_bit(const s21_decimal *decimal) {
  int res = 0;
  int start_low_zero = 96, end_low_zero = 112;
  int start_high_zero = 120, end_high_zero = 127;
  for (int i = start_low_zero; i < end_low_zero && !res; i++) {
    if (get_bit(decimal->bits, i)) {
      res = 1;
    }
  }
  for (int i = start_high_zero; i < end_high_zero && !res; i++) {
    if (get_bit(decimal->bits, i)) {
      res = 1;
    }
  }

  return res;
}

// void increment_decimal_bits(unsigned int *low, unsigned int *mid,
//                             unsigned int *high) {
//   if (++(*low) == 0) {    // произошло переполнение low
//     if (++(*mid) == 0) {  // переполнение mid
//       ++(*high);          // прибавляем к high
//     }
//   }
// }

int is_not_valid_decimal(const s21_decimal *value) {
  int exit_code = 0;
  int scale = get_scale(value);
  int check_bit = check_free_decimal_bit(value);

  if (scale < 0 || scale > MAX_SCALE || check_bit) {
    exit_code = 1;
  }
  return exit_code;
}
