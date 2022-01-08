cmake_minimum_required(VERSION 3.13)
project(POS_semestralnaPraca C)

set(CMAKE_C_STANDARD 99)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(main main.c)
add_executable(server server.c)
add_executable(client client.c)

target_link_libraries(main ${GTK3_LIBRARIES})
target_link_libraries(server pthread)
target_link_libraries(client pthread)