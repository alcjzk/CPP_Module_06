#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "util.hpp"

Base *generate()
{
    const int   CLASS_COUNT = 3;
    static int  seed = std::time(nullptr);
    int         index;

    std::srand(seed++);
    index = std::rand() % CLASS_COUNT;

    switch (index)
    {
        case 0: return new A;
        case 1: return new B;
        case 2:
        default: return new C;
    }
}

void identify(Base *p)
{
    if (dynamic_cast<A*>(p))
    {
        std::cout << "A\n";
        return ;
    }
    if (dynamic_cast<B*>(p))
    {
        std::cout << "B\n";
        return;
    }
    if (dynamic_cast<C*>(p))
    {
        std::cout << "C\n";
        return;
    }
}

void identify(Base &p)
{
    try
    {
        (void)dynamic_cast<A&>(p);
        std::cout << "A\n";
        return;
    }
    catch (...) { }
    try
    {
        (void)dynamic_cast<B&>(p);
        std::cout << "B\n";
        return;
    }
    catch (...) { }
    try
    {
        (void)dynamic_cast<C&>(p);
        std::cout << "C\n";
        return;
    }
    catch (...) { }
}
