//
// Created by user on 05.07.2024.
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
#include "../parser/Universal_parser.h"

class validation_data {
    universal_parser& first;
    universal_parser& second;
    std::string path;
    std::string outputFilename;

public:
    explicit validation_data(universal_parser& first, universal_parser& second, std::string path, std::string outputFilename);

private:
    void compareFiles();
};
