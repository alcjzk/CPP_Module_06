#pragma once

#include <optional>
#include <variant>
#include <string>

class Value
{
    public:
        Value(const std::string& value);

        std::optional<char> as_char() const noexcept;
        std::optional<int> as_int() const noexcept;
        std::optional<float> as_float() const noexcept;
        std::optional<double> as_double() const noexcept;

    private:
        std::variant<std::monostate, char, int, float, double> _value;
};
