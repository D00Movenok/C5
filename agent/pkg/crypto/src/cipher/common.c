#include "crypto/cipher/common.h"

#include <stdlib.h> /* free */

void cipher_destroy(struct Cipher* cipher) {
  if (cipher == NULL) {
    return;
  }

  cipher->vtable->destroy(cipher->params);

  cipher->params = NULL;
  cipher->vtable = NULL;

  free(cipher);
}

void cipher_encrypt(struct Cipher* cipher, const uint8_t* src, uint8_t* dst) {
  cipher->vtable->encrypt(cipher->params, src, dst);
}

void cipher_decrypt(struct Cipher* cipher, const uint8_t* src, uint8_t* dst) {
  cipher->vtable->decrypt(cipher->params, src, dst);
}

size_t get_cipher_block_size(struct Cipher* cipher) {
  return cipher->vtable->block_size;
}

size_t get_cipher_key_size(struct Cipher* cipher) {
  return cipher->vtable->key_size;
}
