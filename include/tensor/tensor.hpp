#pragma once

#include "tensor/define.h"
#include <memory>
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

class Tensor;

typedef std::shared_ptr<Tensor> TensorPtr;

class Tensor {
public:
  Tensor(const Tensor &) = delete;
  void operator=(const Tensor &) = delete;

  Tensor(std::vector<unsigned int> size, TensorType type = DENSE,
         bool requires_grad = true);

  Tensor operator[](unsigned int &&i) const;
  Tensor operator[](unsigned int &&i, unsigned int &&j) const;
  Tensor operator[](unsigned int &&k, unsigned int &&i, unsigned int &&j) const;
  Tensor operator[](unsigned int &&k, unsigned int &&t, unsigned int &&i,
                    unsigned int &&j) const;

  float32 sum() const;
  float32 mean() const;
  float32 item() const;
  void backward(TensorPtr) const;

  bool requires_grad;
  TensorType type;
  unsigned int size;
  std::vector<unsigned int> dims;
  float32 *data;

private:
  Tensor(const Tensor &tensor, std::vector<unsigned int> subSize);
};

} // namespace momas::brokly::tensor