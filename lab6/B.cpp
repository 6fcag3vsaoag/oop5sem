#include "B.h"

// Конструктор
B::B(const std::string& n, int v) : name(n), value(v) {
    // Конструктор инициализирует поля объекта
}

// Виртуальный деструктор
B::~B() {
    // Виртуальный деструктор для правильного удаления объектов
}

// Функция для вывода значений
void B::show() const {
    std::cout << "Class B: name = " << name << ", value = " << value << std::endl;
}

// Геттеры
std::string B::getName() const {
    return name;
}

int B::getValue() const {
    return value;
}