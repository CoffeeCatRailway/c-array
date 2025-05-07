cmake_minimum_required(VERSION 3.30)
project(c_array
    VERSION 1.0
    DESCRIPTION "A small library for dynamic array's"
    LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(DEFAULT_BUILD_TYPE "Release")

# Set build type
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()

set(SOURCE_FILES
        src/main.c
        src/c_array_define.h
        src/c_array.c
        src/c_array.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
