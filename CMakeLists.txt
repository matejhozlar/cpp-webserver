cmake_minimum_required(VERSION 3.15)
project(cpp_webserver)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(cpp_webserver
    src/main.cpp
    src/server.cpp
)

if (WIN32)
    target_link_libraries(cpp_webserver ws2_32)
endif()
