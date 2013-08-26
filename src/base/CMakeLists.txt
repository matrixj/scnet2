set(base_SRCS
    baseloop.cc
    thread.cc
    timer.cc
    time.cc
    timestamp.cc
    channel.cc
    logbuffer.cc
    logger.cc
    condition.cc
    countdown_latch.cc
    )

add_library(scnet2_base ${base_SRCS})
target_link_libraries(scnet2_base pthread rt)

install(TARGETS scnet2_base DESTINATION lib)
file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/scnet2/base)

add_subdirectory(tests)


