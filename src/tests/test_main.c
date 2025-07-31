#include <check.h>
#include <stdlib.h>

Suite *from_float_to_decimal(void);
Suite *from_int_to_decimal(void);
Suite *from_decimal_to_int(void);
Suite *from_decimal_to_float(void);
Suite *comparison_suite(void);
Suite *floor_suite(void);
Suite *round_suite(void);
Suite *truncate_suite(void);
Suite *negate_suite(void);
Suite *add_suite(void);
Suite *sub_suite(void);
Suite *mul_suite(void);
Suite *div_suite(void);

// Потом убрать этот блок
// Suite *from_decimal_to_int_suite1(void);
// Suite *from_decimal_to_int_suite2(void);
//  Suite *from_decimal_to_int_suite3(void);
// Suite *from_decimal_to_int_suite4(void);

// Suite *from_decimal_to_float_suite1(void);
// Suite *from_decimal_to_float_suite2(void);
// Suite *from_decimal_to_float_suite3(void);
// Suite *from_decimal_to_float_suite4(void);
// Suite *from_decimal_to_float_suite5(void);
// Suite *from_decimal_to_float_suite6(void);
// Suite *from_decimal_to_float_suite7(void);
// Suite *from_decimal_to_float_suite8(void);
// Suite *from_decimal_to_float_suite0(void);

// Suite *from_int_to_decimal_suite1(void);

// Suite *from_float_to_decimal_suite1(void);
// Suite *from_float_to_decimal_suite2(void);
// Suite *from_float_to_decimal_suite3(void);
// Suite *from_float_to_decimal_suite4(void);
// Suite *from_float_to_decimal_suite5(void);
// Suite *from_float_to_decimal_suite6(void);
// Suite *from_float_to_decimal_suite7(void);
// Suite *from_float_to_decimal_suite8(void);

// Suite *floor_suite0(void);
// Suite *floor_suite1(void);
// Suite *floor_suite2(void);
// Suite *floor_suite3(void);


int main(void) {
  int number_failed = 0;
  SRunner *sr = srunner_create(from_float_to_decimal());
  srunner_add_suite(sr, from_int_to_decimal());
  srunner_add_suite(sr, from_decimal_to_int());
  srunner_add_suite(sr, from_decimal_to_float());
  srunner_add_suite(sr, comparison_suite());
  srunner_add_suite(sr, floor_suite());
  srunner_add_suite(sr, round_suite());
  srunner_add_suite(sr, truncate_suite());
  srunner_add_suite(sr, negate_suite());
  srunner_add_suite(sr, add_suite());
  srunner_add_suite(sr, sub_suite());
  srunner_add_suite(sr, mul_suite());
  srunner_add_suite(sr, div_suite());
  

  //Потом убрать этот блок
  // srunner_add_suite(sr, from_decimal_to_int_suite1());
  // srunner_add_suite(sr, from_decimal_to_int_suite2());
  // srunner_add_suite(sr, from_decimal_to_int_suite3());
  // srunner_add_suite(sr, from_decimal_to_int_suite4());

  // srunner_add_suite(sr, from_decimal_to_float_suite1());
  // srunner_add_suite(sr, from_decimal_to_float_suite2());
  // srunner_add_suite(sr, from_decimal_to_float_suite3());
  // srunner_add_suite(sr, from_decimal_to_float_suite4());
  // srunner_add_suite(sr, from_decimal_to_float_suite5());
  // srunner_add_suite(sr, from_decimal_to_float_suite6());
  // srunner_add_suite(sr, from_decimal_to_float_suite7());
  // srunner_add_suite(sr, from_decimal_to_float_suite8());
  // srunner_add_suite(sr, from_decimal_to_float_suite0());

  // srunner_add_suite(sr, from_int_to_decimal_suite1());

  // srunner_add_suite(sr, from_float_to_decimal_suite1());
  // srunner_add_suite(sr, from_float_to_decimal_suite2());
  // srunner_add_suite(sr, from_float_to_decimal_suite3());
  // srunner_add_suite(sr, from_float_to_decimal_suite4());
  // srunner_add_suite(sr, from_float_to_decimal_suite5());
  // srunner_add_suite(sr, from_float_to_decimal_suite6());
  // srunner_add_suite(sr, from_float_to_decimal_suite7());
  // srunner_add_suite(sr, from_float_to_decimal_suite8());

  // srunner_add_suite(sr, floor_suite0());
  // srunner_add_suite(sr, floor_suite1());
  // srunner_add_suite(sr, floor_suite2());
  // srunner_add_suite(sr, floor_suite3());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}