//
// Created by yingbingzhu on 2025/4/24.
//

#pragma once

#include <string>

void generate_key();

void encrypt_file(const std::string& inputFile, const std::string& outputFile);

void decrypt_file(const std::string& inputFile, const std::string& outputFile);