#pragma once

#include <stdbool.h> /* bool */
#include <stddef.h>  /* size_t */
#include <stdint.h>  /* uint8_t */

#include "binary_string.h" /* binary_string */

void pkcs7_pad(struct binary_string* data, size_t block_size);
bool pkcs7_unpad(struct binary_string* data, size_t block_size);
