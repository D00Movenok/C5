#include "binary_string.h"

#include <stdlib.h> /* malloc, free */
#include <string.h> /* memset */

struct binary_string* new_binary_string(size_t len, uint8_t* data) {
  struct binary_string* result = malloc(sizeof(struct binary_string));

  result->data = malloc(len);
  result->len = len;

  if (data == NULL) {
    memset(result->data, 0, len);
  } else {
    memcpy(result->data, data, len);
  }

  return result;
}

void destroy_binary_string(struct binary_string* str) {
  if (str == NULL) {
    return;
  }

  free(str->data);
  free(str);
}
