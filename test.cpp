#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

#include <cctype>

#include "String.h"

int main(int, char **)
{
    String hello = "Hello";

#if 1
    try
    {
        std::cerr << hello.at(999) << std::endl;
    }
    catch (std::out_of_range &e)
    {
        std::cerr << e.what() << std::endl;
    }
#endif

    hello = hello.to_uppercase();

    auto substr = hello.substr(3, 10);

    std::cout << substr << " : " << substr.size() << std::endl;

    std::cin.get();

    return 0;
}
