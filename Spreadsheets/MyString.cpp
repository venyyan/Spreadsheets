#include "MyString.h"
#include <cstring>

const unsigned MAX_BUFFER_SIZE = 1024;

void MyString::CopyFrom(const MyString& other) {
	this->length = other.length;
	this->data = new char[length + 1];
	strcpy_s(this->data, this->length + 1, other.data);
}

void MyString::MoveFrom(MyString&& other) {
	this->length = other.length;
	this->data = other.data;
	other.data = nullptr;
}

void MyString::Free() {
	delete[] this->data;
	this->length = 0;
}

MyString::MyString() : MyString(1) {
	this->data[0] = '\0';
}

MyString::MyString(size_t capacity) {
	this->length = capacity - 1;
	this->data = new char[capacity];
}
MyString::MyString(const char* data) : MyString(strlen(data) + 1) {
	strcpy_s(this->data, this->length + 1, data);
}

MyString::MyString(const MyString& other) {
	CopyFrom(other);
}

MyString& MyString::operator=(const MyString& other) {
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}

MyString::MyString(MyString&& other) noexcept {
	MoveFrom(std::move(other));
}

MyString& MyString::operator=(MyString&& other) noexcept {
	if (this != &other)
	{
		Free();
		MoveFrom(std::move(other));
	}
	return *this;
}

MyString::~MyString() {
	Free();
}

size_t MyString::GetLength() const {
	return this->length;
}

MyString MyString::operator+=(const MyString& other) {
	char* newData = new char[(this->length += other.length) + 1];
	newData[0] = '\0';
	strcat_s(newData, this->length + 1, this->data);
	strcat_s(newData, this->length + 1, other.data);

	delete[] this->data;
	this->data = newData;

	return *this;
}

const char* MyString::c_str() const {
	return this->data;
}

char& MyString::operator[](size_t index) {
	if (index >= this->length)
		throw std::runtime_error("index out of range");

	return this->data[index];
}
char MyString::operator[](size_t index) const {
	if (index >= this->length)
		throw std::runtime_error("index out of range");

	return this->data[index];
}

std::istream& operator>>(std::istream& is, MyString& str) {
	char buff[MAX_BUFFER_SIZE];
	is >> buff;

	delete[] str.data;
	str.length = strlen(buff);
	str.data = new char[str.length + 1];
	strcpy_s(str.data, str.length + 1, buff);
	return is;
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
	return os << str.c_str();
}

bool operator<(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}
bool operator<=(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}
bool operator>=(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}
bool operator>(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}
bool operator==(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
bool operator!=(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}