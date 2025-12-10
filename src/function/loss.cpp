#include "function/loss.hpp"
#include "backend/base.h"

namespace momas::brokly::function {
float32 mean_squard_error_loss_forward(tensor::Tensor *input,
                                       tensor::Tensor *target, bool inplace) {
  if (inplace) {
    sub_vec_inplace(input->data, target->data, input->size);
    pow_2_vec_inplace(target->data, target->size);
    return sum_reduce_vec(target->data, target->size);
  }

  // non-inplace approach increase computation cost, in most case you do not
  // need the `target` then, it is worthy to put the inplace value always true.
  return 0;
}
float32 cross_entropy_loss_forward(tensor::Tensor *input,
                                   tensor::Tensor *target) {
  // TODO: complete this function
  return 0;
}
} // namespace momas::brokly::function