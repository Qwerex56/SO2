#include "src/philosopher.h"

#define N 4

Philosopher *create_philosophers(int count, Chopstick *forks);

int main() {
  auto *forks = new Chopstick[N];
  auto *philosophers = create_philosophers(N, forks);
  auto *threads = new std::thread[N];

  for (auto i = 0; i < N; ++i) {
    threads[i] =
        std::thread([philosophers, i] -> void { philosophers[i].work(); });
  }

  for (auto i = 0; i < N; ++i) {
    threads[i].join();
  }

  delete philosophers;
  delete forks;
  return 0;
}

Philosopher *create_philosophers(const int count, Chopstick *forks) {
  auto *philosophers = new Philosopher[count];

  for (auto i = 0; i < count; ++i) {
    philosophers[i] =
        Philosopher{i, &forks[i % count], &forks[(i + 1) % count]};
  }

  return philosophers;
}