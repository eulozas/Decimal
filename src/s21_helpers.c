#include <stdio.h>
#include "s21_helpers.h"


void* print_bits(s21_decimal *decimal) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (decimal->bits[0] >> i) & 1);
        if (i % 8 == 0) printf(" "); 
    }
    printf("\n");
}

int get_bit(s21_decimal *decimal, int index){

    int bit_index = index % 32;
    int bit_number = index / 32;

    return (decimal->bits[bit_number]>>bit_index) & 1u;
}

void set_bit(s21_decimal *decimal, int index, int val){
    int bit_index = index % 32;
    int bit_number = index / 32;

    unsigned int mask = 1u << bit_index;

    if(val){
        decimal->bits[bit_number] = decimal->bits[bit_number] | mask;
    }else{
        decimal->bits[bit_number] = decimal->bits[bit_number] & ~mask;
    }
}

int main() {
    s21_decimal decimal = {10010, 1, 0, 0};
    print_bits(&decimal);
    printf("8 bit - %d\n", get_bit(&decimal, 8));
    printf("9 bit - %d\n", get_bit(&decimal, 9));
    printf("10 bit - %d\n", get_bit(&decimal, 10));
    printf("11 bit - %d\n", get_bit(&decimal, 14));

    set_bit(&decimal, 8, 0);
    printf("8 bit - %d\n", get_bit(&decimal, 8));

    set_bit(&decimal, 11, 1);
    printf("11 bit - %d\n", get_bit(&decimal, 11));

    return 0;
}