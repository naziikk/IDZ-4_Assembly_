#pragma once
#include <vector>
#include <iostream>
#include <random>
#include <pthread.h>
#include <cstdlib>
#include <cstring>

std::string generateNewNoteGen(size_t size) {
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

class RWLockCondvar {
public:
    RWLockCondvar() {
        pthread_mutex_init(&mutex_, nullptr);
        pthread_cond_init(&reader_cv_, nullptr);
        pthread_cond_init(&writer_cv_, nullptr);
    }

    ~RWLockCondvar() {
        pthread_mutex_destroy(&mutex_);
        pthread_cond_destroy(&reader_cv_);
        pthread_cond_destroy(&writer_cv_);
    }

    void Read(std::vector<std::string>& data) {
        pthread_mutex_lock(&mutex_); // захватываем мьютекс
        // ожидаем, пока не станет доступно чтение (нет активного писателя)
        while (writer_active_) {
            pthread_cond_wait(&reader_cv_, &mutex_);
        }
        ++active_readers_; // увеличиваем количество активных читателей
        pthread_mutex_unlock(&mutex_); // отпускаем мьютекс для других потоков
        try {
            // выбираем случайную строку для чтения
            int idx = rand() % data.size();
            std::cout << "Reader reading the " << idx << " note...\n";
            std::cout << "Read note: " << data[idx] << '\n';
        } catch (...) {
            EndRead(); // завершаем чтение при исключении
            throw;
        }
        EndRead();
    }

    void Write(std::vector<std::string>& data) {
        pthread_mutex_lock(&mutex_); // захватываем мьютекс

        // ожидаем, пока запись станет возможной (нет активных читателей или писателей)
        while (writer_active_ || active_readers_ > 0) {
            pthread_cond_wait(&writer_cv_, &mutex_);
        }
        writer_active_ = true; // помечаем, что писатель активен
        pthread_mutex_unlock(&mutex_); // отпускаем мьютекс для других потоков

        try {
            // выбираем случайную строку для изменения
            int idx = rand() % data.size();
            std::cout << "Writer changing the " << idx << " note...\n";
            // генерируем новую строку
            std::string new_note = generateNewNoteGen(data[idx].size());
            std::cout << "New note - " << new_note << '\n';

            data[idx] = new_note + " (changed)";
        } catch (...) {
            EndWrite(); // завершаем запись при исключении
            throw;
        }
        EndWrite();
    }

private:
    pthread_mutex_t mutex_{}; // общий мьютекс для синхронизации
    pthread_cond_t reader_cv_{}; // условная переменная для управления читателями
    pthread_cond_t writer_cv_{}; // условная переменная для управления писателями
    int active_readers_ = 0; // количество активных читателей
    bool writer_active_ = false; // флаг активности писателя

    void EndRead() {
        pthread_mutex_lock(&mutex_); // захватываем мьютекс
        --active_readers_; // уменьшаем количество активных читателей

        if (active_readers_ == 0) {
            pthread_cond_signal(&writer_cv_); // уведомляем писателей, если больше нет активных читателей
        }
        pthread_mutex_unlock(&mutex_);
    }
    void EndWrite() {
        pthread_mutex_lock(&mutex_); // захватываем мьютекс
        writer_active_ = false; // снимаем флаг активности писателя

        pthread_cond_broadcast(&reader_cv_); // уведомляем всех читателей
        pthread_cond_signal(&writer_cv_); // уведомляем одного писателя
        pthread_mutex_unlock(&mutex_);
    }
};