cmake_minimum_required(VERSION 3.16)

project(Widen)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(COPY config.yaml DESTINATION ${CMAKE_BINARY_DIR})
file(COPY known_hosts.txt DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(protos)
add_subdirectory(common)
add_subdirectory(client)

# add_subdirectory(node)
add_subdirectory(test)