#ifndef S21_HELPERS_H
#define S21_HELPERS_H

#include "s21_decimal.h"

void* print_bits_32(const s21_decimal *decimal);
int get_bit(const s21_decimal *decimal, int index);
void set_bit(s21_decimal *decimal, int index, int val);
void set_sign(s21_decimal* decimal);
void clear_sign(s21_decimal* decimal);
int get_sign(const s21_decimal *decimal);
int get_scale(const s21_decimal *decimal);
void mul_10_value(s21_decimal* value_1);
void make_same_scales(s21_decimal* value_1, int* scale_value_1, int* scale_value_2);
int is_zero(const s21_decimal* decimal);

#endif