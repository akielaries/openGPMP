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
  private:
    // VECTOR of threads to execute tasks
    std::vector<std::thread> workers;
    // QUEUE of tasks to be executed
    std::queue<std::function<void()>> tasks;
    // MUTEX synchronizing access to the QUEUE of tasks
    std::mutex queue_mutex;
    // CONDITIONAL to notify waiting threads when queue gets populated
    std::condition_variable condition;
    // BOOL indicating if ThreadPool should stop execution
    bool stop;

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
        
        // this is the return type of the passed in function 
        using return_type = typename std::result_of<F(Args...)>::type;
        // * SHARED POINTER to PACKAGED TASK used to store the passed in i
        //      function + its arguments
        // * std::bind used to create function object binded to the 
        //      function `f` + its args to the packaged tasks
        // * std::forward used for forwarding an argument to another 
        //      function
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        // the FUTURE obj retrieves the return value of the function passed in
        std::future<return_type> res = task->get_future();
        {
            // aquire lock on queue_mutex for synchronization
            std::unique_lock<std::mutex> lock(queue_mutex);
            // 
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
};

/**
 * @brief A class that provides a function to dispatch a function call to a
 * thread pool and return a future object for obtaining the result.
 */
class ThreadDispatch {
  public:
    /**
     * @brief Dispatches a function call to a ThreadPool and returns a
     * future object for obtaining the result.
     * @tparam Function The type of the function to be dispatched.
     * @tparam Args The types of the arguments to be passed to the
     * function.
     * @param pool The ThreadPool object to which the function call is
     * dispatched.
     * @param func The function to be dispatched.
     * @param args The arguments to be passed to the function.
     * @return A future object for obtaining the result of the dispatched
     * function call.
     */
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
