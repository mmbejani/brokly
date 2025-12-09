#pragma once

typedef struct Vector {
  void *data;
  unsigned int allocated;
  unsigned int size;
} Vector;

Vector *create_vector(unsigned int size);
Vector *push_vector(Vector *, void *data);
__attribute__((always_inline)) void cleanup_vector(Vector *);