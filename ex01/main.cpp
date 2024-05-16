#include <cstdlib>
#include <cassert>
#include <iostream>
#include <utility>
#include "Data.hpp"
#include "Serializer.hpp"

int main()
{
    // Orthodox
    {
        Data data; // Default construct
        Data copy(data); // Copy construct
        data = copy; // Copy assign
        Data moved_into(std::move(data)); // Move construct
        moved_into = std::move(copy); // Move assign
    }

    Data data(42);

    uintptr_t data_address = Serializer::serialize(&data);
    Data* data_ptr = Serializer::deserialize(data_address);

    assert(data_ptr == &data);
    assert(data_ptr->value() == 42);

    std::cout << "Tests ok\n";

    return EXIT_SUCCESS;
}
