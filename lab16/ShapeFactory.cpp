#include "ShapeFactory.h"
#include <random>
#include <ctime>

// Инициализация фабрики обычных фигур
RegularShapeFactory::RegularShapeFactory() : rng(std::time(nullptr)) {
    // Определяем обычные фигуры Тетриса
    // I-фигура (4 блока в линию)
    std::vector<std::vector<int>> iShape = {
        {1, 1, 1, 1}
    };
    
    regularShapes.push_back(iShape);
    shapeNames.push_back("I-фигура");
    
    // O-фигура (квадрат 2x2)
    std::vector<std::vector<int>> oShape = {
        {1, 1},
        {1, 1}
    };
    
    regularShapes.push_back(oShape);
    shapeNames.push_back("O-фигура");
    
    // T-фигура
    std::vector<std::vector<int>> tShape = {
        {0, 1, 0},
        {1, 1, 1}
    };
    
    regularShapes.push_back(tShape);
    shapeNames.push_back("T-фигура");
    
    // S-фигура
    std::vector<std::vector<int>> sShape = {
        {0, 1, 1},
        {1, 1, 0}
    };
    
    regularShapes.push_back(sShape);
    shapeNames.push_back("S-фигура");
    
    // Z-фигура
    std::vector<std::vector<int>> zShape = {
        {1, 1, 0},
        {0, 1, 1}
    };
    
    regularShapes.push_back(zShape);
    shapeNames.push_back("Z-фигура");
    
    // J-фигура
    std::vector<std::vector<int>> jShape = {
        {1, 0, 0},
        {1, 1, 1}
    };
    
    regularShapes.push_back(jShape);
    shapeNames.push_back("J-фигура");
    
    // L-фигура
    std::vector<std::vector<int>> lShape = {
        {0, 0, 1},
        {1, 1, 1}
    };
    
    regularShapes.push_back(lShape);
    shapeNames.push_back("L-фигура");
}

std::unique_ptr<Shape> RegularShapeFactory::createShape() {
    std::uniform_int_distribution<int> dist(0, regularShapes.size() - 1);
    int index = dist(rng);
    
    auto& shapeMatrix = regularShapes[index];
    int height = shapeMatrix.size();
    int width = shapeMatrix[0].size();
    
    return std::make_unique<RegularShape>(width, height, shapeNames[index], shapeMatrix);
}

// Инициализация фабрики супер-фигур
SuperShapeFactory::SuperShapeFactory() : rng(std::time(nullptr)) {
    // Определяем супер-фигуры (фигуры с большим числом клеток)
    // Большая L-фигура
    std::vector<std::vector<int>> bigLShape = {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 1, 1}
    };
    
    superShapes.push_back(bigLShape);
    shapeNames.push_back("Большая L-фигура");
    
    // Крест-фигура
    std::vector<std::vector<int>> crossShape = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0}
    };
    
    superShapes.push_back(crossShape);
    shapeNames.push_back("Крест-фигура");
    
    // Большая T-фигура
    std::vector<std::vector<int>> bigTShape = {
        {1, 1, 1, 1},
        {0, 0, 1, 0, 0}
    };
    
    superShapes.push_back(bigTShape);
    shapeNames.push_back("Большая T-фигура");
    
    // Змея-фигура
    std::vector<std::vector<int>> snakeShape = {
        {1, 1, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 1}
    };
    
    superShapes.push_back(snakeShape);
    shapeNames.push_back("Змея-фигура");
}

std::unique_ptr<Shape> SuperShapeFactory::createShape() {
    std::uniform_int_distribution<int> dist(0, superShapes.size() - 1);
    int index = dist(rng);
    
    auto& shapeMatrix = superShapes[index];
    int height = shapeMatrix.size();
    int width = shapeMatrix[0].size();
    
    return std::make_unique<SuperShape>(width, height, shapeNames[index], shapeMatrix);
}

// Инициализация игры Тетрис
TetrisGame::TetrisGame() : rng(std::time(nullptr)), distribution(0, 99) {
    regularFactory = std::make_unique<RegularShapeFactory>();
    superFactory = std::make_unique<SuperShapeFactory>();
}

std::unique_ptr<Shape> TetrisGame::createRandomShape() {
    return regularFactory->createShape();
}

std::unique_ptr<Shape> TetrisGame::createRandomShapeWithSuper() {
    // 20% шанс на создание супер-фигуры
    int chance = distribution(rng);
    if (chance < 20) { // 20% шанс
        return superFactory->createShape();
    } else {
        return regularFactory->createShape();
    }
}