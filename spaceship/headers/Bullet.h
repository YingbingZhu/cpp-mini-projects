//
// Created by yingbingzhu on 2025/3/20.
//

#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
  public:
  sf::CircleShape shape;
  sf::Vector2f velocity;
  bool active = true;

  // The bullet is created at a given position.
  Bullet(sf::Vector2f startPosition) {
    shape.setRadius(5.f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(startPosition);
    // The bullet moves upward.
    velocity = sf::Vector2f(0.f, -300.f);
  }

  // Update bullet position based on elapsed time.
  void update(float deltaTime) {
    shape.move(velocity * deltaTime);
  }
  bool isActive() const { return active; }
  void deactivate() { active = false; }
};

