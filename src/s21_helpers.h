#ifndef S21_HELPERS_H
#define S21_HELPERS_H

#include <math.h>

#include "s21_decimal.h"
#include "s21_types_decimal.h"

void s21_clear_decimal(s21_decimal *decimal);
int s21_get_bit(const unsigned *decimal, int index);
void s21_set_bit(unsigned *bits, int index, int val);
void s21_set_sign(s21_decimal *decimal, int val);
int s21_get_sign(const s21_decimal *decimal);

void s21_set_scale(s21_decimal *decimal, int scale);
int s21_get_scale(const s21_decimal *decimal);
double s21_bank_round(double x);
int s21_count_digits_before_point(unsigned long long n);
int s21_find_point_index(double x);
void s21_normalize_mantissa(unsigned long long *mantissa, int *scale);
void s21_write_mantissa_to_decimal(unsigned long long mantissa,
                                   s21_decimal *decimal);
int s21_is_zero(const unsigned *bits, int index_high_bits);

int s21_check_free_decimal_bit(const s21_decimal *decimal);
void s21_mul_10_decimal(unsigned *bits, int index_high_bits);
void s21_normalization_big_scale(s21_big_decimal *value_1,
                                 s21_big_decimal *value_2);
int s21_is_not_valid_decimal(const s21_decimal *value);

void s21_to_big_decimal(const s21_decimal *decimal, s21_big_decimal *b_decimal);

unsigned s21_div_10_decimal(unsigned *bits, int index_high_bits);

int s21_is_greater_or_equal_big_decimal(s21_big_decimal value_1,
                                        s21_big_decimal value_2);
void s21_is_equal_mantissa(s21_big_decimal value_1, s21_big_decimal value_2,
                           int *result, int *equal);
#endif