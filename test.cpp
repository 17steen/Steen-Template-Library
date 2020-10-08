#include <iostream>
#include "String.h"

int main(int, char**) {
    String hello("Hello, World!");

    {
        String test(hello);
        std::cout << test.address() << std::endl;

    }
    std::cout << hello.address() << std::endl;
}
