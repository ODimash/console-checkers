#include <windows.h>
#include <iostream>
#include "Enemy.h" 

int main() {
    SetConsoleOutputCP(CP_UTF8);

    HANDLE hPipe = CreateFile(
        TEXT("\\\\.\\pipe\\EnemyPipe"),   // Имя канала
        GENERIC_READ | GENERIC_WRITE,     // Доступ на чтение и запись
        0,                                // Без шаринга
        NULL,                             // Атрибуты безопасности по умолчанию
        OPEN_EXISTING,                    // Открываем существующий канал
        0,                                // Атрибуты по умолчанию
        NULL                              // Без шаблона
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Ошибка подключения к Enemy через именованный канал." << std::endl;
    }



    char buffer[1024];
    DWORD bytesRead, bytesWritten;

    Enemy enemy;

    while (true) {
        // Читаем данные от родительского процесса (текущее состояние доски)
        ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL);
        buffer[bytesRead] = '\0';

        Board currentBoard = enemy.deserializeBoard(buffer);
        
        Board newBoard = enemy.move_piece(currentBoard);
        std::string serializedNewBoard = enemy.serializeBoard(newBoard);
        WriteFile(hPipe, serializedNewBoard.c_str(), serializedNewBoard.size() + 1, &bytesWritten, NULL);

        newBoard.rotateBoard();
        newBoard.draw();
    }

    CloseHandle(hPipe);
    return 0;
}
