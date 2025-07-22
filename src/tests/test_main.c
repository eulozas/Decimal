#include <check.h>
#include <stdlib.h>

Suite *from_float_to_decimal(void);
Suite *from_int_to_decimal(void);
Suite *from_decimal_to_int(void);

//Потом убрать этот блок
// Suite *from_decimal_to_int_suite1(void);
// Suite *from_decimal_to_int_suite2(void);
 //Suite *from_decimal_to_int_suite3(void);
// Suite *from_decimal_to_int_suite4(void);

// Suite *from_int_to_decimal_suite1(void);

// Suite *from_float_to_decimal_suite1(void);
// Suite *from_float_to_decimal_suite2(void);
// Suite *from_float_to_decimal_suite3(void);
// Suite *from_float_to_decimal_suite4(void);
// Suite *from_float_to_decimal_suite5(void);
// Suite *from_float_to_decimal_suite6(void);
// Suite *from_float_to_decimal_suite7(void);
// Suite *from_float_to_decimal_suite8(void);

int main(void) {
  int number_failed = 0;
  SRunner *sr = srunner_create(from_float_to_decimal());
  srunner_add_suite(sr, from_int_to_decimal());
  srunner_add_suite(sr, from_decimal_to_int());


  //Потом убрать этот блок
  // srunner_add_suite(sr, from_decimal_to_int_suite1());
  // srunner_add_suite(sr, from_decimal_to_int_suite2());
  // srunner_add_suite(sr, from_decimal_to_int_suite3());
  // srunner_add_suite(sr, from_decimal_to_int_suite4());

  // srunner_add_suite(sr, from_int_to_decimal_suite1());

  // srunner_add_suite(sr, from_float_to_decimal_suite1());
  // srunner_add_suite(sr, from_float_to_decimal_suite2());
  // srunner_add_suite(sr, from_float_to_decimal_suite3());
  // srunner_add_suite(sr, from_float_to_decimal_suite4());
  // srunner_add_suite(sr, from_float_to_decimal_suite5());
  // srunner_add_suite(sr, from_float_to_decimal_suite6());
  // srunner_add_suite(sr, from_float_to_decimal_suite7());
  // srunner_add_suite(sr, from_float_to_decimal_suite8());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}