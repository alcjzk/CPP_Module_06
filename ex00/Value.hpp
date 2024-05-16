#pragma once

#include <optional>
#include <variant>
#include <string>
#include <limits>
#include <cmath>
#include <type_traits>

class Value
{
    public:
        ~Value() = default;
        Value(const std::string& value = "") noexcept;
        Value(const Value&) noexcept = default;
        Value(Value&&) noexcept = default;

        Value& operator=(const Value&) noexcept = default;
        Value& operator=(Value&&) noexcept = default;

        template <typename T>
        std::optional<T> as_optional() const
        {
            return std::visit([](auto value) {
                return optional_from<T>(value);
            }, _value);
        }

    private:
        std::variant<std::monostate, char, int, float, double> _value;

        template <typename T, typename U>
        static std::optional<T> optional_from(U value)
        {
            if constexpr (std::is_integral_v<T> && std::is_floating_point_v<U>)
            {
                U integer_part;
                if (std::isnan(value) ||
                    std::isinf(value) ||
                    std::modf(value, &integer_part) != 0.0)
                {
                    return std::nullopt;
                }
            }
            if (std::isfinite(value) &&
               (value < std::numeric_limits<T>::lowest() ||
                value > std::numeric_limits<T>::max()))
            {
                return std::nullopt;
            }
            return std::optional<T>(static_cast<T>(value));
        }

        template <typename T>
        static std::optional<T> optional_from(std::monostate)
        {
            return std::nullopt;
        }
};
