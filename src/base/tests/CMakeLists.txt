cmake_minimum_required(VERSION 2.6)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(baseandloop baseandloop_test.cc)
add_executable(logbuffer logbuffer_test.cc)
add_executable(condition condition_test.cc)
add_executable(writefile writefile_test.cc)
add_executable(condition_timedwait_test condition_timedwait_test.cc)

target_link_libraries(baseandloop scnet2_base scnet2_net rt)
target_link_libraries(logbuffer scnet2_base scnet2_net)
target_link_libraries(condition scnet2_base)
target_link_libraries(writefile scnet2_base)
target_link_libraries(condition_timedwait_test scnet2_base)
