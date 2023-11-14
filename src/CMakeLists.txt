cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -O2 -fPIC")
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w -O2 -fPIC")

include (FetchContent)

project(CLM)
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(dependency/raylib)

add_subdirectory(window)
target_link_libraries(${PROJECT_NAME} PUBLIC window::lib)

