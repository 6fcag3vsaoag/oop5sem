#include <iostream>
#include "B.h"
#include "D1.h"
#include "D2.h"
#include "D3.h"
#include "D4.h"

int main() {
    std::cout << "=== Демонстрация иерархии наследования ===" << std::endl;
    
    // Создание объекта базового класса B
    B b("Base", 10);
    std::cout << "1. Базовый класс B:" << std::endl;
    b.show();
    std::cout << std::endl;
    
    // Создание объекта класса D1 (наследуется от B публично)
    D1 d1("D1_Object", 20, "D1_Prop");
    std::cout << "2. Класс D1 (наследуется от B публично):" << std::endl;
    d1.show();
    std::cout << std::endl;
    
    // Создание объекта класса D2 (наследуется от B приватно)
    D2 d2("D2_Object", 30, "D2_Prop");
    std::cout << "3. Класс D2 (наследуется от B приватно):" << std::endl;
    d2.show();
    std::cout << std::endl;
    
    // Создание объекта класса D3 (наследуется от D1 приватно)
    D3 d3("D3_Object", 40, "D1_Prop", "D3_Prop");
    std::cout << "4. Класс D3 (наследуется от D1 приватно):" << std::endl;
    d3.show();
    std::cout << std::endl;
    
    // Создание объекта класса D4 (наследуется от D2 публично)
    D4 d4("D4_Object", 50, "D2_Prop", "D4_Prop");
    std::cout << "5. Класс D4 (наследуется от D2 публично):" << std::endl;
    d4.show();
    std::cout << std::endl;
    
    return 0;
}