add_executable(mytests)
add_dependencies(mytests widen_common)
add_subdirectory(proto)

find_package(Protobuf REQUIRED)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/3rdparty/catch2;${CMAKE_MODULE_PATH})
include(Catch)
include(CTest)

set(SOURCES 
    test_main.cc
    test_random.cc
    test_protobuf.cc)

target_include_directories(mytests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(mytests
    PRIVATE
        ${Protobuf_LIBRARIES}
        widen_test_protos)

target_sources(mytests
PRIVATE
    ${SOURCES}
)
catch_discover_tests(mytests)