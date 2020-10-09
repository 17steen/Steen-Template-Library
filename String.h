#pragma once
#define LOG(x) std::cerr << x << std::endl;

#include <iostream>

#include <cctype>
#include <cstring>
#include <cstdio>

#include "StringIterator.h"

class String
{
public:
	using Iterator = StringIterator;

public:
	const char *address() const;
	std::size_t size() const;

	String operator+(const char *str) const;

	const String &operator+=(const char *str);
	const String &operator=(const char *str);
	const String &operator=(const String &str);

	inline String repeat(std::size_t amount) const
	{
		return _repeat(amount);
	};
	inline String operator*(std::size_t amount) const
	{
		return _repeat(amount);
	};

	String();
	String(const char *str);
	String(const String &src);
	~String();

	Iterator begin();
	Iterator end();

	friend std::ostream &operator<<(std::ostream &os, const String &str);

private:
	std::size_t _size;
	char *_addr;
	String &set_zero();
	String _repeat(std::size_t) const;
};
