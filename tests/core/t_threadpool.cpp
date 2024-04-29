#include <chrono>
#include <gtest/gtest.h>
#include <iostream>
#include <openGPMP/core/threads.hpp>
#include <random>
#include <vector>

using namespace std::chrono_literals;

namespace {
TEST(ThreadPoolTest, EnqueueSingleTask) {
    gpmp::core::ThreadPool pool(1);
    std::future<int> result = pool.enqueue([]() { return 42; });
    ASSERT_EQ(result.get(), 42);
}

TEST(ThreadPoolTest, TestSingleTask) {
    gpmp::core::ThreadPool pool(2);

    std::future<int> result =
        pool.enqueue([](int x, int y) { return x + y; }, 3, 4);

    EXPECT_EQ(result.get(), 7);
}

TEST(ThreadPoolTest, EnqueueMultipleTasks) {
    gpmp::core::ThreadPool pool(4);
    std::vector<std::future<int>> results;
    for (int i = 0; i < 100; ++i) {
        results.emplace_back(pool.enqueue([i]() { return i * 2; }));
    }
    for (int i = 0; i < 100; ++i) {
        ASSERT_EQ(results[i].get(), i * 2);
    }
}

TEST(ThreadPoolTest, EnqueueException) {
    gpmp::core::ThreadPool pool(2);
    std::future<void> result =
        pool.enqueue([]() { throw std::runtime_error("test error"); });
    ASSERT_THROW(result.get(), std::runtime_error);
}

TEST(ThreadPoolTest, TestException) {
    gpmp::core::ThreadPool pool(1);

    EXPECT_THROW(
        pool.enqueue([]() { throw std::runtime_error("test exception"); })
            .get(),
        std::runtime_error);
}

TEST(ThreadPoolTest, TestDynamicAllocation) {
    // Create a new ThreadPool with 4 threads
    gpmp::core::ThreadPool *pool = new gpmp::core::ThreadPool(4);

    // Enqueue a task and wait for it to complete
    std::future<int> result = pool->enqueue([]() { return 42; });
    EXPECT_EQ(result.get(), 42);

    // Delete the ThreadPool
    delete pool;
}

TEST(ThreadPoolTest, TestEnqueueOnStoppedThreadPool) {
    // Create a new ThreadPool with 2 threads
    gpmp::core::ThreadPool *pool = new gpmp::core::ThreadPool(2);

    // Stop the ThreadPool explicitly
    delete pool; // pool.~ThreadPool();

    // Try to enqueue a task on the stopped ThreadPool
    EXPECT_THROW(pool->enqueue([]() { return 42; }), std::runtime_error);
}

TEST(ThreadPoolTest, TestEnqueueWithDifferentReturnTypes) {
    gpmp::core::ThreadPool pool(2);

    auto task1 = []() { /* do something */ };
    auto task2 = []() -> int { return 42; };
    auto task3 = []() -> std::string { return "hello world"; };

    auto res1 = pool.enqueue(task1);
    auto res2 = pool.enqueue(task2);
    auto res3 = pool.enqueue(task3);

    res1.wait();
    EXPECT_EQ(res2.get(), 42);
    EXPECT_EQ(res3.get(), "hello world");
}

TEST(ThreadPoolTest, TestEnqueueWithDifferentArgumentTypes) {
    gpmp::core::ThreadPool pool(2);

    auto task1 = [](int x, int y) { /* do something */ };
    auto task2 = [](const std::string &str) { /* do something */ };
    auto task3 = [](bool flag, float value) { /* do something */ };

    auto res1 = pool.enqueue(task1, 2, 3);
    auto res2 = pool.enqueue(task2, "hello world");
    auto res3 = pool.enqueue(task3, true, 3.14f);

    res1.wait();
    res2.wait();
    res3.wait();
}

TEST(ThreadPoolTest, TestEnqueueWithLargeNumberOfTasks) {
    const int numTasks = 1000;
    gpmp::core::ThreadPool pool(4);

    for (int i = 0; i < numTasks; ++i) {
        auto task = []() { /* do something */ };
        auto task2 = pool.enqueue(task);
        task2.wait();
    }
}

TEST(ThreadPoolTest, DispatchFunction) {
    gpmp::core::ThreadPool pool(2);
    gpmp::core::ThreadDispatch dispatch;

    // fefine a lambda function to be dispatched to the thread pool
    auto task = []() -> int { return 42; };

    // dispatch the task to the thread pool using
    // ThreadDispatch::dispatch()
    auto future_result = dispatch.dispatch(pool, task);

    // wait for the task to complete and get the result
    auto result = future_result.get();

    // check if the result is correct
    EXPECT_EQ(result, 42);
}

TEST(ThreadPoolTest, DispatchFunctionWithArgs) {
    gpmp::core::ThreadPool pool(2);
    gpmp::core::ThreadDispatch dispatch;

    // define a lambda function to be dispatched to the thread pool, which
    // takes an integer argument and returns its square
    auto task = [](int x) -> int { return x * x; };

    auto future_result = dispatch.dispatch(pool, task, 5);

    auto result = future_result.get();

    EXPECT_EQ(result, 25);
}

} // namespace
