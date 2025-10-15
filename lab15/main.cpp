#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>
#include <locale>
#include "File.h"

using namespace std;

// Функция для вывода каталога файлов
void printCatalog(const list<File>& catalog) {
    cout << "\n=== Каталог файлов ===" << endl;
    if (catalog.empty()) {
        cout << "Каталог пуст." << endl;
        return;
    }
    
    for (const auto& file : catalog) {
        cout << file << endl;
    }
}

// Функция для начального формирования каталога файлов
void initializeCatalog(list<File>& catalog) {
    cout << "\n=== Начальное формирование каталога файлов ===" << endl;
    int count;
    cout << "Сколько файлов добавить? ";
    cin >> count;
    
    for (int i = 0; i < count; i++) {
        File file;
        cout << "Файл #" << (i + 1) << ":" << endl;
        cin >> file;
        catalog.push_back(file);
        cout << "Файл добавлен." << endl;
    }
}

// Функция для удаления файлов, дата создания которых раньше заданной
void removeFilesBeforeDate(list<File>& catalog) {
    cout << "\n=== Удаление файлов по дате ===" << endl;
    int day, month, year;
    cout << "Введите дату (день месяц год), до которой удалять файлы: ";
    cin >> day >> month >> year;
    
    Date targetDate(day, month, year);
    
    // Используем remove_if для удаления файлов с датой создания раньше заданной
    catalog.remove_if([targetDate](const File& file) {
        return file.getDate() < targetDate;
    });
    
    cout << "Файлы, созданные до " << targetDate.toString() << " удалены." << endl;
}

// Функция для выборки файла с наибольшим количеством обращений
void findFileWithMaxAccess(const list<File>& catalog) {
    cout << "\n=== Файл с наибольшим количеством обращений ===" << endl;
    
    if (catalog.empty()) {
        cout << "Каталог пуст." << endl;
        return;
    }
    
    // Используем max_element для поиска файла с максимальным количеством обращений
    auto maxFile = max_element(catalog.begin(), catalog.end(),
        [](const File& a, const File& b) {
            return a.getAccessCount() < b.getAccessCount();
        });
    
    cout << "Файл с наибольшим количеством обращений:" << endl;
    cout << *maxFile << endl;
    
    // Увеличиваем счетчик обращений для этого файла
    const_cast<File&>(*maxFile).incrementAccessCount();
    cout << "Счетчик обращений увеличен." << endl;
}

// Функция для симуляции обращения к файлу
void simulateAccess(list<File>& catalog) {
    cout << "\n=== Симуляция обращения к файлу ===" << endl;
    string fileName;
    cout << "Введите имя файла для обращения: ";
    cin >> fileName;
    
    auto it = find_if(catalog.begin(), catalog.end(),
        [&fileName](const File& file) {
            return file.getName() == fileName;
        });
    
    if (it != catalog.end()) {
        it->incrementAccessCount();
        cout << "Обращение к файлу '" << fileName << "' зарегистрировано." << endl;
    } else {
        cout << "Файл '" << fileName << "' не найден." << endl;
    }
}

int main() {
    // Установка локали для поддержки русского языка
    std::locale::global(std::locale(""));
    
    list<File> catalog;
    int choice;
    
    cout << "Программа для управления каталогом файлов" << endl;
    
    do {
        cout << "\n=== Меню ===" << endl;
        cout << "1. Начальное формирование каталога файлов" << endl;
        cout << "2. Вывод каталога файлов" << endl;
        cout << "3. Удаление файлов, созданных до заданной даты" << endl;
        cout << "4. Выборка файла с наибольшим количеством обращений" << endl;
        cout << "5. Симуляция обращения к файлу" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                initializeCatalog(catalog);
                break;
            case 2:
                printCatalog(catalog);
                break;
            case 3:
                removeFilesBeforeDate(catalog);
                break;
            case 4:
                findFileWithMaxAccess(catalog);
                break;
            case 5:
                simulateAccess(catalog);
                break;
            case 0:
                cout << "Программа завершена." << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
                break;
        }
    } while (choice != 0);
    
    return 0;
}