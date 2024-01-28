#include <cstdlib>
#include <cassert>
#include <iostream>
#include "Data.hpp"
#include "Serializer.hpp"

int main()
{
    Data* data = new Data(42);

    assert(data->value() == 42);

    Data* data_copy = Serializer::deserialize(Serializer::serialize(data));
    assert(data == data_copy);

    assert(data_copy->value() == 42);

    std::cout << "Tests ok\n";

    return EXIT_SUCCESS;
}
