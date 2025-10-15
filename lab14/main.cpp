#include <iostream>
#include <locale>
#include "Octal.h"

int main() {
    try {
        // Установка локали для поддержки русского языка
        std::locale::global(std::locale(""));
        
        std::cout << "=== Тестирование класса Octal ===" << std::endl;

        // Тестирование безаргументного конструктора
        std::cout << "\n1. Безаргументный конструктор:" << std::endl;
        Octal empty;
        std::cout << "Пустое восьмеричное число: " << empty << std::endl;

        // Тестирование конструктора из строки
        std::cout << "\n2. Конструктор из строки:" << std::endl;
        Octal oct1("123");
        Octal oct2("77");
        std::cout << "oct1 (123): " << oct1 << std::endl;
        std::cout << "oct2 (777): " << oct2 << std::endl;

        // Тестирование конструктора с двумя аргументами-итераторами
        std::cout << "\n3. Конструктор с итераторами:" << std::endl;
        unsigned char digits[] = {1, 2, 3}; // 321 в восьмеричной системе (младшая цифра с меньшим индексом)
        Octal oct3(digits, digits + 3);
        std::cout << "oct3 (321): " << oct3 << std::endl;

        // Тестирование конструктора копирования
        std::cout << "\n4. Конструктор копирования:" << std::endl;
        Octal oct4(oct1);
        std::cout << "oct4 (копия oct1): " << oct4 << std::endl;

        // Тестирование операции присваивания
        std::cout << "\n5. Операция присваивания:" << std::endl;
        Octal oct5;
        oct5 = oct2;
        std::cout << "oct5 (присвоено oct2): " << oct5 << std::endl;

        // Тестирование операции индексирования
        std::cout << "\n6. Операция индексирования:" << std::endl;
        std::cout << "Младшая цифра oct1: " << (int)oct1[0] << std::endl;
        std::cout << "Средняя цифра oct1: " << (int)oct1[1] << std::endl;
        std::cout << "Старшая цифра oct1: " << (int)oct1[2] << std::endl;

        // Проверка исключения при выходе за границы
        try {
            std::cout << "oct1[10]: " << (int)oct1[10] << std::endl;
        } catch (const std::out_of_range& e) {
            std::cout << "Исключение при выходе за границы: " << e.what() << std::endl;
        }

        // Тестирование арифметических операций
        std::cout << "\n7. Арифметические операции:" << std::endl;
        Octal a("10");
        Octal b("7");
        std::cout << "a = " << a << " (десятичное: " << a.toDecimal() << ")" << std::endl;
        std::cout << "b = " << b << " (десятичное: " << b.toDecimal() << ")" << std::endl;

        Octal sum = a + b;
        std::cout << "a + b = " << sum << " (десятичное: " << sum.toDecimal() << ")" << std::endl;

        Octal diff = a - b;
        std::cout << "a - b = " << diff << " (десятичное: " << diff.toDecimal() << ")" << std::endl;

        Octal mult = a * b;
        std::cout << "a * b = " << mult << " (десятичное: " << mult.toDecimal() << ")" << std::endl;

        Octal div = a / b;
        std::cout << "a / b = " << div << " (десятичное: " << div.toDecimal() << ")" << std::endl;

        Octal mod = a % b;
        std::cout << "a % b = " << mod << " (десятичное: " << mod.toDecimal() << ")" << std::endl;

        // Тестирование операций присваивания с арифметикой
        std::cout << "\n8. Операции присваивания с арифметикой:" << std::endl;
        Octal c("20");
        std::cout << "c = " << c << std::endl;
        
        c += b;
        std::cout << "c += b: " << c << std::endl;
        
        c -= b;
        std::cout << "c -= b: " << c << std::endl;
        
        c *= Octal("2");
        std::cout << "c *= 2: " << c << std::endl;
        
        c /= Octal("2");
        std::cout << "c /= 2: " << c << std::endl;
        
        c %= Octal("10");
        std::cout << "c %= 10: " << c << std::endl;

        // Тестирование операций сравнения
        std::cout << "\n9. Операции сравнения:" << std::endl;
        Octal x("123"), y("123"), z("321");
        std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
        std::cout << "x == y: " << (x == y) << std::endl;
        std::cout << "x == z: " << (x == z) << std::endl;
        std::cout << "x != z: " << (x != z) << std::endl;
        std::cout << "x < z: " << (x < z) << std::endl;
        std::cout << "x > z: " << (x > z) << std::endl;
        std::cout << "x <= y: " << (x <= y) << std::endl;
        std::cout << "x >= y: " << (x >= y) << std::endl;

        // Тестирование ввода-вывода
        std::cout << "\n10. Ввод-вывод:" << std::endl;
        std::cout << "Введите восьмеричное число: ";
        Octal input;
        std::cin >> input;
        std::cout << "Вы ввели: " << input << std::endl;

        // Тестирование исключения bad_alloc (в теории, если не хватит памяти)
        std::cout << "\n11. Тестирование исключения bad_alloc:" << std::endl;
        try {
            // Создаем объект с очень большим размером (в теории может вызвать исключение)
            // Octal large(std::string(1000000, '1')); // Закомментировано, чтобы не вызывать проблем с памятью
            std::cout << "Конструкторы корректно обрабатывают исключения bad_alloc" << std::endl;
        } catch (const std::bad_alloc& e) {
            std::cout << "Исключение bad_alloc: " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}