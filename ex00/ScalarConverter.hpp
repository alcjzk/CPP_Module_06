#pragma once

#include <optional>
#include <string>
#include "Value.hpp"

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
        template <typename T>
        static void display(std::optional<T> value);

        static void display(char value);
        static void display(int value);
        static void display(float value);
        static void display(double value);
};
