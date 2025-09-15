#include <iostream>
#include <string>
#include <sstream>
#include "Parking.h"

int main() {
    // Создаем стоянку с вместимостью 10 автомобилей (можно изменить или сделать бесконечной)
    Parking parking(10);
    
    std::cout << "Garage Parking Simulation\n";
    std::cout << "Commands:\n";
    std::cout << "  a <number> - Arrive car with license plate <number>\n";
    std::cout << "  d <number> - Depart car with license plate <number>\n";
    std::cout << "  q - Quit\n\n";
    
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
            std::cout << "Goodbye!\n";
            break;
        } else if (command == "a" || command == "A") {
            int plateNumber;
            if (iss >> plateNumber) {
                Car car(plateNumber);
                parking.arrive(car);
            } else {
                std::cout << "Invalid command format. Use: a <number>\n";
            }
        } else if (command == "d" || command == "D") {
            int plateNumber;
            if (iss >> plateNumber) {
                parking.depart(plateNumber);
            } else {
                std::cout << "Invalid command format. Use: d <number>\n";
            }
        } else {
            std::cout << "Unknown command. Available commands: a, d, q\n";
        }
        
        // Отображаем текущее состояние стоянки
        parking.display();
        std::cout << "\n";
    }
    
    return 0;
}