#include "s21_arithmetic_helpers.h"

int s21_base_add(const s21_big_decimal *value_1, const s21_big_decimal *value_2,
                 s21_big_decimal *result) {
  result->scale = value_1->scale;
  int carry = 0;
  for (int i = 0; i < MAX_BITS_BIG_DECIMAL; i++) {
    int num1 = s21_get_bit(value_1->bits, i);
    int num2 = s21_get_bit(value_2->bits, i);
    s21_set_bit(result->bits, i, num1 ^ num2 ^ carry);
    carry = (num1 & num2) | (num1 & carry) | (num2 & carry);
  }
  return carry;
}

int s21_base_sub(const s21_big_decimal *value_1, const s21_big_decimal *value_2,
                 s21_big_decimal *result) {
  result->scale = value_1->scale;
  int borrow = 0;
  for (int i = 0; i < MAX_BITS_BIG_DECIMAL; i++) {
    int num1 = s21_get_bit(value_1->bits, i);
    int num2 = s21_get_bit(value_2->bits, i);
    s21_set_bit(result->bits, i, borrow ^ num1 ^ num2);
    borrow = ((~num1 & 1u) & num2) | (borrow & (~num1 & 1u)) |
             (borrow & num1 & num2);
  }
  return borrow;
}

int s21_base_mull(const s21_big_decimal *value_1,
                  const s21_big_decimal *value_2, s21_big_decimal *result) {
  for (int i = 0; i < MAX_BITS_BIG_DECIMAL; i++) {
    int num = s21_get_bit(value_1->bits, i);
    if (num == 1) {
      s21_big_decimal tmp = *value_2;
      s21_shift_left(&tmp, i);
      s21_base_add(result, &tmp, result);
    }
  }
  result->scale = value_1->scale + value_2->scale;
  return 0;
}

int s21_base_int_div(const s21_big_decimal *value_1,
                     const s21_big_decimal *value_2, s21_big_decimal *remainder,
                     s21_big_decimal *quotient) {
  int step = 1;
  for (int i = MAX_BITS_BIG_DECIMAL - 1; i >= 0; i--) {
    s21_shift_left(remainder, step);
    int temp = s21_get_bit(value_1->bits, i);
    s21_set_bit(remainder->bits, 0, temp);
    if (s21_is_greater_or_equal_big_decimal(*remainder, *value_2)) {
      s21_base_sub(remainder, value_2, remainder);
      s21_shift_left(quotient, step);
      s21_set_bit(quotient->bits, 0, BIT_ON);
    } else {
      s21_shift_left(quotient, step);
      s21_set_bit(quotient->bits, 0, BIT_OFF);
    }
  }
  return 0;
}

int s21_base_fract_div(const s21_big_decimal *value_2,
                       s21_big_decimal *remainder, s21_big_decimal *quotient) {
  while (s21_is_zero(remainder->bits, UINT_COUNT_BIG_DECIMAL) == 0 &&
         quotient->bits[UINT_COUNT_BIG_DECIMAL - 1] == 0) {
    s21_mul_10_decimal(remainder->bits, UINT_COUNT_BIG_DECIMAL);
    remainder->scale++;
    s21_big_decimal digit = {{0}, 0};
    unsigned bit = 0;
    while (s21_is_greater_or_equal_big_decimal(*remainder, *value_2)) {
      s21_base_sub(remainder, value_2, remainder);
      bit++;
    }
    digit.bits[0] = bit;
    s21_mul_10_decimal(quotient->bits, UINT_COUNT_BIG_DECIMAL);
    quotient->scale++;
    s21_base_add(quotient, &digit, quotient);
  }
  return 0;
}

int s21_shift_left(s21_big_decimal *decimal, int index) {
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
    if (s21_get_bit(decimal->bits, MAX_BITS_BIG_DECIMAL - i - 1)) overflow = 1;
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

int s21_big_to_decimal(s21_big_decimal *b_decimal, s21_decimal *decimal) {
  int code_error = S21_OK;
  unsigned remainder = 0;
  int tail = 0;
  while (s21_mantissa_96_bit(b_decimal, remainder, tail) &&
         code_error == S21_OK) {
    if (b_decimal->scale > 0) {
      if (remainder) tail = 1;
      remainder =
          s21_div_10_decimal(b_decimal->bits, UINT_COUNT_BIG_DECIMAL - 1);
      b_decimal->scale--;
    } else if (s21_get_sign(decimal)) {
      code_error = S21_NEG_OVERFLOW;
    } else
      code_error = S21_OVERFLOW;
  }
  while (b_decimal->scale > MAX_SCALE && code_error == S21_OK) {
    if (remainder) tail = 1;
    remainder = s21_div_10_decimal(b_decimal->bits, UINT_COUNT_BIG_DECIMAL - 1);
    b_decimal->scale--;
    if (s21_is_zero(b_decimal->bits, UINT_COUNT_BIG_DECIMAL) &&
        s21_is_bankers_round_big_decimal_up(b_decimal, remainder, tail) == 0)
      code_error = S21_UNDERFLOW;
  }
  if (code_error == S21_OK) {
    s21_bankers_round_big_decimal(b_decimal, remainder, tail);
    for (int i = 0; i < UINT_COUNT_DECIMAL; i++) {
      decimal->bits[i] = b_decimal->bits[i];
    }
    decimal->bits[UINT_COUNT_DECIMAL] |= b_decimal->scale << 16;
  }
  return code_error;
}

void s21_init_big_decimal(s21_big_decimal *decimal) {
  for (int i = 0; i < UINT_COUNT_BIG_DECIMAL; i++) {
    decimal->bits[i] = 0u;
  }
  decimal->scale = 0u;
}

int s21_mantissa_96_bit(const s21_big_decimal *b_decimal, unsigned remainder,
                        int tail) {
  s21_big_decimal tmp = *b_decimal;
  s21_bankers_round_big_decimal(&tmp, remainder, tail);
  int ret = 0;
  for (int i = UINT_COUNT_DECIMAL; i < UINT_COUNT_BIG_DECIMAL && ret == 0;
       i++) {
    if (tmp.bits[i] != 0u) ret = 1;
  }
  return ret;
}

int s21_is_bankers_round_big_decimal_up(s21_big_decimal *b_decimal,
                                        unsigned remainder, int tail) {
  return (remainder > 5 ||
          (remainder == 5 && ((b_decimal->bits[0] & 1u) || tail)));
}

void s21_bankers_round_big_decimal(s21_big_decimal *b_decimal,
                                   unsigned remainder, int tail) {
  if (s21_is_bankers_round_big_decimal_up(b_decimal, remainder, tail)) {
    s21_big_decimal tmp;
    s21_init_big_decimal(&tmp);
    tmp.bits[0] |= 1u;
    s21_base_add(b_decimal, &tmp, b_decimal);
  }
}
