#pragma once
#include <map>

#include "tensor/Dtype.hh"
#include "tensor/autograd/common.hh"

namespace momas::brokly::tensor {
template <typename T> class Tensor;

namespace autograd {
struct GradFunctor {
  GradFunctor() = default;
  virtual void
  operator()(const std::map<NamedTensor, Tensor<float32>*>& context) const noexcept = 0;
};
} // namespace autograd
} // namespace momas::brokly::tensor