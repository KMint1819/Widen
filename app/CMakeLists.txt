add_executable(MY_APP_NAME main.cc)

target_include_directories(MY_APP_NAME PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(MY_APP_NAME PUBLIC MY_LIB_NAME)