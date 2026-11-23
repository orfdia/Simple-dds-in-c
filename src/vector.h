#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define same_type(a, b)                                                       \
  _Generic((typeof((a)) *)0, typeof((b)) *: 1, default: 0)

#define is_int(SIZE) ((typeof((SIZE)))1 / 2 == 0)

typedef struct {
  alignas(max_align_t) size_t max_capacity;
  size_t size;
} header;

#define vector_hdr(vector) (((header *)(vector)) - 1)

#define vector_init(vector, SIZE)                                             \
  do {                                                                        \
    static_assert(is_int(SIZE), "Vector non int initialiazation size");       \
    static_assert(SIZE > 0, "Vector initialiazation size smaller than 1");    \
    header *vector_header =                                                   \
        malloc(sizeof(header) + sizeof(*(vector)) * (SIZE));                  \
    if (!vector_header)                                                       \
      (vector) = NULL;                                                        \
    vector_header->max_capacity = (SIZE);                                     \
    vector_header->size = 0;                                                  \
    (vector) = (void *)(vector_header + 1);                                   \
  } while (0)

#define vector_push_back(vector, value)                                       \
  do {                                                                        \
    static_assert(same_type(*(vector), (value)),                              \
                  "Vector value error\n Incopatible types");                  \
    typeof(*(vector)) value_val = (value);                                    \
    if (vector_hdr(vector)->size == (vector_hdr(vector)->max_capacity)) {     \
      size_t initial_size = vector_hdr(vector)->size;                         \
      size_t new_capacity =                                                   \
          (sizeof(*(vector)) * (vector_hdr(vector)->max_capacity)) * 3 / 2 +  \
          1 + sizeof(header);                                                 \
      header *vector_header = realloc(vector_hdr(vector), new_capacity);      \
      if (!vector_header)                                                     \
        (vector) = NULL;                                                      \
      vector_header->max_capacity = new_capacity;                             \
      vector_header->size = initial_size;                                     \
      (vector) = (void *)(vector_header + 1);                                 \
      (vector)[vector_hdr(vector)->size++] = value_val;                       \
    } else {                                                                  \
      (vector)[vector_hdr(vector)->size++] = value_val;                       \
    }                                                                         \
  } while (0)

#define free_vector(vector)                                                   \
  do {                                                                        \
    if ((vector))                                                             \
      free(vector_hdr(vector));                                               \
    (vector) = NULL;                                                          \
  } while (0)

bool vector_is_empty(void *vector);
void vector_pop_back(void *vector);

#endif
