#pragma once
#include <atomic>
#include <cassert>
#include <condition_variable>
#include <deque>
#include <functional>
#include <mutex>
#include <queue>

class Function_pool {
    private:
    std::deque<std::function<void()>> m_function_queue;
    std::deque<size_t> m_order_queue;
    std::mutex m_lock;
    std::condition_variable m_data_condition;
    std::atomic<bool> m_accept_functions;

    public:
    Function_pool();
    ~Function_pool();
    void push(std::function<void()> func);
    void done();
    void infinite_loop_func();
};
