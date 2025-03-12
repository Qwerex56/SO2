#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <mutex>
#include <thread>

#include "chopstick.h"

class Philosopher {
 public:
  explicit Philosopher(const int id, Chopstick *left_fork,
                       Chopstick *right_fork, std::mutex &mutex)
      : id_(id),
        left_fork_(left_fork),
        right_fork_(right_fork),
        cout_mutex_(mutex) {}

  void work();

  void dine() const;
  void think() const;

  bool chopsticks_available() const;

 private:
  int id_ = -1;
  bool stuffed_ = false;

  Chopstick *left_fork_ = nullptr;
  Chopstick *right_fork_ = nullptr;

  std::thread thread_;
  std::mutex &cout_mutex_;



  static int rand_time();
};

#endif