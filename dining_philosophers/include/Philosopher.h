//
// Copyright 2025 Qwerex
//

#ifndef DINING_PHILOSOPHERS_INCLUDE_PHILOSOPHER_H_
#define DINING_PHILOSOPHERS_INCLUDE_PHILOSOPHER_H_

#include <mutex>
#include <thread>

#include "../include/Chopstick.h"
#include "PhilosopherStatus.h"

class Philosopher {
 public:
  Philosopher() = default;
  explicit Philosopher(const int id, Chopstick *left_fork,
                       Chopstick *right_fork, std::mutex *mutex);

  void start();
  void stop();

  void join() { thread_.join(); }

  [[nodiscard]] PhilosopherStatus get_status() const;
  [[nodiscard]] std::condition_variable* get_cv();

  static void set_print_to_console(bool print_to_console);

 private:
  static bool print_to_console_;

  int id_ = -1;
  bool stuffed_ = false;
  PhilosopherStatus status_ = PhilosopherStatus::kWaiting;

  Chopstick *right_fork_ = nullptr;
  Chopstick *left_fork_ = nullptr;

 public:
  void SetId(int id);
  void SetRightFork(Chopstick *right_fork);
  void SetLeftFork(Chopstick *left_fork);
  void SetCoutMutex(std::mutex *cout_mutex);

 private:
  std::thread thread_{};
  std::condition_variable cv_{};

  std::mutex cv_mutex_{};
  std::mutex *cout_mutex_ = nullptr;

  static std::chrono::seconds rand_time(int min = 1, int max = 4);

  void thread_worker();
  void dine();
  void think();
  void print_status() const;
  [[nodiscard]] bool chopsticks_available() const;
};

#endif  // DINING_PHILOSOPHERS_INCLUDE_PHILOSOPHER_H_
