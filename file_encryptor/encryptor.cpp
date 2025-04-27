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

bool load_key(unsigned char *key) {
  std::ifstream in(keyFile, std::ios::binary);
  if (!in) {
    std::cerr << "Key file not found. Please run 'genkey' first.\n";
    return false;
  }
  in.read(reinterpret_cast<char*>(key), crypto_secretbox_KEYBYTES);
  return true;
}

void encrypt_file(const std::string& inputFile, const std::string& outputFile) {
  unsigned char key[crypto_secretbox_KEYBYTES];
  // load key from generated key file
  if (!load_key(key)) return;

  // Read the input file.
  std::ifstream in(inputFile, std::ios::binary);
  if (!in) {
    std::cerr << "Cannot open input file: " << inputFile << "\n";
    return;
  }
  // istreambuf_iterator<char> reads the whole file byte by byte.
  std::vector<unsigned char> plaintext((std::istreambuf_iterator<char>(in)),
                                         std::istreambuf_iterator<char>());

  // Encrypt its contents using a secret key + random nonce.
  unsigned char nonce[crypto_secretbox_NONCEBYTES];
  randombytes_buf(nonce, sizeof nonce);

  std::vector<unsigned char> ciphertext(plaintext.size() + crypto_secretbox_MACBYTES);
  crypto_secretbox_easy(ciphertext.data(), plaintext.data(), plaintext.size(), nonce, key);

  // Write the encrypted output to another file
  std::ofstream out(outputFile, std::ios::binary);
  if (!out) {
    std::cerr << "Could not write output file.\n";
    return;
  }
  out.write(reinterpret_cast<const char *>(nonce), crypto_secretbox_NONCEBYTES);
  out.write(reinterpret_cast<const char *>(ciphertext.data()), ciphertext.size());

  std::cout << "File encrypted: " << outputFile << "\n";
}


void decrypt_file(const std::string& inputFile, const std::string& outputFile) {
  unsigned char key[crypto_secretbox_KEYBYTES];
  if (!load_key(key)) return;

  std::ifstream in(inputFile, std::ios::binary);
  if (!in) {
    std::cerr << "Cannot open input file: " << inputFile << "\n";
    return;
  }
  // read the nonce
  unsigned char nonce[crypto_secretbox_NONCEBYTES];
  in.read(reinterpret_cast<char *>(nonce), crypto_secretbox_NONCEBYTES);

  // read the ciphertext
  std::vector<unsigned char> ciphertext((std::istreambuf_iterator<char>(in)),
    std::istreambuf_iterator<char>());
  if (ciphertext.size() < crypto_secretbox_MACBYTES) {
    std::cerr << "Ciphertext too short or corrupted!\n";
    return;
  }
  std::vector<unsigned char> decrypted(ciphertext.size() - crypto_secretbox_MACBYTES);
  if (crypto_secretbox_open_easy(decrypted.data(), ciphertext.data(), ciphertext.size(), nonce, key) != 0) {
    std::cerr << "Decryption failed: Wrong key, nonce, or corrupted data.\n";
    return;
  }

  std::ofstream out(outputFile, std::ios::binary);
  if (!out) {
    std::cerr << "Could not write output file.\n";
    return;
  }
  out.write(reinterpret_cast<const char *>(decrypted.data()), decrypted.size());
  std::cout << "File decrypted: " << outputFile << "\n";
}
