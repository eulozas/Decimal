#include "s21_decimal.h"
#include "s21_helpers.h"
#include <stdio.h>

int s21_from_decimal_to_int(s21_decimal src, int *dst){
    if(!dst)return 1;
    int exit_code = 0;
    int sign = get_sign(&src);
    int scale = get_scale(&src);
    if(scale>MAX_SCALE || scale < 0){
        return 1;
    }

    unsigned int low = src.bits[0];
    unsigned int mid = src.bits[1];
    unsigned int high = src.bits[2];

    while (scale > 0) {
        divide_by_10(&high, &mid, &low);
        scale--;
    }

    if (high != 0 || mid != 0 || low > (unsigned int)MAX_INT + (sign ? 1 : 0)) {
        exit_code = 1; 
    }
    if(!exit_code){
        int result = (int)low;
        if (sign) {
            result = -result;
        }
        *dst = result;
    }
    
    return exit_code;
}