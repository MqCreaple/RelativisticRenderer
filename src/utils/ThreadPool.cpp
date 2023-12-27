#include "utils/ThreadPool.h"

namespace gmq {

ThreadPool::ThreadPool(size_t threadCount) {
    for(size_t i = 0; i < threadCount; i++) {
        threads.push_back(std::thread([this]() {
            while(true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(taskQueueMutex);
                    if(taskQueue.empty()) {
                        break;
                    }
                    task = taskQueue.front();
                    taskQueue.pop();
                }
                task();
            }
        }));
    }
}

void ThreadPool::addTask(std::function<void()> task) {
    std::unique_lock<std::mutex> lock(taskQueueMutex);
    taskQueue.push(task);
}

void ThreadPool::join() {
    for(std::thread &thread : threads) {
        thread.join();
    }
}

} // namespace gmq