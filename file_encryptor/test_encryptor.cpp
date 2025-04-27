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

void test_encrypt() {
  std::cout << "Running test_encrypt_file...\n";
  std::ofstream input("input.txt");
  input << "This is my test message.";
  input.close();

  encrypt_file("input.txt", "output.enc");

  std::ifstream enc("output.enc", std::ios::binary | std::ios::ate);
  assert(enc.is_open() && "❌ Encrypted file was not created!");
  assert(enc.tellg() > 0 && "❌ Encrypted file is empty!");

  std::cout << "[PASS] test_encrypt_file\n";
}

void test_decrypt() {
  std::cout << "Running test_decrypt_file...\n";

  const std::string originalText = "This is my test message.";
  const std::string decryptedFile = "decrypted.txt";

  // Step 1: Decrypt the previously encrypted file
  decrypt_file("output.enc", decryptedFile);

  // Step 2: Check if the decrypted file exists
  std::ifstream result(decryptedFile);
  assert(result.is_open() && "❌ Decrypted file was not created!");

  // Step 3: Read the decrypted content
  std::string decryptedText((std::istreambuf_iterator<char>(result)),
                             std::istreambuf_iterator<char>());

  // Step 4: Compare the decrypted content with the original text

  assert(decryptedText == originalText && "❌ Decrypted content does not match original!");

  std::cout << "[PASS] test_decrypt_file\n";
}


int main() {
  test_generate_key();
  test_encrypt();
  test_decrypt();
  return 0;
}