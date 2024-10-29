#include "../include/enemyAPI.h"

EnemyAPI::EnemyAPI() {

    char buffer[1024];
    DWORD bytesRead, bytesWritten;

    hPipe = CreateNamedPipe(
        TEXT("\\\\.\\pipe\\EnemyPipe"),
        PIPE_ACCESS_DUPLEX,           // Двусторонний доступ
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,                            // Максимум 1 экземпляр канала
        1024,                         // Размер выходного буфера
        1024,                         // Размер входного буфера
        0,                            // Таймаут по умолчанию
        NULL                          // Атрибуты безопасности по умолчанию
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Ошибка создания канала." << std::endl;
        return;
    }

    if (!startEnemyProcess()) {
        throw std::runtime_error("Не удалось запустить процесс Enemy");
    }

    // Ожидаем подключения клиента (родительского процесса)
    if (!ConnectNamedPipe(hPipe, NULL)) {
        std::cerr << "Ошибка подключения клиента." << std::endl;
        CloseHandle(hPipe);
    }
}

EnemyAPI::~EnemyAPI() {
    stopEnemyProcess();
    CloseHandle(hPipe);
}

Board EnemyAPI::move_piece(Board& currentBoard) {
    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Канал не открыт. Невозможно выполнить ход." << std::endl;
        return currentBoard;
    }

    std::string serializedBoard = serializeBoard(currentBoard);

    DWORD bytesWritten;
    WriteFile(hPipe, serializedBoard.c_str(), serializedBoard.size() + 1, &bytesWritten, NULL);

    char buffer[1024];
    DWORD bytesRead;
    ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL);
    buffer[bytesRead] = '\0';

    return deserializeBoard(buffer);
}

std::string EnemyAPI::serializeBoard(Board& board) {
    std::string result;
    result.resize(board_size * board_size); // Резервируем место под строку

    // Копируем данные доски в строку
    memcpy(&result[0], board.getBoardValue(), board_size * board_size);

    return result;
}

// Метод десериализации строки в объект Board
Board EnemyAPI::deserializeBoard(const std::string& data) {
    Board board;
    Piece new_board[board_size * board_size];

    // Копируем данные строки обратно в массив доски
    memcpy(new_board, data.data(), board_size * board_size);

    // Устанавливаем новое значение для доски
    board.setBoardValue(new_board);

    return board;
}


bool EnemyAPI::startEnemyProcess() {
    LPSTR path = "Enemy\\enemy.exe";
    STARTUPINFO si;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(
        NULL,            // Имя исполняемого файла
        path,         // Командная строка
        NULL,            // Дескриптор защиты процесса
        NULL,            // Дескриптор защиты потока
        FALSE,           // Наследование дескрипторов
        CREATE_NEW_CONSOLE,               // Флаги создания
        NULL,            // Переменные окружения
        NULL,            // Текущий каталог
        &si,             // Указатель на информацию о запуске
        &pi)) {          // Указатель на информацию о процессе
        std::cerr << "Не удалось запустить процесс Enemy." << std::endl;
        return false;
    }

    return true;
}

// Метод для завершения процесса Enemy
void EnemyAPI::stopEnemyProcess() {
    // Ожидание завершения дочернего процесса и его закрытие
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}