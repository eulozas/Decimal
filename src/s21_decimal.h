#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#define MAX_DECIMAL_VALUE 79228162514264337593543950335.0
#define MAX_DECIMAL_VALUE_NEXT 79228162514264337593543950336.0
#define MAX_SCALE 28
#define SIGNIF_DIGITS 7
#define MAX_INT 2147483647

typedef struct{
    unsigned int bits[4];
} s21_decimal;

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
//int s21_from_decimal_to_float(s21_decimal src, float *dst);

#endif