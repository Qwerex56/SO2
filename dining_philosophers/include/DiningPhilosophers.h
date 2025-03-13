//
// Created by qwere on 12.03.2025.
//

#ifndef DININGPHILOSOPHERS_H
#define DININGPHILOSOPHERS_H

#include <vector>

#include "Philosopher.h"
#include "PhilosopherStatus.h"

class DiningPhilosophers {
 public:
  explicit DiningPhilosophers() = delete;
  explicit DiningPhilosophers(std::mutex *global_lock, int resolution = 2);

  void init_threads();
  void join_threads();

  void stop_threads();

  std::vector<PhilosopherStatus> get_philosophers_status() const;

 private:
  std::vector<Chopstick> chopsticks_{};
  std::vector<Philosopher> philosophers_{};

  void generate_chopsticks(int count);
  void generate_philosophers(int count, std::mutex *global_mutex);
};

#endif  // DININGPHILOSOPHERS_H
