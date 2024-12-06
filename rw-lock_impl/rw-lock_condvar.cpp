#pragma once
#include <mutex>
#include <vector>
#include <iostream>
#include <random>

std::string generateNewNoteGen(size_t size) {
    // строка для генерации случайной записи от writer
    const std::string pattern = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string result;
    result.reserve(size);
    // генератор случайных чисел
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<size_t> dist(0, pattern.size() - 1);
    for (size_t i = 0; i < size; ++i) {
        result += pattern[dist(mt)];
    }
    // вернем случайно сгенерированную запись
    return result;
}

class RWLockCondvar {
public:
    void Read(std::vector<std::string>& data) {
        std::unique_lock<std::mutex> lock(mutex_);
        reader_cv_.wait(lock, [this]() { return !writer_active_; });
        ++active_readers_;
        lock.unlock();

        try {
            int idx = rand() % data.size();
            std::cout << "Reader reading the " << idx << " note...\n";
            std::cout << "Read note: " << data[idx] << '\n';
        } catch (...) {
            EndRead();
            throw;
        }
        EndRead();
    }

    void Write(std::vector<std::string>& data) {
        std::unique_lock<std::mutex> lock(mutex_);
        writer_cv_.wait(lock, [this]() { return !writer_active_ && active_readers_ == 0; });
        writer_active_ = true;
        lock.unlock();

        try {
            int idx = rand() % data.size();
            std::cout << "Writer changing the " << idx << " note...\n";
            std::string new_note = generateNewNoteGen(data[idx].size());
            std::cout << "New note - " << new_note << '\n';
            data[idx] = new_note;
        } catch (...) {
            EndWrite();
            throw;
        }
        EndWrite();
    }

private:
    std::mutex mutex_;
    std::condition_variable reader_cv_;
    std::condition_variable writer_cv_;
    int active_readers_ = 0;
    bool writer_active_ = false;

    void EndRead() {
        std::unique_lock<std::mutex> lock(mutex_);
        --active_readers_;
        if (active_readers_ == 0) {
            writer_cv_.notify_one();
        }
    }

    void EndWrite() {
        std::unique_lock<std::mutex> lock(mutex_);
        writer_active_ = false;
        reader_cv_.notify_all();
        writer_cv_.notify_one();
    }
};
