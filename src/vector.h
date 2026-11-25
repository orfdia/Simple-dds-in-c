#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define same_type(a, b)                                                       \
  _Generic((typeof((a)) *)0, typeof((b)) *: 1, default: 0)

#define is_int(SIZE) ((typeof((SIZE)))1 / 2 == 0)

typedef struct {
  alignas(max_align_t) size_t max_capacity;
  size_t size;
} header;

#define vector_hdr(vector) (((header *)(vector)) - 1)

#define vector_max_size(vector)                                               \
  ((SIZE_MAX - sizeof(header)) / sizeof(*(vector)))

#define vector_init(vector, SIZE)                                             \
  do {                                                                        \
    if (!is_int(SIZE)) {                                                      \
      fprintf(stderr, "Vector non int initialiazation size\n");               \
      (vector) = NULL;                                                        \
      break;                                                                  \
    }                                                                         \
    typeof((SIZE)) vector_size__ = (SIZE);                                    \
    size_t vector_size_limit__ = vector_max_size((vector));                   \
    if ((vector_size__) < 1) {                                                \
      fprintf(stderr, "Vector initialiazation size smaller than 1\n");        \
      (vector) = NULL;                                                        \
      break;                                                                  \
    }                                                                         \
    if ((uintmax_t)vector_size__ > vector_size_limit__) {                     \
      fprintf(stderr, "Vector initialization size too large\n");              \
      (vector) = NULL;                                                        \
      break;                                                                  \
    }                                                                         \
    header *vector_header__ =                                                 \
        malloc(sizeof(header) + sizeof(*(vector)) * (size_t)vector_size__);   \
    if (!vector_header__) {                                                   \
      (vector) = NULL;                                                        \
      fprintf(stderr, "Vector could not be initialiazed\n");                  \
      break;                                                                  \
    }                                                                         \
    vector_header__->max_capacity = (size_t)vector_size__;                    \
    vector_header__->size = 0;                                                \
    (vector) = (void *)(vector_header__ + 1);                                 \
  } while (0)

#define vector_grow__(vector, ok)                                             \
  do {                                                                        \
    size_t current_capacity__ = vector_hdr(vector)->max_capacity;             \
    size_t max_size__ = vector_max_size(vector);                              \
    (ok) = false;                                                             \
    if (current_capacity__ > max_size__ - (current_capacity__ / 2 + 1)) {     \
      fprintf(stderr, "Vector exceeds size max\n");                           \
      break;                                                                  \
    }                                                                         \
    size_t new_capacity__ = current_capacity__ + current_capacity__ / 2 + 1;  \
    header *vector_header__ =                                                 \
        realloc(vector_hdr(vector),                                           \
                sizeof(header) + sizeof(*(vector)) * new_capacity__);         \
    if (!vector_header__) {                                                   \
      fprintf(stderr, "Vector insertion failed\n");                           \
      break;                                                                  \
    }                                                                         \
    vector_header__->max_capacity = new_capacity__;                           \
    (vector) = (void *)(vector_header__ + 1);                                 \
    (ok) = true;                                                              \
  } while (0)

#define vector_push_back(vector, ...)                                         \
  do {                                                                        \
    static_assert(same_type(*(vector), ((void)0, (__VA_ARGS__))),             \
                  "Vector value error: Incompatible types");                  \
    if (!(vector)) {                                                          \
      fprintf(stderr, "Uninitialized vector\n");                              \
      break;                                                                  \
    }                                                                         \
    typeof(*(vector)) vector_value__ = (__VA_ARGS__);                         \
    if (vector_hdr(vector)->size == vector_hdr(vector)->max_capacity) {       \
      bool vector_ok__;                                                       \
      vector_grow__(vector, vector_ok__);                                     \
      if (!vector_ok__) {                                                     \
        break;                                                                \
      }                                                                       \
    }                                                                         \
    (vector)[vector_hdr(vector)->size++] = vector_value__;                    \
  } while (0)

#define vector_insert(vector, position, ...)                                  \
  do {                                                                        \
    static_assert(same_type(*(vector), ((void)0, (__VA_ARGS__))),             \
                  "Vector value error: Incompatible types");                  \
    static_assert(is_int(position), "Vector position should be an integer");  \
    if (!(vector)) {                                                          \
      fprintf(stderr, "Uninitialized vector\n");                              \
      break;                                                                  \
    }                                                                         \
    typeof(*(vector)) vector_value__ = (__VA_ARGS__);                         \
    typeof(position) vector_pos__ = (position);                               \
    if (vector_pos__ != 0 && vector_pos__ < 1) {                              \
      fprintf(stderr, "Vector position should be larger or equal to 0\n");    \
      break;                                                                  \
    }                                                                         \
    if ((uintmax_t)vector_pos__ > vector_hdr(vector)->size) {                 \
      fprintf(stderr, "Vector position should not exceed size of vector\n");  \
      break;                                                                  \
    }                                                                         \
    if (vector_hdr(vector)->size == vector_hdr(vector)->max_capacity) {       \
      bool vector_ok__;                                                       \
      vector_grow__(vector, vector_ok__);                                     \
      if (!vector_ok__)                                                       \
        break;                                                                \
    }                                                                         \
    size_t vector_i__ = (size_t)vector_pos__;                                 \
    memmove(&(vector)[vector_i__ + 1], &(vector)[vector_i__],                 \
            (vector_hdr(vector)->size - vector_i__) * sizeof(*(vector)));     \
    (vector)[vector_i__] = vector_value__;                                    \
    vector_hdr(vector)->size++;                                               \
  } while (0)

#define free_vector(vector)                                                   \
  do {                                                                        \
    if ((vector))                                                             \
      free(vector_hdr(vector));                                               \
    (vector) = NULL;                                                          \
  } while (0)

bool vector_is_empty(void *vector);
void vector_pop_back(void *vector);

#define vector_erase(vector, position)                                        \
  do {                                                                        \
    static_assert(is_int(position), "Vector position should be an integer");  \
    if (!(vector)) {                                                          \
      fprintf(stderr, "Uninitialized vector\n");                              \
      break;                                                                  \
    }                                                                         \
    typeof(position) vector_pos__ = (position);                               \
    if (vector_pos__ != 0 && vector_pos__ < 1) {                              \
      fprintf(stderr, "Vector position should be larger or equal to 0\n");    \
      break;                                                                  \
    }                                                                         \
    if ((uintmax_t)vector_pos__ >= vector_hdr(vector)->size) {                \
      fprintf(stderr, "Vector position should not exceed size of vector\n");  \
      break;                                                                  \
    }                                                                         \
    size_t vector_i__ = (size_t)vector_pos__;                                 \
    memmove(&(vector)[vector_i__], &(vector)[vector_i__ + 1],                 \
            (vector_hdr(vector)->size - vector_i__ - 1) * sizeof(*(vector))); \
    vector_hdr(vector)->size--;                                               \
  } while (0)

#endif
