//
// Created by user on 12.07.2024.
//
#pragma once
#include <string>

std::string detect_encoding(const std::string& file_path);
void convert_file_encoding(const std::string& input_file, const std::string& source_encoding, const std::string& target_encoding);
