#include "s21_decimal.h"
#include "s21_helpers.h"
#include <stdio.h>

int s21_floor(s21_decimal value, s21_decimal *result){
    if (!result) return 1;
    
    int exit_code = 0;

    int sign = get_sign(&value);
    int scale = get_scale(&value);

    if(scale == 0){
        *result = value;
    }else{
        unsigned int low = value.bits[0];
        unsigned int mid = value.bits[1];
        unsigned int high = value.bits[2];
        printf("%d\n", low);

        while (scale > 0) {
            divide_by_10(&high, &mid, &low);
            scale--;
        }
        if(sign){
        increment_decimal_bits(&low, &mid, &high);
        set_sign(result);
        }
        result->bits[0] = low;
        result->bits[1] = mid;
        result->bits[2] = high;
    }

    return exit_code;
}