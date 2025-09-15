#include "Car.h"

// Конструктор
Car::Car(int plateNumber) : licensePlate(plateNumber), removeCount(0) {}

// Получить номерной знак
int Car::getLicensePlate() const {
    return licensePlate;
}

// Увеличить счетчик удалений
void Car::incrementRemoveCount() {
    removeCount++;
}

// Получить счетчик удалений
int Car::getRemoveCount() const {
    return removeCount;
}

// Оператор сравнения
bool Car::operator==(const Car& other) const {
    return licensePlate == other.licensePlate;
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Car& car) {
    os << "Car #" << car.licensePlate;
    return os;
}