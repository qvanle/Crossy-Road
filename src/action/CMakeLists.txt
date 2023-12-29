project (action)

add_library(
    ${PROJECT_NAME} STATIC 
    src/action.cpp
    src/request.cpp
    src/args.cpp
    src/request/changeinf.cpp
)

add_library(action::lib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PUBLIC utils::lib)

