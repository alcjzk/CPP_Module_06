#include <regex>
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
