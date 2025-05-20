cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 20)

project(chat_server)
add_executable(chat_server
        server_main.cpp)

project(chat_client)
add_executable(chat_client
               client_main.cpp)
