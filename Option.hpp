#pragma once

#ifdef _DEBUG_LOG
#define LOG(x) std::cerr << x << std::endl;
#define D(x) (x)
#else
#define LOG(x) \
	do         \
	{          \
	} while (0)
#define D(x) \
	do       \
	{        \
	} while (0)
#endif

#include <type_traits>
#include <utility>
#include <initializer_list>

template <typename T>
class Option
{
public:
    Option() : has_value_(false) {
        LOG("OPTION: constructs from |default constructor|");
    }

    Option(const T &val) : val_(val), has_value_(true) {}

    Option(T &&val) : val_(std::move(val)), has_value_(true) {
        LOG("OPTION: constructs from |rvalue (T)|");
    }

    Option(const Option &opt) : val_(opt.val_), has_value_(bool(opt)) {
        LOG("OPTION: constructs from |copy|");
    }

    Option(Option &&other) : val_(std::move(other.val_)), has_value_(bool(other))
    {
        LOG("OPTION: constructs from |rvalue|");
    }

    const Option &operator=(const Option &other)
    {
        LOG("OPTION: constructs from |assigns from const reference|");
        has_value_ = other.has_value_;
        if (other)
            val_ = other.val_;
        return *this;
    }

    const Option &operator=(Option &&other)
    {
        LOG("OPTION: constructs from |assigns from rvalue|");
        has_value_ = other.has_value_;
        if (other)
            val_ = std::move(other.val_);
        return *this;
    }

    ~Option() {}

    T &value() &
    {
        if (!has_value_)
            throw;
        return val_;
    }

    T &&value() &&
    {
        std::cerr << "move" << std::endl;
        if (!has_value_)
            throw;
        return std::move(val_);
    }

    const T &value() const &
    {
        if (!has_value_)
            throw;
        return val_;
    }

    const T &&value() const &&
    {
        std::cerr << "move" << std::endl;
        if (!has_value_)
            throw;
        return std::move(val_);
    }

    T value_or(T &&other) &&
    {
        if (!has_value_)
            return other;
        return std::move(val_);
    }

    T value_or(T &&other) const &
    {
        if (!has_value_)
            return other;
        return **this;
    }

    template <class... Args>
    Option &emplace(Args &&... args)
    {
        val_ = T(std::forward<Args>(args)...);
        return *this;
    }

    operator bool() const
    {
        return has_value_;
    }

    T &operator*()
    {
        return val_;
    }

    bool has_value() const
    {
        return bool(*this);
    }

private:
    T val_;
    bool has_value_;
};
