#pragma once

#include <string>
#include <vector>

class Utils {
   public:
    static std::vector<char> readFile(const std::string& filename);
};