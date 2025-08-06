#pragma once

#include "tensor/autograd/base.hh"
#include "tensor/autograd/common.hh"
#include <map>

namespace momas::brokly::tensor {

template <typename T> class Tensor;

namespace autograd {

struct AddScalarGrad : GradFunctor {
  void operator()(const std::map<NamedTensor, Tensor<float32> *> &context)
      const noexcept override {}
};

struct AddVectorGrad : GradFunctor {
  void operator()(const std::map<NamedTensor, Tensor<float32> *> &context)
      const noexcept override {}
};

struct AddMatrixGrad : GradFunctor {
  void operator()(const std::map<NamedTensor, Tensor<float32> *> &context)
      const noexcept override {}
};

struct AddScalarVectorGrad : GradFunctor {
  void operator()(const std::map<NamedTensor, Tensor<float32> *> &context)
      const noexcept override {}
};

struct AddScalarMatrixGrad : GradFunctor {
  void operator()(const std::map<NamedTensor, Tensor<float32> *> &context)
      const noexcept override {}
};

struct AddVectorMatrixGrad : GradFunctor {
  void operator()(const std::map<NamedTensor, Tensor<float32> *> &context)
      const noexcept override {}
};
} // namespace autograd
} // namespace momas::brokly::tensor