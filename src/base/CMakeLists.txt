set(base_SRCS
    BaseLoop.cpp
    Thread.cpp
    Timer.cpp
    Time.cpp
    Timestamp.cpp
    Channel.cpp
    )

add_library(scnet2_base ${base_SRCS})
target_link_libraries(scnet2_base pthread)

install(TARGETS scnet2_base DESTINATION lib)
file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/scnet2/base)

add_subdirectory(tests)


