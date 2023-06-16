#pragma once
#include <iostream>
class MyString
{
private:
	char* data = nullptr;
	size_t length = 0;

public:
	MyString();
	MyString(const char* data);

	MyString(const MyString& other);
	MyString& operator=(const MyString& other);

	MyString(MyString&& other) noexcept;
	MyString& operator=(MyString&& other) noexcept;

	~MyString();

private:
	void CopyFrom(const MyString& other);
	void MoveFrom(MyString&& other);
	void Free();

	explicit MyString(size_t capacity);

public:
	size_t GetLength() const;
	bool IsEmpty() const;

	MyString SubStr(size_t begin, size_t howMany) const;

	MyString operator+=(const MyString& other);

	const char* c_str() const;
	int stoi() const;
	double stod() const;
	MyString ExtractQuote() const;
	MyString ExtractFormula() const;

	char& operator[](size_t index);
	char operator[](size_t index) const;

	bool IsInt() const;
	bool IsDouble() const;
	bool IsQuote() const;
	bool IsFormula() const;
	bool IsEmptyString() const;

	MyString IntToString(int number) const;
	MyString DoubleToString(double number) const;

	void Remove(size_t idx);

	friend std::istream& operator>>(std::istream& is, MyString& str);
};

std::ostream& operator<<(std::ostream& os, const MyString& str);

bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
