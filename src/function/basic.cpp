#include "function/basic.hpp"
#include "base.h"
#include "function/op.hpp"

#define JUST_INFER

namespace momas::brokly::function {
void add(tensor::Tensor *input, tensor::Tensor *base, tensor::Tensor *output) {
#ifdef TRAINING
  input->forwardHooks.push_back(output);
  base->forwardHooks.push_back(output);

  output->backwardHooks.push_back(input);
  output->backwardHooks.push_back(base);

  output->op = Operation::ADD_OP;
  
#endif
  add_vec(input->data, base->data, output->data, input->size);
}

void sub(tensor::Tensor *input, tensor::Tensor *base, tensor::Tensor *output) {}
} // namespace momas::brokly::function