#include "../../include/board.h"
#include <board.h>

class Enemy {
public:
    Enemy() = default;
    Board move_piece(Board);
    std::string serializeBoard(Board& board);
    Board deserializeBoard(const std::string& data);

private:
    Board board;

};