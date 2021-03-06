#include "Utils.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

const float Utils::PI = 3.1415926535f;

std::vector<std::string> Utils::splitString(const std::string& str, char delim)
{
    std::vector<std::string> items;

    std::stringstream strStream(str);
    std::string currentItem;
    while (std::getline(strStream, currentItem, delim))
        items.push_back(currentItem);

    return items;
}

int Utils::stringToInt(const std::string& str, int defaultValue)
{
    int returnValue;

    try
    {
        returnValue = std::stoi(str);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Could not convert \"" << str << "\" to an integer, "
                  << "so return default value of " << defaultValue << std::endl;
        returnValue = defaultValue;
    }
    
    return returnValue;
}

float Utils::randomAngle()
{
    return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / PI);
}
