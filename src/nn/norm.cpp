#include "nn/norm.hpp"
#include "tensor/tensor.hpp"

namespace momas::brokly::nn {

BatchNorm::BatchNorm(unsigned int feature_size) {
  this->mean = tensor::Tensor::zeros(tensor::TensorAllocMode::RESIDENT);
  this->variance = tensor::Tensor::zeros(tensor::TensorAllocMode::RESIDENT);
}

} // namespace momas::brokly::nn