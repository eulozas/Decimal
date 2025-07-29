#include "s21_arithmetic_helpers.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int res_add = 0;
    if (is_zero(&value_1) && is_zero(&value_2)) to_zero(result);
    else {
        int sign1 = get_sign(&value_1);
        int sign2 = get_sign(&value_2);
        big_decimal big_value_1 = {{0}, 0}, big_value_2 = {{0}, 0}, big_result = {{0}, 0};
        to_big_decimal(&value_1, &big_value_1);
        to_big_decimal(&value_2, &big_value_2);
        set_bit(&value_1, 127, 0);
        set_bit(&value_2, 127, 0);
        s21_normalization_big_scale(&big_value_1, &big_value_2);
        if (sign1 == sign2) {
            set_bit(result, 127, sign1);
            base_add(&big_value_1, &big_value_2, &big_result);
            res_add = big_to_decimal(&big_result, result);
        } else {
            if (s21_is_greater(value_1, value_2)) {
                set_bit(result, 127, sign1);
                base_sub(&big_value_1, &big_value_2, &big_result);
                res_add = big_to_decimal(&big_result, result);
            } else if (s21_is_equal(value_1, value_2)) {
                to_zero(result);
            } else {
                set_bit(result, 127, sign2);
                base_sub(&big_value_2, &big_value_1, &big_result);
                res_add = big_to_decimal(&big_result, result);
            }
        }
    }
    return res_add;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int res_sub = 0;
    value_2.bits[3] ^= MINUS;
    res_sub = s21_add(value_1, value_2, result);
    return res_sub;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int res_mull = 0;
    if (is_zero(&value_1) || is_zero(&value_2)) to_zero(result);
    else {
        int sign1 = get_sign(&value_1);
        int sign2 = get_sign(&value_2);
        set_bit(result, 127, sign1 ^ sign2);
        big_decimal temp_value_1 = {{0}, 0}, temp_value_2 = {{0}, 0}, temp_result = {{0}, 0};
        to_big_decimal(&value_1, &temp_value_1);
        to_big_decimal(&value_2, &temp_value_2);
        to_big_decimal(result, &temp_result);
        base_mull(&temp_value_1, &temp_value_2, &temp_result);
        res_mull = big_to_decimal(&temp_result, result);
    }
    return res_mull;
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

// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//     big_decimal remainder = {{0}, 0};
//     big_decimal quotient = {{0}, 0};
//     for (int i = 223; i >= 0; i--) {
//         shift_left(&remainder, 1);
        
//     }

// }