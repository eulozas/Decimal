#include "s21_decimal.h"
#include "s21_helpers.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int res_add = 0;
    int sign1 = get_sign(&value_1);
    int sign2 = get_sign(&value_2);
    s21_big_decimal big_value_1 = {0}, big_value_2 = {0}, big_result = {0};
    to_big_decimal(&value_1, &big_value_1);
    to_big_decimal(&value_2, &big_value_2);
    s21_normalization_big_scale(&big_value_1, &big_value_2); //может подаваться на вход больше 28??
    if (sign1 == sign2) {
        set_bit(result, 127, sign1);
        base_add(&big_value_1, &big_value_2, &big_result);
        res_add = big_to_decimal(&big_result, result);
    } else {
        if (s21_is_greater(value_1, value_2)) {
            set_bit(result, 127, get_sign(&value_1));
            base_sub(&big_value_1, &big_value_2, &big_result);
            res_add = big_to_decimal(&big_result, result);
        } else if (s21_is_equal(value_1, value_2)) {
            to_zero(result);
        } else {
            set_bit(result, 127, get_sign(&value_2));
            base_sub(&big_value_2, &big_value_1, &big_result);
            res_add = big_to_decimal(&big_result, result);
        }
    }
    return res_add;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    value_2.bits[3] ^= MINUS;
    s21_add(value_1, value_2, result);
    return 0;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    s21_big_decimal temp_value_1 = {0}, temp_value_2 = {0}, temp_result = {0};
    to_big_decimal(&value_1, &temp_value_1);
    to_big_decimal(&value_2, &temp_value_2);
    to_big_decimal(result, &temp_result);
    base_mull(&temp_value_1, &temp_value_2, &temp_result);
    big_to_decimal(&temp_result, result);
    return 0;
}

// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//     int q = 0;
//     int tmp_shift = 1;
//     big_decimal digit = {0};
//     digit.bits[0] = 1u;
//     while (s21_is_less_or_equal(value_2, value_1)) {
//         big_decimal temp_value_1 = {0}, temp_value_2 = {0}, temp_result = {0};
//         to_big_decimal(&value_1, &temp_value_1);
//         to_big_decimal(&value_2, &temp_value_2);
//         shift_left(&digit, &tmp_shift);
//         base_mull(&temp_value_2, &digit, &temp_result);
//     }
//     return 0;
// }

int base_add(const s21_big_decimal *value_1, const s21_big_decimal *value_2, s21_big_decimal *result) {
    int carry = 0;
    for (int i = 0; i < 224; i++) {
        int num1 = get_bit_big(value_1, i);
        int num2 = get_bit_big(value_2, i);
        set_bit_big(result, i, num1 ^ num2 ^ carry);
        carry = (num1 & num2) | (num1 & carry) | (num2 & carry);
    }
    return carry;
}

int base_sub(const s21_big_decimal *value_1, const s21_big_decimal *value_2, s21_big_decimal *result){
  int borrow = 0;
  for (int i = 0; i < 224; i++) {
    int num1 = get_bit_big(value_1, i);
    int num2 = get_bit_big(value_2, i);
    set_bit_big(result, i, borrow ^ num1 ^ num2);
    borrow = ((~num1 & 1u) & num2) | (borrow & (~num1 & 1u)) | (borrow & num1 & num2);
  }
  return 0;
}

int base_mull(s21_big_decimal *value_1, s21_big_decimal *value_2, s21_big_decimal *result){
    for (int i = 0; i < 224; i++) {
        int num = get_bit_big(value_1, i);
        if (num) {
            s21_big_decimal tmp = *value_2;
            shift_left(&tmp, i);
            base_add(result, value_2, result); //??????? все норм если изменить в самой base_add работать над конвертируемыми числами и уже в конце записывать результат
        }
    }
    return 0;
}

int shift_left(s21_big_decimal* decimal, int index) {
    unsigned overflow = 0;

    int word_shift = index / 32;
    int index_shift = index % 32;

    for (int i = 6; i >= 0 && !overflow && word_shift; i--) {
        if (i - word_shift >= 0){
            if (decimal->bits[i]) overflow = 1;
            else {
                decimal->bits[i] |= decimal->bits[i - word_shift];
                decimal->bits[i - word_shift] &= 0u;
            }
        }
    }
    for (int i = 0; i < index_shift && !overflow; i++) {
        if (get_bit_big(decimal, 223 - i)) overflow = 1;
    }

    for (int i = 6; i >=0 && !overflow; i--){
        decimal->bits[i] <<= index_shift;
        if (i - 1 >= 0) {
            decimal->bits[i] |= (decimal->bits[i - 1] >> (32 - index_shift));
        }
    }
    return overflow; 
}

void shift_right(s21_big_decimal* decimal, int index) {
    int word_shift = index / 32;
    int index_shift = index % 32;
    for (int i = 0; i < 7; i++) {
        decimal->bits[i] &= 0u;
        decimal->bits[i] &= decimal->bits[i + word_shift];
    }
    if (index_shift > 0) {
        for (int i = 0; i < 7; i++) {
            decimal->bits[i] >>= index_shift;
            if (i + 1 >= 0) {
                decimal->bits[i] |= (decimal->bits[i + 1] << (32 - index_shift));
            }
        }
    }
}

void to_big_decimal(const s21_decimal* decimal, s21_big_decimal* big_decimal) {
    for (int i = 0; i < 3; i++) {
        big_decimal->bits[i] &= decimal->bits[i];
    }
    big_decimal->scale &= get_scale(decimal);
}

int big_to_decimal(s21_big_decimal* big_decimal, s21_decimal* decimal){
    int code_error = 0;
    while (mantissa_96_bit(big_decimal) && code_error == 0) {
        if (big_decimal->scale > 0) {
            div_10_big_decimal(big_decimal);
        } else if (get_sign(decimal)) {
            code_error = 2;
        } else code_error = 1;
    }
    while (big_decimal->scale > 28 && code_error == 0) {
        div_10_big_decimal(big_decimal);
        if (is_zero_big_decimal(big_decimal)) code_error = 2;
    }
    if (code_error == 0) {
        for (int i = 0; i < 3; i++) {
            decimal->bits[i] &= big_decimal->bits[i];
        }
        decimal->bits[3] |= big_decimal->scale << 16;
    }
    return code_error;
}

void init_big_decimal(s21_big_decimal *decimal) {
    for (int i = 0; i < 7; i++){
        decimal->bits[i] = 0u;
    }
    decimal->scale = 0u;
}

void s21_normalization_big_scale(s21_big_decimal* value_1, s21_big_decimal* value_2) {
    while (value_1->scale > value_2->scale) {
        mull_10_big_decimal(value_2);
    }
    while (value_2->scale > value_1->scale) {
        mull_10_big_decimal(value_1);
    }
}

void mull_10_big_decimal(s21_big_decimal* big_decimal) {
    s21_big_decimal tmp = *big_decimal;
    shift_left(&tmp, 3);
    shift_left(big_decimal, 1);
    base_add(big_decimal, &tmp, big_decimal);
    big_decimal->scale++;
}

int mantissa_96_bit(const s21_big_decimal* big_decimal) {
    int ret = 0;
    for (int i = 3; i < 7 && ret == 0; i++) {
        if (big_decimal->bits[i] != 0u) ret = 1;
    }
    return ret;
}

void div_10_big_decimal(s21_big_decimal* big_decimal) {
    unsigned long long remainder = 0;
    for (int i = 6; i > 0; i--) {
        unsigned long long current = (unsigned)(big_decimal->bits[i] | (remainder << 32));
        big_decimal->bits[i] = (unsigned)(current / 10);
        remainder = current % 10;
    }
    if (remainder > 5 || (remainder == 5 && (big_decimal->bits[0] & 1u))) {
        s21_big_decimal tmp;
        init_big_decimal(&tmp);
        tmp.bits[0] |= 1u;
        base_add(big_decimal, &tmp, big_decimal);
        big_decimal->scale--;
    }
}

int is_zero_big_decimal(s21_big_decimal* big_decimal) {
    int ret = 1;
    for (int i = 0; i < 7 && ret; i++){
        if (big_decimal->bits[i] != 0u) ret = 0;
    }
    return ret;
}