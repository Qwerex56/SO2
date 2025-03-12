//
// Copyright 2025 Qwerex
//


#ifndef DINING_PHILOSOPHERS_INCLUDE_CHOPSTICK_H_
#define DINING_PHILOSOPHERS_INCLUDE_CHOPSTICK_H_

#include <mutex>

class Chopstick {
 public:
  Chopstick() = default;

  void take_fork(int philosopher_id);
  void put_fork(int philosopher_id);

  [[nodiscard]] bool get_is_on_table() const;
 private:
  bool is_on_table_ = true;
  std::mutex mutex_{};
};

#endif  // DINING_PHILOSOPHERS_INCLUDE_CHOPSTICK_H_
