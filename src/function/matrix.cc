#include "function/matrix.hh"
#include "tensor/Dtype.hh"
#include "tensor/Tensor.hh"
namespace momas::brokly::function::matrix {
tensor::Tensor<tensor::float32> *add(tensor::Tensor<tensor::float32> &input,
                                     tensor::Tensor<tensor::float32> &bias) {
  auto output = new tensor::Tensor<tensor::float32>(input.dimension);
  
  return output;
}

// Consider that the dimension of the 
// `input` is [C1,C2,B,K] and the `weight` is [C1,C2,M,K]
// The output will be [C1,C2,B,M]
tensor::Tensor<tensor::float32> *
matmul(tensor::Tensor<tensor::float32> &input,
       tensor::Tensor<tensor::float32> &weight) {
  tensor::dim4 output_dim(input.dimension.dx,
                          input.dimension.dy,
                          input.dimension.dz,
                          weight.dimension.dy);
  auto output = new tensor::Tensor<tensor::float32>(output_dim);
  for (size_t c1 = 0; c1 < output->dimension.dx; c1++) {
    for (size_t c2 = 0; c2 < output->dimension.dy; c2++) {
      for (size_t b = 0; b < output->dimension.dz; b++) {
        for (size_t m = 0; m < output->dimension.dw; m++) {
          tensor::float32 sum = 0;
          for (size_t k = 0; k < input.dimension.dw; k++) {
            sum += input.data[c1 * input.dimension.dy * input.dimension.dz +
                              c2 * input.dimension.dz + b] *
                   weight.data[c1 * weight.dimension.dy * weight.dimension.dw +
                               c2 * weight.dimension.dw + m];
          }
          output->data[c1 * output->dimension.dy * output->dimension.dz +
                       c2 * output->dimension.dz + b] = sum;
        }
      }
    }
  }

  return output;
}
} // namespace momas::brokly::function