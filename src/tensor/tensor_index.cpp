#include "tensor/tensor.hpp"
#include <vector>

namespace momas::brokly::tensor {
Tensor::Tensor(const Tensor &tensor, std::vector<unsigned int> subTensorIdx) {
  // TODO: need to validation that the index is bounded in tensor size
  switch (subTensorIdx.size()) {
  case 1:
    this->data = &tensor.data[subTensorIdx[0] * tensor.dims[1] *
                              tensor.dims[2] * tensor.dims[3]];
    this->size = tensor.dims[1] * tensor.dims[2] * tensor.dims[3];
    this->dims = std::vector<unsigned int>(
        {1, tensor.dims[1], tensor.dims[2], tensor.dims[3]});
    break;
  case 2:
    this->data =
        &tensor.data[subTensorIdx[0] * tensor.dims[1] * tensor.dims[2] *
                         tensor.dims[3] +
                     subTensorIdx[1] * tensor.dims[2] * tensor.dims[3]];
    this->size = tensor.dims[2] * tensor.dims[3];
    this->dims =
        std::vector<unsigned int>({1, 1, tensor.dims[2], tensor.dims[3]});
    break;
  case 3:
    this->data =
        &tensor.data[subTensorIdx[0] * tensor.dims[1] * tensor.dims[2] *
                         tensor.dims[3] +
                     subTensorIdx[1] * tensor.dims[2] * tensor.dims[3] +
                     subTensorIdx[2] * tensor.dims[3]];
    this->size = tensor.dims[3];
    this->dims = std::vector<unsigned int>({1, 1, 1, tensor.dims[3]});
    break;
  case 4:
    this->data =
        &tensor.data[subTensorIdx[0] * tensor.dims[1] * tensor.dims[2] *
                         tensor.dims[3] +
                     subTensorIdx[1] * tensor.dims[2] * tensor.dims[3] +
                     subTensorIdx[2] * tensor.dims[3] + subTensorIdx[3]];
    this->size = 1;
    this->dims = std::vector<unsigned int>({1, 1, 1, 1});
    break;
  }
}

Tensor Tensor::operator[](unsigned int &&i) const {
  std::vector<unsigned int> subTensorIdx({i});
  return Tensor((*this), subTensorIdx);
}

Tensor Tensor::operator[](unsigned int &&i, unsigned int &&j) const {
  std::vector<unsigned int> subTensorIdx({i, j});
  return Tensor((*this), subTensorIdx);
}

Tensor Tensor::operator[](unsigned int &&k, unsigned int &&i,
                          unsigned int &&j) const {
  std::vector<unsigned int> subTensorIdx({k, i, j});
  return Tensor((*this), subTensorIdx);
}

Tensor Tensor::operator[](unsigned int &&k, unsigned int &&t, unsigned int &&i,
                          unsigned int &&j) const {
  std::vector<unsigned int> subTensorIdx({k, t, i, j});
  return Tensor((*this), subTensorIdx);
}
} // namespace momas::brokly::tensor