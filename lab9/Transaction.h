#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <memory>
#include <stdexcept>

// Шаблонный класс транзакции
template <typename T>
class Transaction {
private:
    std::shared_ptr<T> currentState;    // Текущее состояние объекта
    std::shared_ptr<T> previousState;  // Предыдущее состояние объекта

public:
    // Конструктор
    explicit Transaction(std::shared_ptr<T> obj);
    
    // Деструктор
    ~Transaction() = default;
    
    // Начало транзакции - сохранение текущего состояния
    void start();
    
    // Закрепление изменений - уничтожение предыдущего состояния
    void commit();
    
    // Отмена изменений - возврат к предыдущему состоянию
    void rollback();
    
    // Получение доступа к текущему состоянию
    std::shared_ptr<T> getObject();
    
    // Проверка, активна ли транзакция
    bool isActive() const;
};

#include "Transaction.cpp"  // Включаем реализацию шаблона

#endif // TRANSACTION_H