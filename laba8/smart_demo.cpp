#include "smart_demo.h"
#include <iostream>
#include <memory>  // Для smart-указателей
#include <vector>
#include "Car.h"

void demonstrateUniquePtr() {
    std::cout << "=== Демонстрация Unique Pointer ===\n";
    
    // Создаем несколько объектов Car с использованием unique_ptr
    auto car1 = std::make_unique<Car>(123);
    auto car2 = std::make_unique<Car>(456);
    auto car3 = std::make_unique<Car>(789);
    
    std::cout << "Созданные автомобили: " << *car1 << ", " << *car2 << ", " << *car3 << "\n";
    
    // Применяем методы класса
    car1->incrementRemoveCount();
    car2->incrementRemoveCount();
    car2->incrementRemoveCount();
    
    std::cout << "Увеличен счетчик перемещений для автомобилей\n";
    std::cout << "Счетчики перемещений: " << car1->getRemoveCount() << ", " 
              << car2->getRemoveCount() << ", " << car3->getRemoveCount() << "\n";
    
    // unique_ptr автоматически удалят объекты при выходе из области видимости
    std::cout << "Unique указатели автоматически удаляют объекты при выходе из области видимости\n\n";
}

void demonstrateSharedPtr() {
    std::cout << "=== Демонстрация Shared Pointer ===\n";
    
    // Создаем объект Car с использованием shared_ptr
    auto car = std::make_shared<Car>(999);
    std::cout << "Создан автомобиль: " << *car << "\n";
    
    // Создаем несколько shared_ptr, указывающих на один объект
    std::vector<std::shared_ptr<Car>> sharedCars;
    sharedCars.push_back(car);
    sharedCars.push_back(car);
    sharedCars.push_back(car);
    
    std::cout << "Создано несколько shared_ptr, указывающих на один объект\n";
    std::cout << "Счетчик ссылок: " << car.use_count() << "\n";
    
    // Применяем методы класса через разные указатели
    car->incrementRemoveCount();
    sharedCars[0]->incrementRemoveCount();
    sharedCars[1]->incrementRemoveCount();
    
    std::cout << "Увеличен счетчик перемещений через разные указатели\n";
    std::cout << "Счетчик перемещений: " << car->getRemoveCount() << "\n";
    std::cout << "Счетчик ссылок: " << car.use_count() << "\n";
    
    // Удаляем указатели из вектора
    sharedCars.clear();
    std::cout << "Удалены указатели из вектора\n";
    std::cout << "Счетчик ссылок: " << car.use_count() << "\n";
    
    // shared_ptr автоматически удалит объект, когда счетчик ссылок достигнет нуля
    std::cout << "Shared указатели автоматически удаляют объект, когда счетчик ссылок достигает нуля\n\n";
}

void demonstrateWeakPtr() {
    std::cout << "=== Демонстрация Weak Pointer ===\n";
    
    // Создаем объект Car с использованием shared_ptr
    auto car = std::make_shared<Car>(888);
    std::cout << "Создан автомобиль: " << *car << "\n";
    
    // Создаем weak_ptr, указывающий на объект
    std::weak_ptr<Car> weakCar = car;
    std::cout << "Создан weak_ptr, указывающий на объект\n";
    
    // Проверяем, действителен ли weak_ptr
    if (auto sharedCar = weakCar.lock()) {
        std::cout << "Weak указатель действителен: " << *sharedCar << "\n";
        sharedCar->incrementRemoveCount();
        std::cout << "Увеличен счетчик перемещений через weak указатель\n";
        std::cout << "Счетчик перемещений: " << sharedCar->getRemoveCount() << "\n";
    } else {
        std::cout << "Weak указатель недействителен\n";
    }
    
    // Удаляем shared_ptr
    car.reset();
    std::cout << "Удален shared_ptr\n";
    
    // Проверяем, действителен ли weak_ptr после удаления shared_ptr
    if (auto sharedCar = weakCar.lock()) {
        std::cout << "Weak указатель действителен: " << *sharedCar << "\n";
    } else {
        std::cout << "Weak указатель недействителен (объект удален)\n";
    }
    
    std::cout << "Weak указатель не увеличивает счетчик ссылок и не препятствует удалению объекта\n\n";
}

void demonstrateSmartPointers() {
    std::cout << "Лабораторная работа №8. Демонстрация Smart Pointers\n\n";
    
    demonstrateUniquePtr();
    demonstrateSharedPtr();
    demonstrateWeakPtr();
    
    std::cout << "Демонстрация smart указателей завершена\n\n";
}