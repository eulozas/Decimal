#include <stdio.h>

#include "s21_arithmetic_helpers.h"
#include "s21_decimal.h"
#include "s21_helpers.h"

int main() {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 39614081257132168796771977148
  s21_decimal decimal_check = {{0x7BC, 0x0, 0x80000000, 0x0}};
  s21_decimal res = {0};
  int k = s21_div(decimal1, decimal2, &res);
  printf("%d\n", k);
  printf_decimal(&res);
}