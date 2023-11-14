project (window)

add_library(
    ${PROJECT_NAME} SHARED 
    src/constructor.cpp
    src/destructor.cpp
)

add_library(window::lib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PUBLIC dep::raylib)
target_link_libraries(${PROJECT_NAME} PUBLIC pthread)

target_link_libraries(${PROJECT_NAME} PUBLIC utils::lib)
