#pragma once

#include <stddef.h> /* size_t */
#include <stdint.h> /* uint8_t */

struct binary_string {
  size_t len;
  uint8_t* data;
};

struct binary_string* new_binary_string(size_t len, uint8_t* data);
void destroy_binary_string(struct binary_string* str);
