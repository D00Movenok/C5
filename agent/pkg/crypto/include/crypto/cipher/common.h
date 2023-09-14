#pragma once

#include <stddef.h> /* size_t */
#include <stdint.h> /* uint8_t */

typedef void* CipherParams;

struct CipherVTable {
  void (*encrypt)(CipherParams cipher, const uint8_t* src, uint8_t* dst);
  void (*decrypt)(CipherParams cipher, const uint8_t* src, uint8_t* dst);
  void (*destroy)(CipherParams cipher);

  size_t block_size;
  size_t key_size;
};

struct Cipher {
  struct CipherVTable* vtable;
  CipherParams params;
};

void cipher_destroy(struct Cipher* cipher);

void cipher_encrypt(struct Cipher* cipher, const uint8_t* src, uint8_t* dst);
void cipher_decrypt(struct Cipher* cipher, const uint8_t* src, uint8_t* dst);

size_t get_cipher_block_size(struct Cipher* cipher);
size_t get_cipher_key_size(struct Cipher* cipher);
