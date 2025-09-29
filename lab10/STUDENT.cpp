#include "STUDENT.h"
#include <algorithm>

// Конструктор по умолчанию
STUDENT::STUDENT() {
    fullName = "";
    groupNumber = "";
    for (int i = 0; i < 5; i++) {
        grades[i] = 0;
    }
}

// Конструктор с параметрами
STUDENT::STUDENT(const std::string& name, const std::string& group, const int gradesArray[5]) {
    fullName = name;
    groupNumber = group;
    for (int i = 0; i < 5; i++) {
        grades[i] = gradesArray[i];
    }
}

// Методы доступа к полям
std::string STUDENT::getFullName() const {
    return fullName;
}

std::string STUDENT::getGroupNumber() const {
    return groupNumber;
}

void STUDENT::getGrades(int gradesArray[5]) const {
    for (int i = 0; i < 5; i++) {
        gradesArray[i] = grades[i];
    }
}

void STUDENT::setFullName(const std::string& name) {
    fullName = name;
}

void STUDENT::setGroupNumber(const std::string& group) {
    groupNumber = group;
}

void STUDENT::setGrades(const int gradesArray[5]) {
    for (int i = 0; i < 5; i++) {
        grades[i] = gradesArray[i];
    }
}

// Метод для проверки наличия оценки 2
bool STUDENT::hasGradeTwo() const {
    for (int i = 0; i < 5; i++) {
        if (grades[i] == 2) {
            return true;
        }
    }
    return false;
}

// Перегрузка операции вставки <<
std::ostream& operator<<(std::ostream& os, const STUDENT& student) {
    os << "ФИО: " << student.fullName << std::endl;
    os << "Группа: " << student.groupNumber << std::endl;
    os << "Оценки: ";
    for (int i = 0; i < 5; i++) {
        os << student.grades[i];
        if (i < 4) os << ", ";
    }
    os << std::endl;
    return os;
}

// Перегрузка операции извлечения >>
std::istream& operator>>(std::istream& is, STUDENT& student) {
    std::cout << "Введите ФИО: ";
    std::getline(is, student.fullName);

    std::cout << "Введите номер группы: ";
    is >> student.groupNumber;

    std::cout << "Введите 5 оценок: ";
    for (int i = 0; i < 5; i++) {
        is >> student.grades[i];
    }

    // Очистка буфера
    is.ignore(32767, '\n');

    return is;
}