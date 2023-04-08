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
    /**
     * @brief Constructor for the ThreadPool class.
     * @param numThreads The number of threads in the thread pool
     * (default: std::thread::hardware_concurrency()).
     * Initializes a new ThreadPool object with the specified number of
     * threads. If the number of threads is not specified, it is set to the
     * number of hardware threads available on the system.
     */
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

    /**
     * @brief Enqueue a task to be executed by the thread pool.
     * @param f The function object to be executed by the thread pool.
     * @param args The arguments to be passed to the function object.
     * @return A future representing the result of the function object.
     * Adds a task to the thread pool and returns a future representing the
     * result of the task.
     * The function object and its arguments are passed using perfect
     * forwarding. If the thread pool is stopped, an exception is thrown.
     */
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

    /*
    void thread_resize(size_t numThreads) {
        bool shouldWait = false;

        // Lock the queue mutex to ensure thread safety
        std::unique_lock<std::mutex> lock(queueMutex);

        // If the requested number of threads is greater than the current
        // number of threads, create new threads
        while (numThreads > workers.size()) {
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

        // If the requested number of threads is less than the current
        // number of threads, signal the threads to stop and join them
        while (numThreads < workers.size()) {
            shouldWait = true;
            workers.back().join();
            workers.pop_back();
        }

        // If there are no more threads, unlock the mutex and return
        if (workers.empty()) {
            lock.unlock();
            return;
        }

        // If there are still threads running, notify them to stop
        stop = true;
        condition.notify_all();

        // If we removed threads, wait for them to finish
        if (shouldWait) {
            for (auto &worker : workers) {
                worker.join();
            }
        }

        // Restart the threads and clear the stop flag
        stop = false;
        for (size_t i = 0; i < workers.size(); ++i) {
            condition.notify_one();
        }
    }*/

    /**
     * @brief Destructor for the ThreadPool class. Stops the thread pool
     * and joins threads
     */
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
