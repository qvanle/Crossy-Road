set(YAMLCPP_VERSION 0.8.0)
find_package(yamlcpp ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT yamlcpp_FOUND) # If there's none, fetch and build
    include(FetchContent)
    FetchContent_Declare(
        yamlcpp
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/jbeder/yaml-cpp/archive/refs/tags/${YAMLCPP_VERSION}.tar.gz
        )
    set(YAML_CPP_BUILD_TESTS OFF)
    FetchContent_GetProperties(yamlcpp)
    if (NOT yamlcpp_POPULATED) # Have we downloaded yamlcpp yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(yamlcpp)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${yamlcpp_SOURCE_DIR} ${yamlcpp_BINARY_DIR})
    endif()
endif()


add_library(dep::yamlcpp ALIAS yaml-cpp)


