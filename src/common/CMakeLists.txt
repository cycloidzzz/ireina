set(IREINA_COMMON_SRCS
    graph.cc
    parser.cc
    resource.cc
)

add_library(ireina_common ${IREINA_COMMON_SRCS})
target_link_libraries(ireina_common glog::glog)

install(TARGETS ireina_common DESTINATION lib)

file(GLOB IREINA_COMMON_HEADERS "*.h")
install(FILES ${IREINA_COMMON_HEADERS} DESTINATION include/ireina/common)