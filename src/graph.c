#include <stdio.h>

#include "list.h"
#include "vector.h"

typedef struct weighted_graph {
  u64 vertex;
  i64 weight;
} wnode;

static inline wnode make_wnode(u64 vertex, i64 weight) {
  return (wnode){vertex, weight};
}

bool make_weighted_connection(bool bidirectional, wnode *node,
                              u64 vertex_source, array_list *adjacency_list) {
  if (bidirectional) {
    wnode rnode = make_wnode(vertex_source, node->weight);
    if (!push_back(&rnode, adjacency_list->list[node->vertex])) {
      return false;
    }
  }
  if (!push_back(node, adjacency_list->list[vertex_source])) {
    return false;
  }
  return true;
}

bool make_connection(bool bidirectional, u64 vertex_source,
                     u64 vertex_destination, array_list *adjacency_list) {
  if (bidirectional) {
    if (!push_back(&vertex_source, adjacency_list->list[vertex_destination])) {
      return false;
    }
  }
  if (!push_back(&vertex_destination, adjacency_list->list[vertex_source])) {
    return false;
  }
  return true;
}

bool dfs(array_list *adjacency_list, u64 vertex_source, bool visited[]) {
  list *stack = init_list(sizeof(u64));
  if (!stack) {
    return false;
  }
  if (push_front(&vertex_source, stack)) {
    return false;
  }
  while (!empty(stack)) {
    u64 *vertex = front(stack);
    pop_front(stack);
    if (visited[*vertex]) {
      continue;
    }
    visited[*vertex] = true;
    for (list_node *cur = adjacency_list->list[*vertex]->list_tail; cur;
         cur = cur->previous) {
      if (!visited[*(u64 *)cur->data]) {
        if (!push_front(cur->data, stack)) {
          return false;
        }
      }
    }
  }
  free_list(stack);
  return true;
}

bool bfs(array_list *adjacency_list, u64 vertex_source, bool visited[]) {
  list *queue = init_list(sizeof(u64));
  if (!queue) {
    return false;
  }
  visited[vertex_source] = true;
  if (!push_back(&vertex_source, queue)) {
    return false;
  }
  while (!empty(queue)) {
    u64 *vertex = front(queue);
    pop_front(queue);
    for (list_node *cur = adjacency_list->list[*vertex]->list_head; cur;
         cur = cur->next) {
      if (!visited[*(u64 *)cur->data]) {
        if (!push_back(cur->data, queue)) {
          return false;
        }
        visited[*(u64 *)cur->data] = true;
      }
    }
  }
  free_list(queue);
  return 1;
}

// void dijkstra(int vertex_source, int distances[], int predecessors[],
//               array_list *adjacency_list) {
// }
int main() {
  float *vector = NULL;
  vector_init(vector, 10);
  vector_insert(vector, 0, 5.4f);
  vector_push_back(vector, 3.4f);
  vector_erase(vector, 0);
  printf("%d", vector_is_empty(vector));
  printf("%f", vector[1]);
  array_list *adjacency_list = init_array(5, sizeof(wnode));
  wnode a = {1, 23};
  if (!make_weighted_connection(true, &a, 0, adjacency_list)) {
    return 1;
  }
  printf(D64, ((wnode *)adjacency_list->list[1]->list_head->data)->weight);
  free_array_list(adjacency_list);
  free_vector(vector);
  return 0;
}
