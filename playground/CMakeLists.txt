add_executable(play
    main.cc
)

target_link_libraries(play
PRIVATE
    widen_common
)