//
// Copyright 2025 Qwerex
//

#include "include/philosopher.h"

#define N 6

std::mutex global_cout_mutex;

Philosopher *create_philosophers(int count, Chopstick *forks);

int main() {
  auto *forks = new Chopstick[N];
  auto *philosophers = create_philosophers(N, forks);

  for (int i = 0; i < N; i++) {
    philosophers[i].start();
  }

  for (int i = 0; i < N; i++) {
    philosophers[i].join();
  }

  delete philosophers;
  delete forks;
  return 0;
}

Philosopher *create_philosophers(const int count, Chopstick *forks) {
  auto *philosophers = new Philosopher[count];

  for (auto i = 0; i < count; ++i) {
    philosophers[i] = Philosopher{i, &forks[i % count], &forks[(i + 1) % count],
                                  &global_cout_mutex};
  }

  return philosophers;
}
