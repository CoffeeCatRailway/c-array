cmake_minimum_required(VERSION 3.30)
project(c_array C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES src/main.c
        src/array_struct.h
        src/array.c
        src/array.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
