#ifndef CHOPSTICK_H
#define CHOPSTICK_H

#include <mutex>

class Chopstick {
 public:
  Chopstick() = default;

  void take_fork(int philosopher_id);
  void put_fork(int philosopher_id);

  bool get_is_on_table() const;
 private:
  bool is_on_table_ = true;
  std::mutex mutex_{};
};

#endif