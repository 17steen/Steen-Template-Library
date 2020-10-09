#pragma once
#include <iostream>

#include <cctype>
#include <cstring>
#include <cstdio>

class String
{
public:
	const char *address();
	std::size_t size();

	String operator+(const char *str);

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
};