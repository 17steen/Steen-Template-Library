#include "String.h"

String::String() : _addr(nullptr), _size(0)
{
}

String::String(String& src) : _size(src._size) {
    _addr = (char*) std::calloc(_size + 1);

    std::strcpy(_addr, src._addr); 
}

String::String(const char *str)
{
    _size = std::strlen(str);
    
    _addr = new char[_size + 1];

    std::strcpy(_addr, str);

}


String String::operator+(const char* str){
    String copy(*this);
    copy._size += std::strlen(str) + 2;
}


String::~String()
{
}

const char *String::address(){
    return (const char*) _addr;
}

std::size_t String::size() {
    return _size;
}