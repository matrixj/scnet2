set(base_SRCS
    BaseLoop.cc
    Thread.cc
    Timer.cc
    Time.cc
    Timestamp.cc
    Channel.cc
    logbuffer.cc
    logger.cc
    condition.cc
    )

add_library(scnet2_base ${base_SRCS})
target_link_libraries(scnet2_base pthread)

install(TARGETS scnet2_base DESTINATION lib)
file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/scnet2/base)

add_subdirectory(tests)


