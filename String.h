#pragma once
#include <iostream>

#include <cctype>
#include <cstring>
#include <cstdio>

class String
{
public:
	const char *address() const;
	std::size_t size() const;

	String operator+(const char *str) const;
	String operator*(std::size_t amount) const;

	const String &operator+=(const char *str);
	const String &operator=(const char *str);
	const String &operator=(const String &str);

	String(const String &src);

	String();
	String(const char *str);
	~String();

	friend std::ostream &operator<<(std::ostream &os, const String &str);

private:
	std::size_t _size;
	char *_addr;
	String _repeat(std::size_t) const;
};