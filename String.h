#pragma once
#include <iostream>

#include <cctype>
#include <cstring>
#include <cstdio>

class String  
{
	private:
		std::size_t _size;
		std::size_t allocated;

		char *_addr;
	public:

		const char* address();
		std::size_t size();

		String operator+(const char* str);

		String(String& src);

		String();
		String(const char *str);
		~String();

};