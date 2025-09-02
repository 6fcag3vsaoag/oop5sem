#include "D1.h"

// Конструктор
D1::D1(const std::string& n, int v, const std::string& prop) 
    : B(n, v), d1_property(prop) {
    // Конструктор инициализирует поля объекта и базового класса
}

// Виртуальный деструктор
D1::~D1() {
    // Виртуальный деструктор для правильного удаления объектов
}

// Переопределенная функция для вывода значений
void D1::show() const {
    std::cout << "Class D1: name = " << name << ", value = " << value 
              << ", d1_property = " << d1_property << std::endl;
}

// Геттер
std::string D1::getD1Property() const {
    return d1_property;
}