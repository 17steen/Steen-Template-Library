#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

#include <cctype>

#include "String.h"

  

int main(int, char**) {
    String hello = "Hello";

#if 0
    try{
        LOG(hello << " xd");
    }
    catch (const char* what){
        std::cerr << what << std::endl;
    }



    {
        String test(hello);
        std::cout << test * 5 << std::endl; //correct result 
    
        std::cout << ((test == "Hello ") ? "it's true" : "it's false") << std::endl; 
    }
#endif

    hello = hello.to_uppercase();

    auto substr =  hello.substr(3, 10);

    std::cout << substr << " : " << substr.size() << std::endl;

    std::cin.get();

    return 0;
}
