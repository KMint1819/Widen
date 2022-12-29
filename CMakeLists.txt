cmake_minimum_required(VERSION 3.14)

project(Widen)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(ExternalProject)
set(EXTERNAL_DESTDIR ${CMAKE_CURRENT_BINARY_DIR}/../external)
add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(worker)
add_subdirectory(test)