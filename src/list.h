#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdint.h>

typedef struct link_list_node {
  void *data;
  struct link_list_node *next;
  struct link_list_node *previous;
} list_node;

typedef struct link_list {
  struct link_list_node *list_head;
  struct link_list_node *list_tail;
  size_t length;
  size_t element_size;
} list;

typedef struct array_list {
  size_t size;
  list **list;
} array_list;

array_list *init_array(size_t size_of_array, size_t element_size);
list *init_list(size_t element_size);
uint8_t push_back(void const *value, list *list);
uint8_t push_front(void const *value, list *list);
void pop(list *list);
void pop_front(list *list);
uint8_t empty(list const *list);
void *front(list const *list);
void *back(list const *list);
uint8_t insert_after(void const *value, size_t position, list *list);
uint8_t insert_before(void const *value, size_t position, list *list);
uint8_t erase(size_t position, list *list);
void free_list(list *list);
void free_array_list(array_list *array_list);
#endif // !LIST_H
