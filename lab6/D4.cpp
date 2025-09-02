#include "D4.h"

// Конструктор
D4::D4(const std::string& n, int v, const std::string& prop1, const std::string& prop2) 
    : D2(n, v, prop1), d4_property(prop2) {
    // Конструктор инициализирует поля объекта и базового класса
}

// Виртуальный деструктор
D4::~D4() {
    // Виртуальный деструктор для правильного удаления объектов
}

// Переопределенная функция для вывода значений
void D4::show() const {
    std::cout << "Class D4: name = " << getBName() << ", value = " << getBValue() 
              << ", d2_property = " << getD2Property() 
              << ", d4_property = " << d4_property << std::endl;
}

// Геттер
std::string D4::getD4Property() const {
    return d4_property;
}