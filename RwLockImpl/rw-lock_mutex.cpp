#pragma once
#include <mutex>
#include <vector>
#include <iostream>
#include <random>

std::string generateNewNote(size_t size) {
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

class RWLock {
public:
    void Read(std::vector<std::string>& data) {
        read_.lock();
        ++blocked_readers_;
        if (blocked_readers_ == 1) {
            global_.lock();
        }
        read_.unlock();
        int idx = rand() % data.size();
        std::cout << "Reader reading the " << idx << " note...\n";
        std::cout << "Read note: " << data[idx] << '\n';
        EndRead();
    }

    void Write(std::vector<std::string>& data) {
        std::lock_guard<std::mutex> lock(global_);
        int idx = rand() % data.size();
        std::cout << "Writer changing the " << idx << " note...\n";
        std::string new_note = generateNewNote(data[idx].size());
        std::cout << "New note - " << new_note << '\n';
        data[idx] = new_note + " (changed)";
    }

private:
    std::mutex read_;
    std::mutex global_;
    int blocked_readers_ = 0;

    void EndRead() {
        read_.lock();
        --blocked_readers_;
        if (!blocked_readers_) {
            global_.unlock();
        }
        read_.unlock();
    }
};
