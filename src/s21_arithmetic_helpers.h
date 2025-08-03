#ifndef S21_ARITHMETICS_HELPERS_H
#define S21_ARITHMETICS_HELPERS_H

#include "s21_decimal.h"
#include "s21_helpers.h"
#include "s21_types_decimal.h"

int s21_base_add(const s21_big_decimal *value_1, const s21_big_decimal *value_2,
                 s21_big_decimal *result);
int s21_base_sub(const s21_big_decimal *value_1, const s21_big_decimal *value_2,
                 s21_big_decimal *result);
int s21_base_mull(const s21_big_decimal *value_1,
                  const s21_big_decimal *value_2, s21_big_decimal *result);

int s21_base_int_div(const s21_big_decimal *value_1,
                     const s21_big_decimal *value_2, s21_big_decimal *remainder,
                     s21_big_decimal *quotient);
int s21_base_fract_div(const s21_big_decimal *value_2,
                       s21_big_decimal *remainder, s21_big_decimal *quotient);

void s21_init_big_decimal(s21_big_decimal *decimal);
int s21_big_to_decimal(s21_big_decimal *b_decimal, s21_decimal *decimal);

int s21_shift_left(s21_big_decimal *decimal, int index);
int s21_mantissa_96_bit(const s21_big_decimal *b_decimal, unsigned remainder,
                        int tail);

int s21_is_bankers_round_big_decimal_up(s21_big_decimal *b_decimal,
                                        unsigned remainder, int tail);
void s21_bankers_round_big_decimal(s21_big_decimal *b_decimal,
                                   unsigned remainder, int tail);

#endif