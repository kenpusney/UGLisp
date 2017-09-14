cmake_minimum_required (VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

project(ugl)

add_subdirectory(src)
add_subdirectory(test)

include_directories(include)

add_executable(ugl src/main.c)

target_link_libraries(ugl libugl)
