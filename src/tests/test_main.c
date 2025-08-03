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
Suite *arithmetic_suite(void);

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
  srunner_add_suite(sr, arithmetic_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}