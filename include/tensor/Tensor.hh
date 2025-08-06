#pragma once
// TODO: this is tensor class that is core of computation. Consider that each
// time a new tensor is created, we have allocate a new part of data inside
// heap. This procedure is expensive, and we have to overload `new` function for
// this function

#include <cstdlib>
#include <cstring>
#include <list>
#include <map>

#include "tensor/Define.hh"
#include "tensor/autograd/base.hh"
#include "tensor/autograd/common.hh"

namespace momas::brokly::tensor {

struct dim4 {
  dim4(int d1, int d2, int d3, int d4) { total = d[0] * d[1] * d[2] * d[3]; }

  bool operator==(dim4 &dim) {
    return this->d[0] == dim.d[0] && this->d[1] == dim.d[1] &&
           this->d[2] == dim.d[2] && this->d[3] == dim.d[3];
  }

  inline unsigned int &operator[](int i) { return this->d[i]; }

  unsigned int d[4];
  int total;
};

template <typename T> class Tensor final {

public:
  Tensor(dim4 dimension, bool requires_grad = false,
         autograd::GradFunctor *grad_fn = nullptr, T *data = nullptr)
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
    for (const Tensor<T> *backwardTensor : this->backwardHooks) {
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
  autograd::GradFunctor *grad_fn;

  Tensor(const Tensor<T> &) = delete;
  Tensor(Tensor<T> &&) = default;
};
} // namespace momas::brokly::tensor