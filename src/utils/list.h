#pragma once
#include <stddef.h>

struct Tensor;

typedef struct Node {
  struct Node *right_nieghbor, *left_nieghbor;
} Node;

typedef struct List {
  Node *head;
  Node *tail;
  size_t size;
} List;

List *list_create();
void list_destroy(List *list);
Node *list_appned(List *list);
Node *list_multi_append(List *list, const int num);
Node *list_insert(List *list, const int index);
Node *list_get(List *list, const int index);
int list_remove(List *list, const int index);
void list_clear(List *list);