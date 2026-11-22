#include "list.h"

#include <stdlib.h>
#include <string.h>

array_list *init_array(size_t size_of_array, size_t element_size) {
  array_list *array_constructor = malloc(sizeof(array_list));
  if (!array_constructor) {
    return NULL;
  }
  array_constructor->list = malloc(size_of_array * sizeof(list *));
  if (!array_constructor->list) {
    return NULL;
  }
  for (size_t i = 0; i < size_of_array; ++i) {
    array_constructor->list[i] = init_list(element_size);
    if (!array_constructor->list[i]) {
      return NULL;
    }
  }
  array_constructor->size = size_of_array;
  return array_constructor;
}

list *init_list(size_t element_size) {
  list *list_constructor = malloc(sizeof(list));
  if (!list_constructor) {
    return NULL;
  }
  list_constructor->list_head = NULL;
  list_constructor->list_tail = NULL;
  list_constructor->length = 0;
  list_constructor->element_size = element_size;
  return list_constructor;
}

static list_node *constructor(void const *value, size_t element_size) {
  list_node *new_node = malloc(sizeof(list_node));
  if (!new_node) {
    return NULL;
  }
  new_node->data = malloc(element_size);
  if (!new_node->data) {
    free(new_node);
    return NULL;
  }
  memcpy(new_node->data, value, element_size);
  new_node->next = NULL;
  new_node->previous = NULL;
  return new_node;
}

bool push_back(void const *value, list *list) {
  list_node *new_node = constructor(value, list->element_size);
  if (!new_node) {
    return 0;
  }
  new_node->previous = list->list_tail;
  list->length++;

  if (!list->list_head) {
    list->list_head = new_node;
    list->list_tail = new_node;
  } else {
    list->list_tail->next = new_node;
    list->list_tail = new_node;
  }
  return 1;
}

bool push_front(void const *value, list *list) {
  list_node *new_node = constructor(value, list->element_size);
  if (!new_node) {
    return 0;
  }

  new_node->next = list->list_head;
  list->length++;

  if (!list->list_head) {
    list->list_head = new_node;
    list->list_tail = new_node;
  } else {
    list->list_head->previous = new_node;
    list->list_head = new_node;
  }

  return 1;
}

void pop(list *list) {
  if (!list->list_tail) {
    return;
  }
  list->list_tail = list->list_tail->previous;
  if (!list->list_tail) {
    free(list->list_head->data);
    free(list->list_head);
    list->list_head = NULL;

  } else {
    free(list->list_tail->next->data);
    free(list->list_tail->next);
    list->list_tail->next = NULL;
  }
  list->length--;
}

void pop_front(list *list) {
  if (!list->list_head) {
    return;
  }
  list->list_head = list->list_head->next;
  if (!list->list_head) {
    free(list->list_tail->data);
    free(list->list_tail);
    list->list_tail = NULL;
  } else {
    free(list->list_head->previous->data);
    free(list->list_head->previous);
    list->list_head->previous = NULL;
  }
  list->length--;
}

bool empty(list const *list) {
  return !list->length;
}

void *front(list const *list) {
  if (!list->list_head) {
    return NULL;
  }
  return list->list_head->data;
}

void *back(list const *list) {
  if (!list->list_tail) {
    return NULL;
  }
  return list->list_tail->data;
}

bool insert_after(void const *value, size_t const position, list *list) {
  if (position >= list->length) {
    return 0;
  }
  list_node *current = list->list_head;
  size_t current_position = 0;
  while (current_position < position) {
    current = current->next;
    current_position++;
  }
  list_node *new_node = constructor(value, list->element_size);
  if (!new_node) {
    return 0;
  }
  new_node->next = current->next;
  new_node->previous = current;
  if (!current->next) {
    list->list_tail = new_node;
  } else {
    current->next->previous = new_node;
  }
  current->next = new_node;
  list->length++;
  return 1;
}

bool insert_before(void const *value, size_t const position, list *list) {
  if (position >= list->length) {
    return 0;
  }
  list_node *current = list->list_head;
  size_t current_position = 0;
  while (current_position < position) {
    current = current->next;
    current_position++;
  }
  list_node *new_node = constructor(value, list->element_size);

  if (!new_node) {
    return 0;
  }
  new_node->next = current;
  new_node->previous = current->previous;
  if (!current->previous) {
    list->list_head = new_node;
  } else {
    current->previous->next = new_node;
  }
  current->previous = new_node;
  list->length++;
  return 1;
}

bool erase(size_t position, list *list) {
  if (position >= list->length) {
    return 0;
  }
  list_node *current = list->list_head;
  size_t current_position = 0;
  while (current_position < position) {
    current = current->next;
    current_position++;
  }
  if (current->previous) {
    current->previous->next = current->next;
  } else {
    list->list_head = current->next;
  }
  if (current->next) {
    current->next->previous = current->previous;
  } else {
    list->list_tail = current->previous;
  }
  free(current->data);
  free(current);
  list->length--;
  return 1;
}

void free_list(list *list) {
  if (!list) {
    return;
  }
  list_node *current = list->list_head;
  while (current) {
    list_node *next = current->next;
    free(current->data);
    free(current);
    current = next;
  }
  free(list);
}

void free_array_list(array_list *array_list) {
  if (!array_list) {
    return;
  }
  for (size_t i = 0; i < array_list->size; ++i) {
    free_list(array_list->list[i]);
  }
  free(array_list->list);
  free(array_list);
}
