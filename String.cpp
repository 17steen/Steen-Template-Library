#include "String.h"

String::String()
{
    *this = String("");
}

String::String(const String &src) : _size(src._size)
{
    LOG("constructs (from copy)");
    _addr = (char *)std::calloc(_size + 1, sizeof(char));

    std::strcpy(_addr, src._addr);
}

String::String(const char *str)
{
    LOG("constructs (from char*)");
    _size = std::strlen(str);

    _addr = (char *)std::calloc(_size + 1, sizeof(char));

    std::strcpy(_addr, str);
}

const String &String::operator=(const char *str)
{
    LOG("assign (from char*)");
    *this = String(str);
    return *this;
}

const String &String::operator=(const String &str)
{
    LOG("assign (from string&)");
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
/*
String String::repeat(std::size_t amount) const
{
    return _repeat(amount);
}

String String::operator*(std::size_t amount) const
{
    return _repeat(amount);
};
*/

String String::_repeat(std::size_t amount) const
{
    if (amount == 0)
    {
        return String("");
    }
    else if (amount == 1)
    {
        return String(*this);
    }
    else
    {
        String copy(*this);
        copy._size *= amount;
        LOG("new size : " << copy._size);
        char *tmp = copy._addr;
        tmp = (char *)std::realloc((void *)copy._addr, (copy._size + 1) * sizeof(char));
        if (!tmp)
        {
            //handle not enough memory
            exit(1);
        }
        while (amount > 1)
        {
            LOG("Loop");
            copy._addr = tmp;
            std::strcat(copy._addr, this->_addr);
            --amount;
        }
        copy.set_zero();
        return copy;
    }
};

String String::operator+(const char *str) const
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
        copy.set_zero();
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
    LOG("destructs");
    std::free((void *)_addr);
    _addr = nullptr;
}

const char *String::address() const
{
    return (const char *)_addr;
}

std::size_t String::size() const
{
    return _size;
}

std::ostream &operator<<(std::ostream &os, const String &str)
{
    return os << str._addr;
}

String &String::set_zero()
{
    _addr[_size] = '\0';
    return *this;
}


StringIterator String::begin()
{
    return StringIterator(_addr);
}

StringIterator String::end()
{
    return StringIterator(_addr + _size);
}

bool String::operator==(const String& str){
    return _comp(str) == 0;
};

bool String::operator!=(const String& str){
    return _comp(str) != 0;
};


bool String::operator>(const String& str){
    return _comp(str) > 0;
};

bool String::operator<(const String& str){
    return _comp(str) < 0;
};


bool String::operator>=(const String& str){
    int res = _comp(str);
    return  res == 0 || res > 0;
};

bool String::operator<=(const String& str){
    int res = _comp(str);
    return  res == 0 || res < 0;
};


int String::_comp(const String& str) const
{
    return std::strcmp(_addr, str._addr);
}