add_executable(widen_worker)

set(SOURCES
    src/widen/worker/main.cc
    src/widen/worker/worker.cc
)
set(HEADERS
    src/widen/worker/worker.hpp
)
target_sources(widen_worker
PRIVATE
    ${SOURCES}
    ${HEADERS}
)

add_dependencies(widen_worker widen_common)
target_include_directories(widen_worker
PUBLIC
    src/
)

target_link_libraries(widen_worker
    widen_common
)
