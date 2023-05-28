/*************************************************************************
 *
 *  Project
 *                        __  __ _______ _____  _  __
 *                       |  \/  |__   __|  __ \| |/ /
 *  ___  _ __   ___ _ __ | \  / |  | |  | |__) | ' /
 * / _ \| '_ \ / _ \ '_ \| |\/| |  | |  |  ___/|  <
 *| (_) | |_) |  __/ | | | |  | |  | |  | |    | . \
 * \___/| .__/ \___|_| |_|_|  |_|  |_|  |_|    |_|\_\
 *      | |
 *      |_|
 *
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openMTPK/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file. As this is an Open Source effort, all implementations
 * must be of the same methodology.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/
/**
 * @file
 * @brief openMTPK Thread Pool
 */
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

namespace core {

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
     * threads to dispatch functions.
     * @param numThreads The number of worker threads to be created.
     * @details Constructs a ThreadPool object with the specified number of
     * worker threads.
     */
    explicit ThreadPool(int numThreads) : stop(false) {

        // traverse through the number of threads specified
        for (int i = 0; i < numThreads; ++i) {
            // add a new thread to the vector storing workers using lambda
            // function
            workers.emplace_back([this] {
                for (;;) {
                    // worker thread creates task object that holds next task to
                    // be executed
                    std::function<void()> task_obj;

                    // this "symbolizes" the critical section of the TheadPool
                    // class
                    {
                        // worker thread locks queue_mutex
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        // wait on conditional_variable (ThreadPool stop OR
                        // queued task), wait() locks/unlocks based on condition
                        // result
                        this->condition.wait(lock, [this] {
                            return this->stop || !this->tasks.empty();
                        });
                        // based on stop OR awaiting tasks, return from the
                        // thread
                        if (this->stop && this->tasks.empty()) {
                            return;
                        }

                        // if above isnt met, move first task in TASKS queue to
                        // the task object to transfer ownership
                        task_obj = std::move(this->tasks.front());

                        // pop the handed off task to make room for a new one.
                        // only ONE thread should remove a task from the queue
                        // at a time
                        this->tasks.pop();
                    }

                    // EXECUTE THE HANDED OFF TASK
                    task_obj();
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
            // check if threadpool stop is initiated
            if (stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            // add a task using emplace to the queue as a lambda that calls the
            // packaged task
            tasks.emplace([task]() { (*task)(); });
        } // once this is hit, unique_lock is out of scope & mutex is
          // automatically unlocked
        // notify one waiting thread of one new task added to the queue
        condition.notify_one();
        // the return is the future object
        return res;
    }

    ~ThreadPool() {
        {
            // lock queue_mutex & set stop to true
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        // unblock all threads
        condition.notify_all();
        // treaverse threads and join
        for (std::thread &worker : workers) {
            worker.join();
        }
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


/**
  * @brief Thread rudimentary for loops
  * @param[in] nb_elements : size of your for loop
  * @param[in] functor(start, end) :
  * your function processing a sub chunk of the for loop.
  * "start" is the first index to process (included) until the index "end"
  * (excluded)
  * @code
  *     for(int i = start; i < end; ++i)
  *         computation(i);
  * @endcode
  * @param use_threads : enable / disable threads
  */
static void parallel_for(unsigned nb_elements,
                  std::function<void (int start, int end)> functor,
                  bool use_threads = true) {
    // -------
    unsigned nb_threads_hint = std::thread::hardware_concurrency();
    unsigned nb_threads = nb_threads_hint == 0 ? 8 : (nb_threads_hint);

    unsigned batch_size = nb_elements / nb_threads;
    unsigned batch_remainder = nb_elements % nb_threads;

    std::vector< std::thread > my_threads(nb_threads);

    if( use_threads )
    {
        // Multithread execution
        for(unsigned i = 0; i < nb_threads; ++i)
        {
            int start = i * batch_size;
            my_threads[i] = std::thread(functor, start, start+batch_size);
        }
    }
    else
    {
        // Single thread execution (for easy debugging)
        for(unsigned i = 0; i < nb_threads; ++i){
            int start = i * batch_size;
            functor( start, start+batch_size );
        }
    }

    // Deform the elements left
    int start = nb_threads * batch_size;
    functor( start, start+batch_remainder);

    // Wait for the other thread to finish their task
    if( use_threads )
        std::for_each(my_threads.begin(), my_threads.end(), std::mem_fn(&std::thread::join));
}
  
} // namespace core

} // namespace mtpk

#endif
