#pragma once
#include <iostream>
#include <string>
#include <algorithm>

class Utils
{
public:
    static bool endsWith(const std::string& str, const std::string& suffix);
    virtual std::string getFileExtension(const std::string& filename) = 0;
    virtual std::string getFileBaseName(const std::string& filename) = 0;
    static std::string toLower(const std::string& str);
};