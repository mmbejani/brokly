#include "function/base.hh"
#include "tensor/Dtype.hh"
#include "tensor/Tensor.hh"
#include <map>
namespace momas::brokly::tensor::autograd {
std::map<NamedTensor, tensor::Tensor<float32> *>
addScalarBackward(std::map<NamedTensor, tensor::Tensor<float32> *> context) {
  return {{BACKPROP, function::ones(context[INPUT]->dimension)}};
}

std::map<NamedTensor, tensor::Tensor<float32> *>
subScalarBackward(std::map<NamedTensor, tensor::Tensor<float32> *> context) {
  return {{BACKPROP, function::ones(context[INPUT]->dimension)}};
}

std::map<NamedTensor, tensor::Tensor<float32> *>
mulScalarBackward(std::map<NamedTensor, tensor::Tensor<float32> *> context) {
  return {{BACKPROP, function::constant(context[INPUT]->dimension,
                                        context[SCALAR]->data[0])}};
}
} // namespace momas::brokly::tensor::autograd