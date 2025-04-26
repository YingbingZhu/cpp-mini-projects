//
// Created by yingbingzhu on 2025/4/24.
//

#include "encryptor.h"
#include <sodium.h>              // For crypto functions
#include <fstream>               // For reading/writing files
#include <iostream>              // For console output
#include <vector>                // For storing file content

const std::string keyFile = "key.bin";

void generate_key() {
  unsigned char key[crypto_secretbox_KEYBYTES]; // 32 bytes = 256 bits.
  randombytes_buf(key, sizeof key);

  // open file
  std::ofstream out(keyFile, std::ios::binary);
  if (!out) {
    std::cerr << "Error: Could not write key file.\n";
    return;
  }
  // A pointer to the data buffer (const char*), The number of bytes to write
  out.write(reinterpret_cast<const char *>(key), sizeof key);
  std::cout << "Key generated and saved to " << keyFile << "\n";
}
