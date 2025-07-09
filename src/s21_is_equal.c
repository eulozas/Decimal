#include "s21_decimal.h"
#include <stdint.h>


void mul_10_value(s21_decimal value_1){
    int overflow = 0;

    for(int i = 0; i < 3; i++){
        uint64_t buffer = (uint64_t)value_1.bits[i] * 10 + overflow;
        value_1.bits[i] = (uint32_t)buffer & 0b11111111111111111111111111111111; //0xFFFFFFFF
        overflow = buffer >> 32;
    }

    if(overflow != 0){
        //переполнение
    }
}

void make_same_scales(s21_decimal value_1, int scale_value_1, int scale_value_2){
    while(scale_value_1 < scale_value_2){
        mul_10_value(value_1);
        scale_value_1++;
    }
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2){
    int sign_value_1 = get_sign(value_1);
    int sign_value_2 = get_sign(value_2);
    int scale_value_1 = get_scale(value_1);
    int scale_value_2 = get_scale(value_2);
    int result = 1;
    if(sign_value_1 == sign_value_2){
        if(scale_value_1 != scale_value_2){
            if(scale_value_1 < scale_value_2){
                make_same_scales(value_1, scale_value_1, scale_value_2);
            }
            else{
                make_same_scales(value_2, scale_value_2, scale_value_1);
            }
        }
        for(int i = 0; i < 3; i++){
            if(value_1.bits[i] != value_2.bits[i]){
                result = 0;
            }
        }
    }
    else{
        result = 0;
    }

    return result;
}