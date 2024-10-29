#pragma once

#include "board.h"
#include "enemyAPI.h"

#include <windows.h>
#include <iostream>



class Game {
public:
    bool gameOver;
    Game() = default;
    void start();
    
private:
    int move_piece();
    Path ask_path();
    Board board;
};