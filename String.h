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

#include "StringIterator.hpp"

class String
{
public:
	using Iterator = StringIterator<false>;
	using ConstIterator = StringIterator<true>;

public:
	const char *address() const;
	std::size_t size() const;

	String operator+(const char *str) const;
	String operator+(const String &str) const;

	String to_lowercase() const;
	String to_uppercase() const;

	//String constructor using printf formatting
	static String format(const char *format, ...);

	char &operator[](int);
	char &at(int);

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

	inline String repeat(std::size_t amount) const { return _repeat(amount); };
	inline String operator*(std::size_t amount) const { return _repeat(amount); };

	String();
	String(ConstIterator first, ConstIterator last);
	String(const char *str);
	String(const String &src);
	String(String &&src) noexcept;
	String(std::istream &);
	~String();

	String substr(int, int) const;

	Iterator begin();
	Iterator end();
	ConstIterator cbegin() const;
	ConstIterator cend() const;

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
	static char *_re_alloc(String &str, size_t amount);
};