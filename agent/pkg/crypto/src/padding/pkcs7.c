#include "crypto/padding/pkcs7.h"

#include <stdlib.h> /* realloc */
#include <string.h> /* memset */

void pkcs7_pad(struct binary_string* data, size_t block_size) {
  uint8_t* buffer = data->data;
  size_t len = data->len;

  uint8_t byte_to_pad = block_size - len % block_size;
  size_t new_len = len + byte_to_pad;

  data->data = realloc(buffer, new_len);
  data->len = new_len;

  memset(data->data + len, byte_to_pad, byte_to_pad);
}

bool pkcs7_unpad(struct binary_string* data, size_t block_size) {
  uint8_t* buffer = data->data;
  size_t len = data->len;

  uint8_t byte_to_unpad = buffer[len - 1];
  uint8_t is_padding_good = 1;

  if (byte_to_unpad > block_size) {
    is_padding_good = 0;
  } else {
    for (size_t i = len - byte_to_unpad; i < len; ++i) {
      if (buffer[i] == byte_to_unpad) {
        buffer[i] = 0;
      } else {
        is_padding_good = 0;
        break;
      }
    }
  }

  if (is_padding_good) {
    size_t new_len = len - byte_to_unpad;

    data->data = realloc(buffer, new_len);
    data->len = new_len;

    return true;
  } else {
    return false;
  }
}
