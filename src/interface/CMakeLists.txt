project (interface)

add_library(
    ${PROJECT_NAME} STATIC 
    src/constructor.cpp
    src/destructor.cpp
    src/arthmetic.cpp
    src/action.cpp
    src/action/moveobject.cpp
    src/action/movetoobject.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC dep::raylib)

add_library(interface::lib ALIAS ${PROJECT_NAME})


target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PUBLIC utils::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC frame::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC visual::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC container::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC object::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC chunk::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC button::lib)

