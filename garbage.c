#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CONNECTIONS 10

/* Reference count (ref_count) = p(v) */
struct Node {
  char *name;
  bool is_root;
  int ref_count; 
  struct Node *points_to[MAX_CONNECTIONS];
  size_t n_points_to;
  struct Node *pointed_by[MAX_CONNECTIONS];
  size_t n_pointed_by;
};

struct Node *create_node(char *name, bool is_root) {
  struct Node *new = malloc(sizeof(struct Node));

  new->name = name;
  new->is_root = is_root;
  new->ref_count = 0;
  new->n_points_to = 0;
  new->n_pointed_by = 0;

  return new;
}

void new_connection(struct Node *from, struct Node *to) {
  if (from->n_points_to < MAX_CONNECTIONS &&
      to->n_pointed_by < MAX_CONNECTIONS) {
    from->points_to[from->n_points_to++] = to;
    to->pointed_by[to->n_pointed_by++] = from;
  }
}

/* p(v) will print 0 if it's a dead object and >0 if not. */
void print_node_info(struct Node *node) {
  printf("Node %s\n", node->name);
  printf("Is root? %s\n", node->is_root ? "Yes" : "No");
  printf("p(%s): %d\n", node->name, node->ref_count);

  printf("Points to: ");
  if (node->n_points_to == 0) {
    printf("no connections :(");
  } else {
    for (size_t i = 0; i < node->n_points_to; i++) {
      printf("(%s) ", node->points_to[i]->name);
    }
  }
  printf("\n");
  
  printf("Pointed by: ");
  if (node->n_pointed_by == 0) {
    printf("no connections :(");
  } else {
    for (size_t i = 0; i < node->n_pointed_by; i++) {
      printf("(%s) ", node->pointed_by[i]->name);
    }
  }
  printf("\n\n");
}

void calculate_ref_count(struct Node *node) {
  node->ref_count = (node->is_root ? 1 : 0) + node->n_pointed_by;
}

int main() {

  struct Node *A = create_node("A", true);
  struct Node *B = create_node("B", false);
  struct Node *C = create_node("C", false);
  struct Node *D = create_node("D", false);

  new_connection(A, B);
  new_connection(B, C);
  new_connection(B, A);

  calculate_ref_count(A);
  calculate_ref_count(B);
  calculate_ref_count(C);
  calculate_ref_count(D);

  print_node_info(A);
  print_node_info(B);
  print_node_info(C);
  print_node_info(D);

  free(D);
  free(C);
  free(B);
  free(A);

  return 0;
}
