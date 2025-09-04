#pragma once
// TODO: this is tensor class that is core of computation. Consider that each
// time a new tensor is created, we have allocate a new part of data inside
// heap. This procedure is expensive, and we have to overload `new` function for
// this function

#include <list>
#include <map>

#include "tensor/Define.hh"
#include "tensor/Dtype.hh"
#include "tensor/autograd/common.hh"

namespace momas::brokly::tensor {

template <typename T> class Tensor {

public:
  Tensor(dim4 dimension, bool requires_grad = false,
         void (*grad_fn)(std::map<autograd::NamedTensor, Tensor<float32> *>) =
             nullptr,
         T *data = nullptr)
      : dimension(dimension), grad_fn(grad_fn), requires_grad(requires_grad),
        data(data), grad(nullptr), forward_hooks_count(0) {

    if (this->data == nullptr) {
      this->data = (T *)aligned_alloc(AVX_MEM_ALIGNED,
                                      this->dimension.total * sizeof(T));
      std::memcpy(this->data, data, sizeof(T) * dimension.total);
    }
    this->single = dimension.total == 1;
  }

  inline bool is_leaf() const { return this->grad_fn == nullptr; }

  void backward() {
    for (const Tensor<T> *&backwardTensor : this->backwardHooks) {
      if (backwardTensor->grad == nullptr) {
        return;
      }
    }
    this->grad_fn(this);
    for (const auto &[name, forwardTensor] : this->forwardHooks) {
      if (forwardTensor->required_grad) {
        forwardTensor->backward();
      }
    }
  }

public:
  dim4 dimension;
  T *data;
  Tensor<T> *grad;
  unsigned int forward_hooks_count;
  bool requires_grad, single;
  std::map<autograd::NamedTensor, Tensor<T> *> forwardHooks;
  std::list<Tensor<T> *> backwardHooks;
  void (*grad_fn)(std::map<autograd::NamedTensor, Tensor<float32> *>);
};
} // namespace momas::brokly::tensor