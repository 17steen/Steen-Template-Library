#include "StringIterator.h"

StringIterator::StringIterator(char *ptr) : ptr_(ptr)
{
}

StringIterator::StringIterator(const StringIterator &iterator)
{
    ptr_ = iterator.ptr_;
}
StringIterator::~StringIterator()
{
    ptr_ = nullptr;
}

StringIterator &StringIterator::operator++()
{
    ++ptr_;
    return *this;
}

StringIterator StringIterator::operator++(int)
{
    StringIterator copy(*this);
    ++(*this);
    return copy;
}

StringIterator &StringIterator::operator--()
{
    --ptr_;
    return *this;
}

StringIterator StringIterator::operator--(int)
{
    StringIterator copy(*this);
    --(*this);
    return copy;
}

char &StringIterator::operator[](int index)
{
    return *(ptr_ + index);
}

char &StringIterator::operator*()
{
    return *ptr_;
}

bool StringIterator::operator==(const StringIterator &other)
{
    return ptr_ == other.ptr_;
};
bool StringIterator::operator!=(const StringIterator &other)
{
    return ptr_ != other.ptr_;
};
bool StringIterator::operator<=(const StringIterator &other)
{
    return ptr_ <= other.ptr_;
};
bool StringIterator::operator>=(const StringIterator &other)
{
    return ptr_ >= other.ptr_;
};
bool StringIterator::operator<(const StringIterator &other)
{
    return ptr_ < other.ptr_;
};
bool StringIterator::operator>(const StringIterator &other)
{
    return ptr_ > other.ptr_;
};
