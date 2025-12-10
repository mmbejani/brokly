#include "backend/vec.h"
#include "tensor/tensor.hpp"

namespace momas::brokly::tensor {
float32 Tensor::sum() const { return sum_reduce_vec(this->data, this->size); }
float32 Tensor::mean() const { return this->sum() / this->size; }
} // namespace momas::brokly::tensor