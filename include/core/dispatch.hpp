#ifndef DISPATCH_HPP
#define DISPATCH_HPP

#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class Dispatch {
  public:
    template <typename Function, typename... Args>
    auto dispatch(Function &&func, Args &&... args)
        -> std::future<typename std::result_of<Function(Args...)>::type> {
        // declares a threadpool with 8 threads
        ThreadPool *pool = new ThreadPool(8);

        // enqueue the function call to the thread pool
        auto result = pool->enqueue(std::forward<Function>(func),
                                    std::forward<Args>(args)...);

        delete pool;

        // return the future object to get the result later
        return result;
    }
};
#endif
