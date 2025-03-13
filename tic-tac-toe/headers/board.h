//
// Created by yingbingzhu on 2025/3/12.
//

#pragma once

#include <iostream>

class Board {
private:
  char board[3][3];
public:
  Board();
  void display();
  bool placeMarker(int position, char marker);
  bool checkWinner() const;
  bool isFull() const;
};