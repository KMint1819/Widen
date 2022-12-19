add_library(widen_common
    src/widen/log.cc
)
target_include_directories(widen_common
PUBLIC
    ${PROJECT_SOURCE_DIR}/3rdparty/
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)