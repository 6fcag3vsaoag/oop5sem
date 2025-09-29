#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <windows.h>

int main() {
    // Установка кодировки UTF-8 для корректного отображения русского текста
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    std::string filename;
    std::cout << "Введите имя файла для чтения: ";
    std::getline(std::cin, filename);

    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл '" << filename << "'" << std::endl;
        return 1;
    }

    std::cout << "\n=== СТРОКИ, СОДЕРЖАЩИЕ ДВУЗНАЧНЫЕ ЧИСЛА ===" << std::endl;

    std::string line;
    int lineNumber = 0;
    int foundLines = 0;
    std::regex twoDigitNumber("\\b[1-9][0-9]\\b"); // Регулярное выражение для двузначных чисел

    while (std::getline(inputFile, line)) {
        lineNumber++;

        if (std::regex_search(line, twoDigitNumber)) {
            std::cout << "Строка " << lineNumber << ": " << line << std::endl;
            foundLines++;
        }
    }

    if (foundLines == 0) {
        std::cout << "Строки с двузначными числами не найдены." << std::endl;
    } else {
        std::cout << "\nНайдено строк с двузначными числами: " << foundLines << std::endl;
    }

    inputFile.close();

    // Создание примера файла для демонстрации
    std::cout << "\n=== СОЗДАНИЕ ПРИМЕРА ФАЙЛА ===" << std::endl;
    std::string exampleFile = "example.txt";
    std::ofstream example(exampleFile);

    if (example.is_open()) {
        example << "Это пример файла для тестирования программы." << std::endl;
        example << "В этой строке есть число 25 и еще одно 99." << std::endl;
        example << "Здесь только однозначные числа: 1, 2, 3." << std::endl;
        example << "А здесь трехзначное число 123 и двузначное 45." << std::endl;
        example << "Строка без чисел." << std::endl;
        example << "Еще одна строка с числами 67 и 89." << std::endl;
        example << "Последняя строка с числом 10." << std::endl;
        example.close();
        std::cout << "Создан файл '" << exampleFile << "' для демонстрации работы программы." << std::endl;
        std::cout << "Запустите программу снова и укажите этот файл для тестирования." << std::endl;
    }

    return 0;
}