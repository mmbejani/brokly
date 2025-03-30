#include "tensor/autograd/activation.hh"
#include "tensor/Dtype.hh"
#include "tensor/Tensor.hh"
#include "tensor/autograd/common.hh"
#include <map>

namespace momas::brokly::tensor::autograd {
std::map<NamedTensor, Tensor<float32> *>
sigmoidBackward(std::map<NamedTensor, Tensor<float32> *> context) {
  auto output = context[OUTPUT];

  auto backprop = new Tensor<float32>(output->dimension);
  for (int i; i < output->dimension.total; i++) {
    backprop->data[i] = output->data[i] * (1 - output->data[i]);
  }
  return {{BACKPROP, backprop}, {GRAD, nullptr}};
}

std::map<NamedTensor, Tensor<float32> *>
tanhBackward(std::map<NamedTensor, Tensor<float32> *> context) {
  auto output = context[OUTPUT];

  auto backprop = new Tensor<float32>(output->dimension);
  for (int i; i < output->dimension.total; i++) {
    backprop->data[i] = (1 - output->data[i] * output->data[i]);
  }
  return {{BACKPROP, backprop}, {GRAD, nullptr}};
}

std::map<NamedTensor, Tensor<float32> *>
reluBackward(std::map<NamedTensor, Tensor<float32> *> context) {
  auto input = context[INPUT];

  auto backprop = new Tensor<float32>(input->dimension);
  for (int i = 0; i < input->dimension.total; i++) {
    backprop->data[i] = input->data[i] > 0 ? 1.0f : 0.05f;
  }
  return {{BACKPROP, backprop}, {GRAD, nullptr}};
}
} // namespace momas::brokly::tensor::autograd