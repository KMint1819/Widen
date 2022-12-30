add_executable(mytests)
add_dependencies(mytests widen_common)

find_package(Protobuf REQUIRED)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/3rdparty/catch2;${CMAKE_MODULE_PATH})
include(Catch)
include(CTest)

set(SOURCES 
    test_main.cc
    test_random.cc
    test_proto.cc)

target_include_directories(mytests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/common/src
        ${PROJECT_BINARY_DIR}/protos)
target_link_libraries(mytests
    PRIVATE
        widen_common
        widen_protos)

target_sources(mytests
PRIVATE
    ${SOURCES}
)
catch_discover_tests(mytests)