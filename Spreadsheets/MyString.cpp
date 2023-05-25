#include "MyString.h"
#include <cstring>
#include <cmath>
#include <iomanip>
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
	//is >> buff;
	is.getline(buff, MAX_BUFFER_SIZE);

	delete[] str.data;
	str.length = strlen(buff);
	str.data = new char[str.length + 1];
	strcpy_s(str.data, str.length + 1, buff);
	return is;
}

bool IsDigit(char c) {
	return c >= '0' && c <= '9';
}

bool MyString::IsInt() const {
	bool isNegative = false;

	if (this->data[0] == '-' || this->data[0] == '+')
		isNegative = true;

	if (!IsDigit(this->data[0]) && !isNegative)
		return false;

	for (size_t i = isNegative; i < this->length; i++)
	{
		if (!IsDigit(this->data[i]))
			return false;
	}

	return true;
}
bool MyString::IsDouble() const {
	bool hasSign = false;
	bool hasDecimalPoint = false;

	if (this->data[0] == '-' || this->data[0] == '+')
		hasSign = true;

	for (size_t i = hasSign; i < this->length; i++)
	{
		if (IsDigit(this->data[i]))
			continue;
		else if (this->data[i] == '.') {
			if (hasDecimalPoint)
				return false;
			hasDecimalPoint = true;
		}
		else
			return false;
	}
	return true;
}

int MyString::stoi() const {
	int result = 0;
	bool isNegative = false;
	int makeNegative = 1;

	if (this->data[0] == '-') {
		isNegative = true;
		makeNegative = -1;
	}

	for (size_t i = isNegative; i < this->length; i++)
	{
		int digit = this->data[i] - '0';
		result = result * 10 + digit;
	}
	return result * makeNegative;
}

size_t NumberSize(int number) {

	int numberSize = 0;

	if (number == 0) {
		numberSize = 1;
	}
	while (number > 0) {
		number /= 10;
		numberSize++;
	}
	return numberSize;
}

double MyString::stod() const {
	double result = 0;
	bool isNegative = false;
	int makeNegative = 1;

	if (this->data[0] == '-') {
		isNegative = true;
		makeNegative = -1;
	}

	int mantissaInt = 0;
	double mantissaDouble = 0;

	bool hasDot = false;

	int index = 0;
	int indexOfDot = 0;
	while (this->data[index] != '\0') {
		if (this->data[index] == '.') {
			indexOfDot = index;
			hasDot = true;
		}
		index++;
	}

	if (!hasDot) {
		indexOfDot = this->length;
	}

	index = 0 + isNegative;
	int counter = indexOfDot - 1 - isNegative;
	while (index != indexOfDot) {
		result += (this->data[index] - '0') * pow(10, counter);
		counter--;
		index++;
	}

	if (!hasDot) {
		return result;
	}

	index = indexOfDot + 1;
	counter = this->length - indexOfDot - 2;
	while (this->data[index] != '\0') {
		mantissaInt += (this->data[index] - '0') * pow(10, counter);
		counter--;
		index++;
	}

	int mantissaCopy = mantissaInt;
	size_t mantissaSize = NumberSize(mantissaCopy);
	mantissaDouble = mantissaInt;
	mantissaDouble /= pow(10, mantissaSize);

	result += mantissaDouble;
	return result * makeNegative;
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