#include "s21_decimal.h"
#include "s21_helpers.h"

int s21_negate(s21_decimal value, s21_decimal *result){
    if (!result) return 1;
    
    int exit_code = 0;

    int sign = get_sign(&value);
    int scale = get_scale(&value);
    int check_bit = check_free_decimal_bit(value);

    if(scale < 0 || scale > MAX_SCALE || check_bit){
        exit_code = 1;
    }

    if(!exit_code){
        *result = value;
        if(sign){     
            clear_sign(result);
        }
        else{
            set_sign(result);
        }
    }

    return exit_code;
}