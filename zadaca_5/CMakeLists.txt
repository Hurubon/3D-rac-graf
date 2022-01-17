cmake_minimum_required(VERSION 3.5)
project(zadaca_5 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    source/CircleRenderer.cpp
    source/LineRenderer.cpp
    source/Shader.cpp
    include/glad/glad.c
    main.cpp)

add_subdirectory(glfw binary)
add_executable(main ${SOURCES})

target_include_directories(main PUBLIC include)
target_include_directories(main PUBLIC glfw)
target_link_libraries(main PUBLIC glfw)
