#include "common/graph.h"

#include <glog/logging.h>

void Graph::destroyBasicBlock() {
  for (auto&& block : block_list_) {
    if (block) {
      delete block;
    }
  }
}

void Graph::destroyOpNode() {
  for (auto&& opnode : opnode_list_) {
    if (opnode) {
      delete opnode;
    }
  }
}