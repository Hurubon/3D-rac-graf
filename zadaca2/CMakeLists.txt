cmake_minimum_required(VERSION 3.5)
project(ray-tracer VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(main main.cpp)

target_include_directories(main PRIVATE inc)
