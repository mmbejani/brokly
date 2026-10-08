#pragma once

#include <concepts>
#include <tensor/tensor.hpp>
#include <vector>

namespace momas::brokly::nn {

template <typename T>
concept Module = requires(T module, tensor::Tensor *tensor) {
  module.forward(tensor);
  { module.parameters() } -> std::same_as<std::vector<tensor::Tensor *>>;
};

} // namespace momas::brokly::nn