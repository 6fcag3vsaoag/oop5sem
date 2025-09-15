#include <iostream>
#include <string>
#include <memory>  // Для smart-указателей
#include <vector>
#include "Car.h"
#include "Parking.h"

void demonstrateUniquePtr() {
    std::cout << "=== Демонстрация unique_ptr ===\n";
    
    // Создаем несколько объектов Car с использованием unique_ptr
    auto car1 = std::make_unique<Car>(123);
    auto car2 = std::make_unique<Car>(456);
    auto car3 = std::make_unique<Car>(789);
    
    std::cout << "Созданы автомобили: " << *car1 << ", " << *car2 << ", " << *car3 << "\n";
    
    // Применяем методы класса
    car1->incrementRemoveCount();
    car2->incrementRemoveCount();
    car2->incrementRemoveCount();
    
    std::cout << "Увеличен счетчик удалений для автомобилей\n";
    std::cout << "Счетчики удалений: " << car1->getRemoveCount() << ", " 
              << car2->getRemoveCount() << ", " << car3->getRemoveCount() << "\n";
    
    // unique_ptr автоматически удалят объекты при выходе из области видимости
    std::cout << "unique_ptr автоматически удалят объекты при выходе из области видимости\n\n";
}

void demonstrateSharedPtr() {
    std::cout << "=== Демонстрация shared_ptr ===\n";
    
    // Создаем объект Car с использованием shared_ptr
    auto car = std::make_shared<Car>(999);
    std::cout << "Создан автомобиль: " << *car << "\n";
    
    // Создаем несколько shared_ptr, указывающих на один объект
    std::vector<std::shared_ptr<Car>> sharedCars;
    sharedCars.push_back(car);
    sharedCars.push_back(car);
    sharedCars.push_back(car);
    
    std::cout << "Создано несколько shared_ptr, указывающих на один объект\n";
    std::cout << "Количество ссылок на объект: " << car.use_count() << "\n";
    
    // Применяем методы класса через разные указатели
    car->incrementRemoveCount();
    sharedCars[0]->incrementRemoveCount();
    sharedCars[1]->incrementRemoveCount();
    
    std::cout << "Увеличен счетчик удалений через разные указатели\n";
    std::cout << "Счетчик удалений: " << car->getRemoveCount() << "\n";
    std::cout << "Количество ссылок на объект: " << car.use_count() << "\n";
    
    // Удаляем указатели из вектора
    sharedCars.clear();
    std::cout << "Удалены указатели из вектора\n";
    std::cout << "Количество ссылок на объект: " << car.use_count() << "\n";
    
    // shared_ptr автоматически удалит объект, когда счетчик ссылок достигнет нуля
    std::cout << "shared_ptr автоматически удалит объект, когда счетчик ссылок достигнет нуля\n\n";
}

void demonstrateWeakPtr() {
    std::cout << "=== Демонстрация weak_ptr ===\n";
    
    // Создаем объект Car с использованием shared_ptr
    auto car = std::make_shared<Car>(888);
    std::cout << "Создан автомобиль: " << *car << "\n";
    
    // Создаем weak_ptr, указывающий на объект
    std::weak_ptr<Car> weakCar = car;
    std::cout << "Создан weak_ptr, указывающий на объект\n";
    
    // Проверяем, действителен ли weak_ptr
    if (auto sharedCar = weakCar.lock()) {
        std::cout << "weak_ptr действителен: " << *sharedCar << "\n";
        sharedCar->incrementRemoveCount();
        std::cout << "Увеличен счетчик удалений через weak_ptr\n";
        std::cout << "Счетчик удалений: " << sharedCar->getRemoveCount() << "\n";
    } else {
        std::cout << "weak_ptr недействителен\n";
    }
    
    // Удаляем shared_ptr
    car.reset();
    std::cout << "Удален shared_ptr\n";
    
    // Проверяем, действителен ли weak_ptr после удаления shared_ptr
    if (auto sharedCar = weakCar.lock()) {
        std::cout << "weak_ptr действителен: " << *sharedCar << "\n";
    } else {
        std::cout << "weak_ptr недействителен (объект удален)\n";
    }
    
    std::cout << "weak_ptr не увеличивает счетчик ссылок и не мешает удалению объекта\n\n";
}

int main() {
    std::cout << "Лабораторная работа №8. Демонстрация smart-указателей\n\n";
    
    demonstrateUniquePtr();
    demonstrateSharedPtr();
    demonstrateWeakPtr();
    
    std::cout << "Программа завершена\n";
    return 0;
}