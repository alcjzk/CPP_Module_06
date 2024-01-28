#pragma once

#include <cstdint>
#include "Data.hpp"

class Serializer
{
    public:
        ~Serializer() = delete;
        Serializer() = delete;
        Serializer(const Serializer&) = delete;
        Serializer(Serializer&&) = delete;

        Serializer& operator=(const Serializer&) = delete;
        Serializer& operator=(Serializer&&) = delete;

        static uintptr_t    serialize(Data* ptr);
        static Data*        deserialize(uintptr_t raw);
};
