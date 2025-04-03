//
// Copyright 2025 Qwerex
//

#include <vector>

#include "../include/DiningPhilosophers.h"

DiningPhilosophers::DiningPhilosophers(std::mutex *global_lock,
                                       const int resolution) {
  generate_chopsticks(resolution);
  generate_philosophers(resolution, global_lock);
}

void DiningPhilosophers::init_threads() {
  for (Philosopher &philosopher : philosophers_) {
    philosopher.start();
  }
}

void DiningPhilosophers::join_threads() {
  for (Philosopher &philosopher : philosophers_) {
    philosopher.join();
  }
}

void DiningPhilosophers::stop_threads() {
  for (Philosopher &philosopher : philosophers_) {
    philosopher.stop();
  }
}

std::vector<PhilosopherStatus> DiningPhilosophers::get_philosophers_status()
    const {
  std::vector<PhilosopherStatus> philosophers_status{};

  for (const Philosopher &philosopher : philosophers_) {
    philosophers_status.emplace_back(philosopher.get_status());
  }

  return philosophers_status;
}

void DiningPhilosophers::generate_chopsticks(const int count) {
  chopsticks_ = std::vector<Chopstick>(count);
}

void DiningPhilosophers::generate_philosophers(const int count,
                                               std::mutex *global_mutex) {
  philosophers_ = std::vector<Philosopher>(count);

  for (int i = 0; i < count; ++i) {
    auto *left_chopstick = &chopsticks_[i];
    auto *right_chopstick = &chopsticks_[(i + 1) % count];

    philosophers_[i].SetId(i);
    philosophers_[i].SetRightFork(right_chopstick);
    philosophers_[i].SetLeftFork(left_chopstick);
    philosophers_[i].SetCoutMutex(global_mutex);
  }
}
