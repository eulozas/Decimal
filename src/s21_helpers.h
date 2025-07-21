#ifndef S21_HELPERS_H
#define S21_HELPERS_H

#include "s21_decimal.h"
#include <math.h>

void clear_decimal(s21_decimal *decimal);
int get_bit(const s21_decimal *decimal, int index);
void set_bit(s21_decimal *decimal, int index, int val);
void set_sign(s21_decimal* decimal);
void clear_sign(s21_decimal* decimal);
int get_sign(const s21_decimal *decimal);
void set_scale(s21_decimal *decimal, int scale);
int get_scale(const s21_decimal *decimal);
double bank_round(double x);
int count_digits_before_point(unsigned long long n);
int find_point_index(double x);
//void round_to_significant_digits(double *x, int n);
void normalize_mantissa(unsigned long long *mantissa, int *scale);
void mul_decimal_by_10_and_carry_bits(s21_decimal *decimal);
void write_mantissa_to_decimal(unsigned long long mantissa, s21_decimal *decimal);
void divide_by_10(unsigned int *high, unsigned int *mid, unsigned int *low);

#endif