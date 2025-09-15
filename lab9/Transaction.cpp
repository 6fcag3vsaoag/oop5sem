#include "Transaction.h"
#include <memory>

// Конструктор
template <typename T>
Transaction<T>::Transaction(std::shared_ptr<T> obj) : currentState(obj), previousState(nullptr) {}

// Начало транзакции - сохранение текущего состояния
template <typename T>
void Transaction<T>::start() {
    if (!currentState) {
        throw std::runtime_error("Cannot start transaction: object is null");
    }
    
    // Создаем копию текущего состояния как предыдущее состояние
    // Это требует, чтобы класс T имел конструктор копирования
    previousState = std::make_shared<T>(*currentState);
}

// Закрепление изменений - уничтожение предыдущего состояния
template <typename T>
void Transaction<T>::commit() {
    if (!previousState) {
        throw std::runtime_error("Cannot commit transaction: no previous state");
    }
    
    // Уничтожаем предыдущее состояние, так как изменения закреплены
    previousState.reset();
}

// Отмена изменений - возврат к предыдущему состоянию
template <typename T>
void Transaction<T>::rollback() {
    if (!previousState) {
        throw std::runtime_error("Cannot rollback transaction: no previous state");
    }
    
    // Восстанавливаем предыдущее состояние
    *currentState = *previousState;
    
    // Уничтожаем предыдущее состояние
    previousState.reset();
}

// Получение доступа к текущему состоянию
template <typename T>
std::shared_ptr<T> Transaction<T>::getObject() {
    return currentState;
}

// Проверка, активна ли транзакция
template <typename T>
bool Transaction<T>::isActive() const {
    return static_cast<bool>(previousState);
}