cmake_minimum_required(VERSION 3.0)
project(Enemy)

# ��������� ���������� � ������������� ������� ������������� �������
include_directories( include)

# ��������� �������� ����� ������� Enemy
file(GLOB SOURCES "src/*.cpp")

# ����������� ������ Enemy, �������� Board.cpp �� ������������� �������
add_executable(enemy ${SOURCES} ${CMAKE_SOURCE_DIR}/src/board.cpp)
target_link_libraries(enemy board_lib)

