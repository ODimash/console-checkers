#include "Enemy.h"

Board Enemy::move_piece(Board board) {
    Piece* b = board.getBoardValue();
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            int8_t current_cell = i * board_size + j;
            if (b[current_cell] != BLACK)
                continue;


            int naighbor_cells[] = { current_cell - 9, current_cell - 7, current_cell + 7, current_cell + 9 };
            int naighbor_of_naighbors[] = { current_cell - 9 * 2, current_cell - 7 * 2, current_cell + 7 * 2, current_cell + 9 * 2 };

            // Проверяем можно ли съесть что-то:
            for (int N = 0; N < 4; N++) {
                if (abs(naighbor_cells[N] % 8 - current_cell % 8) != 1)
                    continue;
                if (b[naighbor_cells[N]] != WHITE)
                    continue;
                if (b[naighbor_of_naighbors[N]] != EMPTY)
                    continue;

                b[naighbor_of_naighbors[N]] = b[current_cell];
                b[current_cell] = EMPTY;
                b[naighbor_cells[N]] = EMPTY;
                return board;

            }

            // Проверяем пустых полей для хода:
            for (int N = 0; N < 2; N++) {
                if (abs(naighbor_cells[N] % 8 - current_cell % 8) != 1)
                    continue;
                if (b[naighbor_cells[N]] != EMPTY)
                    continue;
                b[naighbor_cells[N]] = b[current_cell];
                b[current_cell] = EMPTY;
                return board;
            }

        }
    }

    return board;
}


std::string Enemy::serializeBoard(Board& board) {
    std::string result;
    result.resize(board_size * board_size); 

    // Копируем данные доски в строку
    memcpy(&result[0], board.getBoardValue(), board_size * board_size);

    return result;
}

Board Enemy::deserializeBoard(const std::string& data) {
    Board board;
    Piece new_board[board_size * board_size];

    memcpy(new_board, data.data(), board_size * board_size);

    board.setBoardValue(new_board);

    return board;
}
