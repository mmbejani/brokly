#include "function/scalar.hh"
#include "function/base.hh"
#include "tensor/Dtype.hh"
#include "tensor/Tensor.hh"
#include "tensor/autograd/scalar.hh"
namespace momas::brokly::function::scalar {
tensor::Tensor<tensor::float32> *add(tensor::Tensor<tensor::float32> &input,
                                     tensor::float32 scalar) {
  auto *output = new tensor::Tensor<tensor::float32>(
      input.dimension, true, &tensor::autograd::addScalarBackward);
  for (size_t i = 0; i < input.dimension.total; ++i) {
    output->data[i] = input.data[i] + scalar;
  }
  output->forwardHooks.insert({
      tensor::autograd::NamedTensor::INPUT,
      &input,
  });
  return output;
}

tensor::Tensor<tensor::float32> *sub(tensor::Tensor<tensor::float32> &input,
                                     tensor::float32 scalar) {
  auto *output = new tensor::Tensor<tensor::float32>(
      input.dimension, true, &tensor::autograd::subScalarBackward);
  for (size_t i = 0; i < input.dimension.total; ++i) {
    output->data[i] = input.data[i] - scalar;
  }
  output->forwardHooks.insert({
      tensor::autograd::NamedTensor::INPUT,
      &input,
  });
  return output;
}

tensor::Tensor<tensor::float32> *mul(tensor::Tensor<tensor::float32> &input,
                                     tensor::float32 scalar) {
  auto *output = new tensor::Tensor<tensor::float32>(
      input.dimension, true, &tensor::autograd::mulScalarBackward);
  for (size_t i = 0; i < input.dimension.total; ++i) {
    output->data[i] = input.data[i] * scalar;
  }
  output->forwardHooks.insert({
      tensor::autograd::NamedTensor::INPUT,
      &input,
  });

  output->forwardHooks.insert({
      tensor::autograd::NamedTensor::SCALAR,
      base::constant(tensor::dim4(1, 1, 1, 1), scalar),
  });
  return output;
}
} // namespace momas::brokly::function