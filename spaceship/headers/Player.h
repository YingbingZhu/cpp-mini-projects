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
  void drawBullets(sf::RenderWindow& window);

  public:
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Vector2f position;
  float speed = 200.f;
  int health = 3;

  // Cooldown timer (in seconds) for shooting.
  float shootCooldown = 0.f;

  // Container to hold active bullets.
  std::vector<Bullet> bullets;
};



