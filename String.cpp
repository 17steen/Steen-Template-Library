#include "String.h"

String::String() : _addr(nullptr), _size(0)
{
}

String::String(const String &src) : _size(src._size)
{
    std::cerr << "constructs (from copy)" << std::endl;
    _addr = (char *)std::calloc(_size + 1, sizeof(char));

    std::strcpy(_addr, src._addr);
}

String::String(const char *str)
{

    std::cerr << "constructs (from char*)" << std::endl;
    _size = std::strlen(str);

    _addr = (char *)std::calloc(_size + 1, sizeof(char));

    std::strcpy(_addr, str);
}

const String &String::operator=(const char *str)
{
    std::cerr << "assign (from char*)" << std::endl;
    *this = String(str);
    return *this;
}

const String &String::operator=(const String &str)
{
    std::cerr << "assign (from string&)" << std::endl;
    this->~String();
    _size = str._size;
    _addr = (char *)std::calloc(_size + 1, sizeof(char));
    if (!_addr)
    {
        exit(1);
    }
    std::strcpy(_addr, str._addr);

    return *this;
}

String String::operator+(const char *str)
{
    String copy(*this);
    copy._size += std::strlen(str);
    char *tmp = copy._addr;

    tmp = (char *)std::realloc((void *)copy._addr, (_size + 1) * sizeof(char));
    if (!tmp)
    {
        //handle not enough memory
        exit(1);
    }
    else
    {
        copy._addr = tmp;
        std::strcat(copy._addr, str);
    }
    return copy;
}

const String &String::operator+=(const char *str)
{
    *this = *this + str;
    return *this;
}

String::~String()
{
    std::cerr << "destructs" << std::endl;
    std::free((void *)_addr);
    _addr = nullptr;
}

const char *String::address()
{
    return (const char *)_addr;
}

std::size_t String::size()
{
    return _size;
}

std::ostream &operator<<(std::ostream &os, const String &str)
{
    return os << str._addr;
}
