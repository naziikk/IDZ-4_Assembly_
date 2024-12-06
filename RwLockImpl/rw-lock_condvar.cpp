#pragma once
#include <mutex>
#include <vector>
#include <iostream>
#include <random>


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
    void Read(std::vector<std::string>& data) {
        std::unique_lock<std::mutex> lock(mutex_); // захватываем мьютекс

        // ожидаем, пока не станет доступно чтение (нет активного писателя)
        reader_cv_.wait(lock, [this]() { return !writer_active_; });
        ++active_readers_; // увеличиваем количество активных читателей
        lock.unlock(); // отпускаем мьютекс для других потоков

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
        std::unique_lock<std::mutex> lock(mutex_); // захватываем мьютекс
        // ожидаем, пока запись станет возможной (нет активных читателей или писателей)
        writer_cv_.wait(lock, [this]() { return !writer_active_ && active_readers_ == 0; });
        writer_active_ = true; // помечаем, что писатель активен
        lock.unlock(); // отпускаем мьютекс для других потоков

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
    std::mutex mutex_; // общий мьютекс для синхронизации
    std::condition_variable reader_cv_; // условная переменная для управления читателями
    std::condition_variable writer_cv_; // условная переменная для управления писателями
    int active_readers_ = 0; // количество активных читателей
    bool writer_active_ = false; // флаг активности писателя

    void EndRead() {
        std::unique_lock<std::mutex> lock(mutex_); // захватываем мьютекс
        --active_readers_; // уменьшаем количество активных читателей

        if (active_readers_ == 0) {
            writer_cv_.notify_one(); // уведомляем писателей, если больше нет активных читателей
        }
    }

    void EndWrite() {
        std::unique_lock<std::mutex> lock(mutex_); // захватываем мьютекс
        writer_active_ = false; // снимаем флаг активности писателя

        reader_cv_.notify_all(); // уведомляем всех читателей
        writer_cv_.notify_one(); // уведомляем одного писателя
    }
};
