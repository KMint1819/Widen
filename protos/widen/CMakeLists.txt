add_library(widen_protos)
find_package(Protobuf REQUIRED)

set(PROTOS
    distributed_fs.proto
    failure_detection.proto
    general.proto
    identifier.proto
    introducer.proto
)
target_sources(widen_protos
    PRIVATE
    ${PROTOS}
)

target_include_directories(widen_protos
    PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(widen_protos
    PUBLIC
    protobuf::libprotobuf
)

protobuf_generate(TARGET widen_protos LANGUAGE cpp)