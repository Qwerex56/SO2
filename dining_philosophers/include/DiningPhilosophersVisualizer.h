//
// Created by qwere on 12.03.2025.
//

#ifndef DININGPHILOSOPHERSVISUALIZER_H
#define DININGPHILOSOPHERSVISUALIZER_H
#include <vector>

#include "PhilosopherStatus.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

class DiningPhilosophersVisualizer {
 public:
  DiningPhilosophersVisualizer() = delete;
  explicit DiningPhilosophersVisualizer(sf::RenderWindow &window,
                                        int resolution);

  void draw(const std::vector<PhilosopherStatus> &philosopher_statuses) const;

 private:
  sf::RenderWindow &window_;
  sf::Vector2f philosopher_size_{};
  std::vector<sf::Vector2f> philosophers_positions_{};

  static float get_radius(sf::Vector2u w_size);

  sf::Vector2f generate_philosopher_size(int count) const;
  std::vector<sf::Vector2f> generate_philosopher_positions(int count) const;
};

#endif  // DININGPHILOSOPHERSVISUALIZER_H
