project (storage)

add_library(
    ${PROJECT_NAME} STATIC 
    src/constructor.cpp
    src/destructor.cpp
    src/arthmetic.cpp
)

add_library(storage::lib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PUBLIC utils::lib)

