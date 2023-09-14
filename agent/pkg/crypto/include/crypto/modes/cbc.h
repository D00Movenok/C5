#pragma once

#include <stdbool.h> /* bool */
#include <stdint.h>  /* uint8_t */

#include "crypto/cipher/common.h"

struct CBCCipher {
  struct Cipher* cipher;
  uint8_t* iv;
};

struct CBCCipher* new_cbc_cipher(struct Cipher* cipher, const uint8_t* iv);
void destroy_cbc_cipher(struct CBCCipher* cbc);

bool cbc_encrypt(struct CBCCipher* cbc, const uint8_t* src, size_t len,
                 uint8_t* dst);
bool cbc_decrypt(struct CBCCipher* cbc, const uint8_t* src, size_t len,
                 uint8_t* dst);
