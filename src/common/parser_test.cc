#include "common/parser.h"

#include "gtest/gtest.h"

TEST(DataParserTest, SetUpParserTest) { DataParser parser("./data/graph.txt"); }

TEST(DataParserTesr, ParseGraphTest) {
  DataParser parser("./data/graph.txt");
  GraphUniquePtr graph = parser.parseGraphFromFile();

  auto&& block_list = graph->block_list();
  for (auto&& block : block_list) {
    block->dump();
  }
}