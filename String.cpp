#include "String.h"

String::String() : String("")
{
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

    if(!_addr){
        std::cerr << "out of memory !" << std::endl;
        exit(EXIT_FAILURE);
    }

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
    LOG("after destruction");
    _size = str._size;
    LOG(_size);
    _addr = (char *)std::calloc(_size + 10, sizeof(char));
    
    LOG("after calloc");
    if (!_addr)
    {
        exit(1);
    }
    std::strcpy(_addr, str._addr);

    return *this;
}

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

const String &String::operator+=(const String &str)
{
    *this = *this + str._addr;
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


String operator+(const char *left, const String &right)
{
    std::cerr << left << std::endl;
    String tmp(left);
    LOG("test str left op :\n" << tmp << " | " << tmp.size());
    LOG("before + bs");
    String xd = tmp + right;
    LOG(xd << " | " << xd.size());
    return xd;
}

String String::operator+(const String &right) const
{
    return *this + right._addr;
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

bool String::operator==(const String &str) const
{
    return _comp(str) == 0;
};

bool String::operator!=(const String &str) const
{
    return _comp(str) != 0;
};

bool String::operator>(const String &str) const
{
    return _comp(str) > 0;
};

bool String::operator<(const String &str) const
{
    return _comp(str) < 0;
};

bool String::operator>=(const String &str) const
{
    int res = _comp(str);
    return res == 0 || res > 0;
};

bool String::operator<=(const String &str) const
{
    int res = _comp(str);
    return res == 0 || res < 0;
};

int String::_comp(const String &str) const
{
    return std::strcmp(_addr, str._addr);
}