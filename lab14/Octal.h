#ifndef OCTAL_H
#define OCTAL_H

#include <iostream>
#include <exception>
#include <stdexcept>

class Octal {
private:
    unsigned char* digits;  // Массив для хранения восьмеричных цифр
    size_t size;           // Размер массива
    size_t capacity;       // Текущая емкость

    // Вспомогательная функция для проверки корректности символа восьмеричной цифры
    bool isValidOctDigit(char c) const {
        return c >= '0' && c <= '7';
    }

    // Преобразование строки восьмеричного числа в массив цифр
    void parseOctalString(const std::string& str);

public:
    // Безаргументный конструктор
    Octal() noexcept(false);

    // Конструктор из восьмеричной строки
    Octal(const std::string& str) noexcept(false);

    // Конструктор с двумя аргументами-итераторами (начало и конец)
    Octal(const unsigned char* begin, const unsigned char* end) noexcept(false);

    // Конструктор копирования
    Octal(const Octal& other) noexcept(false);

    // Деструктор
    ~Octal();

    // Операция присваивания
    Octal& operator=(const Octal& other);

    // Операция индексирования с проверкой
    unsigned char& operator[](size_t index);
    const unsigned char& operator[](size_t index) const;

    // Арифметические операции
    Octal operator+(const Octal& other) const;
    Octal operator-(const Octal& other) const;
    Octal operator*(const Octal& other) const;
    Octal operator/(const Octal& other) const;
    Octal operator%(const Octal& other) const;

    // Операции присваивания с арифметикой
    Octal& operator+=(const Octal& other);
    Octal& operator-=(const Octal& other);
    Octal& operator*=(const Octal& other);
    Octal& operator/=(const Octal& other);
    Octal& operator%=(const Octal& other);

    // Операции сравнения
    bool operator==(const Octal& other) const;
    bool operator!=(const Octal& other) const;
    bool operator<(const Octal& other) const;
    bool operator<=(const Octal& other) const;
    bool operator>(const Octal& other) const;
    bool operator>=(const Octal& other) const;

    // Преобразование в десятичное число для внутренних нужд
    unsigned long long toDecimal() const;

    // Преобразование в строку восьмеричного числа
    std::string toString() const;

    // Получение размера
    size_t getSize() const { return size; }

    // Перегрузка операций ввода-вывода
    friend std::istream& operator>>(std::istream& in, Octal& oct);
    friend std::ostream& operator<<(std::ostream& out, const Octal& oct);
};

#endif // OCTAL_H