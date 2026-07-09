cmake_minimum_required(VERSION 3.20)

project(SSE)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(SSE
    src/common.cpp
    src/main.cpp
    src/seq.cpp
    src/sse.cpp
    src/verify.cpp
)
