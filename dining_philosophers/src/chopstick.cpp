#include <iostream>
#include <ostream>

#include "../include/chopstick.h"

void Chopstick::take_fork(const int philosopher_id) {
  mutex_.lock();
  is_on_table_ = false;
}

void Chopstick::put_fork(const int philosopher_id) {
  mutex_.unlock();
  is_on_table_ = true;
}

bool Chopstick::get_is_on_table() const {
  return is_on_table_;
}