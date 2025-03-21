//
// Created by yingbingzhu on 2025/3/20.
//

#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Texture.hpp"


class Enemy {
  public:
  Enemy(const sf::Texture& texture);
  void update(float deltaTime);
  void reset();

  public:
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Vector2f position;
  float speed = 100.f;
  float downwardSpeed = 20.f;
};



