//
// Copyright 2025 Qwerex
//

#include <iostream>

#include "../include/DiningPhilosophers.h"
#include "../include/DiningPhilosophersVisualizer.h"
#include "../include/Philosopher.h"
#include "SFML/Graphics/RenderWindow.hpp"

std::mutex global_cout_mutex;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <integer_value>" << std::endl;
    return 1;
  }

  const int phil_count = std::atoi(argv[1]);

  if (phil_count < 2) {
    std::cerr << "Philosopher count must be greater or equal to 2" << std::endl;
    return 1;
  }

  std::cout << "Philosopher count: " << phil_count << std::endl;

  auto window = sf::RenderWindow(sf::VideoMode{{800, 600}}, "Philosophers");

  DiningPhilosophers table{&global_cout_mutex, phil_count};
  DiningPhilosophersVisualizer visualizer{window, phil_count};

  table.init_threads();

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        table.stop_threads();
        table.join_threads();
        window.close();
      }
    }

    window.clear();

    visualizer.draw(table.get_philosophers_status());

    window.display();
  }

  return 0;
}
