#ifndef S21_HELPERS_H
#define S21_HELPERS_H

#include "s21_decimal.h"
#include <math.h>


#define MINUS 0x80000000
#define SCL 0x00ff0000

void clear_decimal(s21_decimal *decimal);
void* print_bits_32(const s21_decimal *decimal);
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
int base_add(const big_decimal *value_1, const big_decimal *value_2, big_decimal *result);
int base_sub(const big_decimal *value_1, const big_decimal *value_2, big_decimal *result);
int base_mull(big_decimal *value_1, big_decimal *value_2, big_decimal *result);
void mul_10_value(s21_decimal* value_1);
void make_same_scales(s21_decimal* value_1, int* scale_value_1, int* scale_value_2);
int is_zero(const s21_decimal* decimal);
void to_zero(s21_decimal* decimal);
void to_big_decimal(const s21_decimal* decimal, big_decimal* b_decimal);
int big_to_decimal(big_decimal* b_decimal, s21_decimal* decimal);
void init_big_decimal(big_decimal *decimal);
void shift_right(big_decimal* decimal, int index);
int shift_left(big_decimal* decimal, int index);
int get_bit_big(const big_decimal *decimal, int index);
void set_bit_big(big_decimal *decimal, int index, int val);
void mull_10_big_decimal(big_decimal* b_decimal);
void s21_normalization_big_scale(big_decimal* value_1, big_decimal* value_2);
int mantissa_96_bit(const big_decimal* b_decimal);
int is_zero_big_decimal(big_decimal* b_decimal);
void div_10_big_decimal(big_decimal* b_decimal);
void printf_big_decimal(big_decimal *b_decimal);

#endif