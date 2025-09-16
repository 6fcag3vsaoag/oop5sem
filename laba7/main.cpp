#include <iostream>
#include <string>
#include <sstream>
#include "Parking.h"

// Для поддержки русского языка в консоли Windows
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    // Установка кодовой страницы для поддержки русского языка в консоли Windows
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif
    
    // Создаем стоянку с вместимостью 10 автомобилей (можно изменить или сделать бесконечной)
    Parking parking(10);
    
    std::cout << "Моделирование гаражной стоянки\n";
    std::cout << "Команды:\n";
    std::cout << "  a <номер> - Прибытие автомобиля с номером <номер>\n";
    std::cout << "  d <номер> - Отъезд автомобиля с номером <номер>\n";
    std::cout << "  q - Выход\n\n";
    
    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        
        if (input.empty()) {
            continue;
        }
        
        // Парсим команду
        std::istringstream iss(input);
        std::string command;
        iss >> command;
        
        if (command == "q" || command == "Q") {
            std::cout << "До свидания!\n";
            break;
        } else if (command == "a" || command == "A") {
            int plateNumber;
            if (iss >> plateNumber) {
                Car car(plateNumber);
                parking.arrive(car);
            } else {
                std::cout << "Неверный формат команды. Используйте: a <номер>\n";
            }
        } else if (command == "d" || command == "D") {
            int plateNumber;
            if (iss >> plateNumber) {
                parking.depart(plateNumber);
            } else {
                std::cout << "Неверный формат команды. Используйте: d <номер>\n";
            }
        } else {
            std::cout << "Неизвестная команда. Доступные команды: a, d, q\n";
        }
        
        // Отображаем текущее состояние стоянки
        parking.display();
        std::cout << "\n";
    }
    
    return 0;
}