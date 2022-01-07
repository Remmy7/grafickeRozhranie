cmake_minimum_required(VERSION 3.13)
project(posSemka C)

set(CMAKE_C_STANDARD 99)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
# Add other flags to the compiler
add_definitions(${GTK3_CFLAGS_OTHER})
# Add an executable compiled from hello.c

# Link the target to the GTK+ libraries



add_executable(main main.c)
add_executable(server server.c)
add_executable(client client.c)

target_link_libraries(main ${GTK3_LIBRARIES})
target_link_libraries(server pthread)
target_link_libraries(client pthread)