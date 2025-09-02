#include "D3.h"

// Конструктор
D3::D3(const std::string& n, int v, const std::string& prop1, const std::string& prop2) 
    : D1(n, v, prop1), d3_property(prop2) {
    // Конструктор инициализирует поля объекта и базового класса
}

// Виртуальный деструктор
D3::~D3() {
    // Виртуальный деструктор для правильного удаления объектов
}

// Переопределенная функция для вывода значений
void D3::show() const {
    std::cout << "Class D3: name = " << name << ", value = " << value 
              << ", d1_property = " << getD1Property() 
              << ", d3_property = " << d3_property << std::endl;
}

// Геттер
std::string D3::getD3Property() const {
    return d3_property;
}