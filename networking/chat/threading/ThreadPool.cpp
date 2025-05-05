//
// Created by yingbingzhu on 2025/5/4.
//

#include "ThreadPool.hpp"
#include <iostream>

ThreadPool::ThreadPool(size_t thread_count) : stop_(false) {
  for (size_t i = 0; i < thread_count; i++) {
    workers_.emplace_back([this]() {
      while (!stop_) {
        auto task = queue_.poll();  // Waits until a task is available
        task();    // Execute the task
      }
    });
  }
}

ThreadPool::~ThreadPool() {
  stop_ = true;
  for (size_t i = 0; i < workers_.size(); ++i) {
    queue_.push([]{});  // dummy task
  }

  for (auto &worker : workers_) {
    worker.join();
  }
}

// Adds a real task
void ThreadPool::submit(std::function<void()> task) {
  queue_.push(std::move(task));
}