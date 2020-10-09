#pragma once

class StringIterator  
{
public:
	StringIterator(char *ptr);
	StringIterator(const StringIterator& iterator);
	~StringIterator();

	StringIterator &operator++();
	StringIterator operator++(int);
	StringIterator &operator--();
	StringIterator operator--(int);
	char &operator[](int index);
	char &operator*();
	bool operator==(const StringIterator& other);
	bool operator!=(const StringIterator& other);
	bool operator<=(const StringIterator& other);
	bool operator>=(const StringIterator& other);
	bool operator<(const StringIterator& other);
	bool operator>(const StringIterator& other);

private:
	char *ptr_;
};