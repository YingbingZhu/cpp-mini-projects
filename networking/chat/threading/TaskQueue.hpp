//
// Created by yingbingzhu on 2025/5/4.
//

#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

class TaskQueue {
  public:
  // Add a task to the queue (thread-safe)
  void push(std::function<void()> task) { // Pass-by-value, take objects plan to store or move
    std::unique_lock<std::mutex> lock(mutex_);
    tasks_.push(std::move(task));
    condition_.notify_one(); // Wake up one waiting worker
  }

  // Get the next task (waits if queue is empty)
  std::function<void()> poll() {
    std::unique_lock<std::mutex> lock(mutex_);
    condition_.wait(lock, [this] { return !tasks_.empty(); });
    auto task = std::move(tasks_.front());
    tasks_.pop();
    return task;
  }
  private:
  std::queue<std::function<void()>> tasks_;
  std::mutex mutex_;
  std::condition_variable condition_;
};