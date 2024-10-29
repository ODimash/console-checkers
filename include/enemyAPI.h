#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include "board.h" 

class EnemyAPI {
public:
    EnemyAPI();
    ~EnemyAPI();

    Board move_piece(Board& currentBoard);

private:
    HANDLE hPipe;
    PROCESS_INFORMATION pi;

    std::string serializeBoard(Board& board);
    Board deserializeBoard(const std::string& data);
    bool startEnemyProcess();
    void stopEnemyProcess();
};
