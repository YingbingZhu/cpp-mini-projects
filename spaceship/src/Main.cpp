//
// Created by yingbingzhu on 2025/3/20.
//

#include <SFML/Graphics.hpp>
#include "../headers/Player.h"

int main()
{
  // Create the game window with dimensions 800x600 and a title.
  sf::RenderWindow window(sf::VideoMode({800, 600}), "Space Shooter");

  // Set the frame rate limit to 60 frames per second for smooth gameplay.
  window.setFramerateLimit(60);

  // Create an instance of the Player.
  Player player;

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
    // Update player movement and shooting.
    player.update(deltaTime);
    player.processShooting(deltaTime);
    player.updateBullets(deltaTime);

    // Update game objects here.
    // For example: move the player, update enemy positions, check collisions, etc.

    // Render: Clear the window with a black background.
    window.clear(sf::Color::Black);

    // Draw game objects here.
    window.draw(player.sprite);
    player.drawBullets(window);


    // Display the rendered frame on the screen.
    window.display();
  }

  return 0;
}
