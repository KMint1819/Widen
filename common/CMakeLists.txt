add_library(widen_common
    src/widen/common/log.cc
)
find_package(Threads REQUIRED)

set(PROTOBUF_PATH 3rdparty/protobuf)
include(${PROTOBUF_PATH}/cmake/)
find_package(Pro)

target_include_directories(widen_common
PUBLIC
    ${PROJECT_SOURCE_DIR}/3rdparty/
    src
)

target_link_libraries(widen_common
PRIVATE
    Threads::Threads
)