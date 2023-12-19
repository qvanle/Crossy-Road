cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include (FetchContent)

project(CLM)
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(dependency/raylib)
add_subdirectory(dependency/yamlcpp)

add_subdirectory(utils)
add_subdirectory(window)
add_subdirectory(visual)
add_subdirectory(frame)
add_subdirectory(action)
add_subdirectory(container)
add_subdirectory(interface)
add_subdirectory(chunk)
add_subdirectory(object)

target_link_libraries(${PROJECT_NAME} PUBLIC window::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC visual::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC frame::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC utils::lib)

