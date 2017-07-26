#ifndef STRING_CONVERSION
#define STRING_CONVERSION

#include <string>
#include <sstream>

template <typename Type>
std::string toString(const Type & number)
{
    std::ostringstream stream;
    stream << number;
    std::string string = stream.str();
    return string;
}

double toNumber(std::string string)
{
    std::istringstream stream(string);
    double number;
    stream >> number;
    return number;
}

#endif
