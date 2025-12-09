#include "utils/vector.h"
#include <stdlib.h>
#include <string.h>

Vector *create_vector(unsigned int size) {
  Vector *vector = malloc(sizeof(Vector));
  vector->size = size;
  vector->allocated = 0;
  vector->data = malloc(sizeof(size));
  return vector;
}

void cleanup_vector(Vector *vector) { free(vector); }

Vector *push_vector(Vector *vector, void *data) {
  if (vector->size == vector->allocated) {
    Vector *extended_vector = create_vector(vector->size * 2);
    memcpy(extended_vector->data, vector->data, sizeof(void *) * vector->size);
    extended_vector->allocated = vector->allocated;
    
    vector = extended_vector;
  } 

  return vector;
}