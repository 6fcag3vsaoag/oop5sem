#include "Parking.h"
#include <vector>
#include <stdexcept>

// Конструктор с опциональной вместимостью
Parking::Parking(int cap) : capacity(cap) {}

// Прибытие автомобиля
bool Parking::arrive(const Car& car) {
    // Проверяем, есть ли место на стоянке
    if (isFull()) {
        std::cout << "Стоянка заполнена. Автомобиль №" << car.getLicensePlate() << " не может въехать.\n";
        return false;
    }
    
    parkingStack.push(car);
    std::cout << "Автомобиль №" << car.getLicensePlate() << " прибыл и припарковался.\n";
    return true;
}

// Отъезд автомобиля
bool Parking::depart(int licensePlate) {
    if (isEmpty()) {
        std::cout << "Стоянка пуста. Нет автомобилей для выезда.\n";
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
            std::cout << "Автомобиль №" << licensePlate << " выехал. ";
            std::cout << "Он был перемещен " << car.getRemoveCount() << " раз(а) для выезда других автомобилей.\n";
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
        std::cout << "Автомобиль №" << licensePlate << " не найден на стоянке.\n";
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
        std::cout << "Стоянка пуста.\n";
        return;
    }
    
    std::cout << "Состояние стоянки (" << getCurrentCount() << " автомобилей): \n";
    // Для простоты выводим только количество автомобилей
    // В реальной реализации можно было бы вывести все автомобили
}