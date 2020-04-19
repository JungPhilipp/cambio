set (SRC
    doctest_main.cpp
    )

set (HEADERS
    )

add_executable(test ${SRC})
target_link_libraries(test PRIVATE doctest)

enable_testing(test test)