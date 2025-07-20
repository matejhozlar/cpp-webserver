cmake_minimum_required(VERSION 3.15)
project(cpp_webserver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
add_executable(cpp_webserver
    src/main.cpp
)

# Link with Winsock2
if (WIN32)
    target_link_libraries(cpp_webserver ws2_32)
endif()