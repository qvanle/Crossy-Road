project (utils)

add_library(
    ${PROJECT_NAME} STATIC 
    src/file.cpp
    src/keystroke.cpp
    src/constant.cpp
    src/countdown.cpp
    src/random.cpp
    )

add_library(utils::lib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_link_libraries(${PROJECT_NAME} PUBLIC dep::yamlcpp)
target_link_libraries(${PROJECT_NAME} PUBLIC dep::raylib)

target_link_libraries(${PROJECT_NAME} PUBLIC action::lib)
