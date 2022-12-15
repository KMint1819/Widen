cmake_minimum_required(VERSION 3.17)

project(YOUR_PROJECT_NAME) # Change name!


add_library(MY_LIB_NAME 
    src/log.cc
    src/lib.cc)

target_include_directories(MY_LIB_NAME 
    PUBLIC include
    PUBLIC 3rdparty)

add_subdirectory(app)
add_subdirectory(test)