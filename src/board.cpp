#include "../include/board.h"

Board::Board() {
    set_starting_position();
}

void Board::set_starting_position() {
    for (int8_t i = 0; i < board_size; i++) {
        for (int8_t j = 0; j < board_size; j++) {
            bool isWhiteTerr = i < 3; // Белая территория
            bool isBlackTerr = i > 4; // Черная территория
            bool isBlackCell = (i+j)%2 == 0; // Черная квадрат

            board[i*board_size + j] = EMPTY;
            if (isBlackCell) {
                if (isWhiteTerr) 
                    board[i*board_size + j] = WHITE;
                else if (isBlackTerr) 
                    board[i*board_size + j] = BLACK;
            }
        }
    }

}


int Board::move(Path path) {
    Coord fromCell = path.from, toCell = path.to;

    if (get_piece(fromCell) != WHITE)
        return 1;
    if (get_piece(toCell) != EMPTY)
        return 2;

    bool areNeighbors = toCell.index - fromCell.index == 7 || toCell.index - fromCell.index == 9;

    if (areNeighbors) {
        board[toCell.index] = board[fromCell.index];
        board[fromCell.index] = EMPTY;
        return 0;
    }

    bool isEating = (abs(fromCell.index - toCell.index) == 14 || abs(fromCell.index - toCell.index) == 18)
        && get_piece(fromCell.index - (fromCell.index - toCell.index)/2 ) == BLACK;

    if (isEating) {
        board[toCell.index] = board[fromCell.index];
        board[fromCell.index] = EMPTY;
        board[fromCell.index - (fromCell.index - toCell.index)/2] = EMPTY;
        return 0;
    }

    return 3;
}

Piece Board::get_piece(Coord coord) {
    return board[coord.index];
}

void clearConsole() {
    // Получаем handle консоли
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Получаем информацию о буфере консоли
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // Рассчитываем количество символов в консоли
    DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Устанавливаем курсор в верхний левый угол
    COORD topLeft = { 0, 0 };
    SetConsoleCursorPosition(hConsole, topLeft);

    // Заполняем консоль пробелами
    DWORD written;
    FillConsoleOutputCharacter(hConsole, ' ', consoleSize, topLeft, &written);

    // Устанавливаем цвет фона (по желанию, можно установить цвет текста)
    SetConsoleTextAttribute(hConsole, csbi.wAttributes);

    // Возвращаем курсор в начало
    SetConsoleCursorPosition(hConsole, topLeft);
}

void Board::draw() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, {0,0});

    print_horizontal_border();
	for (int i = board_size-1; i >= 0; i--) {
	    for (int h = 0; h < 3; h++) {
	        printf("||");
	        for (int j = 0; j < board_size; j++) {
	            printf("|");
	            for (int w = 0; w < 7; w++) {
                    Piece current_cell = board[i*board_size + j];
					bool isEmpty = current_cell == EMPTY;
	                if (w == 3 && h == 1 && !isEmpty) {
	                    printf("%c", current_cell);
	                } else if ((i + j) % 2 == 0) {
	                    printf(" ");
	                } else {
	                    printf(":");
	                }
	            }
	            printf("||");
	        }
	        printf("|");
			if (h == 1) {
				printf("   %d", i+1);
			}
	        printf("\n");
	    }
	    print_horizontal_border();
	}
	print_letters();
}

Piece* Board::getBoardValue()
{
    return board;
}

void Board::setBoardValue(Piece* board)
{
    for (int i = 0; i < board_size * board_size; i++) {
        this->board[i] = board[i];
    }
}

void Board::rotateBoard()
{
    int cellCount = board_size * board_size;
    for (int i = 0; i < cellCount/2; i++) {
        Piece buffer = board[cellCount - 1 - i];
        board[cellCount - 1 - i] = board[i];
        board[i] = buffer;
    }
}

void Board::print_horizontal_border() {
    for (int i = 0; i < 83; i++)
        printf("|");
    printf("\n");
}

void Board::print_letters() {
	printf("\n");
	for (int i = 0; i < 8; i++) {
		printf("      ");
		printf("%c", 97 + i);
		printf("   ");
	}
	printf("\n\n");
}