#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <functional>

namespace gmq {

class ThreadPool {
public:
    ThreadPool(size_t threadCount);
    void addTask(std::function<void()> task);
    void join();
private:
    std::queue<std::function<void()>> taskQueue;
    std::mutex taskQueueMutex;
    std::vector<std::thread> threads;
};

} // namespace gmq