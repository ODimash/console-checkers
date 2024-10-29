cmake_minimum_required(VERSION 3.0) 
project(Checkers)

include_directories(include ../include/board.h)

file(GLOB SOURCES "src/*.cpp")
file(GLOB BOARD_SOURCES "src/board.cpp" "src/coordination.cpp")

add_library(board_lib STATIC ${BOARD_SOURCES})

add_executable(checkers ${SOURCES})
target_link_libraries(checkers board_lib)

#target_include_directories(checkers PRIVATE include)
add_subdirectory(Enemy)
