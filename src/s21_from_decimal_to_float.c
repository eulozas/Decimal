#include "s21_decimal.h"
#include "s21_helpers.h"
#include <stdio.h>

int s21_from_decimal_to_float(s21_decimal src, float *dst){
    if(!dst)return 1;
    int exit_code = 0;
    int sign = get_sign(&src);
     int scale = get_scale(&src);

     if(scale < 0 || scale > MAX_SCALE){
        exit_code = 1;
    }

    if(!exit_code){
        
        double res = (double)src.bits[0] + (double)src.bits[1] * (1ULL << 32) + (double)src.bits[2] * (1ULL << 64);
        res /= pow(10, scale);
        if(sign) res = -res;
        *dst = (float)res;

    }

    return exit_code;
}