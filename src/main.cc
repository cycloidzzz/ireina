#include <glog/logging.h>

#include <iostream>

#include "common/graph.h"

class GLogInitializer {
 public:
  GLogInitializer(const char* program_name) {
    google::InitGoogleLogging(program_name);
    FLAGS_stderrthreshold = google::INFO;
    FLAGS_colorlogtostderr = true;
    FLAGS_v = 3;
  }

  ~GLogInitializer() { google::ShutdownGoogleLogging(); }
};

int main(int argc, char* argv[]) {
  GLogInitializer initializer(argv[0]);

  LOG(INFO) << "Hello from Google Logging." << std::endl;

  return 0;
}