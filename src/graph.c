#include <stdint.h>
#include <stdio.h>

#include "list.h"

typedef struct weighted_graph {
  int vertex;
  int weight;
} wnode;

static wnode make_wnode(int vertex, int weight) {
  return (wnode){vertex, weight};
}

bool make_weighted_connection(bool bidirectional, wnode *node,
                              int vertex_source, array_list *adjacency_list) {
  if (bidirectional) {
    wnode rnode = make_wnode(vertex_source, node->weight);
    if (!push_back(&rnode, adjacency_list->list[node->vertex])) {
      return 0;
    }
  }
  if (!push_back(node, adjacency_list->list[vertex_source])) {
    return 0;
  }
  return 1;
}

bool make_connection(bool bidirectional, int vertex_source,
                     int vertex_destination, array_list *adjacency_list) {
  if (bidirectional) {
    if (!push_back(&vertex_source, adjacency_list->list[vertex_destination])) {
      return 0;
    }
  }
  if (!push_back(&vertex_destination, adjacency_list->list[vertex_source])) {
    return 0;
  }
  return 1;
}

bool dfs(array_list *adjacency_list, int vertex_source, bool visited[]) {
  list *stack = init_list(sizeof(int));
  if (!stack) {
    return 0;
  }
  if (push_front(&vertex_source, stack)) {
    return 0;
  }
  while (!empty(stack)) {
    int *vertex = front(stack);
    pop_front(stack);
    if (visited[*vertex]) {
      continue;
    }
    visited[*vertex] = true;
    for (list_node *cur = adjacency_list->list[*vertex]->list_tail; cur;
         cur = cur->previous) {
      if (!visited[*(int *)cur->data]) {
        if (!push_front(cur->data, stack)) {
          return 0;
        }
      }
    }
  }
  free_list(stack);
  return 1;
}

bool bfs(array_list *adjacency_list, int vertex_source, bool visited[]) {
  list *queue = init_list(sizeof(int));
  if (!queue) {
    return 0;
  }
  visited[vertex_source] = true;
  if (!push_back(&vertex_source, queue)) {
    return 0;
  }
  while (!empty(queue)) {
    int *vertex = front(queue);
    pop_front(queue);
    for (list_node *cur = adjacency_list->list[*vertex]->list_head; cur;
         cur = cur->next) {
      if (!visited[*(int *)cur->data]) {
        if (!push_back(cur->data, queue)) {
          return 0;
        }
        visited[*(int *)cur->data] = true;
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
  array_list *adjacency_list = init_array(5, sizeof(wnode));
  wnode a = {1, 23};
  if (!make_weighted_connection(true, &a, 0, adjacency_list)) {
    return 1;
  }
  printf("%d", ((wnode *)adjacency_list->list[1]->list_head->data)->weight);
  free_array_list(adjacency_list);
  return 0;
}
