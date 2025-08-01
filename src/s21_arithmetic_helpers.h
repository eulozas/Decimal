#ifndef S21_ARITHMETICS_HELPERS_H
#define S21_ARITHMETICS_HELPERS_H

#include <stdint.h>

#include "s21_decimal.h"
#include "s21_helpers.h"

#define S21_OK 0
#define S21_OVERFLOW 1
#define S21_UNDERFLOW 2
#define S21_NEG_OVERFLOW 2
#define S21_DIV_BY_ZERO 3

#define MAX_IND_DECIMAL 127
#define MAX_IND_BIG_DECIMAL 223
#define MAX_BIG_DECIMAL_MANTISSA 224
#define MAX_DECIMAL_MANTISSA 96

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
int is_zero_big_decimal(const big_decimal *b_decimal);
unsigned div_10_big_decimal(big_decimal *b_decimal);
int is_bankers_round_big_decimal_up(big_decimal *b_decimal, unsigned remainder,
                                    int tail);
void bankers_round_big_decimal(big_decimal *b_decimal, unsigned remainder,
                               int tail);

int s21_is_greater_or_equal_big_decimal(big_decimal value_1,
                                        big_decimal value_2);
void s21_is_equal_mantissa(big_decimal value_1, big_decimal value_2,
                           int *result, int *equal);
#endif