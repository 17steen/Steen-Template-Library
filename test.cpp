#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

#include "String.h"

int main(int, char**) {
    String hello("Hello ");

#if 0
    {
        String test(hello);
        std::cout << test * 5 << std::endl; //correct result 
        std::cout << test.repeat(5) << std::endl; //correct result 
    }
#endif

    for(char &c : hello)
        std::cout << c;
    std::cout << std::endl;


    std::cin.get();

    return 0;
}
