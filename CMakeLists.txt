cmake_minimum_required(VERSION 3.16)
project(stl_containers LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(
    GLOB_RECURSE LIB_INCLUDE CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/include/*.h"
)
file(
    GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_library(stl_containers ${LIB_INCLUDE} ${LIB_SOURCES})
target_include_directories(stl_containers PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(tests)