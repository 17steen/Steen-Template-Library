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

#include <iostream>
#include <memory>

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
	String operator+(const String &str) const;

	const String &operator+=(const char *str);
	const String &operator+=(const String &str);
	const String &operator=(const char *str);
	const String &operator=(const String &str);

	bool operator==(const String &str) const;
	bool operator<(const String &str) const;
	bool operator>(const String &str) const;

	bool operator!=(const String &str) const;
	bool operator>=(const String &str) const;
	bool operator<=(const String &str) const;

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
	String(std::istream &);
	~String();

	Iterator begin();
	Iterator end();

	friend std::ostream &operator<<(std::ostream &os, const String &);
	friend std::istream &operator>>(std::istream &is, String &);
	friend String operator+(const char *, const String &);

private:
	std::size_t _size;
	char *_addr;
	String &set_zero();
	String _repeat(std::size_t) const;
	int _comp(const String &) const;

	static char *_alloc(size_t amount);
	static char *_re_alloc(String& str,size_t amount);
};
