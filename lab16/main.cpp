#include <iostream>
#include <locale>
#include "Shape.h"
#include "ShapeFactory.h"

int main() {
    // Установка локали для поддержки русского языка
    std::locale::global(std::locale(""));
    
    std::cout << "=== Демонстрация паттерна Factory Method ===" << std::endl;
    std::cout << "Игра Тетрис - случайный выбор фигур" << std::endl << std::endl;
    
    // Создаем игру Тетрис
    TetrisGame game;
    
    std::cout << "1. Создание обычных фигур:" << std::endl;
    for (int i = 0; i < 5; i++) {
        auto shape = game.createRandomShape();
        shape->display();
    }
    
    std::cout << "\n2. Создание фигур с возможностью супер-фигур:" << std::endl;
    for (int i = 0; i < 10; i++) {
        auto shape = game.createRandomShapeWithSuper();
        shape->display();
        std::cout << "(Тип: " << shape->getName() << ")" << std::endl;
    }
    
    std::cout << "\n=== Демонстрация завершена ===" << std::endl;
    
    return 0;
}