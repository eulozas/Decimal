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

int s21_from_float_to_decimal(float src, s21_decimal *dst){
    if(!dst) return 1;//????? + добавить не равно беск и НаН

    dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;

    if(src<0){
        set_sign(dst);
    }
    int exp = get_exp_from_float(src);
    if(exp>95){
        return 1;
    }
    if(exp<=95){
        //тут нужно домножать на 10, пока число не будет с целой частью и прибавлять scale - Normalization

    }

    return 0;
}

