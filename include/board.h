#pragma once

#include <stdio.h>
#include <cstdlib>
#include <cstdint>
#include <Windows.h>
#include <string>
#include "coordination.h"

enum Piece : char {EMPTY = ' ', WHITE = '@', BLACK = '#'};

constexpr int8_t board_size = 8;

class Board {
public:
    Board();
    void set_starting_position();
    int move(Path);
    Piece get_piece(Coord);
    void draw();
    Piece* getBoardValue();
    void setBoardValue(Piece* board);
    void rotateBoard();

private:
    Piece board[board_size * board_size];
    void print_horizontal_border();
    void print_letters();
};