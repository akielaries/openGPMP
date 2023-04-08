#include "../include/threadpool.hpp"
#include <chrono>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <vector>

using namespace std::chrono_literals;

namespace {

// A simple task to add two numbers
int add(int a, int b) {
    return a + b;
}

// A task that takes some time to complete
void wait(int duration) {
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

// A task that throws an exception
void error() {
    throw std::runtime_error("An error occurred");
}

// A test that verifies the basic functionality of the thread pool
TEST(ThreadPoolTest, Basic) {
    // Create a thread pool with 4 threads
    mtpk::ThreadPool pool(4);

    // Enqueue some tasks
    auto res1 = pool.enqueue(add, 2, 3);
    auto res2 = pool.enqueue(add, 4, 5);

    // Wait for the tasks to complete and check the results
    EXPECT_EQ(5, res1.get());
    EXPECT_EQ(9, res2.get());
}

// A test that verifies the behavior when an exception is thrown
// TEST(ThreadPoolTest, Exception) {
// Create a thread pool with 4 threads
//    mtpk::ThreadPool pool(4);

// Enqueue a task that throws an exception
//    EXPECT_THROW(pool.enqueue(error), std::runtime_error);
//}

// A test that verifies the behavior when the thread pool is stopped
TEST(ThreadPoolTest, Stop) {
    // Create a thread pool with 4 threads
    mtpk::ThreadPool pool(4);

    // Enqueue some tasks
    auto res1 = pool.enqueue(wait, 100);
    auto res2 = pool.enqueue(wait, 200);

    // Stop the thread pool
    pool.~ThreadPool();

    // Verify that the tasks were not completed
    EXPECT_EQ(std::future_status::timeout, res1.wait_for(0s));
    EXPECT_EQ(std::future_status::timeout, res2.wait_for(0s));
}

// A test that verifies the behavior when the thread pool is resized
TEST(ThreadPoolTest, Resize) {
    // TODO: this test case fails... look into the resize method
    // Create a thread pool with 4 threads
    mtpk::ThreadPool pool(4);

    // Enqueue some tasks
    auto res1 = pool.enqueue(wait, 100);
    auto res2 = pool.enqueue(wait, 200);

    // Wait for tasks to complete
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Resize the thread pool to 2 threads
    pool.thread_resize(2);

    // Verify that the tasks were completed
    EXPECT_EQ(std::future_status::ready, res1.wait_for(0s));
    EXPECT_EQ(std::future_status::ready, res2.wait_for(0s));
}

} // namespace
