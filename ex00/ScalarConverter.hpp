#pragma once

#include <optional>
#include <string>
#include <type_traits>

class ScalarConverter
{
    public:
        ~ScalarConverter() = delete;
        ScalarConverter() = delete;
        ScalarConverter(const ScalarConverter&) = delete;
        ScalarConverter(ScalarConverter&&) = delete;

        ScalarConverter& operator=(const ScalarConverter&) = delete;
        ScalarConverter& operator=(ScalarConverter&&) = delete;

        static void convert(const std::string& value);

    private:
        template <typename Floating,
                  std::enable_if_t<std::is_floating_point_v<Floating>, bool> = true>
        static std::string to_string(Floating value);

        template <typename T>
        static std::string to_literal(std::optional<T> value);

        static std::string to_literal(char value);
        static std::string to_literal(int value);
        static std::string to_literal(float value);
        static std::string to_literal(double value);
};
