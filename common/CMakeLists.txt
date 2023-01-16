add_library(widen_common)
set(SOURCES
    src/widen/common/config.cc
    src/widen/common/exception.cc
    src/widen/common/log.cc
    src/widen/common/message_addon.cc
    src/widen/common/utils.cc
)
set(HEADERS
    src/widen/common/config.hpp
    src/widen/common/exception.hpp
    src/widen/common/fmt.hpp
    src/widen/common/log.hpp
    src/widen/common/message_addon.hpp
    src/widen/common/serialization.hpp
    src/widen/common/utils.hpp
    src/widen/common/proto_wrapper/identifier.hpp
    src/widen/common/proto_wrapper/proto_wrapper.hpp
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
    ${PROJECT_BINARY_DIR}/protos/
    ${YAML_CPP_INCLUDE_DIR}
    src
)
target_link_libraries(widen_common
    PUBLIC
    Threads::Threads
    ${YAML_CPP_LIBRARIES}
    widen_protos
)
