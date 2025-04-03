//
// Copyright 2025 Qwerex
//

#include "../include/Chopstick.h"

#include <iostream>
#include <ostream>

void Chopstick::take_fork(const int philosopher_id) {
  mutex_.lock();
  is_on_table_ = false;
}

void Chopstick::put_fork(const int philosopher_id) {
  mutex_.unlock();
  is_on_table_ = true;

  if (cv_[0] == nullptr) return;
  if (cv_[1] == nullptr) return;

  (*cv_)[0].notify_all();
  (*cv_)[1].notify_all();
}

void Chopstick::inject_cv(std::condition_variable* cv) {
  if (cv_[0] == nullptr) {
    cv_[0] = cv;
  } else if (cv_[1] == nullptr) {
    cv_[1] = cv;
  }
}

bool Chopstick::get_is_on_table() const {
  return is_on_table_;
}
