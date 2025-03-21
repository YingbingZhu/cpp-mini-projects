//
// Created by yingbingzhu on 2025/3/20.
//

#pragma once
#include <iostream>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "../headers/Bullet.h"


class Player {
  public:
  Player();
  void update(float deltaTime);
  void processShooting(float deltaTime);
  void updateBullets(float deltaTime);
  void drawBullets(sf::RenderWindow& window) const;
  void deductHealth(int amount);
  int getHealth() const { return health; }
  sf::Vector2f getPosition() const { return position; }
  void draw(sf::RenderWindow& window);

  // Getter for bullets
  const std::vector<Bullet>& getBullets() const { return bullets; }
  std::vector<Bullet>& getBullets() { return bullets; }  // Non-const version for modification

  private:
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Vector2f position;
  float speed = 200.f;
  int health = 3;

  // Cooldown timer (in seconds) for shooting.
  float shootCooldown = 0.f;

  const float shootCooldownTime = 0.5f;  // Added back: Time between shots (in seconds)

  std::vector<Bullet> bullets;

  // Health bar UI
  sf::RectangleShape healthBarBack;
  sf::RectangleShape healthBarFront;
  const float healthBarWidth = 200.f;
  const float healthBarHeight = 20.f;
  const int maxHealth = 3;
};



