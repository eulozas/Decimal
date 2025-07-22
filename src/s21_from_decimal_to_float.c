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
        double res = src.bits[0] + src.bits[1]*pow(2,32) + src.bits[2]*pow(2,64);
        if(sign){
            res = -res;
        }
        res/=pow(10, scale);
        *dst = (float)res;
    }

    return exit_code;
}