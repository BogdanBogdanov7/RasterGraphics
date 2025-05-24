#pragma once
#include <iostream>
#include <string>
#include <algorithm>

class Utils
{
public:
    virtual bool endsWith(const std::string& str, const std::string& suffix) = 0;
    virtual std::string getFileExtension(const std::string& filename) = 0;
    virtual std::string getFileBaseName(const std::string& filename) = 0;
    virtual std::string toLower(const std::string& str) = 0;
};