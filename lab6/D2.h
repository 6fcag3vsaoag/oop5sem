#ifndef D2_H
#define D2_H

#include "B.h"
#include <iostream>
#include <string>

class D2 : private B {
private:
    std::string d2_property;

public:
    // Конструктор
    D2(const std::string& n, int v, const std::string& prop);
    
    // Виртуальный деструктор
    virtual ~D2();
    
    // Переопределенная функция для вывода значений
    virtual void show() const;
    
    // Геттеры
    std::string getD2Property() const;
    std::string getBName() const;
    int getBValue() const;
};

#endif // D2_H