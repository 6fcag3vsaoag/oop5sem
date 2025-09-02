#ifndef D4_H
#define D4_H

#include "D2.h"
#include <iostream>
#include <string>

class D4 : public D2 {
private:
    std::string d4_property;

public:
    // Конструктор
    D4(const std::string& n, int v, const std::string& prop1, const std::string& prop2);
    
    // Виртуальный деструктор
    virtual ~D4();
    
    // Переопределенная функция для вывода значений
    virtual void show() const;
    
    // Геттер
    std::string getD4Property() const;
};

#endif // D4_H