add_executable(widen_client
    src/widen/client/main.cc
)

target_include_directories(widen_client
PUBLIC
    ${PROJECT_SOURCE_DIR}/3rdparty/
    src/
)

target_link_libraries(widen_client
    widen_common
)
