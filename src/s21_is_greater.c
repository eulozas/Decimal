#include "s21_decimal.h"
#include "s21_helpers.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2){
    int sign_value_1 = get_sign(&value_1);//0 = +, 1 = -
    int sign_value_2 = get_sign(&value_2);
    int scale_value_1 = get_scale(&value_1);
    int scale_value_2 = get_scale(&value_2);
    int result = 1;
    int equal = 0;
    if(is_zero(&value_1) && is_zero(&value_2)){
        result = 0;
    }
    else if(sign_value_1 && !sign_value_2){
        result = 0;
    }
    else if(sign_value_1 == sign_value_2){
        big_decimal big_value_1 = {0}, big_value_2 = {0};
        to_big_decimal(&value_1, &big_value_1);
        to_big_decimal(&value_2, &big_value_2);
        if(scale_value_1 != scale_value_2){
            if(scale_value_1 < scale_value_2){
                make_same_scales(&big_value_1, &scale_value_1, &scale_value_2);
            }
            else{
                make_same_scales(&big_value_2, &scale_value_2, &scale_value_1);
            }
        }
        for(int i = 6; i >= 0; i--){
            if(big_value_1.bits[i] > big_value_2.bits[i]){
                result = 1;
                break;
            }
            else if(big_value_1.bits[i] < big_value_2.bits[i]){
                result = 0;
                break;
            }
            else{
                equal++;
            }
        }
        if(sign_value_1){
            if(result){
                result = 0;
            }
            else{
                result = 1;
            }
        }
        if(equal == 7){
            result = 0;
        }
    }
    else{
        result = 1;
    }
    return result;
}