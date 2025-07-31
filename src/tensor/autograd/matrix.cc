#include "tensor/Dtype.hh"
#include "tensor/Tensor.hh"
#include "tensor/autograd/matrix.hh"
#include "tensor/autograd/common.hh"

namespace momas::brokly::tensor::autograd {
void matmulBackward(std::map<NamedTensor, Tensor<float32> *> context) {
  Tensor<float32> *input = context[NamedTensor::INPUT];
  Tensor<float32> *weight = context[NamedTensor::WEIGHT];


  return;
}

void addVecBackward(std::map<NamedTensor, Tensor<float32> *> context) {}
} // namespace momas::brokly::tensor::autograd