#pragma once
#include <vector>
#include <iostream>
#include <random>
#include <pthread.h>
#include <cstdlib>

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
        pthread_mutex_init(&read_, nullptr);
        pthread_mutex_init(&global_, nullptr);
    }

    ~RWLock() {
        pthread_mutex_destroy(&read_);
        pthread_mutex_destroy(&global_);
    }

    void Read(std::vector<std::string>& data) {
        pthread_mutex_lock(&read_); // блокируем доступ к счетчику читателей
        ++blocked_readers_; // увеличиваем количество активных читателей
        if (blocked_readers_ == 1) {
            pthread_mutex_lock(&global_); // блокируем запись, если это первый читатель
        }
        pthread_mutex_unlock(&read_); // освобождаем доступ к счетчику

        int idx = rand() % data.size();
        std::cout << "Reader reading the " << idx << " note...\n";
        std::cout << "Read note: " << data[idx] << '\n';

        EndRead();
    }

    // метод для записи данных
    void Write(std::vector<std::string>& data) {
        pthread_mutex_lock(&global_); // блокируем глобальный доступ на время записи

        int idx = rand() % data.size(); // выбираем случайный индекс
        std::cout << "Writer changing the " << idx << " note...\n";

        // создаем новую строку такого же размера, как текущая
        std::string new_note = generateNewNote(data[idx].size());
        std::cout << "New note - " << new_note << '\n';

        data[idx] = new_note + " (changed)"; // обновляем выбранную запись

        pthread_mutex_unlock(&global_);
    }

private:
    pthread_mutex_t read_; // мьютекс для управления доступом к счетчику читателей
    pthread_mutex_t global_; // мьютекс для блокировки записи
    int blocked_readers_ = 0; // счетчик активных читателей

    void EndRead() {
        pthread_mutex_lock(&read_); // блокируем доступ к счетчику читателей
        --blocked_readers_; // уменьшаем количество активных читателей
        if (blocked_readers_ == 0) {
            pthread_mutex_unlock(&global_); // разблокируем запись, если больше нет читателей
        }
        pthread_mutex_unlock(&read_); // освобождаем доступ к счетчику
    }
};