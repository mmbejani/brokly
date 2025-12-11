#include "backend/base.h"
#include "tensor/tensor.hpp"

namespace momas::brokly::tensor {
float32 Tensor::sum() const { return sum_reduce_vec(this->data, this->size); }
float32 Tensor::mean() const { return this->sum() / this->size; }
float32 Tensor::item() const { return this->data[0]; }
} // namespace momas::brokly::tensor