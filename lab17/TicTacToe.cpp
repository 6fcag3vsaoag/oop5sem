#include "TicTacToe.h"

// Реализация класса Board
Board::Board(int s) : size(s) {
    grid.resize(size, std::vector<CellState>(size, CellState::EMPTY));
}

CellState Board::getCell(int row, int col) const {
    if (row < 0 || row >= size || col < 0 || col >= size) {
        throw std::out_of_range("Некорректные координаты ячейки");
    }
    return grid[row][col];
}

void Board::setCell(int row, int col, CellState state) {
    if (row < 0 || row >= size || col < 0 || col >= size) {
        throw std::out_of_range("Некорректные координаты ячейки");
    }
    grid[row][col] = state;
}

bool Board::isCellEmpty(int row, int col) const {
    return getCell(row, col) == CellState::EMPTY;
}

bool Board::isFull() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (grid[i][j] == CellState::EMPTY) {
                return false;
            }
        }
    }
    return true;
}

bool Board::checkWin(CellState player) const {
    // Проверка строк
    for (int i = 0; i < size; i++) {
        bool win = true;
        for (int j = 0; j < size; j++) {
            if (grid[i][j] != player) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }

    // Проверка столбцов
    for (int j = 0; j < size; j++) {
        bool win = true;
        for (int i = 0; i < size; i++) {
            if (grid[i][j] != player) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }

    // Проверка диагоналей
    bool win = true;
    for (int i = 0; i < size; i++) {
        if (grid[i][i] != player) {
            win = false;
            break;
        }
    }
    if (win) return true;

    win = true;
    for (int i = 0; i < size; i++) {
        if (grid[i][size - 1 - i] != player) {
            win = false;
            break;
        }
    }
    if (win) return true;

    return false;
}

std::vector<std::pair<int, int>> Board::getEmptyCells() const {
    std::vector<std::pair<int, int>> emptyCells;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (grid[i][j] == CellState::EMPTY) {
                emptyCells.push_back({i, j});
            }
        }
    }
    return emptyCells;
}

void Board::display() const {
    std::cout << "\n  ";
    for (int j = 0; j < size; j++) {
        std::cout << "  " << j << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < size; i++) {
        std::cout << i << " ";
        for (int j = 0; j < size; j++) {
            std::cout << "| ";
            switch (grid[i][j]) {
                case CellState::X:
                    std::cout << "X";
                    break;
                case CellState::O:
                    std::cout << "O";
                    break;
                case CellState::EMPTY:
                    std::cout << " ";
                    break;
            }
            std::cout << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}

void Board::reset() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j] = CellState::EMPTY;
        }
    }
}

// Реализация класса HumanPlayer
std::pair<int, int> HumanPlayer::getMove(const Board& board) {
    int row, col;
    do {
        std::cout << name << ", введите координаты (строка столбец): ";
        std::cin >> row >> col;
        
        if (row < 0 || row >= board.getSize() || col < 0 || col >= board.getSize()) {
            std::cout << "Некорректные координаты! Пожалуйста, введите значения от 0 до " << board.getSize() - 1 << std::endl;
            continue;
        }
        
        if (!board.isCellEmpty(row, col)) {
            std::cout << "Ячейка занята! Выберите другую." << std::endl;
            continue;
        }
        
        break;
    } while (true);
    
    return {row, col};
}

// Реализация класса RobotPlayer
std::pair<int, int> RobotPlayer::getMove(const Board& board) {
    std::cout << name << " делает ход..." << std::endl;
    
    // Попробуем найти выигрышный ход
    auto winningMove = findWinningMove(board, symbol);
    if (winningMove.first != -1) {
        return winningMove;
    }
    
    // Попробуем заблокировать выигрыш противника
    auto blockingMove = findBlockingMove(board);
    if (blockingMove.first != -1) {
        return blockingMove;
    }
    
    // Если нет стратегических ходов, выбираем случайный пустой
    auto emptyCells = board.getEmptyCells();
    if (!emptyCells.empty()) {
        std::uniform_int_distribution<int> dist(0, emptyCells.size() - 1);
        int index = dist(rng);
        return emptyCells[index];
    }
    
    // Если доска заполнена, возвращаем неверные координаты
    return {-1, -1};
}

std::pair<int, int> RobotPlayer::findWinningMove(const Board& board, CellState player) const {
    auto emptyCells = board.getEmptyCells();
    
    for (auto& cell : emptyCells) {
        Board tempBoard = board; // Копируем доску
        tempBoard.setCell(cell.first, cell.second, player);
        
        if (tempBoard.checkWin(player)) {
            return cell; // Нашли выигрышный ход
        }
    }
    
    return {-1, -1}; // Не найдено
}

std::pair<int, int> RobotPlayer::findBlockingMove(const Board& board) const {
    CellState opponent = (symbol == CellState::X) ? CellState::O : CellState::X;
    return findWinningMove(board, opponent); // Ищем выигрышный ход противника и блокируем его
}

// Реализация класса TicTacToeGame
TicTacToeGame::TicTacToeGame() : board(3), gameEnded(false) {
    player1 = new HumanPlayer(CellState::X);
    player2 = new RobotPlayer(CellState::O);
    currentPlayer = player1; // Человек начинает первым
}

TicTacToeGame::~TicTacToeGame() {
    delete player1;
    delete player2;
}

void TicTacToeGame::start() {
    std::cout << "=== Игра Крестики-Нолики ===" << std::endl;
    std::cout << "Вы играете за X, компьютер за O" << std::endl;
    
    play();
}

void TicTacToeGame::play() {
    while (!isGameOver()) {
        board.display();
        
        std::cout << "Ходит: " << currentPlayer->getName() << std::endl;
        
        auto move = currentPlayer->getMove(board);
        
        if (move.first == -1) {
            std::cout << "Нет доступных ходов!" << std::endl;
            gameEnded = true;
            break;
        }
        
        board.setCell(move.first, move.second, currentPlayer->getSymbol());
        
        if (board.checkWin(currentPlayer->getSymbol())) {
            gameEnded = true;
            board.display();
            std::cout << "Поздравляем! " << currentPlayer->getName() << " выиграл!" << std::endl;
            break;
        }
        
        if (board.isFull()) {
            gameEnded = true;
            board.display();
            std::cout << "Ничья!" << std::endl;
            break;
        }
        
        switchPlayer();
    }
    
    displayResult();
}

bool TicTacToeGame::isGameOver() const {
    return gameEnded;
}

CellState TicTacToeGame::getWinner() const {
    if (board.checkWin(CellState::X)) {
        return CellState::X;
    } else if (board.checkWin(CellState::O)) {
        return CellState::O;
    }
    return CellState::EMPTY; // Ничья или игра не завершена
}

void TicTacToeGame::switchPlayer() {
    currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

void TicTacToeGame::displayResult() const {
    std::cout << "\n=== Игра завершена ===" << std::endl;
    
    CellState winner = getWinner();
    if (winner == CellState::X) {
        std::cout << "Победитель: " << player1->getName() << std::endl;
    } else if (winner == CellState::O) {
        std::cout << "Победитель: " << player2->getName() << std::endl;
    } else {
        std::cout << "Ничья!" << std::endl;
    }
}