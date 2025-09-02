#ifndef B_H
#define B_H

#include <iostream>
#include <string>

class B {
protected:
    std::string name;
    int value;

public:
    // Конструктор
    B(const std::string& n, int v);
    
    // Виртуальный деструктор
    virtual ~B();
    
    // Функция для вывода значений
    virtual void show() const;
    
    // Геттеры
    std::string getName() const;
    int getValue() const;
};

#endif // B_H