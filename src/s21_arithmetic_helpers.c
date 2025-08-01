#include "s21_arithmetic_helpers.h"

int base_add(const big_decimal *value_1, const big_decimal *value_2,
             big_decimal *result) {
  result->scale = value_1->scale;
  int carry = 0;
  for (int i = 0; i < MAX_BIG_DECIMAL_MANTISSA; i++) {
    int num1 = get_bit(value_1->bits, i);
    int num2 = get_bit(value_2->bits, i);
    set_bit_big(result, i, num1 ^ num2 ^ carry);
    carry = (num1 & num2) | (num1 & carry) | (num2 & carry);
  }
  return carry;
}

int base_sub(const big_decimal *value_1, const big_decimal *value_2,
             big_decimal *result) {
  result->scale = value_1->scale;
  int borrow = 0;
  for (int i = 0; i < MAX_BIG_DECIMAL_MANTISSA; i++) {
    int num1 = get_bit(value_1->bits, i);
    int num2 = get_bit(value_2->bits, i);
    set_bit_big(result, i, borrow ^ num1 ^ num2);
    borrow = ((~num1 & 1u) & num2) | (borrow & (~num1 & 1u)) |
             (borrow & num1 & num2);
  }
  return borrow;
}

int base_mull(const big_decimal *value_1, const big_decimal *value_2,
              big_decimal *result) {
  for (int i = 0; i < MAX_DECIMAL_MANTISSA; i++) {
    int num = get_bit(value_1->bits, i);
    if (num == 1) {
      big_decimal tmp = *value_2;
      shift_left(&tmp, i);
      base_add(result, &tmp, result);
    }
  }
  result->scale = value_1->scale + value_2->scale;
  return 0;
}

int base_int_div(const big_decimal *value_1, const big_decimal *value_2,
                 big_decimal *remainder, big_decimal *quotient) {
  for (int i = 223; i >= 0; i--) {
    shift_left(remainder, 1);
    int temp = get_bit(value_1->bits, i);
    set_bit_big(remainder, 0, temp);
    if (s21_is_greater_or_equal_big_decimal(*remainder, *value_2)) {
      base_sub(remainder, value_2, remainder);
      shift_left(quotient, 1);
      set_bit_big(quotient, 0, 1);
    } else {
      shift_left(quotient, 1);
      set_bit_big(quotient, 0, 0);
    }
  }
  return 0;
}

int base_fract_div(const big_decimal *value_2, big_decimal *remainder,
                   big_decimal *quotient) {
  while (is_zero_big_decimal(remainder) == 0 && quotient->bits[6] < 0xfffffff) {
    mull_10_big_decimal(remainder);
    big_decimal digit = {{0}, 0};
    unsigned bit = 0;
    while (s21_is_greater_or_equal_big_decimal(*remainder, *value_2)) {
      base_sub(remainder, value_2, remainder);
      bit++;
    }
    digit.bits[0] = bit;
    mull_10_big_decimal(quotient);
    base_add(quotient, &digit, quotient);
  }
  return 0;
}

int shift_left(big_decimal *decimal, int index) {
  unsigned overflow = 0;

  int word_shift = index / 32;
  int index_shift = index % 32;
  for (int i = 6; i >= 0 && !overflow && word_shift; i--) {
    if (i - word_shift >= 0) {
      if (decimal->bits[i])
        overflow = 1;
      else {
        decimal->bits[i] |= decimal->bits[i - word_shift];
        decimal->bits[i - word_shift] &= 0u;
      }
    }
  }
  for (int i = 0; i < index_shift && !overflow; i++) {
    if (get_bit(decimal->bits, MAX_IND_BIG_DECIMAL - i)) overflow = 1;
  }
  for (int i = 6; i >= 0 && !overflow && index_shift != 0; i--) {
    decimal->bits[i] <<= index_shift;
    if (i - 1 >= 0) {
      decimal->bits[i] |= (decimal->bits[i - 1] >> (32 - index_shift));
    }
  }
  return overflow;
}

void to_big_decimal(const s21_decimal *decimal, big_decimal *b_decimal) {
  for (int i = 0; i < 3; i++) {
    b_decimal->bits[i] = decimal->bits[i];
  }
  b_decimal->scale = get_scale(decimal);
}

int big_to_decimal(big_decimal *b_decimal, s21_decimal *decimal) {
  int code_error = S21_OK;
  unsigned remainder = 0;
  int tail = 0;
  int round_done = 0;
  while (mantissa_96_bit(b_decimal, remainder, tail) && code_error == 0) {
    if (b_decimal->scale > 0) {
      if (remainder) tail = 1;
      remainder = div_10_big_decimal(b_decimal);
      if (b_decimal->scale == 0) {
        round_done = 1;
        bankers_round_big_decimal(b_decimal, remainder, tail);
        remainder = 0;
        tail = 0;
      }
    } else if (get_sign(decimal)) {
      code_error = S21_NEG_OVERFLOW;
    } else
      code_error = S21_OVERFLOW;
  }
  while (b_decimal->scale > 28 && code_error == S21_OK) {
    if (remainder) tail = 1;
    remainder = div_10_big_decimal(b_decimal);
    if (is_zero_big_decimal(b_decimal) &&
        is_bankers_round_big_decimal_up(b_decimal, remainder, tail) == 0)
      code_error = S21_UNDERFLOW;
    if (b_decimal->scale == 28) {
      round_done = 1;
      bankers_round_big_decimal(b_decimal, remainder, tail);
    }
  }
  if (code_error == S21_OK && round_done == 0) {
    bankers_round_big_decimal(b_decimal, remainder, tail);
  }
  if (code_error == S21_OK) {
    for (int i = 0; i < 3; i++) {
      decimal->bits[i] = b_decimal->bits[i];
    }
    decimal->bits[3] |= b_decimal->scale << 16;
  }
  return code_error;
}

void init_big_decimal(big_decimal *decimal) {
  for (int i = 0; i < 7; i++) {
    decimal->bits[i] = 0u;
  }
  decimal->scale = 0u;
}

int mantissa_96_bit(const big_decimal *b_decimal, unsigned remainder,
                    int tail) {
  big_decimal tmp = *b_decimal;
  bankers_round_big_decimal(&tmp, remainder, tail);
  int ret = 0;
  for (int i = 3; i < 7 && ret == 0; i++) {
    if (tmp.bits[i] != 0u) ret = 1;
  }
  return ret;
}

unsigned div_10_big_decimal(big_decimal *b_decimal) {
  unsigned long long remainder = 0;
  for (int i = 6; i >= 0; i--) {
    unsigned long long current =
        (unsigned long long)b_decimal->bits[i] + (remainder << 32);
    b_decimal->bits[i] = (unsigned)(current / 10);
    remainder = current % 10;
  }
  b_decimal->scale--;
  return (unsigned)remainder;
}

int is_zero_big_decimal(const big_decimal *b_decimal) {
  int ret = 1;
  for (int i = 0; i < 7 && ret; i++) {
    if (b_decimal->bits[i] != 0u) ret = 0;
  }
  return ret;
}

int is_bankers_round_big_decimal_up(big_decimal *b_decimal, unsigned remainder,
                                    int tail) {
  return (remainder > 5 ||
          (remainder == 5 && ((b_decimal->bits[0] & 1u) || tail)));
}

void bankers_round_big_decimal(big_decimal *b_decimal, unsigned remainder,
                               int tail) {
  if (is_bankers_round_big_decimal_up(b_decimal, remainder, tail)) {
    big_decimal tmp;
    init_big_decimal(&tmp);
    tmp.bits[0] |= 1u;
    base_add(b_decimal, &tmp, b_decimal);
  }
}

int s21_is_greater_or_equal_big_decimal(big_decimal value_1,
                                        big_decimal value_2) {
  int result = 1;
  int equal = 0;
  s21_is_equal_mantissa(value_1, value_2, &result, &equal);
  if (equal == 7) {
    result = 1;
  }
  return result;
}

void s21_is_equal_mantissa(big_decimal value_1, big_decimal value_2,
                           int *result, int *equal) {
  int flag_end = 1;
  for (int i = 6; i >= 0 && flag_end; i--) {
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