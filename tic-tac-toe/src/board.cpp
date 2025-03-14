//
// Created by yingbingzhu on 2025/3/12.
//

#include "../headers/board.h"
#include <iostream>


// Constructor: Initializes empty board
Board::Board() : texts{}, playerXTurn(true) {
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      grid[x][y] = ' ';
    }
  }

  if (!font.openFromFile("font/Arial.ttf")) {
    std::cout << "Error loading font!" << std::endl;
  }

  // Set up grid cells
  float cellSize = 200.0f;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      cells[i][j].setSize(sf::Vector2f(cellSize, cellSize));
      cells[i][j].setOutlineThickness(2);
      cells[i][j].setOutlineColor(sf::Color::White);
      cells[i][j].setPosition({j * cellSize, i * cellSize});
      cells[i][j].setFillColor(sf::Color::Black);

      texts[i][j] = std::make_unique<sf::Text>(font, "", 100);
      texts[i][j]->setFillColor(sf::Color::White);
      texts[i][j]->setPosition({j * cellSize + 50, i * cellSize + 50});
    }
  }
}


void Board::draw(sf::RenderWindow &window) {
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      window.draw(cells[x][y]);
      window.draw(*texts[x][y]);
    }
  }
}

void Board::handleClick(int mouseX, int mouseY) {
  float cellSize = 200.0f;
  int col = mouseX / static_cast<int>(cellSize);
  int row = mouseY / static_cast<int>(cellSize);

  // Check if the click is within bounds
  if (row < 0 || row >= 3 || col < 0 || col >= 3)
    return;

  // If the cell is not empty, ignore the click.
  if (grid[row][col] != ' ')
    return;

  char marker = playerXTurn ? 'X' : 'O';
  grid[row][col] = marker;

  texts[row][col]->setString(std::string(1, marker));

  playerXTurn = !playerXTurn;
}

bool Board::checkWin(char marker) const {
  // Check rows
  for (int i = 0; i < 3; i++) {
    if (grid[i][0] == marker && grid[i][1] == marker && grid[i][2] == marker)
      return true;
  }
  // Check columns
  for (int j = 0; j < 3; j++) {
    if (grid[0][j] == marker && grid[1][j] == marker && grid[2][j] == marker)
      return true;
  }
  // Check diagonals
  if (grid[0][0] == marker && grid[1][1] == marker && grid[2][2] == marker)
    return true;
  if (grid[0][2] == marker && grid[1][1] == marker && grid[2][0] == marker)
    return true;

  return false;
}

// Checks if the board is full (i.e., no empty cell remains).
bool Board::isFull() const {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (grid[i][j] == ' ')
        return false;
    }
  }
  return true;
}

// Resets the board to its initial empty state and sets the turn to Player X.
void Board::reset() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      grid[i][j] = ' ';
      texts[i][j]->setString("");
    }
  }
  playerXTurn = true;
}



