//
// Copyright 2025 Qwerex
//

#include "../include/Philosopher.h"

#include <iostream>
#include <random>

bool Philosopher::print_to_console_ = true;

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

Philosopher::Philosopher(const int id, Chopstick* left_fork,
                         Chopstick* right_fork, std::mutex* mutex)
    : id_(id),
      right_fork_(right_fork),
      left_fork_(left_fork),
      cout_mutex_(mutex) {
  right_fork_->inject_cv(&cv_);
  left_fork_->inject_cv(&cv_);
}

void Philosopher::start() {
  thread_ = std::thread(&Philosopher::thread_worker, this);
}

void Philosopher::stop() { stuffed_ = true; }

PhilosopherStatus Philosopher::get_status() const { return this->status_; }

std::condition_variable* Philosopher::get_cv() {
  return &cv_;
}

void Philosopher::set_print_to_console(const bool print_to_console) {
  print_to_console_ = print_to_console;
}

void Philosopher::SetId(const int id) {
  id_ = id;
}

void Philosopher::SetRightFork(Chopstick* right_fork) {
  right_fork_ = right_fork;
  right_fork_->inject_cv(&cv_);
}

void Philosopher::SetLeftFork(Chopstick* left_fork) {
  left_fork_ = left_fork;
  left_fork_->inject_cv(&cv_);
}

void Philosopher::SetCoutMutex(std::mutex* cout_mutex) {
  cout_mutex_ = cout_mutex;
}

void Philosopher::print_status() const {
  if (!print_to_console_) {
    return;
  }

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

    {
      std::unique_lock lk_cv{cv_mutex_};
      status_ = PhilosopherStatus::kWaiting;
      print_status();
      cv_.wait(lk_cv, [&]() -> bool { return chopsticks_available(); });
    }

    dine();
  }
}
