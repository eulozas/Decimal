#include "s21_decimal.h"
#include "s21_helpers.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (get_sign(&value_1) == get_sign(&value_2)) {
        set_bit(result, 127, get_sign(&value_1));
        base_add(&value_1, &value_2, result);
    } else {
        if (s21_is_greater(value_1, value_2)) {
            set_bit(&result, 127, get_sign(&value_1));
            base_sub(&value_1, &value_2, result);
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
    for (int i = 0; i < 96; i++) {
        int num = get_bit(&value_1, i);
        if (num) {
            s21_decimal temp = value_2; //функцию сдвига надо написать
            base_add(result, &temp, result); //??????? все норм если изменить в самой base_add работать над конвертируемыми числами и уже в конце записывать результат
        }
    }
    return 0;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    return 0;
}

int base_add(const s21_decimal *value_1, const s21_decimal *value_2, s21_decimal *result) {
    int carry = 0;
    for (int i = 0; i < 96; i++) {
        int num1 = get_bit(value_1, i);
        int num2 = get_bit(value_2, i);
        set_bit(result, i, num1 ^ num2 ^ carry);
        carry = (num1 & num2) | (num1 & carry) | (num2 & carry);
    }
    return 0;
}

int base_sub(const s21_decimal *value_1, const s21_decimal *value_2, s21_decimal *result){
  int borrow = 0;
  for (int i = 0; i < 96; i++) {
    int num1 = get_bit(value_1, i);
    int num2 = get_bit(value_2, i);
    set_bit(result, i, borrow ^ num1 ^ num2);
    borrow = ((~num1 & 1u) & num2) | (borrow & (~num1 & 1u)) | (borrow & num1 & num2);
  }
}

void shift_left(big_decimal* decimal, const int* index) {
    int size_dec = 96;
    int word_shift = size_dec / *index;
    int index_shift = size_dec % *index;
    for (int i = 6; i >= 0; i--) {
        if (i - word_shift >= 0){
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

void shift_right(s21_decimal* decimal) {

}

void to_big_decimal(const s21_decimal* decimal, big_decimal* big_decimal) {
    for (int i = 0; i < 3; i++) {
        big_decimal->bits[i] &= decimal->bits[i];
    }
    big_decimal->scale &= get_scale(decimal);
}