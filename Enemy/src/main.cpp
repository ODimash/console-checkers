#include <windows.h>
#include <iostream>
#include "Enemy.h" 

int main() {
    SetConsoleOutputCP(CP_UTF8);

    HANDLE hPipe = CreateFile(
        TEXT("\\\\.\\pipe\\EnemyPipe"),   // ��� ������
        GENERIC_READ | GENERIC_WRITE,     // ������ �� ������ � ������
        0,                                // ��� �������
        NULL,                             // �������� ������������ �� ���������
        OPEN_EXISTING,                    // ��������� ������������ �����
        0,                                // �������� �� ���������
        NULL                              // ��� �������
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "������ ����������� � Enemy ����� ����������� �����." << std::endl;
    }



    char buffer[1024];
    DWORD bytesRead, bytesWritten;

    Enemy enemy;

    while (true) {
        // ������ ������ �� ������������� �������� (������� ��������� �����)
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
