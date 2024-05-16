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

        /// Converts the value into type `To`, returns nullopt if conversion is not valid.
        template <typename To>
        std::optional<To> try_into() const
        {
            return std::visit([](auto value) {
                return try_from<To>(value);
            }, _value);
        }

    private:
        std::variant<std::monostate, char, int, float, double> _value;

        /// Conversion overload for invariant, always returns nullopt.
        template <typename To>
        static std::optional<To> try_from(std::monostate);

        /// Converts from type `To` into type `From`, returns nullopt if conversion is not valid.
        template <typename To, typename From>
        static std::optional<To> try_from(From value);
};

template <typename To>
std::optional<To> Value::try_from(std::monostate)
{
    return std::nullopt;
}

template <typename To, typename From>
std::optional<To> Value::try_from(From value)
{
    if constexpr (std::is_integral_v<To> && std::is_floating_point_v<From>)
    {
        long double integer_part;
        if (std::isnan(value) ||
            std::isinf(value) ||
            std::modf(value, &integer_part) != 0.0)
        {
            return std::nullopt;
        }
    }
    if (std::isfinite(value) &&
       (value < std::numeric_limits<To>::lowest() ||
        value > std::numeric_limits<To>::max()))
    {
        return std::nullopt;
    }
    return std::optional<To>(static_cast<To>(value));
}
