add_executable(ipc_sample main.c)
target_link_libraries(ipc_sample pipe_sample)

add_subdirectory(pipe)