//
// Created by user on 04.07.2024.
//
#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>
#include <regex>
#include <string>
#include <vector>
#include <algorithm>

class universal_parser {
private:
    std::vector<std::map<std::string, std::string>> data;
    std::string filename;
    void parse_file(); // приватный метод для парсинга файла

public:
    explicit universal_parser(const std::string& filename);
    std::vector<std::map<std::string, std::string>> get_data();
};
