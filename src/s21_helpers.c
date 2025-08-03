#include "s21_helpers.h"

void s21_clear_decimal(s21_decimal *decimal) {
  for (int i = 0; i <= UINT_COUNT_DECIMAL; ++i) {
    decimal->bits[i] = 0;
  }
}

int s21_get_bit(const unsigned *decimal, int index) {
  int bit_index = index % BITS_IN_UINT;
  int bit_number = index / BITS_IN_UINT;

  return (decimal[bit_number] >> bit_index) & 1u;
}

void s21_set_bit(unsigned *bits, int index, int val) {
  int bit_index = index % BITS_IN_UINT;
  int bit_number = index / BITS_IN_UINT;
  unsigned mask = 1u << bit_index;

  if (val) {
    bits[bit_number] |= mask;
  } else {
    bits[bit_number] &= ~mask;
  }
}

void s21_set_sign(s21_decimal *decimal, int val) {
  int ind_sign = 127;
  s21_set_bit(decimal->bits, ind_sign, val);
}

int s21_get_sign(const s21_decimal *decimal) {
  return (decimal->bits[UINT_COUNT_DECIMAL] >> (BITS_IN_UINT - 1)) & 1u;
}

int s21_get_scale(const s21_decimal *decimal) {
  return (decimal->bits[UINT_COUNT_DECIMAL] >> 16) & 0xFF;
}

void s21_set_scale(s21_decimal *decimal, int scale) {
  decimal->bits[UINT_COUNT_DECIMAL] |= (scale << 16);
}

void s21_normalization_big_scale(s21_big_decimal *value_1,
                                 s21_big_decimal *value_2) {
  while (value_1->scale > value_2->scale) {
    s21_mul_10_decimal(value_2->bits, UINT_COUNT_BIG_DECIMAL);
    value_2->scale++;
    // mull_10_big_decimal(value_2);
  }
  while (value_2->scale > value_1->scale) {
    s21_mul_10_decimal(value_1->bits, UINT_COUNT_BIG_DECIMAL);
    value_1->scale++;
    // mull_10_big_decimal(value_1);
  }
}

int s21_is_zero(const unsigned *bits, int index_high_bits) {
  int ret = 1;
  for (int i = 0; i < index_high_bits && ret; i++) {
    if (bits[i] != 0u) ret = 0;
  }
  return ret;
}

int s21_count_digits_before_point(unsigned long long n) {
  int count = 0;
  do {
    count++;
    n /= 10;
  } while (n > 0);
  return count;
}

double s21_bank_round(double x) {
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

int s21_find_point_index(double x) {
  x = fabs(x);
  int index = 0;

  while (x >= 10.0) {
    x /= 10.0;
    index++;
  }
  return index;
}

void s21_normalize_mantissa(unsigned long long *mantissa, int *scale) {
  while (*scale > 0 && (*mantissa % 10 == 0)) {
    *mantissa /= 10;
    (*scale)--;
  }
}

void s21_mul_10_decimal(unsigned *bits, int index_high_bits) {
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

void s21_write_mantissa_to_decimal(unsigned long long mantissa,
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

int s21_check_free_decimal_bit(const s21_decimal *decimal) {
  int res = 0;
  int start_low_zero = 96, end_low_zero = 112;
  int start_high_zero = 120, end_high_zero = 127;
  for (int i = start_low_zero; i < end_low_zero && !res; i++) {
    if (s21_get_bit(decimal->bits, i)) {
      res = 1;
    }
  }
  for (int i = start_high_zero; i < end_high_zero && !res; i++) {
    if (s21_get_bit(decimal->bits, i)) {
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

int s21_is_not_valid_decimal(const s21_decimal *value) {
  int exit_code = 0;
  int scale = s21_get_scale(value);
  int check_bit = s21_check_free_decimal_bit(value);

  if (scale < 0 || scale > MAX_SCALE || check_bit) {
    exit_code = 1;
  }
  return exit_code;
}

void s21_to_big_decimal(const s21_decimal *decimal,
                        s21_big_decimal *b_decimal) {
  for (int i = 0; i < UINT_COUNT_DECIMAL; i++) {
    b_decimal->bits[i] = decimal->bits[i];
  }
  b_decimal->scale = s21_get_scale(decimal);
}

unsigned s21_div_10_decimal(unsigned *bits, int index_high_bits) {
  unsigned long long remainder = 0;
  for (int i = index_high_bits; i >= 0; i--) {
    unsigned long long current =
        (unsigned long long)bits[i] + (remainder << 32);
    bits[i] = (unsigned)(current / 10);
    remainder = current % 10;
  }
  return (unsigned)remainder;
}

int s21_is_greater_or_equal_big_decimal(s21_big_decimal value_1,
                                        s21_big_decimal value_2) {
  int result = 1;
  int equal = 0;
  s21_is_equal_mantissa(value_1, value_2, &result, &equal);
  if (equal == UINT_COUNT_BIG_DECIMAL) {
    result = 1;
  }
  return result;
}

void s21_is_equal_mantissa(s21_big_decimal value_1, s21_big_decimal value_2,
                           int *result, int *equal) {
  int flag_end = 1;
  for (int i = UINT_COUNT_BIG_DECIMAL - 1; i >= 0 && flag_end; i--) {
    if (value_1.bits[i] > value_2.bits[i]) {
      *result = 1;
      flag_end = 0;
    } else if (value_1.bits[i] < value_2.bits[i]) {
      *result = 0;
      flag_end = 0;
    } else {
      (*equal)++;
    }
  }
}