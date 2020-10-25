#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

#include <cctype>

#include "String.h"
#include "Option.hpp"

int main(int, char **)
{
    Option<String> opt;
    {
        std::cout << (opt = Option<String>(String("XDDDD"))).value() << std::endl;
    }

#if 0
    try
    {
        std::cerr << hello.at(999) << std::endl;
    }
    catch (std::out_of_range &e)
    {
        std::cerr << e.what() << std::endl;
    }

    hello = hello.to_uppercase();

    auto substr = hello.substr(3, 10);

    std::cout << substr << " : " << substr.size() << std::endl;

    for(auto it = hello.begin(); it != hello.end(); ++it){
        *it = 'X';
        std::cout << *it << std::endl;
    }
#endif

    std::cin.get();

    return 0;
}
