#include <glog/logging.h>

#include <iostream>

int main(int argc, char* argv[]) {
  FLAGS_alsologtostderr = 1;
  google::InitGoogleLogging(argv[0]);

  LOG(INFO) << "Hello from Google Logging." << std::endl;

  return 0;
}