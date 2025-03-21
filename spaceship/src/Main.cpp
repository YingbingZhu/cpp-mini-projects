//
// Created by yingbingzhu on 2025/3/20.
//

#include <SFML/Graphics.hpp>
#include "../headers/Player.h"
#include "../headers/Enemy.h"
#include "../headers/EnemyManager.h"

int main()
{
  // Create the game window with dimensions 800x600 and a title.
  sf::RenderWindow window(sf::VideoMode({800, 600}), "Space Shooter");

  // Set the frame rate limit to 60 frames per second for smooth gameplay.
  window.setFramerateLimit(60);

  // Load font for Game Over
  sf::Font font;
  if (!font.openFromFile("resources/Arial.ttf")) {
    std::cerr << "Failed to load font\n";
  }

  sf::Text gameOverText(font, "GAME OVER", 64);
  gameOverText.setFillColor(sf::Color::Red);
  gameOverText.setStyle(sf::Text::Bold);

  // Center the text
  sf::FloatRect textBounds = gameOverText.getLocalBounds();
  gameOverText.setOrigin({textBounds.size.x / 2, textBounds.size.y / 2});
  gameOverText.setPosition({400.f, 300.f});

  Player player;
  EnemyManager enemy_manager(3.f);;
  sf::Clock clock;


  // Main game loop: runs until the window is closed.
  while (window.isOpen())
  {
    // Event polling: process all events since the last frame.
    while (const std::optional event = window.pollEvent())
    {
      // Close the window when the close event is triggered.
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    float deltaTime = clock.restart().asSeconds();

    // Update all game objects
    player.update(deltaTime);
    player.processShooting(deltaTime);
    player.updateBullets(deltaTime);
    enemy_manager.update(deltaTime, player);

    if (player.getHealth() <= 0) {
      break;
    }

    // Render
    window.clear(sf::Color::Black);
    player.draw(window);
    enemy_manager.draw(window);
    player.drawBullets(window);
    window.display();
  }

  // Game Over screen
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent())
      if (event->is<sf::Event::Closed>())
        window.close();

    window.clear();
    window.draw(gameOverText);
    window.display();
  }

  return 0;
}
