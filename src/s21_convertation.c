#include "s21_decimal.h"
#include "s21_helpers.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst){
    if(!dst) return 1;//?????

    dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;

    unsigned int u_src;
    if(src<0){
        set_sign(dst);
        u_src = ~(unsigned int)src + 1u;
    }else{
        u_src = (unsigned int)src;
    }
    dst->bits[0] = u_src;

    return 0;
}

// int s21_from_float_to_decimal(float src, s21_decimal *dst){

// }

