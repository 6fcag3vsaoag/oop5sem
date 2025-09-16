#include <iostream>
#include <string>
#include <sstream>
#include "Parking.h"
#include "Transaction.h"
#include "smart_demo.h"

// Для поддержки русского языка в консоли Windows
#ifdef _WIN32
#include <windows.h>
#endif

class ParkingTransactionDemo {
private:
    Parking parking;
    std::shared_ptr<Car> selectedCar;
    std::unique_ptr<Transaction<Car>> activeTransaction;

public:
    ParkingTransactionDemo() : parking(10), selectedCar(nullptr), activeTransaction(nullptr) {}

    void showMenu() {
        std::cout << "\n=== Механизм транзакций для стоянки ===\n";
        std::cout << "Команды управления стоянкой:\n";
        std::cout << "  a <номер> - Прибытие автомобиля с номером <номер>\n";
        std::cout << "  d <номер> - Отъезд автомобиля с номером <номер>\n";
        std::cout << "  select <номер> - Выбрать автомобиль для транзакции\n";
        std::cout << "  show      - Показать состояние стоянки\n";
        std::cout << "\nКоманды транзакций:\n";
        std::cout << "  start     - Начать транзакцию\n";
        std::cout << "  inc       - Увеличить счетчик перемещений (в рамках транзакции)\n";
        std::cout << "  commit    - Закрепить изменения\n";
        std::cout << "  rollback  - Отменить изменения\n";
        std::cout << "  s         - Демонстрация smart-указателей (Лабораторная работа №8)\n";
        std::cout << "  q         - Выход\n";
        std::cout << "=====================================\n";
    }

    void selectCar(int plateNumber) {
        // Для упрощения, будем искать автомобиль в стоянке
        // В реальной реализации может потребоваться другой подход
        std::cout << "Выбор автомобиля для транзакции: " << plateNumber << "\n";
        selectedCar = std::make_shared<Car>(plateNumber);
        std::cout << "Автомобиль №" << plateNumber << " выбран для транзакции\n";
    }

    void startTransaction() {
        if (!selectedCar) {
            std::cout << "Ошибка: Сначала выберите автомобиль\n";
            return;
        }

        if (activeTransaction) {
            std::cout << "Ошибка: Транзакция уже активна\n";
            return;
        }

        activeTransaction = std::make_unique<Transaction<Car>>(selectedCar);
        activeTransaction->start();
        std::cout << "Транзакция начата\n";
    }

    void incrementRemoveCount() {
        if (!selectedCar) {
            std::cout << "Ошибка: Сначала выберите автомобиль\n";
            return;
        }

        if (!activeTransaction) {
            std::cout << "Ошибка: Нет активной транзакции\n";
            return;
        }

        selectedCar->incrementRemoveCount();
        std::cout << "Счетчик перемещений увеличен. Текущее значение: " << selectedCar->getRemoveCount() << "\n";
    }

    void commitTransaction() {
        if (!activeTransaction) {
            std::cout << "Ошибка: Нет активной транзакции\n";
            return;
        }

        activeTransaction->commit();
        activeTransaction.reset();
        std::cout << "Транзакция закреплена. Предыдущее состояние уничтожено\n";
    }

    void rollbackTransaction() {
        if (!activeTransaction) {
            std::cout << "Ошибка: Нет активной транзакции\n";
            return;
        }

        activeTransaction->rollback();
        activeTransaction.reset();
        std::cout << "Транзакция отменена. Восстановлено предыдущее состояние\n";
    }

    void run() {
        std::cout << "Лабораторная работа №9. Механизм транзакций для моделирования стоянки\n";
        std::cout << "Основана на Лабораторных работах №7 и №8\n";

        // Установка кодовой страницы для поддержки русского языка в консоли Windows
        #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
        #endif

        std::string input;
        while (true) {
            showMenu();
            std::cout << "> ";
            std::getline(std::cin, input);

            if (input.empty()) {
                continue;
            }

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
                parking.display();
            } else if (command == "d" || command == "D") {
                int plateNumber;
                if (iss >> plateNumber) {
                    parking.depart(plateNumber);
                } else {
                    std::cout << "Неверный формат команды. Используйте: d <номер>\n";
                }
                parking.display();
            } else if (command == "select") {
                int plateNumber;
                if (iss >> plateNumber) {
                    selectCar(plateNumber);
                } else {
                    std::cout << "Неверный формат команды. Используйте: select <номер>\n";
                }
            } else if (command == "show") {
                parking.display();
            } else if (command == "start") {
                startTransaction();
            } else if (command == "inc") {
                incrementRemoveCount();
            } else if (command == "commit") {
                commitTransaction();
            } else if (command == "rollback") {
                rollbackTransaction();
            } else if (command == "s" || command == "S") {
                // Вызываем демонстрацию smart-указателей (Лабораторная работа №8)
                demonstrateSmartPointers();
            } else {
                std::cout << "Неизвестная команда. Введите 'q' для выхода.\n";
            }
            
            std::cout << "\n";
        }
    }
};

int main() {
    ParkingTransactionDemo demo;
    demo.run();
    return 0;
}