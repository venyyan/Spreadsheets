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
	this->data = new char[capacity] {};
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

MyString MyString::SubStr(size_t begin, size_t howMany) const {
	if (begin + howMany > this->length)
		throw std::length_error("Substring out of range!");
	MyString res(howMany + 1);
	for (int i = 0; i < howMany; i++)
		res.data[i] = this->data[begin + i];

	res[howMany] = '\0';
	return res;
}

bool IsDigit(char c) {
	return c >= '0' && c <= '9';
}

bool MyString::IsInt() const {
	bool isNegative = false;
	size_t startIdx = 0;
	size_t endIdx = this->length - 1;

	while (startIdx < this->length && this->data[startIdx] == ' ') {
		startIdx++;
	}

	while (endIdx > startIdx && this->data[endIdx] == ' ') {
		endIdx--;
	}

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
		if (isEmpty)
			return false;
		return true;
	}
}

int MyString::stoi() const {
	int result = 0;
	bool isNegative = false;
	int makeNegative = 1;

	size_t startIdx = 0;
	size_t endIdx = this->length - 1;

	while (startIdx < this->length && this->data[startIdx] == ' ') {
		startIdx++;
	}

	while (endIdx > startIdx && this->data[endIdx] == ' ') {
		endIdx--;
	}

	if (startIdx <= endIdx && (this->data[startIdx] == '+' || this->data[startIdx] == '-')) {
		if (this->data[startIdx] == '-')
			isNegative = true;
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
	MyString result(this->length);
	result = SubStr(1, this->length - 2);
	return result;
}

MyString MyString::ExtractFormula() const
{
	MyString result(this->length);
	result = SubStr(1, this->length - 1);
	return result;
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

	size_t startIdx = 0;
	size_t endIdx = this->length - 1;

	while (startIdx < this->length && this->data[startIdx] == ' ') {
		startIdx++;
	}

	if (startIdx < this->length && (this->data[startIdx] == '-' || this->data[startIdx] == '+')) {
		if (this->data[startIdx] == '-')
			isNegative = true;
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
		indexOfDot = endIdx + 1;
	}

	index = startIdx;
	int counter = indexOfDot - 1 - isNegative - startIdx;
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
	size_t mantissaSize = NumberSize(mantissaCopy);
	mantissaDouble = mantissaInt;
	mantissaDouble /= pow(10, mantissaSize);

	result += mantissaDouble;
	return result * makeNegative;
}

bool MyString::IsQuote() const {
	/*bool isQuote = false;
	for (size_t i = 0; i < length; i++)
	{
		if (this->data[i] == )
	}*/
	return this->data[0] == '"' && this->data[length - 1] == '"';
}

bool MyString::IsFormula() const {
	size_t startIdx = 0;
	size_t endIdx = this->length - 1;
	while (startIdx < this->length && this->data[startIdx] == ' ') {
		startIdx++;
	}

	while (endIdx > startIdx && this->data[endIdx] == ' ') {
		endIdx--;
	}
	if (this->data[startIdx] == '=')
		return true;

	return false;
}

MyString MyString::IntToString(int number) const
{
	size_t ind = 0;
	size_t size = 0;
	int numCopy = number;
	while (numCopy > 0) {
		numCopy /= 10;
		size++;
	}
	char* result = new char[size + 2] {};
	if (number < 0) {
		result[ind++] = '-';
	}
	ind += size - 1;
	for (int i = size - 1; i >= 0; i--)
	{
		result[ind--] = number % 10 + '0';
		number /= 10;
	}
	MyString strResult(result);
	delete[] result;
	return strResult;
}

MyString MyString::DoubleToString(double number) const
{
	MyString wholePart = IntToString(number);
	
	double mantissa = number - (int)number;

	int precision = 5;
	char* result = new char[precision + 2] {};
	result[0] = '.';
	for (size_t i = 0; i < precision; i++)
	{
		mantissa *= 10;
		result[i + 1] =  (int)mantissa + '0';
		mantissa -= (int)mantissa;
	}
	
	wholePart += MyString(result);
	return wholePart;
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
