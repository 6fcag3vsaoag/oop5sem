#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

class STUDENT {
private:
    std::string fullName;    // Фамилия и инициалы
    std::string groupNumber; // Номер группы
    int grades[5];           // Массив оценок (успеваемость)

public:
    // Конструктор по умолчанию
    STUDENT();

    // Конструктор с параметрами
    STUDENT(const std::string& name, const std::string& group, const int gradesArray[5]);

    // Методы доступа к полям
    std::string getFullName() const;
    std::string getGroupNumber() const;
    void getGrades(int gradesArray[5]) const;

    void setFullName(const std::string& name);
    void setGroupNumber(const std::string& group);
    void setGrades(const int gradesArray[5]);

    // Метод для проверки наличия оценки 2
    bool hasGradeTwo() const;

    // Дружественные функции для перегрузки операций
    friend std::ostream& operator<<(std::ostream& os, const STUDENT& student);
    friend std::istream& operator>>(std::istream& is, STUDENT& student);
};

#endif