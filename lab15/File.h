#ifndef FILE_H
#define FILE_H

#include <string>
#include <iostream>

// Структура для представления даты
struct Date {
    int day;
    int month;
    int year;

    Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {}

    // Операторы сравнения для дат
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    bool operator<=(const Date& other) const {
        return *this < other || *this == other;
    }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }

    bool operator!=(const Date& other) const {
        return !(*this == other);
    }

    // Вспомогательный метод для вывода даты
    std::string toString() const {
        return std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
    }
};

// Класс для представления файла
class File {
private:
    std::string name;
    Date creationDate;
    int accessCount;

public:
    // Конструктор
    File(const std::string& n = "", const Date& date = Date(), int count = 0)
        : name(n), creationDate(date), accessCount(count) {}

    // Геттеры
    std::string getName() const { return name; }
    Date getDate() const { return creationDate; }
    int getAccessCount() const { return accessCount; }

    // Сеттеры
    void setName(const std::string& n) { name = n; }
    void setDate(const Date& date) { creationDate = date; }
    void setAccessCount(int count) { accessCount = count; }

    // Увеличение счетчика обращений
    void incrementAccessCount() { accessCount++; }

    // Операторы сравнения
    bool operator<(const File& other) const {
        return creationDate < other.creationDate;
    }

    // Операторы ввода-вывода
    friend std::ostream& operator<<(std::ostream& os, const File& file) {
        os << "Имя: " << file.name 
           << ", Дата создания: " << file.creationDate.toString()
           << ", Количество обращений: " << file.accessCount;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, File& file) {
        std::cout << "Введите имя файла: ";
        is >> file.name;
        std::cout << "Введите дату создания (день месяц год): ";
        is >> file.creationDate.day >> file.creationDate.month >> file.creationDate.year;
        file.accessCount = 0; // При создании файл не имеет обращений
        return is;
    }
};

#endif // FILE_H