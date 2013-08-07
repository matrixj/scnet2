set(base_SRCS
    poller.cc
    epoller.cc
    )

add_library(scnet2_net ${base_SRCS})
target_link_libraries(scnet2_net pthread)

install(TARGETS scnet2_net DESTINATION lib)
file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/scnet2/net)



