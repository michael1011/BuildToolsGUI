cmake_minimum_required(VERSION 3.6)
project(BuildToolsGUI)

set(CMAKE_C_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(PkgConfig REQUIRED)
find_package(CURL REQUIRED)
find_package(Threads REQUIRED)

pkg_search_module(OPENSSL REQUIRED openssl)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${CURL_INCLUDE_DIR})
include_directories(${OPENSSL_INCLUDE_DIRS})
include_directories(${GTK3_INCLUDE_DIRS})

link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*)
add_executable(BuildToolsGUI ${SRC_FILES})

target_link_libraries(BuildToolsGUI ${GTK3_LIBRARIES})
target_link_libraries(BuildToolsGUI ${CURL_LIBRARIES})
target_link_libraries(BuildToolsGUI ${OPENSSL_LIBRARIES})
target_link_libraries(BuildToolsGUI Threads::Threads)