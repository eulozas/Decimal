#include "s21_decimal.h"
#include "s21_helpers.h"
#include <stdio.h>

int main() {
    s21_decimal val1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
    s21_decimal val2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
    set_scale(&val1, 5);
    set_scale(&val2, 3);
    s21_decimal res = {{0}};
    int c = s21_add(val1, val2, &res);
    printf("%d\n", c);
}