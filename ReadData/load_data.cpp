#include <iostream>
#include <fstream>
#include <vector>

void readData(std::vector<std::string>& data_) {
    while (true) {
        std::cout << "Choose an option:\n"
                     "1. Enter data from console\n"
                     "2. Load data from file\n";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Enter the number of notes:\n";
            int notes_cnt;
            std::cin >> notes_cnt;
            data_.resize(notes_cnt);
            for (int i = 0; i < notes_cnt; i++) {
                std::cout << "Enter the note:\n";
                std::cin >> data_[i];
            }
            break;
        } else if (choice == 2) {
            std::cout << "Enter file name:\n";
            std::string file_name;
            std::cin >> file_name;
            std::ifstream file(file_name);
            if (!file.is_open()) {
                std::cout << "Error: Unable to open file \"" << file_name << "\". Try again.\n";
                continue;
            }
            std::cout << "File \"" << file_name << "\" loaded successfully.\n";
            for (std::string note; std::getline(file, note);) {
                data_.push_back(note);
            }
            break;
        } else {
            std::cout << "Incorrect data! Please enter 1 or 2.\n";
        }
    }
}

