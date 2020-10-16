#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

#include "String.h"

  

int main(int, char**) {
    String hello;

    std::cin >> hello;


#if 1
    {
        String test(hello);
        std::cout << test * 5 << std::endl; //correct result 
        std::cout << test.repeat(5) << std::endl; //correct result 
        
        std::cout << ((test == "Hello ") ? "it's true" : "it's false") << std::endl; 
    }
#endif

    for(char &c : hello)
        std::cout << c;
    std::cout << std::endl;


    std::cin.get();

    return 0;
}
