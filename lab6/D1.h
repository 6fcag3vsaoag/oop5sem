#ifndef D1_H
#define D1_H

#include "B.h"
#include <iostream>
#include <string>

class D1 : public B {
private:
    std::string d1_property;

public:
    // Конструктор
    D1(const std::string& n, int v, const std::string& prop);
    
    // Виртуальный деструктор
    virtual ~D1();
    
    // Переопределенная функция для вывода значений
    virtual void show() const;
    
    // Геттер
    std::string getD1Property() const;
};

#endif // D1_H