#include "tensor/autograd/matrix.hh"
#include "tensor/Tensor.hh"
#include "tensor/autograd/common.hh"

namespace momas::brokly::tensor::autograd {
void matmulBackward(std::map<NamedTensor, Tensor<float32> *> context) {
  Tensor<float32> *input = context[NamedTensor::INPUT];
  Tensor<float32> *weight = context[NamedTensor::WEIGHT];
  input->forward_hooks_count--;
  weight->forward_hooks_count--;

  if (input->grad == nullptr) {
  }

  if (weight->grad == nullptr) {

  }

  if (input->forward_hooks_count == 0 && input->requires_grad)
    input->backward();
  if (weight->forward_hooks_count == 0 && weight->requires_grad)
    weight->backward();
  return;
}

void addVecBackward(std::map<NamedTensor, Tensor<float32> *> context) {}
} // namespace momas::brokly::tensor::autograd