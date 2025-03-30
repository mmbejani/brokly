#pragma once

namespace momas::brokly::tensor::autograd {
    enum NamedTensor
    {
        INPUT,
        SCALAR,
        OUTPUT,
        GRAD,
        BACKPROP,
    };
}