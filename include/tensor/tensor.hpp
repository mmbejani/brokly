#pragma once

#include "tensor/define.h"
#include <stdalign.h>
#include <stdbool.h>
#include <vector>

namespace momas::brokly::tensor {

enum TensorType {
  DENSE,
  ZEROS,
  ONES,
  DIAG,
  EYE,
  DIAG_BLOCK_EYES,
  BLOCK,
};

enum TensorAllocMode { RESIDENT, EPHEMERAL };

class Tensor {
public:
  Tensor(const Tensor &) = delete;
  void operator=(const Tensor &) = delete;

  Tensor(std::vector<unsigned int> size, TensorType type = DENSE,
         bool requires_grad = true, TensorAllocMode allocationMode = RESIDENT);
  ~Tensor(); // Destructor to free allocated data

  Tensor operator[](unsigned int &&i) const;
  Tensor operator[](unsigned int &&i, unsigned int &&j) const;
  Tensor operator[](unsigned int &&k, unsigned int &&i, unsigned int &&j) const;
  Tensor operator[](unsigned int &&k, unsigned int &&t, unsigned int &&i,
                    unsigned int &&j) const;

  void addInplace(Tensor *input);
  Tensor *add(Tensor *input) const;

  void subInplace(Tensor *input);
  Tensor *sub(Tensor *input) const;

  void mulInplace(float32 scalar);
  Tensor *mul(float32 scalar);

  float32 sum() const;
  float32 mean() const;
  float32 item() const;
  static Tensor *ones(TensorAllocMode allocMode);
  static Tensor *zeros(TensorAllocMode allocMode);
  static Tensor *rand(TensorAllocMode allocMode);
  void backward(Tensor *) const;

  bool requires_grad;
  TensorType type;
  TensorAllocMode allocationMode;
  unsigned int size;
  std::vector<unsigned int> dims;
  float32 *data;
  Tensor *grad;
  std::vector<Tensor *> forward_hooks, backward_hooks;

private:
  Tensor(const Tensor &tensor, std::vector<unsigned int> subSize);
};

} // namespace momas::brokly::tensor