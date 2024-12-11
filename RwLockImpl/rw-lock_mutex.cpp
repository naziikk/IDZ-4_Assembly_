#pragma once
#include <omp.h>
#include <vector>
#include <iostream>
#include <random>
#include <string>

std::string generateNewNote(size_t size) {
    const std::string pattern = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; // доступные символы
    std::string result;
    result.reserve(size);
    // создаем генератор случайных чисел
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<size_t> dist(0, pattern.size() - 1);

    // добавляем случайные символы в строку
    for (size_t i = 0; i < size; ++i) {
        result += pattern[dist(mt)];
    }
    return result;
}

class RWLock {
public:
    RWLock() {
        omp_init_lock(&global_);
    }

    ~RWLock() {
        omp_destroy_lock(&global_);
    }

    void Read(std::vector<std::string>& data) {
        #pragma omp critical(read_counter)
        {
            ++blocked_readers_; // увеличиваем количество активных читателей
            if (blocked_readers_ == 1) {
                omp_set_lock(&global_); // блокируем запись, если это первый читатель
            }
        }
        int idx = rand() % data.size();
        std::cout << "Reader reading the " << idx << " note...\n";
        std::cout << "Read note: " << data[idx] << '\n';

        EndRead();
    }

    void Write(std::vector<std::string>& data) {
        omp_set_lock(&global_); // блокируем запись

        int idx = rand() % data.size(); // выбираем случайный индекс
        std::cout << "Writer changing the " << idx << " note...\n";
        // создаем новую строку такого же размера, как текущая
        std::string new_note = generateNewNote(data[idx].size());
        std::cout << "New note - " << new_note << '\n';
        data[idx] = new_note + " (changed)"; // обновляем выбранную запись

        omp_unset_lock(&global_); // разблокируем запись
    }

private:
    omp_lock_t global_; // блокировка записи
    int blocked_readers_ = 0; // счетчик активных читателей

    void EndRead() {
        #pragma omp critical(read_counter)
        {
            --blocked_readers_; // уменьшаем количество активных читателей
            if (blocked_readers_ == 0) {
                omp_unset_lock(&global_); // разблокируем запись, если больше нет читателей
            }
        }
    }
};
