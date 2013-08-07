cmake_minimum_required(VERSION 2.6)

include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(BaseLoopAndThread BaseLoopAndThread.cc)
target_link_libraries(BaseLoopAndThread scnet2_base scnet2_net)
