set (SRC
    doctest_main.cpp
    graph_t.cpp
    )

set (HEADERS
    )

add_executable(test ${SRC})
target_link_libraries(test PRIVATE doctest core)

enable_testing(test test)