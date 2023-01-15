add_executable(widen_node)

set(SOURCES
    src/widen/node/main.cc
    src/widen/node/node.cc
    src/widen/node/message_listener.cc
    src/widen/node/handlers/joinRequestHandler.cc
)
set(HEADERS
    src/widen/node/node.hpp
    src/widen/node/message_listener.hpp
    src/widen/node/handlers/joinRequestHandler.hpp
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
