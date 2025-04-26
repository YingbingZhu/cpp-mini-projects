//
// Created by yingbingzhu on 2025/4/26.
//

#include "encryptor.h"
#include <sodium.h>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

// Helper: Check if file exists
bool file_exists(const std::string& filename) {
  std::ifstream f(filename);
  return f.good();
}

void test_generate_key() {
  std::cout << "Running test_generate_key...\n";
  generate_key();

  std::ifstream in("key.bin", std::ios::binary | std::ios::ate);
  assert(in.is_open() && "❌ Key file not created!");
  auto size = in.tellg();
  assert(size == crypto_secretbox_KEYBYTES && "❌ Key size mismatch!");
  std::cout << "[PASS] test_generate_key\n";
}

int main() {
  test_generate_key();
  return 0;
}