#include "function/matrix.hh"
#include "tensor/Dtype.hh"
#include "tensor/Tensor.hh"

#ifdef SIMD
#include "backend/avx/fp32/vec.h"
#else
#include "backend/plain/fp32/vec.h"
#endif
#include <cstddef>
namespace momas::brokly::function::matrix {
tensor::Tensor<tensor::float32> *add(tensor::Tensor<tensor::float32> &input,
                                     tensor::Tensor<tensor::float32> &bias) {
  auto output = new tensor::Tensor<tensor::float32>(input.dimension);

  return output;
}

tensor::Tensor<tensor::float32> *
add_matrix_vector(tensor::Tensor<tensor::float32> &activation,
                  tensor::Tensor<tensor::float32> &bias) {
  auto output = new tensor::Tensor<tensor::float32>(activation.dimension, true);
  for (size_t i = 0; i < activation.dimension[2]; i++) {
    auto row_idx = activation.dimension[2] * i;
#ifdef SIMD
    add_fp32_avx(activation.data + row_idx, bias.data, output->data + row_idx,
                 activation.dimension[2]);

#elifdef MKL

#elifdef BLIS

#else
    add_fp32(activation.data + row_idx, bias.data, output->data + row_idx, output->dimension[3]);
#endif
  }
  bias.forward_hooks_count++;
  activation.forward_hooks_count++;
  return output;
}

// In this function we conside that there is two matrices.
// This means that both two first axis of tensors of input arguments
// are equal to 1.
// Therefore, consider `input` shape is `[1,1,batch_size, input_feature]`
// and the `weight` is `[1,1,output_feature, input_feature]` and the result
// will be `[1,1,batch_size, output_size]`
tensor::Tensor<tensor::float32> *
matmul(tensor::Tensor<tensor::float32> &input,
       tensor::Tensor<tensor::float32> &weight) {
  auto output_dim = tensor::dim4(1, 1, input.dimension[0], weight.dimension[0]);
  auto output = new tensor::Tensor<tensor::float32>(output_dim, true, nullptr);

#ifdef SIMD
  for (size_t i = 0; i < input.dimension[0]; i++) {
    auto row_idx = input.dimension[0] * i;
    for (size_t j = 0; j < weight.dimension[0]; j++) {
      output->data[row_idx + j] = ipr_fp32_avx(
          input.data + row_idx, weight.data + (j * weight.dimension[0]),
          input.dimension[1]);
    }
  }
#else
  for (size_t i = 0; i < input.dimension[0]; i++) {
    auto row_idx = input.dimension[0] * i;
    for (size_t j = 0; j < weight.dimension[0]; j++) {
      output->data[row_idx + j] =
          ipr_fp32(input.data + row_idx,
                   weight.data + (j * weight.dimension[0]), input.dimension[1]);
    }
  }
#endif
  return output;
}

} // namespace momas::brokly::function::matrix