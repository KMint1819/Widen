add_library(widen_test_protos)
find_package(Protobuf REQUIRED)

set(PROTOS 
    me.proto
    person.proto)
protobuf_generate_cpp(WIDEN_TEST_PROTO_SRCS WIDEN_TEST_PROTO_HDRS ${PROTOS})

target_include_directories(widen_test_protos
PUBLIC
    .
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Protobuf_INCLUDE_DIRS})
target_link_libraries(widen_test_protos
    ${Protobuf_LIBRARIES})

target_sources(widen_test_protos
PRIVATE
    ${WIDEN_TEST_PROTO_SRCS}
    ${WIDEN_TEST_PROTO_HDRS}
)