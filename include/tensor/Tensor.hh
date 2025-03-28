#pragma once

#include <map>

#include "tensor/Define.hh"
#include "tensor/autograd/Common.hh"

namespace momas::brokly::tensor {

struct dim4 {
  dim4(int dx, int dy, int dz, int dw) : dx(dx), dy(dy), dz(dz), dw(dw) {
    total = dx * dy * dz * dw;
  }
  int dx, dy, dz, dw;
  int total;
};

template <typename T> class Tensor {

public:
  Tensor(dim4 dimension, bool requires_grad = false,
         std::map<autograd::NamedTensor, Tensor<T> *> (*grad_fn)(
             std::map<autograd::NamedTensor, Tensor<T> *>) = nullptr,
         T *data = nullptr)
      : dimension(dimension), grad_fn(grad_fn), requires_grad(requires_grad),
        data(data) {

    if (this->data == nullptr) {
      this->data = (T *)aligned_alloc(AVX_MEM_ALIGNED,
                                      this->dimension.total * sizeof(T));
      std::memcpy(this->data, data, sizeof(T) * dimension.total);
    }
  }

  inline void backward() {
    this->backwardHooks = this->grad_fn(this->forwardHooks);
  }

public:
  const dim4 dimension;
  T *data;
  Tensor<T> *grad;

  bool requires_grad;
  std::map<autograd::NamedTensor, Tensor<T> *> forwardHooks, backwardHooks;
  std::map<autograd::NamedTensor, Tensor<T> *> (*grad_fn)(
      std::map<autograd::NamedTensor, Tensor<T> *>);
};
} // namespace momas::brokly::tensor