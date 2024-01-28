#include <cstdlib>
#include <iostream>
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "util.hpp"

int main()
{
    std::cout << "Random classes ---\n";
    for (int i = 0; i < 10; i++)
    {
        Base* object = generate();
        identify(object);
        delete object;
    }

    std::cout << "\nRefs ---\n";
    A a;
    B b;
    C c;

    identify(a);
    identify(&a);
    identify(b);
    identify(&b);
    identify(c);
    identify(&c);

    return EXIT_SUCCESS;
}
