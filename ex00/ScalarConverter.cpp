#include <cctype>
#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <variant>
#include <iomanip>
#include "ScalarConverter.hpp"

void ScalarConverter::convert(const std::string& value_str)
{
    Value value(value_str);

    std::cout << "char: ";
    display(value.as_char());
    std::cout << "int: ";
    display(value.as_int());
    std::cout << "float: ";
    display(value.as_float());
    std::cout << "double: ";
    display(value.as_double());
}

template <typename T>
void ScalarConverter::display(std::optional<T> value)
{
    if (value)
    {
        return display(*value);
    }
    std::cout << "impossible\n";
}

void ScalarConverter::display(char value)
{
    if (!std::isprint(value))
    {
        std::cout << "not displayable\n";
        return;
    }
    std::cout << '\'' << value << "'\n";
}

void ScalarConverter::display(int value)
{
    std::cout << value << "\n";
}

void ScalarConverter::display(float value)
{
    if (std::isinf(value))
    {
        std::cout << (value < 0.0f ? '-' : '+');
        std::cout << "inff\n";
        return;
    }
    if (std::isnan(value))
    {
        std::cout << "nanf\n";
        return;
    }
    std::cout << std::fixed << std::setprecision(1) << value << "f\n";
}

void ScalarConverter::display(double value)
{
    if (std::isinf(value))
    {
        std::cout << (value < 0.0 ? '-' : '+');
        std::cout << "inf\n";
        return;
    }
    if (std::isnan(value))
    {
        std::cout << "nan\n";
        return;
    }
    std::cout << std::fixed << std::setprecision(1) << value << "\n";
}
