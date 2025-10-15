#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <algorithm>
#include <stdexcept>

// Перечисление для представления состояния ячейки на доске
enum class CellState {
    EMPTY = 0,
    X = 1,
    O = 2
};

// Класс для представления доски игры
class Board {
private:
    std::vector<std::vector<CellState>> grid;  // 3x3 сетка игры
    int size;

public:
    Board(int s = 3);
    
    // Геттеры
    CellState getCell(int row, int col) const;
    int getSize() const { return size; }
    
    // Сеттеры
    void setCell(int row, int col, CellState state);
    
    // Проверка, является ли ячейка пустой
    bool isCellEmpty(int row, int col) const;
    
    // Проверка, заполнена ли доска
    bool isFull() const;
    
    // Проверка победы
    bool checkWin(CellState player) const;
    
    // Получение всех пустых ячеек
    std::vector<std::pair<int, int>> getEmptyCells() const;
    
    // Вывод доски
    void display() const;
    
    // Сброс доски
    void reset();
};

// Абстрактный класс для игрока
class Player {
protected:
    CellState symbol;
    std::string name;

public:
    Player(CellState s, const std::string& n) : symbol(s), name(n) {}
    virtual ~Player() = default;
    
    CellState getSymbol() const { return symbol; }
    std::string getName() const { return name; }
    
    // Чисто виртуальная функция для получения хода
    virtual std::pair<int, int> getMove(const Board& board) = 0;
};

// Класс для игрока-человека
class HumanPlayer : public Player {
public:
    HumanPlayer(CellState s) : Player(s, s == CellState::X ? "Игрок (X)" : "Игрок (O)") {}
    
    std::pair<int, int> getMove(const Board& board) override;
};

// Класс для игрока-робота (компьютера)
class RobotPlayer : public Player {
private:
    std::mt19937 rng;

public:
    RobotPlayer(CellState s) : Player(s, s == CellState::X ? "Компьютер (X)" : "Компьютер (O)"), rng(std::random_device{}()) {}
    
    std::pair<int, int> getMove(const Board& board) override;
    
    // Внутренние методы для стратегии
    std::pair<int, int> findWinningMove(const Board& board, CellState player) const;
    std::pair<int, int> findBlockingMove(const Board& board) const;
};

// Класс для управления игрой
class TicTacToeGame {
private:
    Board board;
    Player* player1;  // X
    Player* player2;  // O
    Player* currentPlayer;
    bool gameEnded;

public:
    TicTacToeGame();
    ~TicTacToeGame();
    
    // Запуск игры
    void start();
    
    // Основной игровой цикл
    void play();
    
    // Проверка завершения игры
    bool isGameOver() const;
    
    // Определение победителя
    CellState getWinner() const;
    
    // Переключение текущего игрока
    void switchPlayer();
    
    // Вывод результата игры
    void displayResult() const;
};

#endif // TICTACTOE_H