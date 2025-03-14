//
// Created by yingbingzhu on 2025/3/12.
//

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../headers/board.h"

int main()
{
  // create the window
  const int gridSize = 600;
  const int margin = 50; // space for the win message
  const int windowWidth = gridSize;
  const int windowHeight = gridSize + margin;
  sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Tic-Tac-Toe");

  Board gameBoard;

  // Load a font (ensure the path is correct relative to the working directory)
  sf::Font font;
  if (!font.openFromFile("font/Arial.ttf")) {
    std::cerr << "Error loading font!" << std::endl;
    return -1;
  }

  // Create a text object to display the win message
  sf::Text winMessage(font);
  winMessage.setCharacterSize(20);
  winMessage.setFillColor(sf::Color::Red);

  // Variable to store the current win message
  std::string currentWinMessage = "";
  // Create a view for the win message that covers the top margin.
  // The viewport is normalized (0.0 to 1.0) relative to the window.
  sf::View messageView(sf::FloatRect({0, 0}, {windowWidth, margin}));
  messageView.setViewport(sf::FloatRect({0, 0}, {1.f, float(margin) / windowHeight}));

  // Create a view for the board. The world coordinates for the board are (0,0) to (gridSize, gridSize).
  // We set its viewport to occupy the bottom portion of the window.
  sf::View boardView(sf::FloatRect({0, 0}, {gridSize, gridSize}));
  boardView.setViewport(sf::FloatRect({0, float(margin) / windowHeight}, {1.f, float(gridSize) / windowHeight}));

  bool gameEnded = false;

  // run the program as long as the window is open
  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last iteration of the loop
    while (const std::optional event = window.pollEvent()) {
      // "close requested" event: we close the window
      if (event->is<sf::Event::Closed>())
        window.close();

      if (!gameEnded) {
          if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
          {
            if (mouseButtonPressed->button == sf::Mouse::Button::Left)
            {
              int x = mouseButtonPressed->position.x;
              int y = mouseButtonPressed->position.y;
              gameBoard.handleClick(x, y);

              // check if win
              if (gameBoard.checkWin('X')) {
                currentWinMessage = "Player X wins!";
                gameEnded = true;
              } else if (gameBoard.checkWin('O')) {
                currentWinMessage = "Player O wins!";
                gameEnded = true;
              }
              else if (gameBoard.isFull()) {
                currentWinMessage = "It's a draw!";
                gameEnded = true;
              }

              winMessage.setString(currentWinMessage);
            }
          }
      }
      // Reset on key press (e.g., 'R') after game ends
      if (gameEnded && event->is<sf::Event::KeyPressed>()) {
        if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::R) {
          gameBoard.reset();
          currentWinMessage = "";
          gameEnded = false;
        }
      }
    }

    // clear the window with black color
    window.clear(sf::Color::Black);

    window.setView(messageView);
    if (!currentWinMessage.empty()) {
      float textWidth = winMessage.getLocalBounds().size.x;
      float textHeight = winMessage.getLocalBounds().size.y;
      winMessage.setPosition({(windowWidth - textWidth) / 2.f, (margin - textHeight) / 2.f});
      window.draw(winMessage);
    }

    window.setView(boardView);
    gameBoard.draw(window);

    // end the current frame
    window.display();
  }
}
