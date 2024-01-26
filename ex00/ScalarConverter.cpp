#include <iostream>
#include <iomanip>
#include <cctype>
#include <cmath>
#include "ScalarConverter.hpp"

void ScalarConverter::convert(const std::string& value_str)
{
    Value value(value_str);

    std::cout << "char: " << to_literal(value.as_optional<char>()) << '\n';
    std::cout << "int: " << to_literal(value.as_optional<int>()) << '\n';
    std::cout << "float: " << to_literal(value.as_optional<float>()) << '\n';
    std::cout << "double: " << to_literal(value.as_optional<double>()) << '\n';
}

template <typename Floating, std::enable_if_t<std::is_floating_point_v<Floating>, bool>>
std::string ScalarConverter::to_string(Floating value)
{
    if (std::isinf(value))
    {
        return value < 0.0f ? "-inf" : "+inf";
    }
    if (std::isnan(value))
    {
        return "nan";
    }
    return std::to_string(value);
}

template <typename T>
std::string ScalarConverter::to_literal(std::optional<T> value)
{
    if (value)
    {
        return to_literal(*value);
    }
    return "impossible";
}

std::string ScalarConverter::to_literal(char value)
{
    if (!std::isprint(value))
    {
        return "not displayable";
    }
    return std::string("'") + value + "'";
}

std::string ScalarConverter::to_literal(int value)
{
    return std::to_string(value);
}

std::string ScalarConverter::to_literal(float value)
{
    return to_string(value) + 'f';
}

std::string ScalarConverter::to_literal(double value)
{
    return to_string(value);
}
