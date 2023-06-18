#include "MyString.h"
#include <cstring>
#include <cmath>
#include <iomanip>
#include "HelperFunctions.h"

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
	this->data = new char[capacity] {};
}

void MyString::FindIdsOfStrWithoutWhitespace(size_t& startIdx, size_t& endIdx) const {
	while (startIdx < this->length && this->data[startIdx] == ' ') {
		startIdx++;
	}

	while (endIdx > startIdx && this->data[endIdx] == ' ') {
		endIdx--;
	}
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
	if (index > this->length)
		throw std::runtime_error("index out of range");

	return this->data[index];
}
char MyString::operator[](size_t index) const {
	if (index > this->length)
		throw std::runtime_error("index out of range");

	return this->data[index];
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString result = lhs;
	result += rhs;
	return result;
}

std::istream& operator>>(std::istream& is, MyString& str) {
	char buff[MAX_BUFFER_SIZE];
	is.getline(buff, MAX_BUFFER_SIZE);

	delete[] str.data;
	str.length = strlen(buff);
	str.data = new char[str.length + 1];
	strcpy_s(str.data, str.length + 1, buff);
	return is;
}

MyString MyString::SubStr(size_t begin, size_t howMany) const {
	if (begin + howMany > this->length)
		throw std::length_error("Substring out of range!");
	MyString res(howMany + 1);
	for (int i = 0; i < howMany; i++)
		res.data[i] = this->data[begin + i];

	res[howMany] = '\0';
	return res;
}


bool MyString::IsInt() const {
	bool isNegative = false;
	size_t startIdx = 0;
	size_t endIdx = this->length - 1;

	FindIdsOfStrWithoutWhitespace(startIdx, endIdx);

	if (startIdx <= endIdx && (this->data[startIdx] == '-' || this->data[startIdx] == '+')) {
		isNegative = true;
		startIdx++;
	}

	for (size_t i = startIdx; i <= endIdx; i++)
	{
		if (!IsDigit(this->data[i]))
			return false;
	}

	return true;
}
bool MyString::IsDouble() const {
	bool hasSign = false;
	bool hasDecimalPoint = false;
	bool isEmpty = true;

	size_t startIdx = 0;
	size_t endIdx = this->length - 1;

	while (startIdx < this->length && this->data[startIdx] == ' ') {
		startIdx++;
	}

	if (startIdx < this->length && (this->data[startIdx] == '-' || this->data[startIdx] == '+')) {
		hasSign = true;
		startIdx++;
	}

	while (endIdx > startIdx && this->data[endIdx] == ' ') {
		endIdx--;
	}

	for (size_t i = startIdx; i <= endIdx; i++) {
		{
			if (IsDigit(this->data[i])) {
				isEmpty = false;
				continue;
			}
			else if (this->data[i] == '.') {
				if (hasDecimalPoint)
					return false;
				hasDecimalPoint = true;
			}
			else
				return false;
		}
	}
	if (isEmpty)
		return false;
	return true;
}

int MyString::stoi() const {
	int result = 0;
	int makeNegative = 1;

	size_t startIdx = 0;
	size_t endIdx = this->length - 1;

	FindIdsOfStrWithoutWhitespace(startIdx, endIdx);

	if (startIdx <= endIdx && (this->data[startIdx] == '+' || this->data[startIdx] == '-')) {
		if (this->data[startIdx] == '-')
			makeNegative = -1;
		startIdx++;
	}

	for (size_t i = startIdx; i <= endIdx; i++)
	{
		int digit = this->data[i] - '0';
		result = result * 10 + digit;
	}
	return result * makeNegative;
}

MyString MyString::ExtractQuote() const {
	size_t startIdx = 0;
	size_t endIdx = this->length - 1;

	FindIdsOfStrWithoutWhitespace(startIdx, endIdx);

	MyString result(endIdx - startIdx - 2);
	result = SubStr(startIdx + 1, endIdx - startIdx - 1);

	for (size_t i = 0; i < result.length - 1; i++)
	{
		if (result[i] == '\\' && result[i + 1] != '\\') {
			result.Remove(i--);
		}
	}
	return result;
}

MyString MyString::ExtractFormula() const
{
	size_t startIdx = 0;
	size_t endIdx = this->length - 1;

	FindIdsOfStrWithoutWhitespace(startIdx, endIdx);
	MyString result(this->length);
	result = SubStr(startIdx + 1, endIdx - startIdx);
	return result;
}


double MyString::stod() const {
	double result = 0;
	bool isNegative = false;
	int makeNegative = 1;

	size_t startIdx = 0;
	size_t endIdx = this->length - 1;

	while (startIdx < this->length && this->data[startIdx] == ' ') {
		startIdx++;
	}

	if (startIdx < this->length && (this->data[startIdx] == '-' || this->data[startIdx] == '+')) {
		if (this->data[startIdx] == '-') {
			isNegative = true;
			makeNegative = -1;
		}

		startIdx++;
	}

	while (endIdx > startIdx && this->data[endIdx] == ' ') {
		endIdx--;
	}

	int mantissaInt = 0;
	double mantissaDouble = 0;

	bool hasDot = false;

	int indexOfDot = 0;
	int index = 0;
	for (size_t i = startIdx; i <= endIdx; i++) {
		if (this->data[i] == '.') {
			indexOfDot = i;
			hasDot = true;
			break;
		}
	}

	if (!hasDot) {
		return stoi();
	}

	index = startIdx;
	int counter = indexOfDot - 1 - startIdx;
	while (index != indexOfDot) {
		result += (this->data[index] - '0') * pow(10, counter);
		counter--;
		index++;
	}

	if (!hasDot) {
		return result;
	}

	index = indexOfDot + 1;
	counter = endIdx - indexOfDot;
	while (this->data[index] != endIdx && counter > 0) {
		mantissaInt += (this->data[index] - '0') * pow(10, counter);
		counter--;
		index++;
	}

	int mantissaCopy = mantissaInt;
	size_t mantissaSize = GetNumberSize(mantissaCopy);
	mantissaDouble = mantissaInt;
	mantissaDouble /= pow(10, mantissaSize);

	result += mantissaDouble;
	return result * makeNegative;
}

bool MyString::IsQuote() const {
	size_t startIdx = 0;
	size_t endIdx = this->length - 1;
	
	FindIdsOfStrWithoutWhitespace(startIdx, endIdx);
	return this->data[startIdx] == '"' && this->data[endIdx] == '"';
}

bool MyString::IsFormula() const {
	size_t startIdx = 0;
	size_t endIdx = this->length - 1;
	
	FindIdsOfStrWithoutWhitespace(startIdx, endIdx);
	if (this->data[startIdx] == '=')
		return true;

	return false;
}

bool MyString::IsEmptyString() const
{
	for (size_t i = 0; i < this->length; i++)
	{
		if (this->data[i] != ' ')
			return false;
	}
	return true;
}

void MyString::Remove(size_t idx)
{
	for (size_t j = idx; j < length - 1; j++)
	{
		this->data[j] = this->data[j + 1];
	}
	this->data[--length] = '\0';
}

bool MyString::IsEmpty() const {
	return this->length == 0;
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
