#ifndef S21_ARITHMETICS_HELPERS_H
#define S21_ARITHMETICS_HELPERS_H

#include <stdint.h>

#include "s21_decimal.h"
#include "s21_helpers.h"

typedef enum {
  S21_OK = 0,
  S21_OVERFLOW = 1,
  S21_UNDERFLOW = 2,
  S21_NEG_OVERFLOW = 2,
  S21_DIV_BY_ZERO = 3
} s21_error_code;

typedef enum {
  MAX_BITS_BIG_DECIMAL = 224,
  MAX_BITS_DECIMAL = 96,
  UINT_COUNT_BIG_DECIMAL = 7,
  UINT_COUNT_DECIMAL = 3,
  BITS_IN_UINT = 32
} s21_size_decimal;

typedef enum { BIT_ON = 1, BIT_OFF = 0, SIGN_OFF = 0 } s21_bit;

#define MAX_IND_DECIMAL 127

int base_add(const big_decimal *value_1, const big_decimal *value_2,
             big_decimal *result);
int base_sub(const big_decimal *value_1, const big_decimal *value_2,
             big_decimal *result);
int base_mull(const big_decimal *value_1, const big_decimal *value_2,
              big_decimal *result);

int base_int_div(const big_decimal *value_1, const big_decimal *value_2,
                 big_decimal *remainder, big_decimal *quotient);
int base_fract_div(const big_decimal *value_2, big_decimal *remainder,
                   big_decimal *quotient);

void init_big_decimal(big_decimal *decimal);
void to_big_decimal(const s21_decimal *decimal, big_decimal *b_decimal);
int big_to_decimal(big_decimal *b_decimal, s21_decimal *decimal);

int shift_left(big_decimal *decimal, int index);
int mantissa_96_bit(const big_decimal *b_decimal, unsigned remainder, int tail);
// int is_zero_big_decimal(const big_decimal *b_decimal);
unsigned div_10_decimal(unsigned *bits, int index_high_bits);
int is_bankers_round_big_decimal_up(big_decimal *b_decimal, unsigned remainder,
                                    int tail);
void bankers_round_big_decimal(big_decimal *b_decimal, unsigned remainder,
                               int tail);

int s21_is_greater_or_equal_big_decimal(big_decimal value_1,
                                        big_decimal value_2);
void s21_is_equal_mantissa(big_decimal value_1, big_decimal value_2,
                           int *result, int *equal);

#endif