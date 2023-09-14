#include <check.h>
#include <stdlib.h> /* malloc, free, EXIT_SUCCESS, EXIT_FAILURE */

#include "crypto/cipher/aes.h" /* new_aes_cipher, AES_KEYLEN, AES_BLOCKSIZE */
#include "crypto/cipher/common.h" /* Cipher, cipher_destroy, cipher_encrypt, cipher_decrypt */
#include "crypto/modes/cbc.h" /* CBCCipher, new_cbc_cipher, destroy_cbc_cipher, cbc_encrypt, cbc_encrypt */

#define PLAIN                                                                \
  "01234567890123456789012345678901\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10" \
  "\x10\x10\x10\x10\x10\x10"
#define PLAIN_LEN 48
#define KEY "01234567890123456789012345678901"
#define IV "5432109876543210"

#if defined(AES256)
#  define CIPHER                                                               \
    "\xc2\xf4\x83\x90\x70\x18\x1d\x94\x3a\xa4\x0a\x9b\x95\xb2\x88\xea\xb5\x04" \
    "\xde\x9a\xb5\xa4\x22\x06\xd3\x70\xf8\x56\x8d\x24\x7c\x51\x28\x6d\x23\xa4" \
    "\xff\x29\x5f\xd6\x63\x81\x0c\x07\xc9\xa4\x64\x3d"
#elif defined(AES192)
#  define CIPHER                                                               \
    "\xed\xbd\xd4\xb3\x64\x4a\xb7\x4a\x8b\x4e\xc4\x77\x49\xb7\x50\x3b\xfc\x84" \
    "\x71\xa3\xc0\x5f\xc6\x0b\xff\xef\x82\xb7\x19\x3d\xeb\x7e\xb0\x38\xc1\x60" \
    "\x2a\x3e\x7b\x61\x0d\x3d\x7a\x48\x8c\x4c\xab\xc5"
#else
#  define CIPHER                                                               \
    "\x84\x3f\xee\xa7\xfd\xcc\xf1\x44\x3a\x43\x36\xef\xe2\x02\x46\x5d\x5d\x05" \
    "\x62\x3d\xcd\xb1\xbf\x6c\x73\xf3\x75\x33\x8a\x0b\x3d\xec\x82\x78\x9c\x3d" \
    "\xa8\x59\x21\x38\x54\x1a\xe8\x99\x51\xd4\xe5\xaf"
#endif

struct Cipher* AES;
struct CBCCipher* CBC;
uint8_t* DST;

void setup(void) {
  DST = malloc(PLAIN_LEN);
  AES = new_aes_cipher(KEY);
  CBC = new_cbc_cipher(AES, IV);
}

void teardown(void) {
  free(DST);
  destroy_cbc_cipher(CBC);
  cipher_destroy(AES);
}

START_TEST(encrypt) {
  uint8_t src[PLAIN_LEN] = PLAIN;
  uint8_t want[PLAIN_LEN] = CIPHER;

  bool ok = cbc_encrypt(CBC, src, sizeof(src), DST);

  ck_assert_int_eq(ok, true);
  ck_assert_mem_eq(want, DST, sizeof(want));
}

END_TEST

START_TEST(encrypt_bad_blocksize) {
  uint8_t src[PLAIN_LEN] = PLAIN;

  bool ok = cbc_encrypt(CBC, src, sizeof(src) - 1, DST);

  ck_assert_int_eq(ok, false);
}

END_TEST

START_TEST(decrypt) {
  uint8_t src[PLAIN_LEN] = CIPHER;
  uint8_t want[PLAIN_LEN] = PLAIN;

  bool ok = cbc_decrypt(CBC, src, sizeof(src), DST);

  ck_assert_int_eq(ok, true);
  ck_assert_mem_eq(want, DST, sizeof(want));
}

END_TEST

START_TEST(decrypt_bad_blocksize) {
  uint8_t src[PLAIN_LEN] = CIPHER;

  bool ok = cbc_decrypt(CBC, src, sizeof(src) - 1, DST);

  ck_assert_int_eq(ok, false);
}

END_TEST

Suite* cbc_suite(void) {
  Suite* s;
  TCase* tc_core;
  TCase* tc_limits;

  s = suite_create("cbc");
  tc_core = tcase_create("Core");
  tcase_add_checked_fixture(tc_core, setup, teardown);

  tcase_add_test(tc_core, encrypt);
  tcase_add_test(tc_core, encrypt_bad_blocksize);
  tcase_add_test(tc_core, decrypt);
  tcase_add_test(tc_core, decrypt_bad_blocksize);

  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  int number_failed;
  Suite* s;
  SRunner* sr;

  s = cbc_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}