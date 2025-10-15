#include "Octal.h"
#include <string>
#include <algorithm>
#include <stdexcept>

// Вспомогательная функция для проверки корректности символа восьмеричной цифры
void Octal::parseOctalString(const std::string& str) {
    size = 0;
    
    // Пропускаем ведущие нули
    size_t start = 0;
    while (start < str.length() && str[start] == '0') {
        start++;
    }
    
    // Если строка состоит только из нулей
    if (start == str.length()) {
        size = 1;
        digits[0] = 0;
        return;
    }
    
    // Проверяем, что все символы - восьмеричные цифры
    for (size_t i = start; i < str.length(); i++) {
        if (!isValidOctDigit(str[i])) {
            throw std::invalid_argument("Invalid octal digit in string");
        }
    }
    
    // Выделяем память под нужное количество цифр
    size_t needed_size = str.length() - start;
    if (needed_size > capacity) {
        delete[] digits;
        capacity = needed_size;
        digits = new unsigned char[capacity];
    }
    
    // Копируем цифры в обратном порядке (младшая цифра имеет меньший индекс)
    size = needed_size;
    for (size_t i = 0; i < size; i++) {
        digits[i] = str[str.length() - 1 - i] - '0';
    }
}

// Безаргументный конструктор
Octal::Octal() noexcept(false) : size(1), capacity(1) {
    try {
        digits = new unsigned char[1];
        digits[0] = 0;
    } catch (const std::bad_alloc&) {
        throw;
    }
}

// Конструктор из восьмеричной строки
Octal::Octal(const std::string& str) noexcept(false) : size(0), capacity(0) {
    try {
        if (str.empty()) {
            capacity = 1;
            digits = new unsigned char[1];
            digits[0] = 0;
            size = 1;
        } else {
            capacity = str.length();
            digits = new unsigned char[capacity];
            parseOctalString(str);
        }
    } catch (const std::bad_alloc&) {
        throw;
    }
}

// Конструктор с двумя аргументами-итераторами (начало и конец)
Octal::Octal(const unsigned char* begin, const unsigned char* end) noexcept(false) : size(0), capacity(0) {
    if (begin >= end) {
        capacity = 1;
        digits = new unsigned char[1];
        digits[0] = 0;
        size = 1;
        return;
    }
    
    size = end - begin;
    capacity = size;
    
    try {
        digits = new unsigned char[capacity];
        for (size_t i = 0; i < size; i++) {
            if (begin[i] > 7) {
                delete[] digits;
                throw std::invalid_argument("Invalid octal digit in range");
            }
            digits[i] = begin[i];
        }
    } catch (const std::bad_alloc&) {
        throw;
    }
}

// Конструктор копирования
Octal::Octal(const Octal& other) noexcept(false) : size(other.size), capacity(other.capacity) {
    try {
        digits = new unsigned char[capacity];
        for (size_t i = 0; i < size; i++) {
            digits[i] = other.digits[i];
        }
    } catch (const std::bad_alloc&) {
        throw;
    }
}

// Деструктор
Octal::~Octal() {
    delete[] digits;
}

// Операция присваивания
Octal& Octal::operator=(const Octal& other) {
    if (this != &other) {
        delete[] digits;
        
        size = other.size;
        capacity = other.capacity;
        
        try {
            digits = new unsigned char[capacity];
            for (size_t i = 0; i < size; i++) {
                digits[i] = other.digits[i];
            }
        } catch (const std::bad_alloc&) {
            throw;
        }
    }
    return *this;
}

// Операция индексирования с проверкой
unsigned char& Octal::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return digits[index];
}

const unsigned char& Octal::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return digits[index];
}

// Преобразование в десятичное число для внутренних нужд
unsigned long long Octal::toDecimal() const {
    unsigned long long result = 0;
    unsigned long long multiplier = 1;
    
    for (size_t i = 0; i < size; i++) {
        result += digits[i] * multiplier;
        multiplier *= 8;
    }
    
    return result;
}

// Преобразование в строку восьмеричного числа
std::string Octal::toString() const {
    if (size == 0) {
        return "0";
    }
    
    std::string result = "";
    for (int i = size - 1; i >= 0; i--) {
        result += (char)('0' + digits[i]);
    }
    
    if (result.empty()) {
        return "0";
    }
    
    return result;
}

// Арифметические операции
Octal Octal::operator+(const Octal& other) const {
    unsigned long long a = toDecimal();
    unsigned long long b = other.toDecimal();
    unsigned long long result = a + b;
    
    // Преобразуем результат обратно в восьмеричное число
    if (result == 0) {
        return Octal("0");
    }
    
    std::string oct_str = "";
    while (result > 0) {
        oct_str = (char)('0' + (result % 8)) + oct_str;
        result /= 8;
    }
    
    return Octal(oct_str);
}

Octal Octal::operator-(const Octal& other) const {
    unsigned long long a = toDecimal();
    unsigned long long b = other.toDecimal();
    
    if (a < b) {
        throw std::invalid_argument("Result would be negative");
    }
    
    unsigned long long result = a - b;
    
    // Преобразуем результат обратно в восьмеричное число
    if (result == 0) {
        return Octal("0");
    }
    
    std::string oct_str = "";
    while (result > 0) {
        oct_str = (char)('0' + (result % 8)) + oct_str;
        result /= 8;
    }
    
    return Octal(oct_str);
}

Octal Octal::operator*(const Octal& other) const {
    unsigned long long a = toDecimal();
    unsigned long long b = other.toDecimal();
    unsigned long long result = a * b;
    
    // Преобразуем результат обратно в восьмеричное число
    if (result == 0) {
        return Octal("0");
    }
    
    std::string oct_str = "";
    while (result > 0) {
        oct_str = (char)('0' + (result % 8)) + oct_str;
        result /= 8;
    }
    
    return Octal(oct_str);
}

Octal Octal::operator/(const Octal& other) const {
    unsigned long long a = toDecimal();
    unsigned long long b = other.toDecimal();
    
    if (b == 0) {
        throw std::invalid_argument("Division by zero");
    }
    
    unsigned long long result = a / b;
    
    // Преобразуем результат обратно в восьмеричное число
    if (result == 0) {
        return Octal("0");
    }
    
    std::string oct_str = "";
    while (result > 0) {
        oct_str = (char)('0' + (result % 8)) + oct_str;
        result /= 8;
    }
    
    return Octal(oct_str);
}

Octal Octal::operator%(const Octal& other) const {
    unsigned long long a = toDecimal();
    unsigned long long b = other.toDecimal();
    
    if (b == 0) {
        throw std::invalid_argument("Division by zero in modulo operation");
    }
    
    unsigned long long result = a % b;
    
    // Преобразуем результат обратно в восьмеричное число
    if (result == 0) {
        return Octal("0");
    }
    
    std::string oct_str = "";
    while (result > 0) {
        oct_str = (char)('0' + (result % 8)) + oct_str;
        result /= 8;
    }
    
    return Octal(oct_str);
}

// Операции присваивания с арифметикой
Octal& Octal::operator+=(const Octal& other) {
    *this = *this + other;
    return *this;
}

Octal& Octal::operator-=(const Octal& other) {
    *this = *this - other;
    return *this;
}

Octal& Octal::operator*=(const Octal& other) {
    *this = *this * other;
    return *this;
}

Octal& Octal::operator/=(const Octal& other) {
    *this = *this / other;
    return *this;
}

Octal& Octal::operator%=(const Octal& other) {
    *this = *this % other;
    return *this;
}

// Операции сравнения
bool Octal::operator==(const Octal& other) const {
    if (size != other.size) {
        return false;
    }
    
    for (size_t i = 0; i < size; i++) {
        if (digits[i] != other.digits[i]) {
            return false;
        }
    }
    
    return true;
}

bool Octal::operator!=(const Octal& other) const {
    return !(*this == other);
}

bool Octal::operator<(const Octal& other) const {
    if (size != other.size) {
        return size < other.size;
    }
    
    for (int i = size - 1; i >= 0; i--) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
        }
    }
    
    return false; // Равны
}

bool Octal::operator<=(const Octal& other) const {
    return (*this < other) || (*this == other);
}

bool Octal::operator>(const Octal& other) const {
    return !(*this <= other);
}

bool Octal::operator>=(const Octal& other) const {
    return !(*this < other);
}

// Перегрузка операций ввода-вывода
std::istream& operator>>(std::istream& in, Octal& oct) {
    std::string str;
    in >> str;
    
    // Создаем временный объект и проверяем корректность ввода
    Octal temp(str);
    oct = temp;
    
    return in;
}

std::ostream& operator<<(std::ostream& out, const Octal& oct) {
    out << oct.toString();
    return out;
}