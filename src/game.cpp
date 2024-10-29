#include "../include/game.h"


void Game::start() {
    gameOver = false;
    board.draw();
    EnemyAPI enemy;
    while (!gameOver) {
        while (move_piece()) {
            getchar();
            printf("Қате енгздіңі!\n");
        }
        Board newBoard = enemy.move_piece(board);
        board = newBoard;
        
        board.draw();
    }
    printf("Противник проиграл!\n");
}

int Game::move_piece() {
    Path path = ask_path();
    return board.move(path);
}

void clearCurrentLine() {
    // Получаем handle консоли
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Получаем информацию о буфере экрана
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // Получаем текущую позицию курсора
    COORD cursorPos = csbi.dwCursorPosition;

    // Устанавливаем курсор в начало текущей строки
    SetConsoleCursorPosition(hConsole, { 0, cursorPos.Y });

    // Заполняем строку пробелами
    DWORD written;
    FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X, { 0, cursorPos.Y }, &written);

    // Возвращаем курсор в ту же позицию
    SetConsoleCursorPosition(hConsole, cursorPos);
}

Path Game::ask_path() {
    clearCurrentLine();
    char fromLetter = 0, toLetter = 0;
    char fromNumber = 0, toNumber = 0;
    printf("Дойбының қазіргі және жүретін нүктесін енгізіңіз: ");
    scanf("%c%c %c%c", &fromLetter, &fromNumber, &toLetter, &toNumber);
    getchar();
    return Path({fromNumber, fromLetter}, {toNumber, toLetter}); 
}