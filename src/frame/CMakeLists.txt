project (frame)

add_library(
    ${PROJECT_NAME} STATIC 
    src/constructor.cpp
    src/destructor.cpp
    src/family.cpp
    src/arthmetic.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC dep::raylib)

add_library(frame::lib ALIAS ${PROJECT_NAME})


target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PUBLIC utils::lib)
