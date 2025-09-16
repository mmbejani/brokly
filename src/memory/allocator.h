#include "stddef.h"
#include "stdint.h"
#include "tensor/tensor.h"

struct Arena {
  uint8_t *base;
  size_t capacity;
  size_t offset;
};

typedef struct {
  void *base;
  size_t capacity;
} TensorAllocator;

Tensor *allocate_resident(TensorAllocator *A, size_t size, int id);
Tensor *allocate_ephemeral(TensorAllocator *A, size_t size, int id);
void free_ephemeral(TensorAllocator *A, int id);
Tensor *get_tensor(TensorAllocator *A, int id);
