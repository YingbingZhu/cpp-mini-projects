//
// Created by yingbingzhu on 2025/3/12.
//

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../headers/board.h"

int main()
{
  // create the window
  sf::RenderWindow window(sf::VideoMode({600, 600}), "Tic-Tac-Toe");

  Board gameBoard;

  // Load a font (ensure the path is correct relative to the working directory)
  sf::Font font;
  if (!font.openFromFile("font/Arial.ttf")) {
    std::cerr << "Error loading font!" << std::endl;
    return -1;
  }

  // Create a text object to display the win message
  sf::Text winMessage(font);
  winMessage.setCharacterSize(50);
  winMessage.setFillColor(sf::Color::Red);

  // run the program as long as the window is open
  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last iteration of the loop
    while (const std::optional event = window.pollEvent())
    {
      // "close requested" event: we close the window
      if (event->is<sf::Event::Closed>())
        window.close();

      if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
      {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
        {
          int x = mouseButtonPressed->position.x;
          int y = mouseButtonPressed->position.y;
          gameBoard.handleClick(x, y);

          // check if win
          if (gameBoard.checkWin('X')) {
            winMessage.setString("Player X wins!");
            window.draw(winMessage);
            gameBoard.reset();
          } else if (gameBoard.checkWin('O')) {
            winMessage.setString("Player O wins!");
            window.draw(winMessage);
            gameBoard.reset();
          }
          else if (gameBoard.isFull()) {
            winMessage.setString("It's a draw!");
            window.draw(winMessage);
            gameBoard.reset();
          }

        }
      }
    }

    // clear the window with black color
    window.clear(sf::Color::Black);

    // draw everything here...
    gameBoard.draw(window);

    // end the current frame
    window.display();
  }
}
