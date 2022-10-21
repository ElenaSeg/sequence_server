cmake_minimum_required(VERSION 3.5)

project(seq_server1 LANGUAGES CXX)
find_package (Threads)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sequence_server main.cpp client_handler.cpp client_handler.h socket.cpp socket.h settings_storage.cpp settings_storage.h)

# -lpthreads
target_link_libraries (sequence_server ${CMAKE_THREAD_LIBS_INIT})
