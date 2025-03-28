#include "function/base.hh"
#include "tensor/Dtype.hh"
#include "tensor/Tensor.hh"
#include <map>

namespace momas::brokly::tensor::autograd {
    std::map<NamedTensor, Tensor<float32>*> sigmoidBackward(std::map<NamedTensor, Tensor<float32> *> context)
    {
        auto input = context[INPUT];

        auto backprop = function::zeros(input->dimension);
        for (int i = 0; i < input->dimension.total; i++) {
            backprop->data[i] = input->data[i] > 0? 1.0f : 0.05f;
        }
        return {{BACKPROP, backprop}};
    }
}