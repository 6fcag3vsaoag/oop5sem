#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <memory>

template<typename T>
class Transaction {
private:
    std::shared_ptr<T> current;      // Указатель на текущий объект
    std::shared_ptr<T> previous;     // Указатель на предыдущее состояние объекта

public:
    // Конструктор
    Transaction(std::shared_ptr<T> obj);
    
    // Функция начала транзакции
    void start();
    
    // Функция закрепления изменений
    void commit();
    
    // Функция отмены изменений
    void rollback();
    
    // Получение указателя на текущий объект
    std::shared_ptr<T> get();
};

#include "Transaction.tpp"

#endif // TRANSACTION_H