#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

class Utils
{
    public:
        static std::vector<std::string> splitString(const std::string& str, char delim);
        static int stringToInt(const std::string& str, int defaultValue);
        static float randomAngle();

    public:
        static const float PI;
};

#endif
