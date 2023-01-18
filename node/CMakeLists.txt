add_executable(widen_node)

set(SOURCES
    src/widen/node/main.cc
    src/widen/node/memberlist.cc
    src/widen/node/node.cc
    src/widen/node/distributed_fs/distributed_fs.cc
    src/widen/node/failure_detector/failure_detector.cc
    src/widen/node/introducer/introducer.cc
    src/widen/node/introducer/joinRequestHandler.cc
)
set(HEADERS
    src/widen/node/node.hpp
    src/widen/node/memberlist.hpp
    src/widen/node/distributed_fs/distributed_fs.hpp
    src/widen/node/failure_detector/failure_detector.hpp
    src/widen/node/introducer/introducer.hpp
    src/widen/node/introducer/joinRequestHandler.hpp
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
