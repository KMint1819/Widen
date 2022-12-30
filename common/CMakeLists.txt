add_library(widen_common)
set(SOURCES
    src/widen/common/log.cc
    src/widen/common/config.cc
)
set(HEADERS
    src/widen/common/fmt.hpp
    src/widen/common/log.hpp
    src/widen/common/config.hpp
)
target_sources(widen_common
PRIVATE
    ${SOURCES}
    ${HEADERS}
)
add_dependencies(widen_common widen_protos)

find_package(Threads REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

target_include_directories(widen_common
PUBLIC
    ${PROJECT_SOURCE_DIR}/3rdparty/
    ${YAML_CPP_INCLUDE_DIR}
    src
)
target_link_libraries(widen_common
PUBLIC
    Threads::Threads
    ${YAML_CPP_LIBRARIES}
    widen_protos
)
