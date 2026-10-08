#include "backend/base.h"
#include "function/basic.hpp"
#include "tensor/tensor.hpp"
#include <cstring>

namespace momas::brokly::tensor {

float32 Tensor::sum() const { return sum_reduce_vec(this->data, this->size); }
float32 Tensor::mean() const { return this->sum() / this->size; }
float32 Tensor::item() const { return this->data[0]; }

Tensor *Tensor::add(Tensor *input) {
  auto output =
      Tensor::zeros(input->dims, TensorType::DENSE, TensorAllocMode::EPHEMERAL);
  function::add(this, input, output);
  return output;
}

} // namespace momas::brokly::tensor