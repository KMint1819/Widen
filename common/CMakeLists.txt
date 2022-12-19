add_library(widen_common
    src/widen/log.cc
)
find_package(Threads REQUIRED)

target_include_directories(widen_common
PUBLIC
    ${PROJECT_SOURCE_DIR}/3rdparty/
    src
)

target_link_libraries(widen_common
PRIVATE
    Threads::Threads
)