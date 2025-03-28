#pragma once

namespace momas::brokly::tensor::autograd {
    enum NamedTensor
    {
        INPUT,
        OUTPUT,
        GRAD,
        BACKPROP,
    };
}