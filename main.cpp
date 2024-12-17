#include <iostream>
#include <fstream>
#include <vector>
#include "ReadData/load_data.cpp"
#include "RwLockImpl/rw-lock_mutex.cpp"
//#include "RwLockImpl/rw-lock_condvar.cpp"
#include <thread>

int main() {
    std::vector<std::string> data_;
    readData(data_);
    std::cout << "EnterRandomData the name of output file:\n";
    std::string file_name;
    std::cin >> file_name;
    // вся задача сводится к базовой задаче rw-lock (readers-writers lock)
    // https://en.wikipedia.org/wiki/Readers%E2%80%93writer_lock
    // для первого решения опишем алгоритм
    // мы имеем 2 mutex-а, один mutex отвечает за писателей, второй за читателей
    // так же зафиксируем счетчик читателей, которые в данный момент просматривают базу данных
    // при появлении нового читателя блокируем поток читателей, инкрементим счетчик и
    // если счетчик = 1, блокируем писателей
    // далее рассмотрим решение - 2, используя condition_variable
    // для этого опишем алгоритм
    // мы имеем 2 condition_variable, один condition_variable отвечает за писателей, второй за читателей

    std::cout << "----------------------------------------------------------------------------\n";

    RWLock rw_lock;
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i++) {
        // делаем выбор операции полностью рандомизированным
        int choice = rand() % 2;
        threads.emplace_back([&, choice]() {
            if (choice == 0) {
                rw_lock.Read(data_);
            } else {
                rw_lock.Write(data_);
            }
            std::cout << "----------------------------------------------------------------------------\n";
        });
    }
    // дождемся завершения всех потоков
    for (auto& thread : threads) {
        thread.join();
    }
    std::cout << "New data:\n";
    // выведем новые данные на экран
    for (const auto& note : data_) {
        std::cout << note << '\n';
    }
    std::ofstream file(file_name);
    // в случае ошибки выводим сообщение об ошибке
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file \"" << file_name << "\".\n";
        return 1;
    }
    // запишем данные в файл
    for (const auto& note : data_) {
        file << note << '\n';
    }
    std::cout << "Data saved successfully.\n";
    return 0;
}
