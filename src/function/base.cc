#include "function/base.hh"
#include "tensor/Define.hh"
#include "tensor/Dtype.hh"
#include "tensor/Tensor.hh"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <random>

namespace momas::brokly::function::base {

tensor::Tensor<tensor::float32> *constant(tensor::dim4 dimension,
                                          tensor::float32 c) {
  tensor::float32 *data = (tensor::float32 *)std::aligned_alloc(
      AVX_MEM_ALIGNED, sizeof(tensor::float32) * dimension.total);
  std::memset(data, c, dimension.total);

  return new tensor::Tensor<tensor::float32>(dimension, false, nullptr, data);
}

tensor::Tensor<tensor::float32> *ones(tensor::dim4 dimension) {
  return constant(dimension, 1.0f);
}

tensor::Tensor<tensor::float32> *zeros(tensor::dim4 dimension) {
  return constant(dimension, 0.0f);
}

tensor::Tensor<tensor::float32> *rand(tensor::dim4 dimension,
                                      bool requires_grad) {
  tensor::float32 *data = (tensor::float32 *)std::aligned_alloc(
      AVX_MEM_ALIGNED, sizeof(tensor::float32) * dimension.total);

  std::mt19937_64 rng;
  rng.seed(0);
  std::uniform_real_distribution<tensor::float32> unif(0, 1);
  for (size_t i = 0; i < dimension.total; i++) {
    data[i] = unif(rng);
  }

  return new tensor::Tensor<tensor::float32>(dimension, requires_grad, nullptr,
                                             data);
}
} // namespace momas::brokly::function