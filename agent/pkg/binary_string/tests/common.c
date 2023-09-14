#include <check.h>
#include <stdlib.h> /* malloc, free */

#include "binary_string.h" /* binary_string, new_binary_string, destroy_binary_string */

struct binary_string* BS;

void teardown(void) {
  destroy_binary_string(BS);
}

START_TEST(binary_string_null) {
  size_t len = 257;

  BS = new_binary_string(len, NULL);

  ck_assert_uint_eq(len, BS->len);
}

END_TEST

START_TEST(binary_string_data) {
  size_t len = 13;
  uint8_t* data = "0123456789012";

  BS = new_binary_string(len, data);

  ck_assert_uint_eq(len, BS->len);
  ck_assert_mem_eq(data, BS->data, len);
}

END_TEST

Suite* binary_string_suite(void) {
  Suite* s;
  TCase* tc_core;
  TCase* tc_limits;

  s = suite_create("binary_string");
  tc_core = tcase_create("Core");
  tcase_add_checked_fixture(tc_core, NULL, teardown);

  tcase_add_test(tc_core, binary_string_null);
  tcase_add_test(tc_core, binary_string_data);

  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  int number_failed;
  Suite* s;
  SRunner* sr;

  s = binary_string_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}