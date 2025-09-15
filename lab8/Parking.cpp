#include "Parking.h"
#include <vector>
#include <stdexcept>

// Конструктор с опциональной вместимостью
Parking::Parking(int cap) : capacity(cap) {}

// Прибытие автомобиля
bool Parking::arrive(const Car& car) {
    // Проверяем, есть ли место на стоянке
    if (isFull()) {
        std::cout << "Parking is full. Car #" << car.getLicensePlate() << " cannot enter.\n";
        return false;
    }
    
    parkingStack.push(car);
    std::cout << "Car #" << car.getLicensePlate() << " has arrived and parked.\n";
    return true;
}

// Отъезд автомобиля
bool Parking::depart(int licensePlate) {
    if (isEmpty()) {
        std::cout << "Parking is empty. No cars to depart.\n";
        return false;
    }
    
    // Временный стек для хранения автомобилей, которые нужно будет вернуть
    Stack<Car> tempStack;
    bool found = false;
    Car targetCar(licensePlate);
    
    // Ищем автомобиль в стеке
    while (!parkingStack.isEmpty()) {
        Car car = parkingStack.pop();
        
        if (car == targetCar) {
            // Найден целевой автомобиль
            found = true;
            std::cout << "Car #" << licensePlate << " has departed. ";
            std::cout << "It was removed " << car.getRemoveCount() << " times for other cars to exit.\n";
            break;
        } else {
            // Увеличиваем счетчик удалений для этого автомобиля
            // (так как он будет временно удален для доступа к целевому)
            car.incrementRemoveCount();
            tempStack.push(car);
        }
    }
    
    // Возвращаем автомобили обратно на стоянку
    while (!tempStack.isEmpty()) {
        parkingStack.push(tempStack.pop());
    }
    
    if (!found) {
        std::cout << "Car #" << licensePlate << " not found in parking.\n";
        return false;
    }
    
    return true;
}

// Проверить, пуста ли стоянка
bool Parking::isEmpty() const {
    return parkingStack.isEmpty();
}

// Проверить, заполнена ли стоянка
bool Parking::isFull() const {
    // Если capacity == -1, считаем стоянку бесконечной
    return (capacity != -1) && (parkingStack.size() >= static_cast<size_t>(capacity));
}

// Получить текущее количество автомобилей
int Parking::getCurrentCount() const {
    return static_cast<int>(parkingStack.size());
}

// Вывести состояние стоянки
void Parking::display() const {
    if (isEmpty()) {
        std::cout << "Parking is empty.\n";
        return;
    }
    
    std::cout << "Parking status (" << getCurrentCount() << " cars): \n";
    // Для простоты выводим только количество автомобилей
    // В реальной реализации можно было бы вывести все автомобили
}