#include "tensor/tensor.hpp"
#include <gtest/gtest.h>

TEST(Tensor, Creation) { auto t = new momas::brokly::tensor::Tensor({3, 3}); }

TEST(Tensor, Summation) {
  auto t1 = new momas::brokly::tensor::Tensor({3, 3});
  auto t2 = new momas::brokly::tensor::Tensor({3, 3});

  auto t3 = t1->add(t2);

  ASSERT_EQ(t3->size, t1->size);
  ASSERT_EQ(t3->size, t2->size);
}