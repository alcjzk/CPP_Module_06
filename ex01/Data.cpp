#include "Data.hpp"

Data::Data(int value) : _value(value)
{
}

int Data::value() const
{
    return _value;
}

void Data::value(int value)
{
    _value = value;
}
