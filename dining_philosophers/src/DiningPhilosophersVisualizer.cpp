//
// Copyright 2025 Qwerex
//

#include "../include/DiningPhilosophersVisualizer.h"

#include <math.h>

#include <vector>

#include "SFML/Graphics/RectangleShape.hpp"

DiningPhilosophersVisualizer::DiningPhilosophersVisualizer(
    sf::RenderWindow* window, const int resolution)
    : window_(window) {
  philosopher_size_ = generate_philosopher_size(resolution);
  philosophers_positions_ = generate_philosopher_positions(resolution);
}

void DiningPhilosophersVisualizer::draw(
    const std::vector<PhilosopherStatus>& philosopher_statuses) const {
  for (int i = 0; i < philosopher_statuses.size(); ++i) {
    const auto status = philosopher_statuses[i];
    const auto position = philosophers_positions_[i];

    auto phil = sf::RectangleShape{};
    phil.setPosition(position);
    phil.setSize(philosopher_size_);

    switch (status) {
      case PhilosopherStatus::kThinking:
        phil.setFillColor(sf::Color::Red);
        break;
      case PhilosopherStatus::kEating:
        phil.setFillColor(sf::Color::Green);
        break;
      case PhilosopherStatus::kWaiting:
        phil.setFillColor(sf::Color::Blue);
        break;
    }

    window_->draw(phil);
  }
}

sf::Vector2f DiningPhilosophersVisualizer::generate_philosopher_size(
    int const count) const {
  auto const w_size = window_->getSize();

  float const radius = get_radius(w_size);

  return sf::Vector2f{radius / count, radius / count};
}

float DiningPhilosophersVisualizer::get_radius(sf::Vector2u const w_size) {
  return (w_size.y - w_size.y * 0.15f) / 2.0f;
}
std::vector<sf::Vector2f>
DiningPhilosophersVisualizer::generate_philosopher_positions(
    const int count) const {
  auto const w_size = window_->getSize();

  float const radius = get_radius(w_size);
  constexpr float pi = 3.14159265f;
  float const delta_angle = 2.f * pi / count;

  std::vector<sf::Vector2f> philosopher_positions{};

  for (int i = 0; i < count; ++i) {
    const float angle = delta_angle * i;
    philosopher_positions.emplace_back(radius *
                                       sf::Vector2f{cos(angle), sin(angle)});
    philosopher_positions.back() += sf::Vector2f(w_size) / 2.0f;
    philosopher_positions.back() -= philosopher_size_ / 2.0f;
  }

  return philosopher_positions;
}
