#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "../lab10/STUDENT.h"

const int MAX_STUDENTS = 100;

int main() {
    // Установка кодировки UTF-8 для корректного отображения русского текста
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    std::string filename;
    std::cout << "Введите имя бинарного файла для работы со студентами: ";
    std::getline(std::cin, filename);

    STUDENT students[MAX_STUDENTS];
    int studentCount = 0;

    // Попытка чтения данных из файла
    std::ifstream inputFile(filename, std::ios::binary);
    if (inputFile.is_open()) {
        std::cout << "Чтение данных из файла..." << std::endl;

        // Читаем количество студентов
        inputFile.read(reinterpret_cast<char*>(&studentCount), sizeof(studentCount));

        if (studentCount > 0 && studentCount <= MAX_STUDENTS) {
            // Читаем массив студентов
            for (int i = 0; i < studentCount; i++) {
                // Читаем ФИО
                size_t nameLength;
                inputFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
                char* nameBuffer = new char[nameLength + 1];
                inputFile.read(nameBuffer, nameLength);
                nameBuffer[nameLength] = '\0';
                students[i].setFullName(std::string(nameBuffer));
                delete[] nameBuffer;

                // Читаем номер группы
                size_t groupLength;
                inputFile.read(reinterpret_cast<char*>(&groupLength), sizeof(groupLength));
                char* groupBuffer = new char[groupLength + 1];
                inputFile.read(groupBuffer, groupLength);
                groupBuffer[groupLength] = '\0';
                students[i].setGroupNumber(std::string(groupBuffer));
                delete[] groupBuffer;

                // Читаем оценки
                int grades[5];
                inputFile.read(reinterpret_cast<char*>(grades), sizeof(grades));
                students[i].setGrades(grades);
            }
            std::cout << "Успешно прочитано " << studentCount << " студентов из файла." << std::endl;
        } else {
            std::cout << "Файл не содержит корректных данных или пуст." << std::endl;
            studentCount = 0;
        }
        inputFile.close();
    } else {
        std::cout << "Файл не найден. Будет создан новый файл." << std::endl;
    }

    // Если данных нет, создаем пример
    if (studentCount == 0) {
        std::cout << "\n=== СОЗДАНИЕ ПРИМЕРНЫХ ДАННЫХ ===" << std::endl;

        // Пример данных
        std::string names[] = {
            "Иванов Иван Иванович", "Петров Петр Петрович", "Сидорова Анна Сергеевна",
            "Козлов Дмитрий Александрович", "Морозова Елена Викторовна"
        };
        std::string groups[] = {"ИВТ-101", "ИВТ-102", "ИВТ-101", "ИВТ-103", "ИВТ-102"};
        int gradesArray[][5] = {
            {5, 4, 4, 3, 5},
            {3, 3, 4, 4, 3},
            {5, 5, 5, 4, 5},
            {4, 4, 3, 4, 4},
            {2, 3, 4, 3, 4}
        };

        studentCount = 5;
        for (int i = 0; i < studentCount; i++) {
            students[i].setFullName(names[i]);
            students[i].setGroupNumber(groups[i]);
            students[i].setGrades(gradesArray[i]);
        }
        std::cout << "Создано " << studentCount << " примеров студентов." << std::endl;
    }

    // Вывод текущих данных
    std::cout << "\n=== ТЕКУЩИЕ ДАННЫЕ СТУДЕНТОВ ===" << std::endl;
    for (int i = 0; i < studentCount; i++) {
        std::cout << "\nСтудент " << (i + 1) << ":" << std::endl;
        std::cout << students[i];
    }

    // Поиск студентов с двойками
    std::cout << "\n=== СТУДЕНТЫ С ОЦЕНКОЙ 2 ===" << std::endl;
    bool foundStudentsWithTwo = false;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].hasGradeTwo()) {
            std::cout << "ФИО: " << students[i].getFullName()
                      << ", Группа: " << students[i].getGroupNumber() << std::endl;
            foundStudentsWithTwo = true;
        }
    }

    if (!foundStudentsWithTwo) {
        std::cout << "Студентов с оценкой 2 не найдено." << std::endl;
    }

    // Сохранение данных в файл
    std::cout << "\n=== СОХРАНЕНИЕ ДАННЫХ В ФАЙЛ ===" << std::endl;
    std::ofstream outputFile(filename, std::ios::binary);

    if (outputFile.is_open()) {
        // Записываем количество студентов
        outputFile.write(reinterpret_cast<const char*>(&studentCount), sizeof(studentCount));

        // Записываем массив студентов
        for (int i = 0; i < studentCount; i++) {
            // Записываем ФИО
            std::string name = students[i].getFullName();
            size_t nameLength = name.length();
            outputFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
            outputFile.write(name.c_str(), nameLength);

            // Записываем номер группы
            std::string group = students[i].getGroupNumber();
            size_t groupLength = group.length();
            outputFile.write(reinterpret_cast<const char*>(&groupLength), sizeof(groupLength));
            outputFile.write(group.c_str(), groupLength);

            // Записываем оценки
            int grades[5];
            students[i].getGrades(grades);
            outputFile.write(reinterpret_cast<const char*>(grades), sizeof(grades));
        }
        outputFile.close();
        std::cout << "Данные успешно сохранены в файл '" << filename << "'" << std::endl;
    } else {
        std::cerr << "Ошибка при сохранении файла!" << std::endl;
        return 1;
    }

    return 0;
}