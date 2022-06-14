#ifndef IREINA_SRC_COMMON_TYPES_H
#define IREINA_SRC_COMMON_TYPES_H

#include <chrono>
#include <cstddef>
#include <cstdint>

enum class OpType {
  kBranchOp = 0,
  kAllocaOp,
  kLoadOp,
  kStoreOp,
  kPhiOp,
  kArithmeticOp,
  kBoolOp,
  kCompareOp
};

using OpNodeIdType = size_t;
using BasicBlockIdType = size_t;

#endif  // ! IREINA_SRC_COMMON_TYPES_H