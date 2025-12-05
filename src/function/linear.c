#include "function/linear.h"
#include "backend/plain/vec.h"
#include "nn/linear.h"
#include "tensor/autograd/linear.h"

void linear_forward(Linear *linear_module, Tensor *input, Tensor *output) {
#ifdef AVX
  // TODO : add other backends
#else

  for (int batch_idx = 0; batch_idx < input->dim[1]; batch_idx++) {
    for (int out_nfeat = 0; out_nfeat < output->dim[0]; out_nfeat++) {
      output->data[batch_idx * input->dim[0] + out_nfeat] =
          ipr_fp32(&input->data[batch_idx * input->dim[0]],
                   &linear_module->weight
                        ->data[out_nfeat * linear_module->weight->dim[0]],
                   input->dim[0]);
    }
  }

#endif
  output->forward_hooks_count++;
  output->backward = &linear_backward;
  output->requires_grad = true;
}