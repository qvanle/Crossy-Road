project (window)

add_library(
    ${PROJECT_NAME} STATIC 
    src/UI.cpp
    src/musiccontroller.cpp
    src/wincontent.cpp
    src/constructor.cpp
    src/destructor.cpp
    src/running.cpp
    src/acting.cpp
    src/interface.cpp
    src/action/close.cpp
    src/action/resize.cpp
    src/action/dying.cpp
)

add_library(window::lib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PUBLIC dep::raylib)

target_link_libraries(${PROJECT_NAME} PUBLIC utils::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC visual::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC action::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC container::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC interface::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC button::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC object::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC game::lib)
target_link_libraries(${PROJECT_NAME} PUBLIC inputbox::lib)

