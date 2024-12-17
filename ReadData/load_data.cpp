#include <iostream>
#include <fstream>
#include <vector>
#include </Users/nazarzakrevskij/CLionProjects/IDZ-4-Assembly/RwLockImpl/rw-lock_mutex.cpp>

void readData(std::vector<std::string>& data_) {
    // бесконечный цикл для повторного запроса, если пользователь введет некорректный выбор
    while (true) {
        std::cout << "Choose an option:\n"
                     "1. Enter data from console\n"
                     "2. Load data from file\n";
        int choice;
        std::cin >> choice; // считываем выбор пользователя

        if (choice == 1) {
            std::cout << "Choose an option:\n"
                         "1. Get random data\n"
                         "2. Enter the data\n";
            int choice_enter = 0;
            std::cin >> choice_enter;
            if (choice_enter == 1) {
                std::cout << "Generated data:\n";
                int random = rand() % 15;
                data_.resize(random); // изменяем размер вектора, чтобы вместить записи
                for (int i = 0; i < random; i++) {
                    data_[i] = generateNewNote(rand() % 15);
                    std::cout << data_[i] << '\n';
                }
                break;
            } else if (choice_enter == 2) {
                std::cout << "EnterRandomData the number of notes:\n";
                int notes_cnt;
                std::cin >> notes_cnt; // количество записей, которые пользователь хочет ввести
                data_.resize(notes_cnt); // изменяем размер вектора, чтобы вместить записи
                for (int i = 0; i < notes_cnt; i++) {
                    std::cout << "EnterRandomData the note:\n";
                    std::cin >> data_[i];
                }
                break;
            }
        } else if (choice == 2) {
            std::cout << "EnterRandomData file name:\n";
            std::string file_name;
            std::cin >> file_name; // имя файла, из которого нужно загрузить данные
            std::ifstream file(file_name); // открываем файл для чтения
            if (!file.is_open()) {
                // проверяем, удалось ли открыть файл
                std::cout << "Error: Unable to open file \"" << file_name << "\". Try again.\n";
                continue; // если файл не открылся, повторяем ввод
            }
            std::cout << "File \"" << file_name << "\" loaded successfully.\n";
            for (std::string note; std::getline(file, note);) {
                data_.push_back(note);
            }
            break;
        } else {
            // если пользователь ввел некорректный выбор
            std::cout << "Incorrect data! Please enter 1 or 2.\n";
        }
    }
}
