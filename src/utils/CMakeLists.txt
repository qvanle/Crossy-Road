project (utils)

add_library(
    ${PROJECT_NAME} SHARED 
    src/file.cpp
    src/constant.cpp
    )

add_library(utils::lib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_link_libraries(${PROJECT_NAME} PUBLIC dep::yamlcpp)
