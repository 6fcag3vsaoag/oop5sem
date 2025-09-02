#ifndef D3_H
#define D3_H

#include "D1.h"
#include <iostream>
#include <string>

class D3 : private D1 {
private:
    std::string d3_property;

public:
    // Конструктор
    D3(const std::string& n, int v, const std::string& prop1, const std::string& prop2);
    
    // Виртуальный деструктор
    virtual ~D3();
    
    // Переопределенная функция для вывода значений
    virtual void show() const;
    
    // Геттер
    std::string getD3Property() const;
};

#endif // D3_H