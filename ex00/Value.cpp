#include <regex>
#include <limits>
#include <cmath>
#include "Value.hpp"

Value::Value(const std::string& value) noexcept : _value(std::monostate{})
{
    std::regex char_expr(R"('.')", std::regex::ECMAScript);
    std::regex int_expr(R"([\+-]?[0-9]+)", std::regex::ECMAScript);
    std::regex float_expr(R"([\+-]?(?:(?:\.[0-9]+)|(?:[0-9]+\.[0-9]*))f)", std::regex::ECMAScript);
    std::regex double_expr(R"([\+-]?(?:(?:\.[0-9]+)|(?:[0-9]+\.[0-9]*)))", std::regex::ECMAScript);

    try
    {
        if (std::regex_match(value, char_expr))
        {
            _value = value[1];
        }
        else if (std::regex_match(value, int_expr))
        {
            _value = std::stoi(value);
        }
        else if (std::regex_match(value, float_expr))
        {
            _value = std::stof(value);
        }
        else if (value == "+inff")
        {
            _value = std::numeric_limits<float>::infinity();
        }
        else if (value == "-inff")
        {
            _value = -std::numeric_limits<float>::infinity();
        }
        else if (value == "nanf")
        {
            _value = std::numeric_limits<float>::quiet_NaN();
        }
        else if (std::regex_match(value, double_expr))
        {
            _value = std::stod(value);
        }
        else if (value == "+inf")
        {
            _value = std::numeric_limits<double>::infinity();
        }
        else if (value == "-inf")
        {
            _value = -std::numeric_limits<double>::infinity();
        }
        else if (value == "nan")
        {
            _value = std::numeric_limits<double>::quiet_NaN();
        }
    }
    catch (const std::exception&) {}
}

std::optional<char> Value::as_char() const noexcept
{
    if (const char* value = std::get_if<char>(&_value))
    {
        return std::optional<char>(*value);
    }
    if (const float* value = std::get_if<float>(&_value))
    {
        float ivalue;

        if (*value < std::numeric_limits<char>::min() ||
            *value > std::numeric_limits<char>::max() ||
            std::isnan(*value) ||
            std::modf(*value, &ivalue) != 0.0f)
        {
            return std::nullopt;
        }
        return std::optional<char>(static_cast<char>(*value));
    }
    if (const double* value = std::get_if<double>(&_value))
    {
        double ivalue;

        if (*value < std::numeric_limits<char>::min() ||
            *value > std::numeric_limits<char>::max() ||
            std::isnan(*value) ||
            std::modf(*value, &ivalue) != 0.0)
        {
            return std::nullopt;
        }
        return std::optional<char>(static_cast<char>(*value));
    }
    if (const int* value = std::get_if<int>(&_value))
    {
        if (*value < std::numeric_limits<char>::min() ||
            *value > std::numeric_limits<char>::max())
        {
            return std::nullopt;
        }
        return std::optional<char>(static_cast<char>(*value));
    }
    return std::nullopt;
}

std::optional<int> Value::as_int() const noexcept
{
    if (const char* value = std::get_if<char>(&_value))
    {
        return std::optional<int>(static_cast<int>(*value));
    }
    if (const float* value = std::get_if<float>(&_value))
    {
        float ivalue;

        if (*value < std::numeric_limits<int>::min() ||
            *value > std::numeric_limits<int>::max() ||
            std::isnan(*value) ||
            std::modf(*value, &ivalue) != 0.0f)
        {
            return std::nullopt;
        }
        return std::optional<int>(static_cast<int>(*value));
    }
    if (const double* value = std::get_if<double>(&_value))
    {
        double ivalue;

        if (*value < std::numeric_limits<int>::min() ||
            *value > std::numeric_limits<int>::max() ||
            std::isnan(*value) ||
            std::modf(*value, &ivalue) != 0.0)
        {
            return std::nullopt;
        }
        return std::optional<int>(static_cast<int>(*value));
    }
    if (const int* value = std::get_if<int>(&_value))
    {
        return std::optional<int>(*value);
    }
    return std::nullopt;
}

std::optional<float> Value::as_float() const noexcept
{
    if (const char* value = std::get_if<char>(&_value))
    {
        return std::optional<float>(static_cast<float>(*value));
    }
    if (const float* value = std::get_if<float>(&_value))
    {
        return std::optional<float>(*value);
    }
    if (const double* value = std::get_if<double>(&_value))
    {
        return std::optional<float>(static_cast<float>(*value));
    }
    if (const int* value = std::get_if<int>(&_value))
    {
        return std::optional<float>(static_cast<float>(*value));
    }
    return std::nullopt;
}

std::optional<double> Value::as_double() const noexcept
{
    if (const char* value = std::get_if<char>(&_value))
    {
        return std::optional<double>(static_cast<double>(*value));
    }
    if (const float* value = std::get_if<float>(&_value))
    {
        return std::optional<double>(static_cast<double>(*value));
    }
    if (const double* value = std::get_if<double>(&_value))
    {
        return std::optional<double>(*value);
    }
    if (const int* value = std::get_if<int>(&_value))
    {
        return std::optional<double>(static_cast<double>(*value));
    }
    return std::nullopt;
}
