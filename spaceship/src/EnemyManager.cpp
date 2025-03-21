//
// Created by yingbingzhu on 2025/3/21.
//

#include "../headers/EnemyManager.h"

EnemyManager::EnemyManager(float spawnRate)
: spawnTimer(0.f), spawnRate(spawnRate) {
  // Load the enemy texture
  if (!enemyTexture.loadFromFile("resources/enemy.png")) {
    std::cerr << "Error loading enemy texture in EnemyManager!" << std::endl;
  }
}

void EnemyManager::update(float dt, Player& player) {
  spawnTimer -= dt;
  if (spawnTimer <= 0.f) {
    spawnEnemy();
    spawnTimer = spawnRate;
  }

  for (auto& e : enemies) e.update(dt);

  // Check for collisions between bullets and enemies
  auto& bullets = player.getBullets();
  for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ++bulletIt) {
    if (!bulletIt->isActive()) continue;  // Skip inactive bullets

    sf::FloatRect bulletBounds = bulletIt->shape.getGlobalBounds();
    for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
      sf::FloatRect enemyBounds = enemyIt->sprite.getGlobalBounds();
      if (bulletBounds.findIntersection(enemyBounds)) {
        // Collision detected: deactivate the bullet and remove the enemy
        bulletIt->deactivate();
        enemyIt = enemies.erase(enemyIt);  // Remove the enemy
      } else {
        ++enemyIt;
      }
    }
  }

  enemies.erase(
      std::remove_if(enemies.begin(), enemies.end(),
          [&](Enemy& e) {
              if (e.sprite.getGlobalBounds().position.y >= 600.f) {
                  player.deductHealth(1);
                  return true;
              }
              return false;
          }),
      enemies.end()
  );
}

void EnemyManager::draw(sf::RenderWindow& window) {
  for (auto& e : enemies) window.draw(e.sprite);
}

void EnemyManager::spawnEnemy() {
  enemies.emplace_back(enemyTexture);
  enemies.back().reset();
}

