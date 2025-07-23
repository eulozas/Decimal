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
int base_add(const s21_big_decimal *value_1, const s21_big_decimal *value_2, s21_big_decimal *result);
int base_sub(const s21_big_decimal *value_1, const s21_big_decimal *value_2, s21_big_decimal *result);
int base_mull(s21_big_decimal *value_1, s21_big_decimal *value_2, s21_big_decimal *result);
void mul_10_value(s21_decimal* value_1);
void make_same_scales(s21_decimal* value_1, int* scale_value_1, int* scale_value_2);
int is_zero(const s21_decimal* decimal);
void to_zero(s21_decimal* decimal);
void to_big_decimal(const s21_decimal* decimal, s21_big_decimal* s21_big_decimal);
void big_to_decimal(const s21_big_decimal* s21_big_decimal, s21_decimal* decimal);
void init_big_decimal(s21_big_decimal *decimal);
void shift_right(s21_big_decimal* decimal, int index);
int shift_left(s21_big_decimal* decimal, int index);
int get_bit_big(const s21_big_decimal *decimal, int index);
void set_bit_big(s21_big_decimal *decimal, int index, int val);

#endif