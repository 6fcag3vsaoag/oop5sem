#include "D2.h"

// Конструктор
D2::D2(const std::string& n, int v, const std::string& prop) 
    : B(n, v), d2_property(prop) {
    // Конструктор инициализирует поля объекта и базового класса
}

// Виртуальный деструктор
D2::~D2() {
    // Виртуальный деструктор для правильного удаления объектов
}

// Переопределенная функция для вывода значений
void D2::show() const {
    std::cout << "Class D2: name = " << name << ", value = " << value 
              << ", d2_property = " << d2_property << std::endl;
}

// Геттеры
std::string D2::getD2Property() const {
    return d2_property;
}

std::string D2::getBName() const {
    return name;
}

int D2::getBValue() const {
    return value;
}