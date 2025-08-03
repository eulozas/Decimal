#ifndef S21_ARITHMETICS_HELPERS_H
#define S21_ARITHMETICS_HELPERS_H

#include "s21_decimal.h"
#include "s21_helpers.h"
#include "s21_types_decimal.h"

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
int big_to_decimal(big_decimal *b_decimal, s21_decimal *decimal);

int shift_left(big_decimal *decimal, int index);
int mantissa_96_bit(const big_decimal *b_decimal, unsigned remainder, int tail);

int is_bankers_round_big_decimal_up(big_decimal *b_decimal, unsigned remainder,
                                    int tail);
void bankers_round_big_decimal(big_decimal *b_decimal, unsigned remainder,
                               int tail);

#endif