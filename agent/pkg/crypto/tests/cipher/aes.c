#include <check.h>
#include <stdlib.h> /* malloc, free, EXIT_SUCCESS, EXIT_FAILURE */

#include "crypto/cipher/aes.h" /* new_aes_cipher, AES_KEYLEN, AES_BLOCKSIZE */
#include "crypto/cipher/common.h" /* Cipher, cipher_destroy, cipher_encrypt, cipher_decrypt */

#define PLAIN "0123456789012345"
#define KEY "01234567890123456789012345678901"

#if defined(AES256)
#  define CIPHER \
    "\x5d\x99\x81\x44\xe9\x4f\x14\x46\x5b\x7d\x39\xf4\x3c\xf1\x8a\x57"
#elif defined(AES192)
#  define CIPHER \
    "\x2d\x76\x01\x45\x67\x3e\x42\x59\xde\x72\xee\x5c\x2a\x75\x4a\x67"
#else
#  define CIPHER \
    "\x5f\x7d\xf0\xbf\x10\x3a\x8c\x4a\xe6\xfa\xad\x99\x06\xac\x3b\x2a"
#endif

struct Cipher* AES;
uint8_t* DST;

void setup(void) {
  DST = malloc(AES_BLOCKSIZE);
  AES = new_aes_cipher(KEY);
}

void teardown(void) {
  free(DST);
  cipher_destroy(AES);
}

START_TEST(encrypt) {
  uint8_t src[AES_BLOCKSIZE] = PLAIN;
  uint8_t want[AES_BLOCKSIZE] = CIPHER;

  cipher_encrypt(AES, src, DST);

  ck_assert_mem_eq(want, DST, sizeof(want));
}

END_TEST

START_TEST(decrypt) {
  uint8_t src[AES_BLOCKSIZE] = CIPHER;
  uint8_t want[AES_BLOCKSIZE] = PLAIN;

  cipher_decrypt(AES, src, DST);

  ck_assert_mem_eq(want, DST, sizeof(want));
}

END_TEST

Suite* aes_suite(void) {
  Suite* s;
  TCase* tc_core;
  TCase* tc_limits;

  s = suite_create("aes");
  tc_core = tcase_create("Core");
  tcase_add_checked_fixture(tc_core, setup, teardown);

  tcase_add_test(tc_core, encrypt);
  tcase_add_test(tc_core, decrypt);

  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  int number_failed;
  Suite* s;
  SRunner* sr;

  s = aes_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}