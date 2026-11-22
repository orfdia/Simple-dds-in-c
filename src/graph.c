#include <stdint.h>
#include <stdio.h>

#include "list.h"

#define true 1
#define false 0

typedef struct weighted_graph {
  int vertex;
  int weight;
} wnode;

static wnode make_wnode(int vertex, int weight) {
  return (wnode){vertex, weight};
}

void make_weighted_connection(uint8_t bidirectional, wnode *node,
                              int vertex_source, array_list *adjacency_list) {
  if (bidirectional) {
    wnode rnode = make_wnode(vertex_source, node->weight);
    push_back(&rnode, adjacency_list->list[node->vertex]);
  }
  push_back(node, adjacency_list->list[vertex_source]);
}

void make_connection(uint8_t bidirectional, int vertex_source,
                     int vertex_destination, list **adjacency_list) {
  if (bidirectional) {
    push_back(&vertex_source, adjacency_list[vertex_destination]);
  }
  push_back(&vertex_destination, adjacency_list[vertex_source]);
}

void dfs(list **adjacency_list, int vertex_source, uint8_t visited[]) {
  list *stack = init_list(sizeof(int));
  push_front(&vertex_source, stack);
  while (!empty(stack)) {
    int *vertex = front(stack);
    pop_front(stack);
    if (visited[*vertex]) {
      continue;
    }
    visited[*vertex] = true;
    for (list_node *cur = adjacency_list[*vertex]->list_tail; cur;
         cur = cur->previous) {
      if (!visited[*(int *)cur->data]) {
        push_front(cur->data, stack);
      }
    }
  }
  free_list(stack);
}

void bfs(list **adjacency_list, int vertex_source, uint8_t visited[]) {
  list *queue = init_list(sizeof(int));
  visited[vertex_source] = true;
  push_back(&vertex_source, queue);
  while (!empty(queue)) {
    int *vertex = front(queue);
    pop_front(queue);
    for (list_node *cur = adjacency_list[*vertex]->list_head; cur;
         cur = cur->next) {
      if (!visited[*(int *)cur->data]) {
        push_back(cur->data, queue);
        visited[*(int *)cur->data] = true;
      }
    }
  }
  free_list(queue);
}

// void dijkstra(int vertex_source, int distances[], int predecessors[],
//              list **adjacency_list) {}

int main() {
  array_list *adjacency_list = init_array(5, sizeof(wnode));
  wnode a = {1, 23};
  make_weighted_connection(1, &a, 0, adjacency_list);
  printf("%d", ((wnode *)adjacency_list->list[1]->list_head->data)->weight);
  free_array_list(adjacency_list);
  return 0;
}
