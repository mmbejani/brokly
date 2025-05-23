#pragma once

#include "tensor/Tensor.hh"
#include <vector>

namespace momas::brokly::nn {

template <typename T> class Module {
public:
  Module() = default;

  virtual std::vector<tensor::Tensor<T> *> forward(std::vector<tensor::Tensor<T>*> inputs);
  virtual std::vector<tensor::Tensor<T> *> parameters();
};

} // namespace momas::brokly::nn