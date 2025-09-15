#ifndef STACK_H
#define STACK_H

#include <vector>
#include <cstddef>

template <typename T>
class Stack {
private:
    std::vector<T> elements;

public:
    // Конструктор по умолчанию
    Stack() = default;
    
    // Деструктор
    ~Stack() = default;
    
    // Поместить элемент на вершину стека
    void push(const T& item) {
        elements.push_back(item);
    }
    
    // Удалить элемент с вершины стека и вернуть его
    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        T item = elements.back();
        elements.pop_back();
        return item;
    }
    
    // Получить элемент с вершины стека без удаления
    T top() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return elements.back();
    }
    
    // Проверить, пуст ли стек
    bool isEmpty() const {
        return elements.empty();
    }
    
    // Получить размер стека
    size_t size() const {
        return elements.size();
    }
    
    // Очистить стек
    void clear() {
        elements.clear();
    }
};

#endif // STACK_H