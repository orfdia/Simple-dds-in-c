cmake_minimum_required(VERSION 4.5)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER /usr/bin/clang)


project(graph
  LANGUAGES C
)
add_compile_options(-Wall -Wextra -fsanitize=address)
add_link_options(-Wall -Wextra -fsanitize=address)
add_library(types STATIC types.c)
add_library(list STATIC list.c)
add_library(vector STATIC vector.c)
add_executable(graph graph.c)
target_link_libraries(types PRIVATE list)
target_link_libraries(types PRIVATE vector)
target_link_libraries(graph PRIVATE list PRIVATE vector)
