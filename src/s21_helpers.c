#include <stdio.h>
#include "s21_helpers.h"

void print_bits(const s21_decimal *decimal) {
    for (int i = 127; i >= 96; i--) {
        printf("%d", (decimal->bits[3] >> i) & 1);
        if (i % 8 == 0) printf(" "); 
    }
    printf("| ");
    for (int i = 95; i >= 64; i--) {
        printf("%d", (decimal->bits[2] >> i) & 1);
        if (i % 8 == 0) printf(" "); 
    }
    printf("| ");
    for (int i = 63; i >= 32; i--) {
        printf("%d", (decimal->bits[1] >> i) & 1);
        if (i % 8 == 0) printf(" "); 
    }
    printf("| ");
   for (int i = 31; i >= 0; i--) {
        printf("%d", (decimal->bits[0] >> i) & 1);
        if (i % 8 == 0) printf(" "); 
    }
    printf("\n");
}

int get_bit(const s21_decimal *decimal, int index){
    if (!decimal || index < 0 || index > 127) return 0;//см по покрытию и логике далее нужно ли это? и ретерн надо изменить на другое значение

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
    return (decimal->bits[3]>>31) & 1;
}

int get_scale(const s21_decimal *decimal){
    if (!decimal) return 0;//?????
    return (decimal->bits[3] >> 16) & 0b11111111; //0xFF
}

int main() {
    s21_decimal *decimal;
    s21_from_int_to_decimal(-2,decimal);

    print_bits(decimal);

    return 0;
}