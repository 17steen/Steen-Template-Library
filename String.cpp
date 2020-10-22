#include "String.h"

#include <algorithm>
#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <memory>

using Iterator = StringIterator<false>;
using ConstIterator = StringIterator<true>;

char *String::_alloc(size_t amount) { return new char[amount]; }

// takes care of resizing and copying + assigning the new length
char *String::_re_alloc(String &str, size_t len_next)
{
    char *tmp = _alloc(len_next + 1);
    char *end = std::uninitialized_copy(str._addr, str._addr + str._size, tmp);
    delete[] str._addr;
    str._addr = tmp;
    str._size = len_next;

    return end;
}

String String::format(const char *format, ...)
{
    char buffer[256] = {0};
    va_list args;
    va_start(args, format);
    std::vsnprintf(buffer, 256, format, args);
    va_end(args);
    return String(buffer);
}

String::String() : String("") {}

String::String(const String &src) : _size(src._size)
{
    LOG("constructs (from copy)");
    _addr = _alloc(_size + 1);

    std::uninitialized_copy_n(src._addr, _size, _addr);
}

String::String(String &&src) noexcept : _size(src._size), _addr(src._addr)
{
    src._addr = nullptr;
    LOG("constructs (from moving)");
}

String::String(const char *str)
{
    LOG("constructs (from char*)");
    _size = std::strlen(str);

    _addr = _alloc(_size + 1);

    std::uninitialized_copy_n(str, _size, _addr);

    set_zero();
}

String::String(ConstIterator first, ConstIterator last)
{
    if (last < first) throw std::out_of_range("Cannot have a negative size.");
    
    const char* ptr = &(*first);
    size_t sub_max_len = strlen(ptr);
    size_t sub_len = last - first;
    _size = sub_max_len < sub_len ? sub_max_len : sub_len;
    _addr = _alloc(_size + 1);
    char *c = _addr;
    std::uninitialized_copy(first, last, begin());
    set_zero();
}

String::String(std::istream &is)
{
    char buffer[256] = {0};
    LOG("size of buffer" << sizeof(buffer));
    is.getline(buffer, sizeof(buffer) - 1, '\n');
    size_t len = std::strlen(buffer);
    _addr = _alloc(len + 1);

    std::uninitialized_copy_n(buffer, len, _addr);

    _size = len;
    set_zero();
}

String String::substr(int start, int take_n) const
{
    if (_size <= start) throw std::out_of_range("String::substr(int, int) : Starting position out of bounds.");
    return String(cbegin() + start, cbegin() + start + take_n);
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
    _addr = _alloc(_size + 1);

    std::uninitialized_copy_n(str._addr, _size, _addr);

    set_zero();

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
        char *end = _re_alloc(copy, copy._size * amount);
        LOG("new size : " << copy._size);
        while (amount > 1)
        {
            LOG("Loop");
            end =
                std::uninitialized_copy(this->_addr, this->_addr + _size, end);
            --amount;
        }
        copy.set_zero();
        return copy;
    }
};

String String::operator+(const char *str) const
{
    String copy(*this);
    size_t len = std::strlen(str);
    size_t full_len = len + _size;
    char *end = _re_alloc(copy, full_len);
    std::uninitialized_copy(str, str + len, end);

    return copy;
}

char &String::operator[](int index) { return _addr[index]; }

// boundary checking and reverse access (negative)
char &String::at(int index)
{
    bool is_positive = index >= 0 ? true : false;
    int max_reach = is_positive ? index : -index - 1;
    if (max_reach >= _size)
    {
        throw std::out_of_range("String::at() : Index out of range.");
    }
    if (is_positive)
    {
        return _addr[index];
    }
    else
    {
        return _addr[_size + index];
    }
}

const String &String::operator+=(const char *str)
{
    size_t len = strlen(str);
    char *end = _re_alloc(*this, _size + len);
    std::uninitialized_copy(str, str + len, end);
    set_zero();
    return *this;
}

const String &String::operator+=(const String &str)
{
    return *this += str._addr;
}

String String::to_lowercase() const
{
    String copy(*this);
    for (char &c : copy)
        c = std::tolower((int)c);
    return copy;
}

String String::to_uppercase() const
{
    String copy(*this);
    for (char &c : copy)
        c = std::toupper((int)c);
    return copy;
}

String::~String()
{
    LOG("destructs");
    if (_addr)
        delete[] _addr;
    _addr = nullptr;
}

const char *String::address() const { return _addr; }

std::size_t String::size() const { return _size; }

std::ostream &operator<<(std::ostream &os, const String &str)
{
    return os << str._addr;
}

// length of the buffer is 255;
std::istream &operator>>(std::istream &is, String &str)
{
    str = String(is);
    return is;
}

String operator+(const char *left, const String &right)
{
    return String(left) + right;
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

Iterator String::begin() { return Iterator(_addr); }

Iterator String::end() { return Iterator(_addr + _size); }

ConstIterator String::cbegin() const { return ConstIterator(_addr); }

ConstIterator String::cend() const { return ConstIterator(_addr + _size); }

bool String::operator==(const String &str) const { return _comp(str) == 0; };

bool String::operator!=(const String &str) const { return _comp(str) != 0; };

bool String::operator>(const String &str) const { return _comp(str) > 0; };

bool String::operator<(const String &str) const { return _comp(str) < 0; };

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