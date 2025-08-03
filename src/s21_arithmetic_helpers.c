#include "s21_arithmetic_helpers.h"

int base_add(const big_decimal *value_1, const big_decimal *value_2,
             big_decimal *result) {
  result->scale = value_1->scale;
  int carry = 0;
  for (int i = 0; i < MAX_BITS_BIG_DECIMAL; i++) {
    int num1 = get_bit(value_1->bits, i);
    int num2 = get_bit(value_2->bits, i);
    set_bit(result->bits, i, num1 ^ num2 ^ carry);
    carry = (num1 & num2) | (num1 & carry) | (num2 & carry);
  }
  return carry;
}

int base_sub(const big_decimal *value_1, const big_decimal *value_2,
             big_decimal *result) {
  result->scale = value_1->scale;
  int borrow = 0;
  for (int i = 0; i < MAX_BITS_BIG_DECIMAL; i++) {
    int num1 = get_bit(value_1->bits, i);
    int num2 = get_bit(value_2->bits, i);
    set_bit(result->bits, i, borrow ^ num1 ^ num2);
    borrow = ((~num1 & 1u) & num2) | (borrow & (~num1 & 1u)) |
             (borrow & num1 & num2);
  }
  return borrow;
}

int base_mull(const big_decimal *value_1, const big_decimal *value_2,
              big_decimal *result) {
  for (int i = 0; i < MAX_BITS_BIG_DECIMAL; i++) {
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
  int step = 1;
  for (int i = MAX_BITS_BIG_DECIMAL - 1; i >= 0; i--) {
    shift_left(remainder, step);
    int temp = get_bit(value_1->bits, i);
    set_bit(remainder->bits, 0, temp);
    if (s21_is_greater_or_equal_big_decimal(*remainder, *value_2)) {
      base_sub(remainder, value_2, remainder);
      shift_left(quotient, step);
      set_bit(quotient->bits, 0, BIT_ON);
    } else {
      shift_left(quotient, step);
      set_bit(quotient->bits, 0, BIT_OFF);
    }
  }
  return 0;
}

int base_fract_div(const big_decimal *value_2, big_decimal *remainder,
                   big_decimal *quotient) {
  while (is_zero(remainder->bits, UINT_COUNT_BIG_DECIMAL) == 0 &&
         quotient->bits[6] < 0xfffffff) {
    mul_10_decimal(remainder->bits, UINT_COUNT_BIG_DECIMAL);
    remainder->scale++;
    big_decimal digit = {{0}, 0};
    unsigned bit = 0;
    while (s21_is_greater_or_equal_big_decimal(*remainder, *value_2)) {
      base_sub(remainder, value_2, remainder);
      bit++;
    }
    digit.bits[0] = bit;
    mul_10_decimal(quotient->bits, UINT_COUNT_BIG_DECIMAL);
    quotient->scale++;
    base_add(quotient, &digit, quotient);
  }
  return 0;
}

int shift_left(big_decimal *decimal, int index) {
  unsigned overflow = 0;

  int word_shift = index / BITS_IN_UINT;
  int index_shift = index % BITS_IN_UINT;
  for (int i = UINT_COUNT_BIG_DECIMAL - 1; i >= 0 && !overflow && word_shift;
       i--) {
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
    if (get_bit(decimal->bits, MAX_BITS_BIG_DECIMAL - i - 1)) overflow = 1;
  }
  for (int i = UINT_COUNT_BIG_DECIMAL - 1;
       i >= 0 && !overflow && index_shift != 0; i--) {
    decimal->bits[i] <<= index_shift;
    if (i - 1 >= 0) {
      decimal->bits[i] |=
          (decimal->bits[i - 1] >> (BITS_IN_UINT - index_shift));
    }
  }
  return overflow;
}

int big_to_decimal(big_decimal *b_decimal, s21_decimal *decimal) {
  int code_error = S21_OK;
  unsigned remainder = 0;
  int tail = 0;
  while (mantissa_96_bit(b_decimal, remainder, tail) && code_error == S21_OK) {
    if (b_decimal->scale > 0) {
      if (remainder) tail = 1;
      remainder = div_10_decimal(b_decimal->bits, UINT_COUNT_BIG_DECIMAL - 1);
      b_decimal->scale--;
    } else if (get_sign(decimal)) {
      code_error = S21_NEG_OVERFLOW;
    } else
      code_error = S21_OVERFLOW;
  }
  while (b_decimal->scale > MAX_SCALE && code_error == S21_OK) {
    if (remainder) tail = 1;
    remainder = div_10_decimal(b_decimal->bits, UINT_COUNT_BIG_DECIMAL - 1);
    b_decimal->scale--;
    if (is_zero(b_decimal->bits, UINT_COUNT_BIG_DECIMAL) &&
        is_bankers_round_big_decimal_up(b_decimal, remainder, tail) == 0)
      code_error = S21_UNDERFLOW;
  }
  if (code_error == S21_OK) {
    bankers_round_big_decimal(b_decimal, remainder, tail);
    for (int i = 0; i < UINT_COUNT_DECIMAL; i++) {
      decimal->bits[i] = b_decimal->bits[i];
    }
    decimal->bits[UINT_COUNT_DECIMAL] |= b_decimal->scale << 16;
  }
  return code_error;
}

void init_big_decimal(big_decimal *decimal) {
  for (int i = 0; i < UINT_COUNT_BIG_DECIMAL; i++) {
    decimal->bits[i] = 0u;
  }
  decimal->scale = 0u;
}

int mantissa_96_bit(const big_decimal *b_decimal, unsigned remainder,
                    int tail) {
  big_decimal tmp = *b_decimal;
  bankers_round_big_decimal(&tmp, remainder, tail);
  int ret = 0;
  for (int i = UINT_COUNT_DECIMAL; i < UINT_COUNT_BIG_DECIMAL && ret == 0;
       i++) {
    if (tmp.bits[i] != 0u) ret = 1;
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
