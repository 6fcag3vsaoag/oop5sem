#include "Transaction.h"
#include <memory>

template<typename T>
Transaction<T>::Transaction(std::shared_ptr<T> obj) : current(obj), previous(nullptr) {}

template<typename T>
void Transaction<T>::start() {
    // Создаем копию текущего объекта как предыдущее состояние
    if (current) {
        previous = std::make_shared<T>(*current);
    }
}

template<typename T>
void Transaction<T>::commit() {
    // Закрепляем изменения - уничтожаем предыдущее состояние
    previous.reset();
}

template<typename T>
void Transaction<T>::rollback() {
    // Отменяем изменения - возвращаемся к предыдущему состоянию
    if (previous) {
        *current = *previous;
        previous.reset();
    }
}

template<typename T>
std::shared_ptr<T> Transaction<T>::get() {
    return current;
}