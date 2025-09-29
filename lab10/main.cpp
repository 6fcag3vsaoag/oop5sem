#include <iostream>
#include <algorithm>
#include <iomanip>
#include "STUDENT.h"

int main() {
    const int STUDENT_COUNT = 10;
    STUDENT students[STUDENT_COUNT];

    std::cout << "=== ВВОД ДАННЫХ СТУДЕНТОВ ===" << std::endl;
    std::cout << "Введите данные для " << STUDENT_COUNT << " студентов:" << std::endl;

    // Ввод данных студентов
    for (int i = 0; i < STUDENT_COUNT; i++) {
        std::cout << "\nСтудент №" << (i + 1) << ":" << std::endl;
        std::cin >> students[i];
    }

    // Сортировка по алфавиту (по ФИО)
    std::sort(students, students + STUDENT_COUNT, [](const STUDENT& a, const STUDENT& b) {
        return a.getFullName() < b.getFullName();
    });

    std::cout << "\n=== ОТСОРТИРОВАННЫЙ СПИСОК СТУДЕНТОВ ===" << std::endl;
    for (int i = 0; i < STUDENT_COUNT; i++) {
        std::cout << "\n" << (i + 1) << ". " << students[i];
    }

    // Поиск студентов с оценкой 2
    std::cout << "\n=== СТУДЕНТЫ С ОЦЕНКОЙ 2 ===" << std::endl;
    bool foundStudentsWithTwo = false;

    for (int i = 0; i < STUDENT_COUNT; i++) {
        if (students[i].hasGradeTwo()) {
            std::cout << "ФИО: " << students[i].getFullName()
                      << ", Группа: " << students[i].getGroupNumber() << std::endl;
            foundStudentsWithTwo = true;
        }
    }

    if (!foundStudentsWithTwo) {
        std::cout << "Студентов с оценкой 2 не найдено." << std::endl;
    }

    std::cout << "\n=== АНАЛИЗ УСПЕВАЕМОСТИ ===" << std::endl;
    int totalTwos = 0;
    int totalStudentsWithTwos = 0;

    for (int i = 0; i < STUDENT_COUNT; i++) {
        if (students[i].hasGradeTwo()) {
            totalStudentsWithTwos++;
            // Подсчет количества двоек у каждого студента
            int twosCount = 0;
            for (int j = 0; j < 5; j++) {
                int grade;
                students[i].getGrades(&grade); // Это не сработает правильно
                // Нужно получить оценки по-другому
            }
        }
    }

    std::cout << "Всего студентов с оценками 2: " << totalStudentsWithTwos << std::endl;

    return 0;
}