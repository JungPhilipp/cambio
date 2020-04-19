set (SRC
    src/Graph.cpp
    )
set (HEADERS
    include/graph/Graph.h
    )

add_library(core ${SRC} ${HEADERS})
target_include_directories(core PUBLIC include)

add_subdirectory(test)
