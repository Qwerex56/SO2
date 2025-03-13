//
// Copyright 2025 Qwerex
//

#include "../include/Philosopher.h"

#include <iostream>
#include <random>

void Philosopher::dine() {
  left_fork_->take_fork(id_);
  right_fork_->take_fork(id_);

  status_ = PhilosopherStatus::kEating;
  print_status();
  std::this_thread::sleep_for(rand_time());  // Simulate heavy work

  left_fork_->put_fork(id_);
  right_fork_->put_fork(id_);
}

void Philosopher::think() {
  if (status_ == PhilosopherStatus::kWaiting) {
    // print_status();
    return;
  }

  status_ = PhilosopherStatus::kThinking;
  print_status();
  std::this_thread::sleep_for(rand_time());
}

bool Philosopher::chopsticks_available() const {
  return left_fork_->get_is_on_table() && right_fork_->get_is_on_table();
}

void Philosopher::start() {
  thread_ = std::thread(&Philosopher::thread_worker, this);
  // thread_.join();
}

void Philosopher::stop() { stuffed_ = true; }

PhilosopherStatus Philosopher::get_status() const {
  return this->status_;
}

void Philosopher::print_status() const {
  auto status = "";
  switch (status_) {
    case PhilosopherStatus::kThinking:
      status = "thinking";
      break;
    case PhilosopherStatus::kEating:
      status = "eating";
      break;
    case PhilosopherStatus::kWaiting:
      status = "waiting";
      break;
  }

  {
    std::lock_guard lk_cout{(*cout_mutex_)};
    std::cout << "Philosopher " << id_ << ": " << status << "!\n";
  }
}

std::chrono::seconds Philosopher::rand_time(const int min, const int max) {
  std::random_device rd{};
  std::mt19937 gen{rd()};
  std::uniform_int_distribution dist_int{min, max};

  return std::chrono::seconds(dist_int(gen));
}

void Philosopher::thread_worker() {
  while (!stuffed_) {
    think();
    if (!chopsticks_available()) {
      status_ = PhilosopherStatus::kWaiting;
      continue;
    }
    dine();
  }
}
