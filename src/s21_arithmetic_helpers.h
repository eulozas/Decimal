#ifndef S21_ARITHMETICS_HELPERS_H
#define S21_ARITHMETICS_HELPERS_H

#include "s21_decimal.h"
#include "s21_helpers.h"

#include <stdio.h>

int base_add(const big_decimal *value_1, const big_decimal *value_2, big_decimal *result);
int base_sub(const big_decimal *value_1, const big_decimal *value_2, big_decimal *result);
int base_mull(big_decimal *value_1, big_decimal *value_2, big_decimal *result);

void shift_right(big_decimal* decimal, int index);
int shift_left(big_decimal* decimal, int index);

void init_big_decimal(big_decimal *decimal);
void to_big_decimal(const s21_decimal* decimal, big_decimal* b_decimal);
int big_to_decimal(big_decimal* b_decimal, s21_decimal* decimal);

void s21_normalization_big_scale(big_decimal* value_1, big_decimal* value_2);
int mantissa_96_bit(const big_decimal* b_decimal);

int is_zero_big_decimal(big_decimal* b_decimal);
void div_10_big_decimal(big_decimal* b_decimal);
void printf_big_decimal(big_decimal *b_decimal);

#endif