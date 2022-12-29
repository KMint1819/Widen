set(SOURCES
    src/widen/common/log.cc)
set(HEADERS
    src/widen/common/fmt.hpp
    src/widen/common/log.hpp)
add_library(widen_common
    ${SOURCES}
    ${HEADERS})

find_package(Threads REQUIRED)

target_include_directories(widen_common
PUBLIC
    ${PROJECT_SOURCE_DIR}/3rdparty/
    src)

target_link_libraries(widen_common
PUBLIC
    Threads::Threads
)
