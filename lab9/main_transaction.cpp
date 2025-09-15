#include <iostream>
#include <memory>
#include "Car.h"
#include "Transaction.h"

void demonstrateTransaction() {
    std::cout << "=== Демонстрация механизма транзакций ===\n";
    
    // Создаем объект Car с использованием shared_ptr
    auto car = std::make_shared<Car>(123);
    std::cout << "Создан автомобиль: " << *car << "\n";
    
    // Создаем транзакцию для этого объекта
    Transaction<Car> transaction(car);
    
    // Начинаем транзакцию
    transaction.start();
    std::cout << "Транзакция начата\n";
    
    // Проверяем состояние транзакции
    std::cout << "Транзакция активна: " << (transaction.isActive() ? "да" : "нет") << "\n";
    
    // Вносим изменения в объект
    car->incrementRemoveCount();
    car->incrementRemoveCount();
    std::cout << "Внесены изменения в объект. Счетчик удалений: " << car->getRemoveCount() << "\n";
    
    // Закрепляем изменения
    transaction.commit();
    std::cout << "Изменения закреплены\n";
    std::cout << "Транзакция активна: " << (transaction.isActive() ? "да" : "нет") << "\n";
    
    // Начинаем новую транзакцию
    transaction.start();
    std::cout << "Новая транзакция начата\n";
    
    // Вносим изменения
    car->incrementRemoveCount();
    car->incrementRemoveCount();
    car->incrementRemoveCount();
    std::cout << "Внесены изменения в объект. Счетчик удалений: " << car->getRemoveCount() << "\n";
    
    // Отменяем изменения
    transaction.rollback();
    std::cout << "Изменения отменены. Счетчик удалений: " << car->getRemoveCount() << "\n";
    std::cout << "Транзакция активна: " << (transaction.isActive() ? "да" : "нет") << "\n";
    
    std::cout << "\n";
}

int main() {
    std::cout << "Лабораторная работа №9. Демонстрация механизма транзакций\n\n";
    
    try {
        demonstrateTransaction();
        std::cout << "Демонстрация завершена успешно\n";
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}