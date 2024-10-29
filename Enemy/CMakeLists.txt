cmake_minimum_required(VERSION 3.0)
project(Enemy)

# Указываем директорию с заголовочными файлами родительского проекта
include_directories( include)

# Указываем исходные файлы проекта Enemy
file(GLOB SOURCES "src/*.cpp")

# Компилируем проект Enemy, указывая Board.cpp из родительского проекта
add_executable(enemy ${SOURCES} ${CMAKE_SOURCE_DIR}/src/board.cpp)
target_link_libraries(enemy board_lib)

