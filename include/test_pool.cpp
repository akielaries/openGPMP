#include "test_pool.hpp"

Function_pool::Function_pool()
    : m_function_queue(), m_lock(), m_data_condition(),
      m_accept_functions(true) {
}

Function_pool::~Function_pool() {
}

void Function_pool::push(std::function<void()> func) {
    std::unique_lock<std::mutex> lock(m_lock);
    m_function_queue.push_back(func);
    // when we send the notification immediately, the consumer will try to
    // get the lock , so unlock asap
    lock.unlock();
    m_data_condition.notify_one();
}

/*
void Function_pool::push(std::function<void()> func) {
    std::unique_lock<std::mutex> lock(m_lock);
    m_function_queue.push(func);
    // when we send the notification immediately, the consumer will try to
    // get the lock , so unlock asap
    lock.unlock();
    m_data_condition.notify_one();
}*/

void Function_pool::done() {
    std::unique_lock<std::mutex> lock(m_lock);
    m_accept_functions = false;
    lock.unlock();
    // when we send the notification immediately, the consumer will try to
    // get the lock , so unlock asap
    m_data_condition.notify_all();
    // notify all waiting threads.
}

void Function_pool::infinite_loop_func() {
    std::function<void()> func;
    while (true) {
        {
            std::unique_lock<std::mutex> lock(m_lock);
            m_data_condition.wait(lock, [this]() {
                return !m_function_queue.empty() || !m_accept_functions;
            });
            if (!m_accept_functions && m_function_queue.empty()) {
                // lock will be release automatically.
                // finish the thread loop and let it join in the main
                // thread.
                return;
            }
            func = m_function_queue.front();
            m_function_queue.pop_front();
            // release the lock
        }
        func();
    }
}

/*
void Function_pool::infinite_loop_func() {
    std::function<void()> func;
    while (true) {
        {
            std::unique_lock<std::mutex> lock(m_lock);
            m_data_condition.wait(lock, [this]() {
                return !m_function_queue.empty() || !m_accept_functions;
            });
            if (!m_accept_functions && m_function_queue.empty()) {
                // lock will be release automatically.
                // finish the thread loop and let it join in the main
                // thread.
                return;
            }
            func = m_function_queue.front();
            m_function_queue.pop();
            // release the lock
        }
        func();
    }
}*/
