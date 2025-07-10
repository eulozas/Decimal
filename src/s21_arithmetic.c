#include "s21_decimal.h"
#include "s21_helpers.h"
#include <stdio.h>

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (get_sign(&value_1) == get_sign(&value_2)) {
        set_bit(result, 127, get_sign(&value_1));
        base_add(&value_1, &value_2, result);
    } else {
        //сравниваем числа
        //берем знак большего
        //из большего вычитаем меньшее
    } 
}


int base_add(const s21_decimal *value_1, const s21_decimal *value_2, s21_decimal *result) {
    int carry = 0;
    for (int i = 0; i < 96; i++) {
        int num1 = get_bit(value_1, i);
        int num2 = get_bit(value_2, i);
        set_bit(result, i, num1 ^ num2 ^ carry);
        carry = (num1 & num2) | (num1 & carry) | (num2 & carry);
    }
    return 0;
}

int base_sub(const s21_decimal *value_1, const s21_decimal *value_2, s21_decimal *result){
  int borrow = 0;
  for (int i = 0; i < 96; i++) {
    int num1 = get_bit(value_1, i);
    int num2 = get_bit(value_2, i);
    set_bit(result, i, borrow ^ num1 ^ num2);
    borrow = ((~num1 & 1u) & num2) | (borrow & (~num1 & 1u)) | (borrow & num1 & num2);
  }
}