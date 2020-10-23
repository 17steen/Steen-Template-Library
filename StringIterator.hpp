#pragma once

#include <cstddef>
#include <iterator>

template <bool is_const>
class StringIterator
{
public:
    using iterator = StringIterator<is_const>;
    using difference_type = std::ptrdiff_t;
    using value_type = typename std::conditional<is_const, const char, char>::type;
    using pointer = value_type *;
    using reference = value_type &;
    using iterator_category = std::forward_iterator_tag;

private:
    char *ptr_;

public:
    StringIterator(char *ptr) : ptr_(ptr){};
    StringIterator(const StringIterator &iterator)
    {
        ptr_ = iterator.ptr_;
    };
    ~StringIterator()
    {
        ptr_ = nullptr;
    };

    iterator &operator++()
    {
        ++ptr_;
        return *this;
    };
    iterator operator++(int)
    {
        iterator copy(*this);
        ++(*this);
        return copy;
    };
    iterator &operator--()
    {
        --ptr_;
        return *this;
    };
    iterator operator--(int)
    {
        iterator copy(*this);
        --(*this);
        return copy;
    };

    iterator operator+(difference_type i) const
    {
        return iterator(ptr_ + i);
    };

    iterator operator-(difference_type i) const
    {
        return iterator(ptr_ - i);
    };

    difference_type operator+(iterator it) const
    {
        return reinterpret_cast<difference_type>(ptr_) + reinterpret_cast<difference_type>(it.ptr_);
    };
    difference_type operator-(iterator it) const
    {
        return reinterpret_cast<difference_type>(ptr_) - reinterpret_cast<difference_type>(it.ptr_);
    };

    reference operator[](int index)
    {
        return *(ptr_ + index);
    };

    reference operator*()
    {
        return *ptr_;
    };

    bool operator==(const iterator &other) const
    {
        return ptr_ == other.ptr_;
    };
    bool operator!=(const iterator &other) const
    {
        return ptr_ != other.ptr_;
    };
    bool operator<=(const iterator &other) const
    {
        return ptr_ <= other.ptr_;
    };
    bool operator>=(const iterator &other) const
    {
        return ptr_ >= other.ptr_;
    };
    bool operator<(const iterator &other) const
    {
        return ptr_ < other.ptr_;
    };
    bool operator>(const iterator &other) const
    {
        return ptr_ > other.ptr_;
    };
};