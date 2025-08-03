#include "s21_helpers.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (!dst) return 1;

  s21_clear_decimal(dst);

  unsigned int u_src;
  if (src < 0) {
    s21_set_sign(dst, 1);
    u_src = ~(unsigned int)src + 1u;
  } else {
    u_src = (unsigned int)src;
  }
  dst->bits[0] = u_src;

  return 0;
}
