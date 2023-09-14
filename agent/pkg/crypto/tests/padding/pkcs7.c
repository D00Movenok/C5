#include <check.h>
#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE */

#include "binary_string.h" /* binary_string, new_binary_string, destroy_binary_string */
#include "crypto/padding/pkcs7.h" /* pkcs7_pad, pkcs7_unpad */

struct binary_string* BS;

void teardown(void) {
  destroy_binary_string(BS);
}

START_TEST(pad_simple) {
  uint8_t data[13] = "0123456789012";
  size_t block_size = 16;

  uint8_t want[16] = "0123456789012\x03\x03\x03";
  size_t want_size = sizeof(want);

  BS = new_binary_string(sizeof(data), data);

  pkcs7_pad(BS, block_size);

  ck_assert_uint_eq(want_size, BS->len);
  ck_assert_mem_eq(want, BS->data, want_size);
}

END_TEST

START_TEST(pad_block_size) {
  uint8_t data[16] = "0123456789012345";
  size_t block_size = 16;

  uint8_t want[32] =
      "0123456789012345\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10"
      "\x10\x10";
  size_t want_size = sizeof(want);

  BS = new_binary_string(sizeof(data), data);

  pkcs7_pad(BS, block_size);

  ck_assert_uint_eq(want_size, BS->len);
  ck_assert_mem_eq(want, BS->data, want_size);
}

END_TEST

START_TEST(pad_contains_padding) {
  uint8_t data[8] = "\x08\x08\x08\x08\x08\x08\x08\x08";
  size_t block_size = 16;

  uint8_t want[16] =
      "\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08";
  size_t want_size = sizeof(want);

  BS = new_binary_string(sizeof(data), data);

  pkcs7_pad(BS, block_size);

  ck_assert_uint_eq(want_size, BS->len);
  ck_assert_mem_eq(want, BS->data, want_size);
}

END_TEST

START_TEST(unpad_simple) {
  uint8_t data[16] = "0123456789012\x03\x03\x03";
  size_t block_size = 16;

  uint8_t want[13] = "0123456789012";
  size_t want_size = sizeof(want);

  BS = new_binary_string(sizeof(data), data);

  bool ok = pkcs7_unpad(BS, block_size);

  ck_assert_int_eq(ok, true);
  ck_assert_uint_eq(want_size, BS->len);
  ck_assert_mem_eq(want, BS->data, want_size);
}

END_TEST

START_TEST(unpad_block_size) {
  uint8_t data[32] =
      "0123456789012345\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10"
      "\x10\x10";
  size_t block_size = 16;

  uint8_t want[16] = "0123456789012345";
  size_t want_size = sizeof(want);

  BS = new_binary_string(sizeof(data), data);

  bool ok = pkcs7_unpad(BS, block_size);

  ck_assert_int_eq(ok, true);
  ck_assert_uint_eq(want_size, BS->len);
  ck_assert_mem_eq(want, BS->data, want_size);
}

END_TEST

START_TEST(unpad_contains_padding) {
  uint8_t data[16] =
      "\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08";
  size_t block_size = 16;

  uint8_t want[8] = "\x08\x08\x08\x08\x08\x08\x08\x08";
  size_t want_size = sizeof(want);

  BS = new_binary_string(sizeof(data), data);

  bool ok = pkcs7_unpad(BS, block_size);

  ck_assert_int_eq(ok, true);
  ck_assert_uint_eq(want_size, BS->len);
  ck_assert_mem_eq(want, BS->data, want_size);
}

END_TEST

START_TEST(unpad_bad_padding) {
  uint8_t data[16] = "01234567890123\x03\x03";
  size_t block_size = 16;

  BS = new_binary_string(sizeof(data), data);

  bool ok = pkcs7_unpad(BS, block_size);

  ck_assert_int_eq(ok, false);
}

END_TEST

Suite* pkcs7_suite(void) {
  Suite* s;
  TCase* tc_core;
  TCase* tc_limits;

  s = suite_create("pkcs7");
  tc_core = tcase_create("Core");
  tcase_add_checked_fixture(tc_core, NULL, teardown);

  tcase_add_test(tc_core, pad_simple);
  tcase_add_test(tc_core, pad_block_size);
  tcase_add_test(tc_core, pad_contains_padding);
  tcase_add_test(tc_core, unpad_simple);
  tcase_add_test(tc_core, unpad_block_size);
  tcase_add_test(tc_core, unpad_contains_padding);
  tcase_add_test(tc_core, unpad_bad_padding);

  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  int number_failed;
  Suite* s;
  SRunner* sr;

  s = pkcs7_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}