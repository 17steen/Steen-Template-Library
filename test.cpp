#include <iostream>
#include "String.h"

int main(int, char**) {
    String hello("Hello, ");

#if 1
    {
        String test(hello);
        std::cout << (test += " test +=") << std::endl; //correct result
        std::cout << "after assignment : " << test << std::endl; //not concatenated
    }
#endif

    std::cin.get();

    return 0;
}
