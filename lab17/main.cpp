#include <iostream>
#include <locale>
#include "TicTacToe.h"

int main() {
    // Установка локали для поддержки русского языка
    std::locale::global(std::locale(""));
    
    std::cout << "Добро пожаловать в игру Крестики-Нолики!" << std::endl;
    
    TicTacToeGame game;
    game.start();
    
    std::cout << "Спасибо за игру!" << std::endl;
    
    return 0;
}