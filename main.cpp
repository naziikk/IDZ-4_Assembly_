#include <iostream>
#include <fstream>
#include <vector>
#include <pthread.h>
#include <cstdlib>
#include <cstring>
#include "ReadData/load_data.cpp"
#include "RwLockImpl/rw-lock_condvar.cpp"
#include "RwLockImpl/rw-lock_mutex.cpp"

struct ThreadArgs {
    RWLockCondvar* rw_lock;
    std::vector<std::string>* data;
    int choice;
};

void* threadFunction(void* arg) {
    ThreadArgs* args = static_cast<ThreadArgs*>(arg);

    if (args->choice == 0) {
        args->rw_lock->Read(*args->data);
    } else {
        args->rw_lock->Write(*args->data);
    }

    std::cout << "----------------------------------------------------------------------------\n";

    delete args;
    return nullptr;
}

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

    RWLockCondvar rw_lock;
    pthread_t threads[10];

    for (int i = 0; i < 10; i++) {
        // делаем выбор операции полностью рандомизированным
        int choice = rand() % 2;
        ThreadArgs* args = new ThreadArgs{&rw_lock, &data_, choice};
        int result = pthread_create(&threads[i], nullptr, threadFunction, args);
        if (result != 0) {
            std::cerr << "Error creating thread: " << strerror(result) << std::endl;
            return 1;
        }
    }
    // дождемся завершения всех потоков
    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], nullptr);
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