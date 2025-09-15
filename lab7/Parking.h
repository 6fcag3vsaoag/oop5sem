#ifndef PARKING_H
#define PARKING_H

#include "Stack.h"
#include "Car.h"
#include <iostream>
#include <vector>

class Parking {
private:
    Stack<Car> parkingStack;  // Стек для хранения автомобилей на стоянке
    int capacity;             // Вместимость стоянки (-1 для бесконечной)

public:
    // Конструктор с опциональной вместимостью
    Parking(int cap = -1);
    
    // Деструктор
    ~Parking() = default;
    
    // Прибытие автомобиля
    bool arrive(const Car& car);
    
    // Отъезд автомобиля
    bool depart(int licensePlate);
    
    // Проверить, пуста ли стоянка
    bool isEmpty() const;
    
    // Проверить, заполнена ли стоянка
    bool isFull() const;
    
    // Получить текущее количество автомобилей
    int getCurrentCount() const;
    
    // Вывести состояние стоянки
    void display() const;
};

#endif // PARKING_H