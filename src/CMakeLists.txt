cmake_minimum_required(VERSION 4.5)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER /usr/bin/clang)


project(graph
  LANGUAGES C
)
add_compile_options(-Wall -Wextra -fsanitize=address -g)
add_link_options(-Wall -Wextra -fsanitize=address -g)
add_library(types STATIC types.c)
add_library(list STATIC list.c)
add_executable(graph graph.c)
target_link_libraries(types PRIVATE list)
target_link_libraries(graph PRIVATE list)
