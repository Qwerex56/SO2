#include "philosopher.h"

#include <iostream>
#include <random>

void Philosopher::work() {
  int i = 0;
  while (i++ < 2) {
    think();
    // while (!chopsticks_available()) {
    // }
    dine();
  }
}

void Philosopher::dine() const {
  left_fork_->take_fork(id_);
  right_fork_->take_fork(id_);

  std::cout << "Philosopher " << id_ << " is eating!\n";
  std::this_thread::sleep_for(std::chrono::seconds(rand_time()));
  std::cout << "Philosopher " << id_ << " finished eating!\n";

  left_fork_->put_fork(id_);
  right_fork_->put_fork(id_);
}
void Philosopher::think() const {
  {
    std::cout << "Philosopher " << id_ << " is thinking!\n";
  }
  std::this_thread::sleep_for(std::chrono::seconds(rand_time()));
}

bool Philosopher::chopsticks_available() const {
  return left_fork_->get_is_on_table() && right_fork_->get_is_on_table();
}

int Philosopher::rand_time() {
  std::random_device rd{};
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<> dist_int{1, 4};

  return dist_int(gen);
}
