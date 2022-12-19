add_executable(widen_worker
    src/widen/worker/main.cc
)

target_include_directories(widen_worker
PUBLIC
    ${PROJECT_SOURCE_DIR}/3rdparty/
    src/
)

target_link_libraries(widen_worker
    widen_common
)
