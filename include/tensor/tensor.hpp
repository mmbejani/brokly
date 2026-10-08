#pragma once

#include "function/op.hpp"
#include "tensor/define.h"
#include "utils/cg.hpp"
#include <stdalign.h>
#include <stdbool.h>
#include <vector>

namespace momas::brokly::tensor {

/**
 * @brief This enum class indicate how underlying of a tensor should be store.
 * This kind of classification need to use the memory optimal
 *
 */
enum class TensorType {
  // Regular tesnor that data is stored in array style
  DENSE,
  // This is constant size of tensor, with value of zero
  ZEROS,
  // This is constant size of tensor, with value of one
  ONES,
  // The underlying data is store in format of $min{m,n}$
  DIAG,
  // Similar to `ZERO`, store single value of one is diag
  EYE,
  // This type
  DIAG_BLOCK_EYES,
  BLOCK,
  SPARSE,
};

enum class TensorAllocMode { RESIDENT, EPHEMERAL };

class Tensor {
public:
  Tensor(const Tensor &) = delete;
  void operator=(const Tensor &) = delete;

  Tensor(std::vector<unsigned int> size, TensorType type = TensorType::DENSE,
         bool requires_grad = true,
         TensorAllocMode allocationMode = TensorAllocMode::RESIDENT);
  ~Tensor(); // Destructor to free allocated data

  Tensor operator[](unsigned int &&i) const;
  Tensor operator[](unsigned int &&i, unsigned int &&j) const;
  Tensor operator[](unsigned int &&k, unsigned int &&i, unsigned int &&j) const;
  Tensor operator[](unsigned int &&k, unsigned int &&t, unsigned int &&i,
                    unsigned int &&j) const;

  void addInplace(Tensor *input);
  Tensor *add(Tensor *input);

  void subInplace(Tensor *input);
  Tensor *sub(Tensor *input);

  void mulInplace(float32 scalar);
  Tensor *mul(float32 scalar);

  float32 sum() const;
  float32 mean() const;
  float32 item() const;
  static Tensor *ones(std::vector<unsigned int> size,
                      TensorType tensorType = TensorType::ONES,
                      TensorAllocMode allocMode = TensorAllocMode::EPHEMERAL);
  static Tensor *zeros(std::vector<unsigned int> size,
                       TensorType tensorType = TensorType::ZEROS,
                       TensorAllocMode allocMode = TensorAllocMode::EPHEMERAL);
  static Tensor *rand(std::vector<unsigned int> size,
                      TensorAllocMode allocMode = TensorAllocMode::EPHEMERAL);
  void backward(Tensor *tensor = nullptr) const;

  function::Operation op;
  bool requires_grad;
  TensorType type;
  TensorAllocMode allocationMode;
  unsigned int size;
  std::vector<unsigned int> dims;
  float32 *data;
  Tensor *grad;
  std::vector<Tensor *> forwardHooks, backwardHooks;
  unsigned int usedCounter;

private:
  Tensor(const Tensor &tensor, std::vector<unsigned int> subSize);
};

} // namespace momas::brokly::tensor