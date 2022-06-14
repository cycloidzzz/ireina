#include "common/parser.h"

#include <glog/logging.h>

GraphUniquePtr DataParser::parseGraphFromFile() {
  size_t num_block, num_opnode;
  input_file_ >> num_block >> num_opnode;

  GraphUniquePtr graph = std::make_unique<Graph>(num_block, num_opnode);
  // TODO (ozr) : read OpTypes

  // read BasicBlocks
  for (size_t block_id = 0; block_id < num_block; block_id++) {
    size_t num_operation, num_pred, num_succ;
    float exec_time;

    LOG(INFO) << "DataParser.parseGraphFromFile(): parsing BasicBlock("
              << block_id << ")" << std::endl;

    input_file_ >> num_operation >> num_pred >> num_succ >> exec_time;
    BasicBlock* block = graph->findBasicBlock(block_id);

    block->setBasicBlock(num_operation, num_pred, num_succ, exec_time);

    for (size_t i = 0; i < num_operation; i++) {
      size_t opnode_id;
      input_file_ >> opnode_id;
      OpNode* opnode = graph->findOpNode(opnode_id);
      block->insertOpNodeAt(opnode_id, opnode);
    }

    for (size_t i = 0; i < num_pred; i++) {
      size_t pred_block_id;
      input_file_ >> pred_block_id;
      LOG(INFO) << "inserting pred block = " << pred_block_id << std::endl;
      BasicBlock* pred_block = graph->findBasicBlock(pred_block_id);
      block->insertPredAt(pred_block_id, pred_block);
    }

    for (size_t i = 0; i < num_succ; i++) {
      size_t succ_block_id;
      input_file_ >> succ_block_id;
      LOG(INFO) << "inserting succ block = " << succ_block_id << std::endl;
      BasicBlock* succ_block = graph->findBasicBlock(succ_block_id);
      block->insertSuccAt(succ_block_id, succ_block);
    }
  }

  return graph;
}