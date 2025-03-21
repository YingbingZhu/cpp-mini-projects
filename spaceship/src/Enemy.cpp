//
// Created by yingbingzhu on 2025/3/21.
//

#include "../headers/Enemy.h"

Enemy::Enemy(const sf::Texture& texture) : sprite(texture), position(400.f, 50.f) {
  // Scale the sprite (e.g., to 64x64 pixels, similar to the player)
  sf::FloatRect spriteBounds = sprite.getLocalBounds();
  const float desiredSize = 30.f;
  float scaleX = desiredSize / spriteBounds.size.x;
  float scaleY = desiredSize / spriteBounds.size.y;
  sprite.setScale({scaleX, scaleY});

  // Recalculate bounds after scaling
  spriteBounds = sprite.getLocalBounds();
  sprite.setOrigin({spriteBounds.size.x / 2.f, spriteBounds.size.y / 2.f});

  // Set the position (center the sprite horizontally)
  sprite.setPosition(position);
}

void Enemy::update(float deltaTime) {
  // Move enemy.
  position.x += speed * deltaTime;

  position.y += downwardSpeed * deltaTime;

  // Get the bounds to know the sprite's size.
  sf::FloatRect bounds = sprite.getLocalBounds();

  // Bounce off the window edges (assuming an 800px wide window)
  if (position.x - bounds.size.x / 2.f < 0 || position.x + bounds.size.x / 2.f > 800) {
    speed = -speed;
    position.x = std::max(bounds.size.x / 2.f, std::min(position.x, 800.f - bounds.size.x / 2.f));
  }

  sprite.setPosition(position);
}

void Enemy::reset() {
  // Get sprite dimensions
  sf::FloatRect bounds = sprite.getLocalBounds();

  // Position just above the top of the window
  position.y = -bounds.position.y;

  // Randomize X so enemies don’t all stack
  position.x = static_cast<float>(random() % static_cast<int>(800 - bounds.size.x));

  sprite.setPosition(position);
}

