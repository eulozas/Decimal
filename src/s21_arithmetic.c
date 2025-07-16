#include "s21_decimal.h"
#include "s21_helpers.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    big_decimal big_value_1 = {0}, big_value_2 = {0}, big_result = {0};
    to_big_decimal(&value_1, &big_value_1);
    to_big_decimal(&value_2, &big_value_2);
    to_big_decimal(&result, &big_result);
    if (get_sign(&value_1) == get_sign(&value_2)) {
        set_bit(result, 127, get_sign(&value_1));
        base_add(&big_value_1, &big_value_2, &big_result);
    } else {
        if (s21_is_greater(value_1, value_2)) {
            set_bit(&result, 127, get_sign(&value_1));
            base_sub(&big_value_1, &big_value_2, &big_result);
        } else if (s21_is_equal(value_1, value_2)) {
            to_zero(&result);
        } else {
            set_bit(&result, 127, get_sign(&value_2));
            base_sub(&value_2, &value_1, result);
        }
    } 
    return 0;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    value_2.bits[3] ^= MINUS;
    s21_add(value_1, value_2, result);
    return 0;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    big_decimal temp_value_1 = {0}, temp_value_2 = {0}, temp_result = {0};
    for (int i = 0; i < 224; i++) {
        int num = get_bit(&value_1, i);
        if (num) {
            shift_left(&temp_value_2, i);//функцию сдвига надо написать
            base_add(&temp_result, &temp_value_2, &temp_result); //??????? все норм если изменить в самой base_add работать над конвертируемыми числами и уже в конце записывать результат
        }
    }
    return 0;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    return 0;
}

int base_add(const big_decimal *value_1, const big_decimal *value_2, big_decimal *result) {
    int carry = 0;
    for (int i = 0; i < 224; i++) {
        int num1 = get_bit(value_1, i);
        int num2 = get_bit(value_2, i);
        set_bit_big(result, i, num1 ^ num2 ^ carry);
        carry = (num1 & num2) | (num1 & carry) | (num2 & carry);
    }
    if (carry) return 1;
    //возможно нормализовать нужно
    big_to_decimal(&result, result);
    return 0;
}

int base_sub(const big_decimal *value_1, const big_decimal *value_2, big_decimal *result){
  int borrow = 0;
  for (int i = 0; i < 224; i++) {
    int num1 = get_bit(value_1, i);
    int num2 = get_bit(value_2, i);
    set_bit_big(result, i, borrow ^ num1 ^ num2);
    borrow = ((~num1 & 1u) & num2) | (borrow & (~num1 & 1u)) | (borrow & num1 & num2);
  }
}

void shift_left(big_decimal* decimal, const int* index) {
    int word_shift = *index / 32;
    int index_shift = *index % 32;
    for (int i = 6; i >= 0; i--) {
        if (i - word_shift >= 0 && word_shift > 0){
            decimal->bits[i] |= decimal->bits[i - word_shift];
        } else {
            decimal->bits[i] &= 0u;
        }
    }
    for (int i = 6; i >=0; i--){
        decimal->bits[i] << index_shift;
        if (i - 1 >= 0) {
            decimal->bits[i] |= (decimal->bits[i - 1] >> (32 - index_shift));
        }
    }
}

void shift_right(big_decimal* decimal, const int* index) {
    int word_shift = *index / 32;
    int index_shift = *index % 32;
    for (int i = 0; i < 7; i++) {
        decimal->bits[i] &= 0u;
        decimal->bits[i] &= decimal->bits[i + word_shift];
    }
    if (index_shift > 0) {
        for (int i = 0; i < 7; i++) {
            decimal->bits[i] >> index_shift;
            if (i + 1 >= 0) {
                decimal->bits[i] |= (decimal->bits[i + 1] << (32 - index_shift));
            }
        }
    }
}

void to_big_decimal(const s21_decimal* decimal, big_decimal* big_decimal) {
    for (int i = 0; i < 3; i++) {
        big_decimal->bits[i] &= decimal->bits[i];
    }
    big_decimal->scale &= get_scale(decimal);
}

void big_to_decimal(const big_decimal* big_decimal, s21_decimal* decimal){
    for (int i = 0; i < 3; i++) {
        decimal->bits[i] &= big_decimal->bits[i];
    }
    decimal->bits[3] |= big_decimal->scale << 16;
}

void init_big_decimal(big_decimal *decimal) {
    for (int i = 0; i < 7; i++){
        decimal->bits[i] = 0u;
    }
    decimal->scale = 0u;
}