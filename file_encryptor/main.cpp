//
// Created by yingbingzhu on 2025/4/24.
//

#include "encryptor.h"
#include <iostream>
#include <sodium.h>
#include <cstring>


int main() {
  if (sodium_init() < 0) {
    std::cerr << "Failed to initialize libsodium!" << std::endl;
    return 1;  // Exit if sodium can't initialize (it sets up random number generator, etc.)
  }

}