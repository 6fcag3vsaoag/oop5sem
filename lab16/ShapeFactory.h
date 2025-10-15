#ifndef SHAPE_FACTORY_H
#define SHAPE_FACTORY_H

#include "Shape.h"
#include <memory>
#include <vector>
#include <random>

// Абстрактный класс фабрики для создания фигур
class ShapeFactory {
public:
    virtual ~ShapeFactory() = default;
    virtual std::unique_ptr<Shape> createShape() = 0;
};

// Конкретная фабрика для создания обычных фигур
class RegularShapeFactory : public ShapeFactory {
private:
    std::vector<std::vector<std::vector<int>>> regularShapes;  // Вектор матриц фигур
    std::vector<std::string> shapeNames;
    std::mt19937 rng;

public:
    RegularShapeFactory();
    std::unique_ptr<Shape> createShape() override;
};

// Конкретная фабрика для создания супер-фигур
class SuperShapeFactory : public ShapeFactory {
private:
    std::vector<std::vector<std::vector<int>>> superShapes;  // Вектор матриц фигур
    std::vector<std::string> shapeNames;
    std::mt19937 rng;

public:
    SuperShapeFactory();
    std::unique_ptr<Shape> createShape() override;
};

// Класс для управления созданием фигур с использованием паттерна Factory Method
class TetrisGame {
private:
    std::unique_ptr<RegularShapeFactory> regularFactory;
    std::unique_ptr<SuperShapeFactory> superFactory;
    std::mt19937 rng;
    std::uniform_int_distribution<int> distribution;

public:
    TetrisGame();
    
    // Метод для создания случайной фигуры (Factory Method)
    std::unique_ptr<Shape> createRandomShape();
    
    // Метод для создания случайной фигуры с возможностью супер-фигуры
    std::unique_ptr<Shape> createRandomShapeWithSuper();
};

#endif // SHAPE_FACTORY_H