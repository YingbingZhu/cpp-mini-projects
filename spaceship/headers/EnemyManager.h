//
// Created by yingbingzhu on 2025/3/21.
//

#pragma once

#include "Enemy.h"
#include "Player.h"
#include <vector>

class EnemyManager {
public:
    EnemyManager(float spawnRate = 1.f);
    void update(float deltaTime, Player& player);
    void draw(sf::RenderWindow& window);

private:
    void spawnEnemy();

    std::vector<Enemy> enemies;
    float spawnTimer;
    float spawnRate;
    sf::Texture enemyTexture;  // Shared texture for all enemies
};



