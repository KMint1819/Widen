set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/3rdparty/catch2;${CMAKE_MODULE_PATH})
message(${CMAKE_MODULE_PATH})
include(Catch)
include(CTest)
add_executable(mytests 
    test_main.cc
    test_alan.cc
)
target_include_directories(mytests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include/
)
target_link_libraries(mytests
    PRIVATE
        MY_LIB_NAME
)

catch_discover_tests(mytests)