//
// Created by yingbingzhu on 2025/3/12.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Board {
public:
  Board();
  void draw(sf::RenderWindow& window);
  void handleClick(int x, int y);
  bool checkWin(char marker) const;
  bool isFull() const;
  void reset();
private:
  char grid[3][3];
  sf::RectangleShape cells[3][3];
  sf::Font font;
  std::unique_ptr<sf::Text> texts[3][3];
  bool playerXTurn;
};