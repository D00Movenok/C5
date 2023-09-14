#include "crypto/modes/cbc.h"

#include <stdlib.h> /* malloc, free */
#include <string.h> /* memset */

#include "crypto/cipher/common.h"

// clang-format off
void xor(const uint8_t* src1, const uint8_t* src2, size_t len, uint8_t* dst) {
  for (size_t i = 0; i < len; ++i) {
    dst[i] = src1[i] ^ src2[i];
  }
}

struct CBCCipher* new_cbc_cipher(struct Cipher* cipher, const uint8_t* iv) {
  struct CBCCipher* cbc = malloc(sizeof(struct CBCCipher));

  size_t iv_size = get_cipher_block_size(cipher);

  cbc->cipher = cipher;
  cbc->iv = malloc(iv_size);

  memcpy(cbc->iv, iv, iv_size);

  return cbc;
}

// clang-format on

void destroy_cbc_cipher(struct CBCCipher* cbc) {
  if (cbc == NULL) {
    return;
  }

  memset(cbc->iv, 0, get_cipher_block_size(cbc->cipher));
  free(cbc->iv);

  cbc->cipher = NULL;
  cbc->iv = NULL;

  free(cbc);
}

bool cbc_encrypt(struct CBCCipher* cbc, const uint8_t* src, size_t len,
                 uint8_t* dst) {
  size_t block_size = get_cipher_block_size(cbc->cipher);

  if (len % block_size != 0) {
    return false;
  }

  uint8_t* src_curr = src;
  uint8_t* dst_curr = dst;

  uint8_t* src_end = src + len;
  uint8_t* dst_end = dst + len;

  while (src_curr < src_end) {
    if (src_curr == src) {
      xor(cbc->iv, src_curr, block_size, dst_curr);
    } else {
      xor(dst_curr - block_size, src_curr, block_size, dst_curr);
    }

    cipher_encrypt(cbc->cipher, dst_curr, dst_curr);

    src_curr += block_size;
    dst_curr += block_size;
  }

  return true;
}

bool cbc_decrypt(struct CBCCipher* cbc, const uint8_t* src, size_t len,
                 uint8_t* dst) {
  size_t block_size = get_cipher_block_size(cbc->cipher);

  if (len % block_size != 0) {
    return false;
  }

  uint8_t* src_curr = src + len - block_size;
  uint8_t* dst_curr = dst + len - block_size;

  while (src_curr >= src) {
    cipher_decrypt(cbc->cipher, src_curr, dst_curr);

    if (src_curr == src) {
      xor(cbc->iv, dst_curr, block_size, dst_curr);
    } else {
      xor(src_curr - block_size, dst_curr, block_size, dst_curr);
    }

    src_curr -= block_size;
    dst_curr -= block_size;
  }

  return true;
}
