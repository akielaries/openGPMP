#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace mtpk {

class ThreadPool {
  public:
    /**
     * @brief Default constructor that creates a ThreadPool with the number
     * of threads
     */
    ThreadPool() : ThreadPool(std::thread::hardware_concurrency()) {
    }

    /**
     * @brief Constructs a ThreadPool with a given number of worker
     * threads.
     * @param numThreads The number of worker threads to be created.
     * @details Constructs a ThreadPool object with the specified number of
     * worker threads.
     */
    explicit ThreadPool(int numThreads) : stop(false) {
        for (int i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                for (;;) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(
                            this->queue_mutex);
                        this->condition.wait(lock, [this] {
                            return this->stop || !this->tasks.empty();
                        });
                        if (this->stop && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    /**
     * @brief Enqueues a task to the thread pool.
     * @tparam F Type of the function to be enqueued.
     * @tparam Args Variadic template parameter pack of the arguments
     * passed to the function.
     * @param f Function to be enqueued.
     * @param args Arguments passed to the function
     * @return std::future<typename std::result_of<F(Args...)>::type> A
     * future object that will contain the result of the function
     * execution.
     * @throw std::runtime_error If the ThreadPool has already been
     * stopped.
     */
    template <class F, class... Args>
    auto enqueue(F &&f, Args &&... args)
        -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if (stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();

        return res;
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker : workers)
            worker.join();
    }

  private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

class ThreadDispatch {
  public:
    template <typename Function, typename... Args>
    auto dispatch(ThreadPool &pool, Function &&func, Args &&... args)
        -> std::future<typename std::result_of<Function(Args...)>::type> {

        // enqueue the function call to the thread pool
        auto result = pool.enqueue(std::forward<Function>(func),
                                   std::forward<Args>(args)...);

        // return the future object to get the result later
        return result;
    }
};

} // namespace mtpk

#endif
