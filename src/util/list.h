#pragma once
#include <stddef.h>

#include "tensor/fp32/tensor.h"

typedef struct TensorNode {
  struct TensorNode *right_nieghbor, *left_nieghbor;
  Tensor *tensor;
} TensorNode;

typedef struct TensorList {
  TensorNode *root;
  size_t size;
} TensorList;

TensorList *list_create();
void list_destroy(TensorList *lit);
void list_append(TensorList *list, Tensor *tensor);
void list_insert(TensorList *list, Tensor *tensor, const int index);
Tensor *list_get(TensorList *list, const int index);
int list_remove(TensorList *list, const int index);
void list_clear(TensorList *list);