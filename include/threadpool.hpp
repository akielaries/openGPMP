#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace mtpk {

/**
 * @class ThreadPool
 * @brief A thread pool implementation for concurrent task execution.
 * This class provides a thread pool implementation that can execute
 * tasks in parallel on multiple threads. It supports adding tasks to
 * the pool and retrieving their results using futures.
 * The number of threads in the pool can be specified or it can be
 * automatically determined using std::thread::hardware_concurrency(),
 * therefore using maximum amount of threads on the system. The pool is
 * stopped and all threads are joined on destruction of the object.
 */
class ThreadPool {
    public:
    // default to the number of cores the host machine uses (4 CORES = 8
    // THREADS)
    ThreadPool(size_t numThreads) // = std::thread::hardware_concurrency())
        : stop(false) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::unique_lock<std::mutex> lock(queueMutex);
                    condition.wait(
                        lock, [this] { return stop || !tasks.empty(); });

                    if (stop && tasks.empty()) {
                        return;
                    }

                    auto task = std::move(tasks.front());
                    tasks.pop();
                    lock.unlock();

                    task();
                }
            });
        }
    }

    template <class F, class... Args>
    auto enqueue(F &&f, Args &&... args)
        -> std::future<typename std::result_of<F(Args...)>::type> {
        using returnType = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<returnType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<returnType> res = task->get_future();

        {
            std::unique_lock<std::mutex> lock(queueMutex);
            if (stop) {
                throw std::runtime_error(
                    "[!] Enqueue on stopped ThreadPool");
            }
            tasks.emplace([task]() { (*task)(); });
        }

        condition.notify_one();
        return res;
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }

        condition.notify_all();

        for (auto &worker : workers) {
            worker.join();
        }
    }

    private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;

    bool stop;
};

} // namespace mtpk

#endif
