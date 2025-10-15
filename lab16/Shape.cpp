#include "Shape.h"
#include <iostream>

void Shape::display() const {
    std::cout << "Фигура: " << name << std::endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (matrix[i][j] == 1) {
                std::cout << "[]";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}