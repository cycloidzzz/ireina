#ifndef IREINA_SRC_COMMON_COMMON_H
#define IREINA_SRC_COMMON_COMMON_H

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

#define IREINA_DISALLOW_COPY(type)       \
  type& operator=(const type&) = delete; \
  type(const type&) = delete;

#define IREINA_DISALLOW_MOVE(type)  \
  type& operator=(type&&) = delete; \
  type(type&&) = delete;

#define IREINA_DISALLOW_COPY_AND_MOVE(type) \
  IREINA_DISALLOW_COPY(type);               \
  IREINA_DISALLOW_MOVE(type)

#endif  // ! IREINA_SRC_COMMON_COMMON_H