//
// Created by yingbingzhu on 2025/4/20.
//

#include "calculator.h"

int main() {
  std::cout << "Hello Calculator starting…\n";
  int num1, num2;
  char op;
  std::cout << "Enter two numbers: ";
  std::cin >> num1 >> num2;
  std::cout << "You just entered " << num1 << " and " << num2 << '\n';
  std::cout << "Enter operator: ";
  std::cin >> op;
  std::cout << "You just entered " << op << '\n';
  switch (op) {
    case '+':
      std::cout << "Result: " << num1 + num2 << '\n';
    break;
    case '-':
      std::cout << "Result: " << num1 - num2 << '\n';
    break;
    case '*':
      std::cout << "Result: " << num1 * num2 << '\n';
    break;
    case '/':
      if (num2 == 0) {
        std::cout << "Error: Cannot divide by zero.\n";
      } else {
        std::cout << "Result: " << num1 / num2 << '\n';
      }
    break;
    default:
      std::cout << "Invalid operator entered.\n";
  }

  return 0;
}
