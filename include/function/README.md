# Function Package

Consists of function definition. The purpose of this package is that creates an interface to call a computational function and establish computational graph. Computation graph consist of three store-tracking

* `forwardHook` : Consists of tensors that compose this tensor.
* `backwardHook`: I am not really know that this `std::vector` needed! :)
* `usedCounter`: An interger that count how many time this tensor is used in different operation.


## `forwardHook`

When a function in `function` package is called (e.g. in `activation.hpp` there is function named `sigmoid`)

## `backwardHook`

## `usedCounter`