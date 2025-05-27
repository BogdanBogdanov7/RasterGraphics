#include <string>
#include <algorithm>
#include "Utils.h"

bool Utils::endsWith(const std::string& str, const std::string& suffix)
{
    if(suffix.size() > str.size())
    {
        return false;
    }
    return str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

std::string Utils::getFileExtension(const std::string& filename)
{
    std::size_t getDotPosition = filename.find_last_of('.');
    if(getDotPosition == std::string::npos)
    {
        return "";
    }
    return filename.substr(getDotPosition);
}

std::string Utils::getFileBaseName(const std::string& filename)
{
    std::size_t getSlashPosition = filename.find_last_of("/\\");
    std::size_t getDotPosition = filename.find_last_of('.');
    if(getDotPosition == std::string::npos)
    {
        getDotPosition = filename.length();
    }
    return filename.substr(getSlashPosition + 1, getDotPosition - getSlashPosition - 1);
}

std::string Utils::toLower(const std::string& str)
{
    std::string lowered = str;
    std::transform(lowered.begin(), lowered.end(), lowered.begin(), ::tolower);
    return lowered;
}