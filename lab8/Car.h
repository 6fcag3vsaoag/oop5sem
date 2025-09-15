#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <string>

class Car {
private:
    int licensePlate;  // Номерной знак автомобиля
    int removeCount;   // Счетчик удалений для обеспечения выезда других автомобилей

public:
    // Конструктор
    Car(int plateNumber);
    
    // Деструктор
    ~Car() = default;
    
    // Получить номерной знак
    int getLicensePlate() const;
    
    // Увеличить счетчик удалений
    void incrementRemoveCount();
    
    // Получить счетчик удалений
    int getRemoveCount() const;
    
    // Оператор сравнения
    bool operator==(const Car& other) const;
    
    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Car& car);
};

#endif // CAR_H