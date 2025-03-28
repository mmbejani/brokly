
#include "function/activation.hh"
#include "tensor/Dtype.hh"
#include "tensor/Tensor.hh"
#include "tensor/autograd/Common.hh"
#include "tensor/autograd/activation.hh"
#include <cmath>
#include <cstddef>
namespace momas::brokly::function {
tensor::Tensor<tensor::float32> *
sigmoid(tensor::Tensor<tensor::float32> &&input) {
  auto output = new tensor::Tensor<tensor::float32>(
      input.dimension, true, &tensor::autograd::sigmoidBackward);
  for (size_t i = 0; i < input.dimension.total; i++) {
    output->data[i] = 1.0f / (1 + std::exp(-input.data[i]));
  }
  output->forwardHooks[tensor::autograd::OUTPUT] = output;
  return output;
}

tensor::Tensor<tensor::float32> *tanh(tensor::Tensor<tensor::float32> &&input) {
  auto output = new tensor::Tensor<tensor::float32>(
      input.dimension, true, &tensor::autograd::tanhBackward);
  for (size_t i = 0; i < input.dimension.total; i++) {
    output->data[i] = std::tanh(input.data[i]);
  }
  output->forwardHooks[tensor::autograd::OUTPUT] = output;
  return output;
}

tensor::Tensor<tensor::float32> *relu(tensor::Tensor<tensor::float32> &&input) {
  auto output = new tensor::Tensor<tensor::float32>(
      input.dimension, true, &tensor::autograd::reluBackward);
  for (size_t i = 0; i < input.dimension.total; i++) {
    output->data[i] = std::max(0.0f, input.data[i]);
  }
  output->forwardHooks[tensor::autograd::INPUT] = &input;
  return output;
}
} // namespace momas::brokly::function