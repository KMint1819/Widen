add_executable(widen_node)

set(SOURCES
    src/widen/node/main.cc
    src/widen/node/node.cc
)
set(HEADERS
    src/widen/node/node.hpp
)
target_sources(widen_node
PRIVATE
    ${SOURCES}
    ${HEADERS}
)

add_dependencies(widen_node widen_common)
target_include_directories(widen_node
PUBLIC
    src/
)

target_link_libraries(widen_node
    widen_common
)
