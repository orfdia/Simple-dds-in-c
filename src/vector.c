#include "vector.h"

bool vector_is_empty(void *vector) {
  if (!vector)
    return true;
  return !(vector_hdr(vector)->size);
}
void vector_pop_back(void *vector) {

  if (vector_is_empty(vector)) {
    return;
  }
  vector_hdr(vector)->size--;
}
