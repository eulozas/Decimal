#include "s21_arithmetic_helpers.h"

int base_add(const big_decimal *value_1, const big_decimal *value_2, big_decimal *result) {
    result->scale = value_1->scale;
    int carry = 0;
    for (int i = 0; i < 224; i++) {
        int num1 = get_bit_big(value_1, i);
        int num2 = get_bit_big(value_2, i);
        set_bit_big(result, i, num1 ^ num2 ^ carry);
        carry = (num1 & num2) | (num1 & carry) | (num2 & carry);
    }
    return carry;
}

int base_sub(const big_decimal *value_1, const big_decimal *value_2, big_decimal *result){
    result->scale = value_1->scale;
    int borrow = 0;
    for (int i = 0; i < 224; i++) {
        int num1 = get_bit_big(value_1, i);
        int num2 = get_bit_big(value_2, i);
        set_bit_big(result, i, borrow ^ num1 ^ num2);
        borrow = ((~num1 & 1u) & num2) | (borrow & (~num1 & 1u)) | (borrow & num1 & num2);
    }
    return 0;
    }

int base_mull(big_decimal *value_1, big_decimal *value_2, big_decimal *result){
    for (int i = 0; i < 224; i++) {
        int num = get_bit_big(value_1, i);
        if (num) {
            big_decimal tmp = *value_2;
            shift_left(&tmp, i);
            base_add(result, value_2, result); //??????? все норм если изменить в самой base_add работать над конвертируемыми числами и уже в конце записывать результат
        }
    }
    return 0;
}

int shift_left(big_decimal* decimal, int index) {
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

void shift_right(big_decimal* decimal, int index) {
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

void to_big_decimal(const s21_decimal* decimal, big_decimal* b_decimal) {
    for (int i = 0; i < 3; i++) {
        b_decimal->bits[i] = decimal->bits[i];
    }
    b_decimal->scale = get_scale(decimal);
}

int big_to_decimal(big_decimal* b_decimal, s21_decimal* decimal){
    int code_error = 0;
    while (mantissa_96_bit(b_decimal) && code_error == 0) {
        if (b_decimal->scale > 0) {
            div_10_big_decimal(b_decimal);
        } else if (get_sign(decimal)) {
            code_error = 2;
        } else code_error = 1;
    }
    while (b_decimal->scale > 28 && code_error == 0) {
        div_10_big_decimal(b_decimal);
        if (is_zero_big_decimal(b_decimal)) code_error = 2;
    }
    if (code_error == 0) {
        for (int i = 0; i < 3; i++) {
            decimal->bits[i] = b_decimal->bits[i];
        }
        decimal->bits[3] |= b_decimal->scale << 16;
    }
    return code_error;
}

void init_big_decimal(big_decimal *decimal) {
    for (int i = 0; i < 7; i++){
        decimal->bits[i] = 0u;
    }
    decimal->scale = 0u;
}

void s21_normalization_big_scale(big_decimal* value_1, big_decimal* value_2) {
    while (value_1->scale > value_2->scale) {
        mull_10_big_decimal(value_2);
    }
    while (value_2->scale > value_1->scale) {
        mull_10_big_decimal(value_1);
    }
}

void mull_10_value(big_decimal* value_1){
    int overflow = 0;

    for(int i = 0; i < 7; i++){
        uint64_t buffer = (uint64_t)value_1->bits[i] * 10 + overflow;
        value_1->bits[i] = (uint32_t)buffer & 0xFFFFFFFF;
        overflow = buffer >> 32;
    }
    value_1->scale++;
}


void mull_10_big_decimal(big_decimal* b_decimal) {
    big_decimal tmp1 = *b_decimal;
    big_decimal tmp2 = *b_decimal;
    shift_left(&tmp1, 3);
    shift_left(&tmp2, 1);
    base_add(&tmp1, &tmp2, b_decimal);
    b_decimal->scale++;
}

int mantissa_96_bit(const big_decimal* b_decimal) {
    int ret = 0;
    for (int i = 3; i < 7 && ret == 0; i++) {
        if (b_decimal->bits[i] != 0u) ret = 1;
    }
    return ret;
}

void div_10_big_decimal(big_decimal* b_decimal) {
    unsigned long long remainder = 0;
    for (int i = 6; i >= 0; i--) {
        unsigned long long current = (unsigned long long)b_decimal->bits[i] + (remainder << 32);
        b_decimal->bits[i] = (unsigned)(current / 10);
        remainder = current % 10;
    }
    if (remainder > 5 || (remainder == 5 && (b_decimal->bits[0] & 1u))) {
        big_decimal tmp;
        init_big_decimal(&tmp);
        tmp.bits[0] |= 1u;
        base_add(b_decimal, &tmp, b_decimal);
    }
    b_decimal->scale--;
}

int is_zero_big_decimal(big_decimal* b_decimal) {
    int ret = 1;
    for (int i = 0; i < 7 && ret; i++){
        if (b_decimal->bits[i] != 0u) ret = 0;
    }
    return ret;
}

void printf_big_decimal(big_decimal *b_decimal) {
    printf("mantissa\n");
    for (int i = 0; i < 7; i++){
        printf("%d=%u\n", i, b_decimal->bits[i]);
    }
    printf("scale=%u\n", b_decimal->scale);
}

void printf_decimal(s21_decimal *b_decimal) {
    printf("mantissa\n");
    for (int i = 0; i < 4; i++){
        printf("%d=%x\n", i, b_decimal->bits[i]);
    }
}