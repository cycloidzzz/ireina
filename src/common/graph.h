#ifndef IREINA_SRC_COMMON_GRAPH_H
#define IREINA_SRC_COMMON_GRAPH_H

#include <glog/logging.h>

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "common/common.h"

class Graph;
using GraphSharedPtr = std::shared_ptr<Graph>;
using GraphUniquePtr = std::unique_ptr<Graph>;

class OpNode {
 public:
  explicit OpNode(OpNodeIdType node_id) : node_id_(node_id){};
  ~OpNode() = default;

  IREINA_DISALLOW_COPY_AND_MOVE(OpNode);

  /// Setter function.

  /// Getter function for node_id_.
  const OpNodeIdType node_id() const { return node_id_; }

 private:
  OpNodeIdType node_id_;
};

class BasicBlock {
 public:
  using OpNodeMap = std::map<OpNodeIdType, OpNode*>;
  using BasicBlockMap = std::map<BasicBlockIdType, BasicBlock*>;

 public:
  explicit BasicBlock(BasicBlockIdType block_id) : block_id_(block_id) {}
  ~BasicBlock() = default;

  IREINA_DISALLOW_COPY_AND_MOVE(BasicBlock);

  /// Setter function for BasicBlock.
  void setBasicBlock(size_t num_operation, size_t num_pred, size_t num_succ,
                     float exec_times) {
    num_operation_ = num_operation;
    num_pred_ = num_pred;
    num_succ_ = num_succ;
    exec_times_ = exec_times;

    LOG(INFO) << "BasicBlock(" << block_id_
              << "): num_operation = " << num_operation_ << std::endl
              << " num_pred = " << num_pred_ << std::endl
              << " num_succ = " << num_succ << std::endl
              << " exec_times = " << exec_times_ << std::endl;
  }

  /// Getter function for BasicBlock.
  const BasicBlockIdType block_id() const { return block_id_; }

  /// Getter function for operations_.
  const OpNodeMap& operations() const { return operations_; }

  /// Getter function for pred_.
  const BasicBlockMap& pred() const { return pred_; }

  /// Getter function for succ_.
  const BasicBlockMap& succ() const { return succ_; }

  void insertOpNodeAt(OpNodeIdType opnode_id, OpNode* opnode) {
    operations_[opnode_id] = opnode;
  }

  void insertPredAt(BasicBlockIdType block_id, BasicBlock* block) {
    pred_[block_id] = block;
  }

  void insertSuccAt(BasicBlockIdType block_id, BasicBlock* block) {
    succ_[block_id] = block;
  }

  /// Dump the info of this Basic Block, just for debug use.
  void dump() {
    LOG(INFO) << "In BasicBlock(" << block_id_ << ")" << std::endl;

    LOG(INFO) << "num_operation = " << num_operation_ << std::endl
              << "num_pred = " << num_pred_ << std::endl
              << "num_succ = " << num_succ_ << std::endl
              << "exec_times = " << exec_times_ << std::endl;

    LOG(INFO) << "Precedessors of this block : ";
    for (auto&& block_pair : pred_) {
      LOG(INFO) << block_pair.first << " " << block_pair.second->block_id();
    }

    LOG(INFO) << "Successors of this block : ";
    for (auto&& block_pair : succ_) {
      LOG(INFO) << block_pair.first << " " << block_pair.second->block_id();
    }

    LOG(INFO) << "Operations in this block : ";
    for (auto& opnode_pair : operations_) {
      LOG(INFO) << opnode_pair.first << " " << opnode_pair.second->node_id();
    }
  }

 private:
  BasicBlockIdType block_id_;
  size_t num_operation_{0};
  size_t num_pred_{0};
  size_t num_succ_{0};
  float exec_times_{0};

  /// Operations within this basic block.
  OpNodeMap operations_{};
  /// Predecessors of the current basic block.
  BasicBlockMap pred_{};
  /// Successors of the current basic block.
  BasicBlockMap succ_{};
};

class Graph {
 public:
  using OpNodeList = std::vector<OpNode*>;
  using BasicBlockList = std::vector<BasicBlock*>;

  using OpNodeMap = std::map<OpNodeIdType, OpNode*>;
  using BasicBlockMap = std::map<BasicBlockIdType, BasicBlock*>;

 public:
  explicit Graph(size_t num_block, size_t num_operation)
      : num_block_(num_block), num_operation_(num_operation) {
    for (size_t block_id = 0; block_id < num_block_; block_id++) {
      block_list_.push_back(new BasicBlock(block_id));
    }

    for (size_t opnode_id = 0; opnode_id < num_operation_; opnode_id++) {
      opnode_list_.push_back(new OpNode(opnode_id));
    }
  }

  ~Graph() {
    destroyOpNode();
    destroyBasicBlock();
  }

  IREINA_DISALLOW_COPY_AND_MOVE(Graph);

  OpNode* findOpNode(size_t opnode_id) { return opnode_list_[opnode_id]; }
  BasicBlock* findBasicBlock(size_t block_id) { return block_list_[block_id]; }

  /// Getter functions for block_list_;
  const BasicBlockList& block_list() const { return block_list_; }

 private:
  void destroyOpNode();
  void destroyBasicBlock();

  size_t num_operation_;
  size_t num_block_;
  size_t num_op_type_;

  /// For OpNode allocation
  OpNodeList opnode_list_;
  /// For BasicBlock allocation
  BasicBlockList block_list_;
  /// Topological Sort for basic blocks.
  BasicBlockList topo_block_list_;
};

#endif  // ! IREINA_SRC_COMMON_GRAPH_H