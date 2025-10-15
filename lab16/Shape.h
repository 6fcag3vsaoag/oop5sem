#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <memory>
#include <string>

// Класс для представления фигуры в игре Тетрис
class Shape {
protected:
    std::vector<std::vector<int>> matrix;  // Матрица фигуры (0 - пустая клетка, 1 - занятая)
    int width;                            // Ширина матрицы
    int height;                           // Высота матрицы
    std::string name;                     // Название фигуры

public:
    Shape(int w, int h, const std::string& n) : width(w), height(h), name(n) {
        matrix.resize(height, std::vector<int>(width, 0));
    }

    virtual ~Shape() = default;

    // Получить ширину фигуры
    int getWidth() const { return width; }

    // Получить высоту фигуры
    int getHeight() const { return height; }

    // Получить название фигуры
    std::string getName() const { return name; }

    // Получить матрицу фигуры
    const std::vector<std::vector<int>>& getMatrix() const { return matrix; }

    // Проверить, занята ли клетка в позиции (row, col)
    bool isCellOccupied(int row, int col) const {
        if (row < 0 || row >= height || col < 0 || col >= width) {
            return false;
        }
        return matrix[row][col] == 1;
    }

    // Вывести фигуру в консоль
    virtual void display() const;
};

// Класс для обычной фигуры (обычная фигура Тетриса)
class RegularShape : public Shape {
public:
    RegularShape(int w, int h, const std::string& n, const std::vector<std::vector<int>>& mat) 
        : Shape(w, h, n) {
        matrix = mat;
    }
};

// Класс для супер-фигуры (фигура с большим числом клеток)
class SuperShape : public Shape {
public:
    SuperShape(int w, int h, const std::string& n, const std::vector<std::vector<int>>& mat) 
        : Shape(w, h, n) {
        matrix = mat;
    }
};

#endif // SHAPE_H