#include <stdio.h>
#include <stdint.h>
#include "s21_helpers.h"

void clear_decimal(s21_decimal *decimal) {
    if (!decimal) return;
    for (int i = 0; i < 4; ++i) {
        decimal->bits[i] = 0;
    }
}

int get_bit(const s21_decimal *decimal, int index){
    if (!decimal || index < 0 || index > 127) return 0;//?????
    int bit_index = index % 32;
    int bit_number = index / 32;

    return (decimal->bits[bit_number] >> bit_index) & 1u;
}

void set_bit(s21_decimal *decimal, int index, int val){
    if (!decimal || index < 0 || index > 127) return;//см по покрытию и логике далее нужно ли это? и ретерн надо изменить на другое значение

    int bit_index = index % 32;
    int bit_number = index / 32;

    unsigned int mask = 1u << bit_index;

    if(val){
        decimal->bits[bit_number] = decimal->bits[bit_number] | mask;
    }else{
        decimal->bits[bit_number] = decimal->bits[bit_number] & ~mask;
    }
}

void set_bit_big(big_decimal *decimal, int index, int val){
    if (!decimal || index < 0 || index > 224) return;//см по покрытию и логике далее нужно ли это? и ретерн надо изменить на другое значение

    int bit_index = index % 32;
    int bit_number = index / 32;

    unsigned int mask = 1u << bit_index;

    if(val){
        decimal->bits[bit_number] = decimal->bits[bit_number] | mask;
    }else{
        decimal->bits[bit_number] = decimal->bits[bit_number] & ~mask;
    }
}

void set_sign(s21_decimal* decimal){
    if (!decimal) return;//?????
    set_bit(decimal, 127, 1);
}

void clear_sign(s21_decimal* decimal){
    if (!decimal) return;//?????
    set_bit(decimal, 127, 0);
}

int get_sign(const s21_decimal *decimal){
    if (!decimal) return 0;//?????
    return (decimal->bits[3]>>31) & 1u;
}

int get_scale(const s21_decimal *decimal){
    if (!decimal) return 0;//?????
    return (decimal->bits[3] >> 16) & 0xFF;
}

void mul_10_value(big_decimal* value_1){
    int overflow = 0;

    for(int i = 0; i < 7; i++){
        uint64_t buffer = (uint64_t)value_1->bits[i] * 10 + overflow;
        value_1->bits[i] = (uint32_t)buffer & 0xFFFFFFFF;
        overflow = buffer >> 32;
    }
}

void to_big_decimal(const s21_decimal* decimal, big_decimal* big_decimal) {
    for (int i = 0; i < 3; i++) {
        big_decimal->bits[i] = decimal->bits[i];
    }
    big_decimal->scale = get_scale(decimal);
}

void make_same_scales(big_decimal* value_1, int* scale_value_1, int* scale_value_2){
    while(*scale_value_1 < *scale_value_2){
        mul_10_value(value_1);
        (*scale_value_1)++;
    }
}

int is_zero(const s21_decimal* decimal){
    return decimal->bits[0] == 0 && decimal->bits[1] == 0 && decimal->bits[2] == 0;
}

void to_zero(s21_decimal* decimal) {
    for (int i = 0; i < 4; i++) {
        decimal->bits[i] = 0;
    }
}

void set_scale(s21_decimal *decimal, int scale) {
    if (!decimal) return;//?????
    decimal->bits[3] &= ~(0xFF << 16);
    decimal->bits[3] |= (scale << 16);
}


int count_digits_before_point(unsigned long long n) {
    int count = 0;
    do {
        count++;
        n /= 10;
    } while (n > 0);
    return count;
}

double bank_round(double x) {
    //до нижнего
    double floor_x = floor(x);
    double diff = x - floor_x;

    if (diff > 0.5) {
        //до верхнего
        return ceil(x);
    } else if (diff < 0.5) {
        return floor_x;
    } else {
        if (fmod(floor_x, 2.0) == 0.0) {
            // чётное — вниз
            return floor_x; 
        } else {
            // нечётное — вверх
            return ceil(x);
        }
    }
}

int find_point_index(double x) {
    x = fabs(x);
    int index = 0;

    while (x >= 10.0) {
        x /= 10.0;
        index++;
    }
    return index;
}

void normalize_mantissa(unsigned long long *mantissa, int *scale) {
    while (*scale > 0 && (*mantissa % 10 == 0)) {
        *mantissa /= 10;
        (*scale)--;
    }
}

void mul_decimal_by_10_and_carry_bits(s21_decimal *decimal) {
    unsigned long long a = (unsigned long long)decimal->bits[0] * 10;
    unsigned long long b = (unsigned long long)decimal->bits[1] * 10 + (a >> 32);
    unsigned long long c = (unsigned long long)decimal->bits[2] * 10 + (b >> 32);

    decimal->bits[0] = (unsigned int)(a & 0xFFFFFFFF);
    decimal->bits[1] = (unsigned int)(b & 0xFFFFFFFF);
    decimal->bits[2] = (unsigned int)(c & 0xFFFFFFFF);
}

void write_mantissa_to_decimal(unsigned long long mantissa, s21_decimal *decimal) {
    decimal->bits[0] = (unsigned int)(mantissa & 0xFFFFFFFF);
    decimal->bits[1] = (unsigned int)((mantissa >> 32) & 0xFFFFFFFF);
    decimal->bits[2] = 0;
}

void divide_by_10(unsigned int *high, unsigned int *mid, unsigned int *low) {
    unsigned long long rest = 0;

    unsigned long long value = ((unsigned long long)(*high));
    *high = (unsigned int)(value / 10);
    rest = value % 10;

    value = ((unsigned long long)(*mid)) + (rest << 32);
    *mid = (unsigned int)(value / 10);
    rest = value % 10;

    value = ((unsigned long long)(*low)) + (rest << 32);
    *low = (unsigned int)(value / 10);
}

int check_free_decimal_bit(s21_decimal decimal){
    int res = 0;
    for(int i = 96; i < 112 && !res; i++){
        if(get_bit(&decimal, i)){
            res = 1;
        }
    }
    for(int i = 120; i < 127 && !res; i++){
        if(get_bit(&decimal, i)){
            res = 1;
        }
    }

    return res;
}

// int main() {

//     // s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
//     // // 5281877500950955839569596689
//     // s21_decimal decimal2 = {{0x11111111, 0x11111111, 0x11111111, 0x0}};

//     // printf("%d\n", s21_is_less(decimal1, decimal2));


//     s21_decimal a = {{1000, 0, 0, 1 << 16}};  // 100.0
//     s21_decimal b = {{10000, 0, 0, 2 << 16}}; // 100.00
//     printf("%d\n", s21_is_equal(a, b));

//     return 0;
// }