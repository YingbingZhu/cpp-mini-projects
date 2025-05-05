//
// Created by yingbingzhu on 2025/5/4.
//

#pragma once

#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include "TaskQueue.hpp"

class ThreadPool {
  public:
    ThreadPool(size_t threads);
    ~ThreadPool();

    void submit(std::function<void()> task);

  private:
    std::vector<std::thread> workers_;
    TaskQueue queue_;
    std::atomic<bool> stop_;     // Flag to stop threads
};