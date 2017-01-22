cmake_minimum_required(VERSION 3.6)
project(BuildToolsGUI)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.20)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
add_executable(BuildToolsGUI ${SRC_FILES})

target_link_libraries(BuildToolsGUI ${GTK3_LIBRARIES})