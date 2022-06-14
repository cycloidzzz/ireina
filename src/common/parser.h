#ifndef IREINA_SRC_COMMON_PARSER_H
#define IREINA_SRC_COMMON_PARSER_H

#include <glog/logging.h>

#include <fstream>
#include <iostream>
#include <string>

#include "common/common.h"
#include "common/graph.h"

class DataParser {
 public:
  explicit DataParser(const std::string& data_path)
      : data_path_(data_path), input_file_(data_path) {
    if (!input_file_) {
      LOG(ERROR) << "DataParser: Cannot open file " << data_path << std::endl;
    }
  }
  ~DataParser() { input_file_.close(); }

  IREINA_DISALLOW_COPY_AND_MOVE(DataParser);

  GraphUniquePtr parseGraphFromFile();

 private:
  std::string data_path_;
  std::ifstream input_file_;
};

#endif  // ! IREINA_SRC_COMMON_PARSER_H