#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <windows.h>
#include "../lab10/STUDENT.h"

// Классы исключений
class FileError {
private:
    std::string message;
    std::string filename;
public:
    FileError(const std::string& msg, const std::string& file = "")
        : message(msg), filename(file) {}
    void print() const {
        std::cerr << "Ошибка файла: " << message;
        if (!filename.empty()) {
            std::cerr << " (Файл: " << filename << ")";
        }
        std::cerr << std::endl;
    }
};

class MemoryError {
private:
    std::string message;
public:
    MemoryError(const std::string& msg = "Ошибка выделения памяти") : message(msg) {}
    void print() const {
        std::cerr << "Ошибка памяти: " << message << std::endl;
    }
};

class InputError {
private:
    std::string message;
public:
    InputError(const std::string& msg = "Ошибка ввода данных") : message(msg) {}
    void print() const {
        std::cerr << "Ошибка ввода: " << message << std::endl;
    }
};

const int MAX_STUDENTS = 100;

int getStudentCount() {
    int count;
    std::cout << "Введите количество студентов (1-" << MAX_STUDENTS << "): ";

    while (!(std::cin >> count)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: введите целое число: ";
    }

    if (count < 1 || count > MAX_STUDENTS) {
        throw InputError("Количество студентов должно быть в диапазоне 1-" + std::to_string(MAX_STUDENTS));
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return count;
}

STUDENT* createStudentArray(int count) {
    STUDENT* students = nullptr;

    try {
        students = new STUDENT[count];
    } catch (const std::bad_alloc& e) {
        throw MemoryError("Не удалось выделить память для массива студентов");
    }

    return students;
}

void inputStudents(STUDENT* students, int count) {
    std::cout << "\n=== ВВОД ДАННЫХ СТУДЕНТОВ ===" << std::endl;

    for (int i = 0; i < count; i++) {
        std::cout << "\nСтудент №" << (i + 1) << ":" << std::endl;

        try {
            std::cin >> students[i];
        } catch (const std::exception& e) {
            throw InputError("Ошибка при вводе данных студента №" + std::to_string(i + 1) + ": " + e.what());
        }
    }
}

void saveToFile(const STUDENT* students, int count, const std::string& filename) {
    std::ofstream outputFile(filename, std::ios::binary);

    if (!outputFile.is_open()) {
        throw FileError("Не удалось открыть файл для записи", filename);
    }

    try {
        // Записываем количество студентов
        outputFile.write(reinterpret_cast<const char*>(&count), sizeof(count));
        if (!outputFile.good()) {
            throw FileError("Ошибка записи количества студентов", filename);
        }

        // Записываем массив студентов
        for (int i = 0; i < count; i++) {
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

            if (!outputFile.good()) {
                throw FileError("Ошибка записи данных студента №" + std::to_string(i + 1), filename);
            }
        }
    } catch (const FileError&) {
        outputFile.close();
        throw;
    } catch (const std::exception& e) {
        outputFile.close();
        throw FileError("Неожиданная ошибка при записи: " + std::string(e.what()), filename);
    }

    outputFile.close();
}

void loadFromFile(STUDENT* students, int& count, const std::string& filename) {
    std::ifstream inputFile(filename, std::ios::binary);

    if (!inputFile.is_open()) {
        throw FileError("Не удалось открыть файл для чтения", filename);
    }

    try {
        // Читаем количество студентов
        inputFile.read(reinterpret_cast<char*>(&count), sizeof(count));
        if (!inputFile.good()) {
            throw FileError("Ошибка чтения количества студентов или файл поврежден", filename);
        }

        if (count <= 0 || count > MAX_STUDENTS) {
            throw FileError("Некорректное количество студентов в файле: " + std::to_string(count), filename);
        }

        // Читаем массив студентов
        for (int i = 0; i < count; i++) {
            // Читаем ФИО
            size_t nameLength;
            inputFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
            if (!inputFile.good()) {
                throw FileError("Ошибка чтения длины ФИО студента №" + std::to_string(i + 1), filename);
            }

            char* nameBuffer = nullptr;
            try {
                nameBuffer = new char[nameLength + 1];
                inputFile.read(nameBuffer, nameLength);
                nameBuffer[nameLength] = '\0';
                students[i].setFullName(std::string(nameBuffer));
                delete[] nameBuffer;
            } catch (const std::bad_alloc&) {
                delete[] nameBuffer;
                throw MemoryError("Не удалось выделить память для чтения ФИО студента №" + std::to_string(i + 1));
            }

            // Читаем номер группы
            size_t groupLength;
            inputFile.read(reinterpret_cast<char*>(&groupLength), sizeof(groupLength));
            if (!inputFile.good()) {
                throw FileError("Ошибка чтения длины номера группы студента №" + std::to_string(i + 1), filename);
            }

            char* groupBuffer = nullptr;
            try {
                groupBuffer = new char[groupLength + 1];
                inputFile.read(groupBuffer, groupLength);
                groupBuffer[groupLength] = '\0';
                students[i].setGroupNumber(std::string(groupBuffer));
                delete[] groupBuffer;
            } catch (const std::bad_alloc&) {
                delete[] groupBuffer;
                throw MemoryError("Не удалось выделить память для чтения номера группы студента №" + std::to_string(i + 1));
            }

            // Читаем оценки
            int grades[5];
            inputFile.read(reinterpret_cast<char*>(grades), sizeof(grades));
            if (!inputFile.good()) {
                throw FileError("Ошибка чтения оценок студента №" + std::to_string(i + 1), filename);
            }
            students[i].setGrades(grades);
        }
    } catch (const FileError&) {
        inputFile.close();
        throw;
    } catch (const MemoryError&) {
        inputFile.close();
        throw;
    } catch (const std::exception& e) {
        inputFile.close();
        throw FileError("Неожиданная ошибка при чтении: " + std::string(e.what()), filename);
    }

    inputFile.close();
}

void displayStudents(const STUDENT* students, int count) {
    std::cout << "\n=== СПИСОК СТУДЕНТОВ ===" << std::endl;
    for (int i = 0; i < count; i++) {
        std::cout << "\nСтудент " << (i + 1) << ":" << std::endl;
        std::cout << students[i];
    }
}

void analyzeStudents(const STUDENT* students, int count) {
    std::cout << "\n=== АНАЛИЗ УСПЕВАЕМОСТИ ===" << std::endl;

    int studentsWithTwos = 0;
    int totalTwos = 0;

    for (int i = 0; i < count; i++) {
        if (students[i].hasGradeTwo()) {
            studentsWithTwos++;
            totalTwos += students[i].getTwosCount();
        }
    }

    std::cout << "Студентов с оценками 2: " << studentsWithTwos << std::endl;
    std::cout << "Общее количество оценок 2: " << totalTwos << std::endl;

    if (studentsWithTwos > 0) {
        std::cout << "\n=== СТУДЕНТЫ С ОЦЕНКОЙ 2 ===" << std::endl;
        for (int i = 0; i < count; i++) {
            if (students[i].hasGradeTwo()) {
                std::cout << "ФИО: " << students[i].getFullName()
                          << ", Группа: " << students[i].getGroupNumber() << std::endl;
            }
        }
    } else {
        std::cout << "\nСтудентов с оценкой 2 не найдено." << std::endl;
    }
}

int main() {
    // Установка кодировки UTF-8 для корректного отображения русского текста
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    STUDENT* students = nullptr;
    int studentCount = 0;
    std::string filename = "students.dat";

    try {
        // Получение количества студентов с обработкой ошибок ввода
        studentCount = getStudentCount();

        // Создание массива студентов с обработкой ошибок памяти
        students = createStudentArray(studentCount);

        // Ввод данных студентов
        inputStudents(students, studentCount);

        // Отображение введенных данных
        displayStudents(students, studentCount);

        // Анализ данных
        analyzeStudents(students, studentCount);

        // Сохранение в файл с обработкой ошибок
        saveToFile(students, studentCount, filename);

        std::cout << "\nПрограмма выполнена успешно!" << std::endl;

    } catch (const InputError& e) {
        e.print();
        std::cout << "Программа завершена из-за ошибки ввода." << std::endl;
    } catch (const MemoryError& e) {
        e.print();
        std::cout << "Программа завершена из-за ошибки памяти." << std::endl;
    } catch (const FileError& e) {
        e.print();
        std::cout << "Программа завершена из-за ошибки файла." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Неожиданная ошибка: " << e.what() << std::endl;
        std::cout << "Программа завершена из-за неожиданной ошибки." << std::endl;
    }

    // Освобождение памяти
    if (students != nullptr) {
        delete[] students;
        students = nullptr;
    }

    return 0;
}