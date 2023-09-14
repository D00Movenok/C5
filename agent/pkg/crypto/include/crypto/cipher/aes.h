#pragma once

#include <stdint.h> /* uint8_t */

#include "crypto/cipher/common.h"

#define AES256
#define Nb 4
#define AES_BLOCKSIZE 16

#if defined(AES256)
#  define Nk 8
#  define Nr 14
#  define AES_KEYLEN 32
#  define AES_keyExpSize 240
#elif defined(AES192)
#  define Nk 6
#  define Nr 12
#  define AES_KEYLEN 24
#  define AES_keyExpSize 208
#else
#  define Nk 4               /* The number of 32 bit words in a key. */
#  define Nr 10              /* The number of rounds in AES Cipher. */
#  define AES_KEYLEN 16      /* Key length in bytes */
#  define AES_keyExpSize 176 /* round_key size */
#endif

struct AES {
  uint8_t round_key[AES_keyExpSize];
};

struct Cipher* new_aes_cipher(const uint8_t* key);
void destroy_aes_cipher(struct AES* cipher);

void aes_encrypt_block(struct AES* cipher, const uint8_t* src, uint8_t* dst);
void aes_decrypt_block(struct AES* cipher, const uint8_t* src, uint8_t* dst);

extern struct CipherVTable AESVTable;
