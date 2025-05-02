#pragma once

#include <list>
#include <map>

#include "tensor/Define.hh"
#include "tensor/autograd/common.hh"

namespace momas::brokly::tensor {

struct dim4 {
  dim4(int dx, int dy, int dz, int dw) : dx(dx), dy(dy), dz(dz), dw(dw) {
    total = dx * dy * dz * dw;
  }

  bool operator==(dim4 &dim) {
    return this->dx == dim.dx && this->dy == dim.dy && this->dz == dim.dz &&
           this->dw == dim.dw;
  }

  int dx, dy, dz, dw;
  int total;
};

template <typename T> class Tensor {

public:
  Tensor(dim4 dimension, bool requires_grad = false,
         void (*grad_fn)(Tensor<T> *) = nullptr, T *data = nullptr)
      : dimension(dimension), grad_fn(grad_fn), requires_grad(requires_grad),
        data(data), grad(nullptr) {

    if (this->data == nullptr) {
      this->data = (T *)aligned_alloc(AVX_MEM_ALIGNED,
                                      this->dimension.total * sizeof(T));
      std::memcpy(this->data, data, sizeof(T) * dimension.total);
    }
    this->single = dimension.total == 1;
  }

  inline bool is_leaf() const { return this->grad_fn == nullptr; }

  void backward() {
    for (const Tensor<T>* &backwardTensor : this->backwardHooks) {
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

  bool requires_grad, single;
  std::map<autograd::NamedTensor, Tensor<T> *> forwardHooks;
  std::list<Tensor<T> *> backwardHooks;
  void (*grad_fn)(Tensor<T> *);
};
} // namespace momas::brokly::tensor