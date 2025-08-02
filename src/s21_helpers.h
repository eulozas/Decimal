#ifndef S21_HELPERS_H
#define S21_HELPERS_H

#include <math.h>

#include "s21_arithmetic_helpers.h"
#include "s21_decimal.h"

#define MINUS 0x80000000
#define SCL 0x00ff0000

void clear_decimal(s21_decimal *decimal);
int get_bit(const unsigned *decimal, int index);
void set_bit(unsigned *bits, int index, int val);
void set_sign(s21_decimal *decimal, int val);
int get_sign(const s21_decimal *decimal);

void set_scale(s21_decimal *decimal, int scale);
int get_scale(const s21_decimal *decimal);
double bank_round(double x);
int count_digits_before_point(unsigned long long n);
int find_point_index(double x);
void normalize_mantissa(unsigned long long *mantissa, int *scale);
void mul_decimal_by_10_and_carry_bits(s21_decimal *decimal);
void write_mantissa_to_decimal(unsigned long long mantissa,
                               s21_decimal *decimal);
int divide_by_10(unsigned int *high, unsigned int *mid, unsigned int *low);
int is_zero(const s21_decimal *decimal);
void to_zero(s21_decimal *decimal);
void init_big_decimal(big_decimal *decimal);
int check_free_decimal_bit(s21_decimal decimal);
// void increment_decimal_bits(unsigned int *low, unsigned int *mid,
//                             unsigned int *high);
// void increment_decimal_bits(s21_decimal *decimal);
void mull_10_big_decimal(big_decimal *b_decimal);

void s21_normalization_big_scale(big_decimal *value_1, big_decimal *value_2);
#endif