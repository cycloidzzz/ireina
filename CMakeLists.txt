cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include_directories(src)

add_subdirectory(thirdparty/glog)
add_subdirectory(thirdparty/googletest)

add_subdirectory(src/common)

add_executable(main src/main.cc)
target_link_libraries(main glog::glog)

add_executable(main_test src/main_test.cc)
target_link_libraries(main_test gtest gtest_main)
add_test(NAME main_test COMMAND $<TARGET_FILE:main_test>)

add_executable(parser_test src/common/parser_test.cc)
target_link_libraries(parser_test gtest gtest_main ireina_common)
add_test(NAME parser_test COMMAND $<TARGET_FILE:parser_test>)